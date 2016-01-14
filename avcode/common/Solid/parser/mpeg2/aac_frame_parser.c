
#include <string.h>
#include <stdlib.h>

#include "mpeg2_aac_parser.h"
#include "aac_frame_parser.h"

#include "../../util/log_debug.h"


/** ��Ƶ������������С */
#define AAC_FRAME_PARSER_MAX_BUF_SIZE                      (16*1024)


/** AAC֡������ */
typedef struct tag_aac_parser
{
	/** ��ʼ����־ */
	int32  b_init;

	/** �Ƿ���Ƶ���п�ʼ */
	int32  b_audio_start;
	/** �Ƿ��ѻ�ȡǰһ֡��Ƶ���� */
	int32  b_get_audio;
	/** ��ǰ��Ƶ֡ */
	ADTS_PACK audio1;
	/** ��һ��Ƶ֡ */
	ADTS_PACK audio2;

	/** ��Ƶ���ݻ����� */
	uint8 *p_audio_buf;
	/** ��Ƶ�������ܳ��� */
	int32 abuf_total_size;
	/** ��Ƶ��������ʹ�ó��� */
	int32 abuf_use_size;
	/** ��Ƶ������ʣ�೤�� */
	int32 abuf_left_size;
	/** ��Ƶ������֡���� */
	int32 abuf_frame_size;
	/** ��Ƶ�������ѽ������� */
	int32 abuf_parse_size;
	/** ��Ƶ������δ�������� */
	int32 abuf_unparse_size;

	/** ��Ƶ֡ͷ���� */
	int32 audio_header_size;

} AAC_PARSER, *PAAC_PARSER;


static int32 aac_update_audio(AAC_PARSER *p_parser);
static int32 aac_submit_audio(AAC_PARSER *p_parser, MEDIA_FRAME *p_frame);

/**  
 * @brief ����AAC��Ƶ��
 * @param [in] p_parser ���������
 * @param [out] p_frame ֡���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in] buf_len �������ݳ���
 * @param [out] p_parse_len ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2���������ݲ����Խ���
 */
static int32 aac_parse_audio(AAC_PARSER *p_parser, MEDIA_FRAME *p_frame, uint8 *p_buf, int32 buf_len, int32 *p_parse_len)
{
	int32  parse_len;
	uint8* p_parse_pos = NULL;
	uint8* p_head_pos;
	int32  head_len = 0;
	int32  b_find_next_frame;

	int32  ret;

	if( buf_len > p_parser->abuf_total_size )
	{
		*p_parse_len = 0;
		log_warn(_T("[aac_frame_parser::aac_parse_audio] audio input size = %d too large!\n"), buf_len);
		return -1;
	}

	if( buf_len > p_parser->abuf_left_size )
	{
		/** ֡������� */
		p_parser->abuf_use_size = 0;
		p_parser->abuf_left_size = p_parser->abuf_total_size;
		p_parser->abuf_frame_size = 0;
		p_parser->abuf_unparse_size = 0;
		log_warn(_T("[aac_frame_parser::aac_parse_audio] audio frame too large!\n"));
	}

	/** ������Ƶ���� */
	memcpy(p_parser->p_audio_buf + p_parser->abuf_use_size, p_buf, buf_len);
	p_parser->abuf_use_size += buf_len;
	p_parser->abuf_left_size -= buf_len;
	p_parser->abuf_unparse_size += buf_len;

	/** ������Ƶ֡ */
	b_find_next_frame = 0;
	p_parse_pos = p_parser->p_audio_buf + p_parser->abuf_frame_size;
	while( 1 )
	{
		ret = aac_adts_parse(&p_parser->audio2, p_parse_pos, p_parser->abuf_unparse_size, &parse_len);
		p_parse_pos += parse_len;
		p_parser->abuf_frame_size += parse_len;
		p_parser->abuf_unparse_size -= parse_len;

		if( ret )
		{
			break;
		}

		b_find_next_frame = 1;

		/** ������һ֡��֡ͷ���� */
		p_head_pos = p_parser->audio2.p_start;
		head_len = p_parse_pos - p_parser->audio2.p_start;

		p_parser->audio_header_size = head_len;

		/** ���㵱ǰ֡ʵ�ʳ��� */
		p_parser->abuf_frame_size -= head_len;
		p_parser->abuf_unparse_size += head_len;
		p_parser->abuf_parse_size = head_len;

		break;
	}

	*p_parse_len = buf_len;

	if( b_find_next_frame )
	{
		return 0;

	}else
	{
		return ret;
	}
}

/**  
 * @brief ���µ�ǰ��Ƶ֡״̬
 * @param [in] p_parser ���������
 * @return
 * 0���ɹ�
 */
static int32 aac_update_audio(AAC_PARSER *p_parser)
{
	if( p_parser->abuf_frame_size > 0 && p_parser->abuf_unparse_size > 0 )
	{
		/** ������һ֡���� */
		memcpy(p_parser->p_audio_buf, p_parser->p_audio_buf + p_parser->abuf_frame_size, p_parser->abuf_unparse_size);
	}

	p_parser->abuf_use_size = p_parser->abuf_unparse_size;
	p_parser->abuf_left_size = p_parser->abuf_total_size - p_parser->abuf_use_size;
	p_parser->abuf_frame_size = p_parser->abuf_parse_size;
	p_parser->abuf_unparse_size -= p_parser->abuf_parse_size;
	p_parser->audio_header_size = 0;

	memcpy(&p_parser->audio1, &p_parser->audio2, sizeof(ADTS_PACK));

	return 0;
}

/**  
 * @brief �ύ��Ƶ֡
 * @param [in] p_parser ���������
 * @param [in] p_frame ֡���
 * @return
 * 0���ɹ�
 */
static int32 aac_submit_audio(AAC_PARSER *p_parser, MEDIA_FRAME *p_frame)
{
	p_parser->b_get_audio = 1;

	p_frame->type = MP_DATA_TYPE_AUDIO;
	p_frame->p_frame = p_parser->p_audio_buf;
	p_frame->frame_size = p_parser->abuf_frame_size;

	p_frame->frame_flag = 0;
	p_frame->frame_flag |= MP_FRAME_VALID;
	p_frame->frame_ts = 0;

	p_frame->param.audio.algo = MP_AUDIO_AAC;
	p_frame->param.audio.chn = MP_AUDIO_DUAL;
	p_frame->param.audio.sample_rate = p_parser->audio2.fix_header.sample_freq;
	p_frame->param.audio.sample_bits = MP_AUDIO_SAMPLE_16BIT;
	p_frame->param.audio.b_padding = 0;
	p_frame->param.audio.elapse = 30;

	p_frame->p_user_data = NULL;
	p_frame->user_data_size = 0;

	return 0;
}


///////////////////////////////////�ⲿ�ӿ�////////////////////////////////////
AAC_FRAME_PARSER aac_frame_parser_create()
{
	AAC_PARSER *p_parser = NULL;
	p_parser = (AAC_PARSER*)malloc( sizeof(AAC_PARSER) );

	if( p_parser == NULL )
	{
		return NULL;
	}

	memset(p_parser, 0, sizeof(AAC_PARSER));

	return p_parser;
}

int32 aac_frame_parser_destroy(AAC_FRAME_PARSER frame_parser)
{
	AAC_PARSER *p_parser = (AAC_PARSER*)frame_parser;

	if( p_parser == NULL )
	{
		return -1;
	}

	if( p_parser->b_init )
	{
		aac_frame_parser_deinit(p_parser);
	}

	free(p_parser);

	return 0;
}

int32 aac_frame_parser_init(AAC_FRAME_PARSER frame_parser)
{
	AAC_PARSER *p_parser = (AAC_PARSER*)frame_parser;

	if( p_parser == NULL )
	{
		return -1;
	}

	if( p_parser->b_init )
	{
		return 0;
	}

	p_parser->b_audio_start = 0;
	p_parser->b_get_audio = 0;
	aac_adts_init(&p_parser->audio1);
	aac_adts_init(&p_parser->audio2);

	p_parser->p_audio_buf = (uint8*)malloc( AAC_FRAME_PARSER_MAX_BUF_SIZE );
	if( p_parser->p_audio_buf == NULL )
	{
		aac_frame_parser_deinit(p_parser);
		return -2;
	}
	p_parser->abuf_total_size = AAC_FRAME_PARSER_MAX_BUF_SIZE;
	p_parser->abuf_use_size = 0;
	p_parser->abuf_left_size = AAC_FRAME_PARSER_MAX_BUF_SIZE;
	p_parser->abuf_frame_size = 0;
	p_parser->abuf_parse_size = 0;
	p_parser->abuf_unparse_size = 0;
	p_parser->audio_header_size = 0;

	p_parser->b_init = 1;

	return 0;
}

int32 aac_frame_parser_deinit(AAC_FRAME_PARSER frame_parser)
{
	AAC_PARSER *p_parser = (AAC_PARSER*)frame_parser;

	if( p_parser == NULL )
	{
		return -1;
	}

	if( p_parser->p_audio_buf )
	{
		free(p_parser->p_audio_buf);
		p_parser->p_audio_buf = NULL;
	}

	p_parser->b_init = 0;

	return 0;
}

int32 aac_frame_parser_reset(AAC_FRAME_PARSER frame_parser)
{
	AAC_PARSER *p_parser = (AAC_PARSER*)frame_parser;

	if( p_parser == NULL )
	{
		return -1;
	}

	if( !p_parser->b_init )
	{
		return -3;
	}

	p_parser->b_audio_start = 0;
	p_parser->b_get_audio = 0;
	aac_adts_init(&p_parser->audio1);
	aac_adts_init(&p_parser->audio2);

	p_parser->abuf_total_size = AAC_FRAME_PARSER_MAX_BUF_SIZE;
	p_parser->abuf_use_size = 0;
	p_parser->abuf_left_size = AAC_FRAME_PARSER_MAX_BUF_SIZE;
	p_parser->abuf_frame_size = 0;
	p_parser->abuf_parse_size = 0;
	p_parser->abuf_unparse_size = 0;
	p_parser->audio_header_size = 0;

	return 0;
}

int32 aac_frame_parse(AAC_FRAME_PARSER frame_parser, MEDIA_FRAME *p_frame, uint8 *p_buf, int32 buf_len, int32 *p_parse_len)
{
	AAC_PARSER *p_parser = (AAC_PARSER*)frame_parser;

	int32  parse_len;
	int32  total_parse_len = 0;
	int32  unparse_len = buf_len;
	uint8* p_parse_buf = p_buf;
	int32  b_get_frame = 0;

	int32  ret;

	if( p_parser == NULL || p_frame == NULL || p_buf == NULL || p_parse_len == NULL )
	{
		return -1;
	}

	if( !p_parser->b_init )
	{
		return -1;
	}

	if( p_parser->b_get_audio )
	{
		aac_update_audio(p_parser);
		p_parser->b_get_audio = 0;
	}

	while( !b_get_frame )
	{
		ret = aac_parse_audio(p_parser, p_frame, p_parse_buf, unparse_len, &parse_len);
		p_parse_buf += parse_len;
		total_parse_len += parse_len;
		unparse_len -= parse_len;

		if( ret )
		{
			break;
		}

		if( p_parser->b_audio_start )
		{
			/** �ύ��ǰ��Ƶ֡ */
			b_get_frame = 1;
			aac_submit_audio(p_parser, p_frame);

		}else
		{
			aac_update_audio(p_parser);
		}

		p_parser->b_audio_start = 1;
	}

	*p_parse_len = total_parse_len;

	if( b_get_frame )
	{
		return 0;

	}else
	{
		return -2;
	}
}
