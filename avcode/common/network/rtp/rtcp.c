
#include <string.h>

#include "../public/gen_endian.h"
#include "rtcp.h"

#define RTCP_HEADER_SIZE                           (sizeof(RTCP_HEADER))

/**
 * @brief ����RTCP SRͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�ʽ�������
 * @param [out] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP SRͷ��ʽ����
 */
static int32 rtcp_parse_sr(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	RTCP_SR *p_rtcp_sr = (RTCP_SR *)p_buf;
	RTCP_RB *p_rb_src = NULL;
	RTCP_RB *p_rb_dst = NULL;

	int32  left_len;
	int32  parse_len;

	int32  i;

	left_len = *p_len;
	if( left_len < RTCP_SR_SIZE )
	{
		*p_len = RTCP_SR_SIZE;
		return -2;
	}

	/** SSRC */
	p_pack->body.sr.ssrc = ntoh_u32(p_rtcp_sr->ssrc);

	/** NTPʱ�����32λ */
	p_pack->body.sr.ntp_ts_high = ntoh_u32(p_rtcp_sr->ntp_ts_high);

	/** NTPʱ�����32λ */
	p_pack->body.sr.ntp_ts_low = ntoh_u32(p_rtcp_sr->ntp_ts_low);

	/** RTPʱ��� */
	p_pack->body.sr.rtp_ts = ntoh_u32(p_rtcp_sr->rtp_ts);

	/** �ѷ������� */
	p_pack->body.sr.pack_send = ntoh_u32(p_rtcp_sr->pack_send);

	/** �ѷ����ֽ��� */
	p_pack->body.sr.bytes_send = ntoh_u32(p_rtcp_sr->bytes_send);

	if( p_pack->ssrc_cnt > 0 )
	{
		left_len -= RTCP_SR_SIZE;
		if( left_len < p_pack->ssrc_cnt * RTCP_RB_SIZE )
		{
			/** ���������Ȳ��� */
			*p_len = RTCP_SR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
			return -2;
		}

		p_rb_src = (RTCP_RB *)(p_buf+RTCP_SR_SIZE);
		p_rb_dst = p_pack->body.sr.report_block;

		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			p_rb_dst->ssrc = ntoh_u32(p_rb_src->ssrc);
			p_rb_dst->frac_lost = p_rb_src->frac_lost;

			/** ����cumulative_pack_lost */
			p_rb_dst->pack_lost[0] = p_rb_src->pack_lost[2];
			p_rb_dst->pack_lost[1] = p_rb_src->pack_lost[1];
			p_rb_dst->pack_lost[2] = p_rb_src->pack_lost[0];

			p_rb_dst->ext_sn = ntoh_u32(p_rb_src->ext_sn);
			p_rb_dst->jitter = ntoh_u32(p_rb_src->jitter);
			p_rb_dst->last_sr = ntoh_u32(p_rb_src->delay_sr);
			p_rb_dst->delay_sr = ntoh_u32(p_rb_src->delay_sr);

			p_rb_src++;
			p_rb_dst++;
		}

	}

	parse_len = RTCP_SR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
	*p_len = parse_len;

	return 0;
}

/**
 * @brief ����RTCP RRͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�ʽ�������
 * @param [out] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP RRͷ��ʽ����
 */
static int32 rtcp_parse_rr(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	RTCP_RR *p_rtcp_rr = (RTCP_RR *)p_buf;
	RTCP_RB *p_rb_src = NULL;
	RTCP_RB *p_rb_dst = NULL;

	int32  left_len;
	int32  parse_len;

	int32  i;

	//if( p_buf == NULL || p_pack == NULL || len < sizeof(RTCP_RR) )
	{
	//	return RTP_ERR_INVALID_PARAM;
	}

	left_len = *p_len;
	if( left_len < RTCP_RR_SIZE )
	{
		*p_len = RTCP_RR_SIZE;
		return -2;
	}

	/** SSRC */
	p_pack->body.rr.ssrc = ntoh_u32(p_rtcp_rr->ssrc);

	if( p_pack->ssrc_cnt > 0 )
	{
		left_len -= RTCP_RR_SIZE;
		if( left_len < p_pack->ssrc_cnt * RTCP_RB_SIZE )
		{
			/** ���������Ȳ��� */
			*p_len = RTCP_RR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
			return -2;
		}

		p_rb_src = (RTCP_RB *)(p_buf+RTCP_RR_SIZE);
		p_rb_dst = p_pack->body.rr.report_block;

		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			p_rb_dst->ssrc = ntoh_u32(p_rb_src->ssrc);
			p_rb_dst->frac_lost = p_rb_src->frac_lost;

			/** ����cumulative_pack_lost */
			p_rb_dst->pack_lost[0] = p_rb_src->pack_lost[2];
			p_rb_dst->pack_lost[1] = p_rb_src->pack_lost[1];
			p_rb_dst->pack_lost[2] = p_rb_src->pack_lost[0];

			p_rb_dst->ext_sn = ntoh_u32(p_rb_src->ext_sn);
			p_rb_dst->jitter = ntoh_u32(p_rb_src->jitter);
			p_rb_dst->last_sr = ntoh_u32(p_rb_src->delay_sr);
			p_rb_dst->delay_sr = ntoh_u32(p_rb_src->delay_sr);

			p_rb_src++;
			p_rb_dst++;
		}

	}

	parse_len = RTCP_RR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
	*p_len = parse_len;

	return 0;
}

/**
 * @brief ����RTCP SDESͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�ʽ�������
 * @param [out] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP SDESͷ��ʽ����
 */
static int32 rtcp_parse_sdes(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	int8 *p_temp = p_buf;
	RTCP_CHUNK *p_chunk = NULL;
	RTCP_CHUNK_PARAM *p_chunk_param = NULL;
	RTCP_ITEM *p_item = NULL;

	int32  left_len;
	int32  parse_len;
	int32  tail_len;
	int32  i, j;

	//if( p_buf == NULL || p_pack == NULL || len < sizeof(RTCP_CHUNK) )
	{
	//	return RTP_ERR_INVALID_PARAM;
	}

	left_len = *p_len;
	if( left_len < RTCP_CHUNK_SIZE )
	{
		*p_len = RTCP_CHUNK_SIZE;
		return -2;
	}

	if( p_pack->ssrc_cnt > 0 )
	{
		/**
		 * ע�⣬sdes item���ı�������'\0'��β�ģ��мǣ�
		 */
		p_chunk_param = p_pack->body.sdes.chunk;
		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			p_chunk = (RTCP_CHUNK *)p_temp;
			p_chunk_param->ssrc = ntoh_u32(p_chunk->ssrc);
			p_temp += sizeof(RTCP_CHUNK);

			parse_len = 0;
			j = 0;
			while( j < RTCP_MAX_ITEM )
			{
				p_item = (RTCP_ITEM *)p_temp;

				if( p_item->type == RTCP_SDES_END )
				{
					/** �������ĳ��� */
					parse_len++;
					p_temp++;

					tail_len = parse_len%RTCP_BASE_UNIT;
					if( tail_len != 0 )
					{
						parse_len += (RTCP_BASE_UNIT - tail_len);
						p_temp += (RTCP_BASE_UNIT - tail_len);
					}

					break;

				}else
				{
					p_chunk_param->item[j].type = p_item->type;
					p_chunk_param->item[j].len = p_item->len;
					p_chunk_param->item[j].p_text = p_temp + 2;

					parse_len += (2+p_chunk_param->item[j].len);
					p_temp += (2+p_chunk_param->item[j].len);

					j++;
				}
			}
			p_chunk_param->item_cnt = j;

			p_chunk_param++;
		}

	}

	parse_len = RTCP_CHUNK_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
	*p_len = parse_len;

	return 0;
}

/**
 * @brief ����RTCP BYEͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�ʽ�������
 * @param [out] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP BYEͷ��ʽ����
 */
static int32 rtcp_parse_bye(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	uint32 *p_uint32 = (uint32 *)p_buf;

	int32  left_len;
	int32  parse_len;

	int32  i;

	//if( p_buf == NULL || p_pack == NULL || len < sizeof(RTCP_RR) )
	{
		//	return RTP_ERR_INVALID_PARAM;
	}

	left_len = *p_len;
	if( left_len < RTCP_BYE_SIZE )
	{
		*p_len = RTCP_BYE_SIZE;
		return -2;
	}

	if( p_pack->ssrc_cnt > 0 )
	{
		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			p_pack->body.bye.ssrc[i] = ntoh_u32(*p_uint32);

			p_uint32++;
		}

	}

	parse_len = RTCP_BYE_SIZE + p_pack->ssrc_cnt * RTCP_BASE_UNIT;
	*p_len = parse_len;

	return 0;
}

/**
 * @brief ����RTCP SRͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�����ɳ���
 * @param [in] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP SRͷ������Ч
 */
static int32 rtcp_build_sr(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	RTCP_SR *p_rtcp_sr = (RTCP_SR *)p_buf;
	RTCP_RB *p_rb_src = NULL;
	RTCP_RB *p_rb_dst = NULL;

	int32  left_len;
	int32  build_len;
	int32  i;

	//if( p_buf == NULL || p_pack == NULL || len < sizeof(RTCP_SR) )
	{
	//	return RTP_ERR_INVALID_PARAM;
	}

	left_len = *p_len;
	if( left_len < RTCP_SR_SIZE )
	{
		*p_len = RTCP_SR_SIZE;
		return -2;
	}

	/** SSRC */
	p_rtcp_sr->ssrc = hton_u32(p_pack->body.sr.ssrc);

	/** NTPʱ�����32λ */
	p_rtcp_sr->ntp_ts_high = hton_u32(p_pack->body.sr.ntp_ts_high);

	/** NTPʱ�����32λ */
	p_rtcp_sr->ntp_ts_low = hton_u32(p_pack->body.sr.ntp_ts_low);

	/** RTPʱ��� */
	p_rtcp_sr->rtp_ts = hton_u32(p_pack->body.sr.rtp_ts);

	/** �ѷ������� */
	p_rtcp_sr->pack_send = hton_u32(p_pack->body.sr.pack_send);

	/** �ѷ����ֽ��� */
	p_rtcp_sr->bytes_send = hton_u32(p_pack->body.sr.bytes_send);

	if( p_pack->ssrc_cnt > 0 )
	{
		left_len -= RTCP_SR_SIZE;
		if( left_len < p_pack->ssrc_cnt * RTCP_RB_SIZE )
		{
			/** ���������Ȳ��� */
			*p_len = RTCP_SR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
			return -2;
		}

		p_rb_dst = (RTCP_RB *)(p_buf+RTCP_SR_SIZE);
		p_rb_src = p_pack->body.sr.report_block;

		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			p_rb_dst->ssrc = hton_u32(p_rb_src->ssrc);
			p_rb_dst->frac_lost = p_rb_src->frac_lost;

			/** ����cumulative_pack_lost */
			p_rb_dst->pack_lost[0] = p_rb_src->pack_lost[2];
			p_rb_dst->pack_lost[1] = p_rb_src->pack_lost[1];
			p_rb_dst->pack_lost[2] = p_rb_src->pack_lost[0];

			p_rb_dst->ext_sn = hton_u32(p_rb_src->ext_sn);
			p_rb_dst->jitter = hton_u32(p_rb_src->jitter);
			p_rb_dst->last_sr = hton_u32(p_rb_src->delay_sr);
			p_rb_dst->delay_sr = hton_u32(p_rb_src->delay_sr);

			p_rb_src++;
			p_rb_dst++;
		}

	}

	build_len = RTCP_SR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
	*p_len = build_len;
	//p_pack->len = ( sizeof(RTCP_HEAD) + sizeof(RTCP_SR) + p_pack->ssrc_cnt * sizeof(RTCP_RB) );

	return 0;
}

/**
 * @brief ����RTCP RRͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�����ɳ���
 * @param [in] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP RRͷ������Ч
 */
static int32 rtcp_build_rr(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	RTCP_RR *p_rtcp_rr = (RTCP_RR *)p_buf;
	RTCP_RB *p_rb_src = NULL;
	RTCP_RB *p_rb_dst = NULL;

	int32  left_len;
	int32  build_len;
	int32  i;

	//if( p_buf == NULL || p_pack == NULL || len < sizeof(RTCP_RR) )
	{
	//	return RTP_ERR_INVALID_PARAM;
	}

	left_len = *p_len;
	if( left_len < RTCP_RR_SIZE )
	{
		*p_len = RTCP_RR_SIZE;
		return -2;
	}

	/** SSRC */
	p_rtcp_rr->ssrc = hton_u32(p_pack->body.rr.ssrc);

	if( p_pack->ssrc_cnt > 0 )
	{
		left_len -= RTCP_RR_SIZE;
		if( left_len < p_pack->ssrc_cnt * RTCP_RB_SIZE )
		{
			/** ���������Ȳ��� */
			*p_len = RTCP_RR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
			return -2;
		}

		p_rb_dst = (RTCP_RB *)(p_buf+RTCP_RR_SIZE);
		p_rb_src = p_pack->body.rr.report_block;

		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			p_rb_dst->ssrc = hton_u32(p_rb_src->ssrc);
			p_rb_dst->frac_lost = p_rb_src->frac_lost;

			/** ����cumulative_pack_lost */
			p_rb_dst->pack_lost[0] = p_rb_src->pack_lost[2];
			p_rb_dst->pack_lost[1] = p_rb_src->pack_lost[1];
			p_rb_dst->pack_lost[2] = p_rb_src->pack_lost[0];

			p_rb_dst->ext_sn = hton_u32(p_rb_src->ext_sn);
			p_rb_dst->jitter = hton_u32(p_rb_src->jitter);
			p_rb_dst->last_sr = hton_u32(p_rb_src->delay_sr);
			p_rb_dst->delay_sr = hton_u32(p_rb_src->delay_sr);

			p_rb_src++;
			p_rb_dst++;
		}

	}

	build_len = RTCP_RR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
	*p_len = build_len;
	//p_pack->len = ( sizeof(RTCP_HEAD) + sizeof(RTCP_RR) + p_pack->ssrc_cnt * sizeof(RTCP_RB) );

	return 0;
}

/**
 * @brief ����RTCP SDESͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�����ɳ���
 * @param [in] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP SDESͷ������Ч
 */
static int32 rtcp_build_sdes(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	int8 *p_temp = p_buf;
	RTCP_CHUNK *p_chunk = NULL;
	RTCP_CHUNK_PARAM *p_chunk_param = NULL;
	RTCP_ITEM *p_item = NULL;

	int32  left_len;
	int32  total_len = 0;
	int32  parse_len = 0;
	int32  tail_len = 0;
	int32  i, j;

	//if( p_buf == NULL || p_pack == NULL || len < sizeof(RTCP_CHUNK) )
	{
	//	return RTP_ERR_INVALID_PARAM;
	}

	left_len = *p_len;
	if( left_len < RTCP_SDES_SIZE )
	{
		*p_len = RTCP_SDES_SIZE;
		return -2;
	}

	if( p_pack->ssrc_cnt > 0 )
	{
		p_chunk_param = p_pack->body.sdes.chunk;
		total_len = 0;

		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			if( p_chunk_param->item_cnt > RTCP_MAX_ITEM )
			{
				return RTP_ERR_INVALID_PARAM;
			}

			p_chunk = (RTCP_CHUNK *)p_temp;
			p_chunk->ssrc = ntoh_u32(p_chunk_param->ssrc);
			p_temp += sizeof(RTCP_CHUNK);

			parse_len = 0;
			j = 0;
			while( j < p_chunk_param->item_cnt )
			{
				p_item = (RTCP_ITEM *)p_temp;
				/** ����item�����볤�� */
				p_item->type = p_chunk_param->item[j].type;
				p_item->len = p_chunk_param->item[j].len;
				/** ����item�ı� */
				memcpy(p_temp + 2, p_chunk_param->item[j].p_text, p_item->len);

				parse_len += (2+p_item->len);
				p_temp += (2+p_item->len);

				j++;
			}

			/** ����Ҫ��1��'\0'��ʾitem���� */
			parse_len++;
			p_temp++;
			*p_temp = '\0';

			/** �������ĳ��� */
			tail_len = parse_len%RTCP_BASE_UNIT;
			if( tail_len != 0 )
			{
				parse_len += (RTCP_BASE_UNIT - tail_len);
				memset(p_temp, 0, RTCP_BASE_UNIT - tail_len);
				p_temp += (RTCP_BASE_UNIT - tail_len);
			}

			total_len += parse_len;
			p_chunk_param++;
		}

	}

	//build_len = RTCP_RR_SIZE + p_pack->ssrc_cnt * RTCP_RB_SIZE;
	*p_len = total_len;
	//p_pack->len = ( sizeof(RTCP_HEAD) + total_len );

	return 0;
}

/**
 * @brief ����RTCP BYEͷ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�����ɳ���
 * @param [in] p_param �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��RTCP BYEͷ������Ч
 */
static int32 rtcp_build_bye(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	uint32 *p_uint32 = (uint32 *)p_buf;

	int32  left_len;
	int32  build_len;
	int32  i;

	//if( p_buf == NULL || p_pack == NULL || len < sizeof(RTCP_RR) )
	{
	//	return RTP_ERR_INVALID_PARAM;
	}

	left_len = *p_len;
	if( left_len < RTCP_BYE_SIZE )
	{
		*p_len = RTCP_BYE_SIZE;
		return -2;
	}

	if( p_pack->ssrc_cnt > 0 )
	{
		for( i=0; i<p_pack->ssrc_cnt; i++ )
		{
			*p_uint32 = hton_u32(p_pack->body.bye.ssrc[i]);

			p_uint32++;
		}

	}

	build_len = p_pack->ssrc_cnt * RTP_CSRC_SIZE;
	*p_len = build_len;
	//p_pack->len = ( sizeof(RTCP_HEAD) + p_pack->ssrc_cnt * RTP_CSRC_SIZE );

	return 0;
}


///////////////////////////////////�ⲿ�ӿ�////////////////////////////////////
int32 rtcp_pack(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	RTCP_HEADER *p_header = (RTCP_HEADER *)p_buf;
	int32  header_len = 0;
	int32  pack_len, left_len;
	uint16 data_uint16;
	int32  ret;

	if( p_buf == NULL || p_len == NULL || p_pack == NULL )
	{
		return -1;
	}

	left_len = *p_len;
	if( left_len < RTCP_HEADER_SIZE )
	{
		/** ���������Ȳ��� */
		*p_len = RTCP_HEADER_SIZE;
		return -2;
	}

	/** �汾 */
	p_header->flag = ((p_pack->version & 0x3) << 6 );

	/** ����־ */
	p_header->flag |= ((p_pack->b_pad & 0x1) << 5 );

	/** SSRC���� */
	p_header->flag |= (p_pack->ssrc_cnt & 0x1F);

	/** payload type */
	p_header->pt = p_pack->pt;

	left_len -= RTCP_HEADER_SIZE;
	header_len += RTCP_HEADER_SIZE;

	pack_len = left_len;
	switch( p_pack->pt )
	{
	case RTCP_PT_SR:
		{
			ret = rtcp_build_sr(p_buf+header_len, &pack_len, p_pack);
		}
		break;

	case RTCP_PT_RR:
		{
			ret = rtcp_build_rr(p_buf+header_len, &pack_len, p_pack);
		}
		break;

	case RTCP_PT_SDES:
		{
			ret = rtcp_build_sdes(p_buf+header_len, &pack_len, p_pack);			
		}
		break;

	case RTCP_PT_BYE:
		{
			ret = rtcp_build_bye(p_buf+header_len, &pack_len, p_pack);
		}
		break;

	default:
		return -3;
	}

	if( ret )
	{
		*p_len = header_len + pack_len;
		return ret;
	}

	header_len += pack_len;

	/** RTCP������ */
	p_header->len = hton_u16(header_len/RTCP_BASE_UNIT - 1);
	*p_len = header_len;

	return 0;
}

int32 rtcp_unpack(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack)
{
	RTCP_HEADER *p_header = (RTCP_HEADER *)p_buf;

	int32  header_len = 0;
	int32  parse_len, left_len;

	uint16 data_uint16;

	int32  ret;

	if( p_buf == NULL || p_len == NULL || p_pack == NULL )
	{
		return -1;
	}

	left_len = *p_len;
	if( left_len < RTCP_HEADER_SIZE )
	{
		/** ���������Ȳ��� */
		*p_len = RTCP_HEADER_SIZE;
		return -2;
	}

	/** �汾 */
	p_pack->version = ( (p_header->flag & 0xC0) >> 6 );

	/** ����־ */
	p_pack->b_pad = ( (p_header->flag & 0x20) >> 5 );

	/** SSRC���� */
	p_pack->ssrc_cnt = (p_header->flag & 0x1F);

	/** payload type */
	p_pack->pt = p_header->pt;

	/** RTCP��Ϣ���� */
	data_uint16 = ntoh_u16(p_header->len);
	parse_len = (data_uint16+1) * RTCP_BASE_UNIT;

	left_len -= RTCP_HEADER_SIZE;
	header_len += RTCP_HEADER_SIZE;

	parse_len = left_len;
	switch( p_pack->pt )
	{
	case RTCP_PT_SR:
		{
			ret = rtcp_parse_sr(p_buf+header_len, &parse_len, p_pack);
		}
		break;

	case RTCP_PT_RR:
		{
			ret = rtcp_parse_rr(p_buf+header_len, &parse_len, p_pack);
		}
		break;

	case RTCP_PT_SDES:
		{
			ret = rtcp_parse_sdes(p_buf+header_len, &parse_len, p_pack);
		}
		break;

	case RTCP_PT_BYE:
		{
			ret = rtcp_parse_bye(p_buf+header_len, &parse_len, p_pack);
		}
		break;

	default:
		return -3;
	}

	if( ret )
	{
		*p_len = header_len + parse_len;
		return ret;
	}

	header_len += parse_len;
	*p_len = header_len;

	return 0;
}
