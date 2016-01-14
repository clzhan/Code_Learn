
#include <string.h>

#include "../public/gen_endian.h"
#include "rtp.h"

#define RTP_HEADER_MIN_SIZE                        (sizeof(RTP_HEADER))
#define RTP_EXT_HEADER_MIN_SIZE                    (sizeof(RTP_EXT_HEADER))

/**
 * @brief ����RTPͷ
 * @param [in] p_param �������
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_buf_len �������ܳ���/ʵ�����ɳ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTPͷ������Ч
 */
static int32 rtp_make_header(RTP_HEADER_PARAM *p_param, int8 *p_buf, int32 *p_buf_len)
{
	RTP_HEADER *p_header = (RTP_HEADER*)p_buf;
	int32 need_len;

	need_len = sizeof(RTP_HEADER) + p_param->csrc_num * RTP_CSRC_SIZE;
	if( *p_buf_len < need_len )
	{
		/** ���Ȳ��� */
		*p_buf_len = need_len;
		return -2;
	}

	if( p_param->version != RTP_VERSION )
	{
		return -3;
	}

	if( p_param->csrc_num > RTP_MAX_CSRC_NUM )
	{
		return -3;
	}

	/** �汾 */
	p_header->flag = 0;
	p_header->flag |= ((p_param->version & 0x3) << 6);

	/** ����־ */
	p_header->flag |= ((p_param->b_pad & 0x1) << 5 );

	/** ��չ��־ */
	p_header->flag |= ((p_param->b_ext & 0x1) << 4 );

	/** CSRC���� */
	p_header->flag |= (p_param->csrc_num & 0xF);

	/** �����־ */
	p_header->mark_pt = ((p_param->b_mark & 0x1) << 7 );

	/** �غ����� */
	p_header->mark_pt |= (p_param->payload_type & 0x7F);

	/** ���к� */
	p_header->seq = hton_u16(p_param->seq);

	/** ʱ��� */
	p_header->timestamp = hton_u32(p_param->timestamp);

	/** SSRC */
	p_header->ssrc = hton_u32(p_param->ssrc);

	if( p_param->csrc_num > 0 )
	{
		/** ����CSRC�б� */
		if( p_param->p_csrc_data == NULL )
		{
			return -1;
		}

		memcpy(p_buf + sizeof(RTP_HEADER), p_param->p_csrc_data, p_param->csrc_num * RTP_CSRC_SIZE);
	}

	*p_buf_len = need_len;
	
	return 0;
}

/**
 * @brief ����RTP��չͷ
 * @param [in] p_ext_param ��չ�������
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_buf_len �������ܳ���/ʵ�����ɳ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��������Ч
 */
static int32 rtp_make_ext_header(RTP_EXT_HEADER_PARAM *p_ext_param, int8 *p_buf, int32 *p_buf_len)
{
	RTP_EXT_HEADER *p_ext_header = (RTP_EXT_HEADER*)p_buf;
	int32 need_len;

	need_len = sizeof(RTP_EXT_HEADER) + p_ext_param->ext_data_len * RTP_CSRC_SIZE;
	if( *p_buf_len < need_len )
	{
		*p_buf_len = need_len;
		return -2;
	}

	/** Profile */
	p_ext_header->profile = hton_u16(p_ext_param->profile);

	/** ��չ���� */
	p_ext_header->ext_data_len = hton_u16(p_ext_param->ext_data_len);

	if( p_ext_param->ext_data_len > 0 )
	{
		if( p_ext_param->p_ext_data == NULL )
		{
			return -3;
		}

		memcpy(p_buf + sizeof(RTP_EXT_HEADER), p_ext_param->p_ext_data, p_ext_param->ext_data_len * RTP_CSRC_SIZE);
	}

	*p_buf_len = need_len;
	
	return 0;
}

/**
 * @brief ����RTPͷ
 * @param [out] p_param �������
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_len �����ܳ���/�ѽ�������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���������ݲ����Խ���
 * -3��������Ч
 * @remark
 * 1�����۽����ɹ����p_buf_len���᷵���ѽ�������
 */
static int32 rtp_parse_header(RTP_HEADER_PARAM *p_param, int8 *p_buf, int32 *p_buf_len)
{
	RTP_HEADER *p_header = (RTP_HEADER*)p_buf;
	int32 left_len;
	int32 need_len;

	left_len = *p_buf_len;
	*p_buf_len = 0;
	if( left_len < RTP_HEADER_MIN_SIZE )
	{
		return -2;
	}

	/** CSRC���� */
	p_param->csrc_num = (p_header->flag & 0xF);
	need_len = RTP_HEADER_MIN_SIZE + p_param->csrc_num * RTP_CSRC_SIZE;
	if( left_len < need_len )
	{
		return -2;
	}
	
	/** �汾 */
	p_param->version = ((p_header->flag & 0xC0) >> 6 );
	if( p_param->version != RTP_VERSION )
	{
		*p_buf_len = 1;
		return -3;
	}

	/** ����־ */
	p_param->b_pad = ((p_header->flag & 0x20) >> 5 );

	/** ��չ��־ */
	p_param->b_ext = ((p_header->flag & 0x10) >> 4 );
	
	/** �����־ */
	p_param->b_mark = ((p_header->mark_pt & 0x80) >> 7 );
	
	/** �غ����� */
	p_param->payload_type = (p_header->mark_pt & 0x7F);
	
	/** ���к� */
	p_param->seq = ntoh_u16(p_header->seq);

	/** ʱ��� */
	p_param->timestamp = ntoh_u32(p_header->timestamp);
	
	/** SSRC */
	p_param->ssrc = ntoh_u32(p_header->ssrc);
	
	if( p_param->csrc_num > 0 )
	{
		p_param->p_csrc_data = p_buf + sizeof(RTP_HEADER);

	}else
	{
		p_param->p_csrc_data = NULL;
	}

	*p_buf_len = need_len;

	return 0;
}

/**
 * @brief ����RTP��չͷ
 * @param [out] p_ext_param ��չͷ�������
 * @param [in] p_buf �������ݵ�ַ
 * @param [in/out] p_buf_len �����ܳ���/ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���������ݲ����Խ���
 * -3��RTPͷ��ʽ����
 */
static int32 rtp_parse_ext_header(RTP_EXT_HEADER_PARAM *p_ext_param, int8 *p_buf, int32 *p_buf_len)
{
	RTP_EXT_HEADER *p_ext_header = (RTP_EXT_HEADER*)p_buf;
	int32 left_len;
	int32 need_len;

	left_len = *p_buf_len;
	*p_buf_len = 0;
	if( left_len < RTP_EXT_HEADER_MIN_SIZE )
	{
		return -2;
	}

	/** ��չ���ݳ��� */
	p_ext_param->ext_data_len = ntoh_u16(p_ext_header->ext_data_len);
	need_len = RTP_EXT_HEADER_MIN_SIZE + p_ext_param->ext_data_len * RTP_CSRC_SIZE;
	if( left_len < need_len )
	{
		return -2;
	}

	/** Profile */
	p_ext_param->profile = ntoh_u16(p_ext_header->profile);

	if( p_ext_param->ext_data_len > 0 )
	{
		p_ext_param->p_ext_data = p_buf + sizeof(RTP_EXT_HEADER);

	}else
	{
		p_ext_param->p_ext_data = NULL;
	}

	*p_buf_len = need_len;
	
	return 0;
}

///////////////////////////////////�ⲿ�ӿ�////////////////////////////////////////
int32 rtp_mux(RTP_HEADER_PARAM *p_param, RTP_EXT_HEADER_PARAM *p_ext_param, int8 *p_buf, int32 *p_buf_len)
{
	int32 header_len;
	int32 left_len;
	int32 need_len;
	int32 pack_len;

	int32 ret;

	if( p_param == NULL || p_ext_param == NULL || p_buf == NULL || p_buf_len == NULL )
	{
		return -1;
	}

	need_len = RTP_HEADER_MIN_SIZE + p_param->csrc_num * RTP_CSRC_SIZE;
	if( p_param->b_ext )
	{
		need_len += (RTP_EXT_HEADER_MIN_SIZE + p_ext_param->ext_data_len * RTP_CSRC_SIZE);
	}

	left_len = *p_buf_len;
	if( left_len < need_len )
	{
		*p_buf_len = need_len;
		return -2;
	}

	header_len = 0;
	pack_len = left_len;
	ret = rtp_make_header(p_param, p_buf, &pack_len);
	if( ret )
	{
		return ret;
	}

	/** ���»��������� */
	header_len += pack_len;
	left_len -= pack_len;

	if( p_param->b_ext )
	{
		pack_len = left_len;
		ret = rtp_make_ext_header(p_ext_param, p_buf + header_len, &pack_len);
		if( ret )
		{
			return ret;
		}

		header_len += pack_len;
	}

	*p_buf_len = header_len;

	return 0;
}

int32 rtp_demux(RTP_HEADER_PARAM *p_param, RTP_EXT_HEADER_PARAM *p_ext_param, int8 *p_buf, int32 *p_buf_len)
{
	int32 header_len = 0;
	int32 left_len;
	int32 parse_len;

	int32 ret;

	if( p_param == NULL || p_ext_param == NULL || p_buf == NULL || p_buf_len == NULL )
	{
		return -1;
	}

	left_len = *p_buf_len;
	parse_len = *p_buf_len;
	ret = rtp_parse_header(p_param, p_buf, &parse_len);
	if( ret )
	{
		*p_buf_len = parse_len;
		return ret;
	}

	/** ���»��������� */
	header_len += parse_len;
	left_len -= parse_len;

	if( p_param->b_ext )
	{
		/** ������չͷ */
		parse_len = left_len;
		ret = rtp_parse_ext_header(p_ext_param, p_buf + header_len, &parse_len);
		if( ret )
		{
			*p_buf_len = header_len + parse_len;
			return ret;
		}

		header_len += parse_len;
	}

	*p_buf_len = header_len;

	return 0;
}
