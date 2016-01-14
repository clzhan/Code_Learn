/**
 * @file rtp.h   RTP��
 *
 * Copyright (C) 2007-2009 ������ͨ��Ϣ�������޹�˾�����з���
 * 
 *
 * @author ���� <wengyan@bqvision.com>
 * @version 0.1
 * @date 2010.02.25
 *
 *
 */


#ifndef __RTP_H__
#define __RTP_H__

#include "../public/gen_int.h"

#include "rtp_public.h"

/** RTPͷ */
typedef struct tag_rtp_header
{
	/** ��־ */
	uint8      flag;
	/** ����λ���غ����� */
	uint8      mark_pt;
	/** ���к� */
	uint16     seq;
	/** ʱ��� */
	uint32     timestamp;
	/** SSRC */
	uint32     ssrc;

} RTP_HEADER, *PRTP_HEADER;

/** RTP��չͷ */
typedef struct tag_rtp_ext_header
{
	/** profile */
	uint16     profile;
	/** ��չ���ݳ���(������4�ֽ���չͷ)����λ��4�ֽ� */
	uint16     ext_data_len;

} RTP_EXT_HEADER, *PRTP_EXT_HEADER;

/** RTPͷ���� */
typedef struct tag_rtp_header_param
{
	/** �汾 */
	uint8      version;
	/** ����־ */
	uint8      b_pad;
	/** ��չ��־ */
	uint8      b_ext;
	/** �����־ */
	uint8      b_mark;
	/** �غ����� */
	uint8      payload_type;
	/** CSRC���� */
	uint8      csrc_num;
	/** ���к� */
	uint16     seq;
	/** ʱ��� */
	uint32     timestamp;
	/** SSRC */
	uint32     ssrc;
	/** CSRC���� */
	uint8      *p_csrc_data;

} RTP_HEADER_PARAM, *PRTP_HEADER_PARAM;

/** RTP��չͷ���� */
typedef struct tag_rtp_ext_header_param
{
	/** Profile */
	uint16     profile;
	/** ��չ���ݳ��ȣ���λ��4�ֽ� */
	uint16     ext_data_len;
	/** ��չ���� */
	uint8      *p_ext_data;

} RTP_EXT_HEADER_PARAM, *PRTP_EXT_HEADER_PARAM;


#ifdef __cplusplus
extern "C"
{
#endif

/** 
 * @brief RTP���
 * @param [in] p_param RTPͷ����
 * @param [in] p_ext_param RTP��չͷ����
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_buf_len �������ܳ���/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ���
 * -3��������Ч
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_len����
 */
int32 rtp_mux(RTP_HEADER_PARAM *p_param, RTP_EXT_HEADER_PARAM *p_ext_param, int8 *p_buf, int32 *p_buf_len);

/** 
 * @brief RTP����
 * @param [out] p_param RTPͷ����
 * @param [out] p_ext_param RTP��չͷ����
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_buf_len �������ܳ���/ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���������ݲ����Խ���
 * -3��������Ч
 */
int32 rtp_demux(RTP_HEADER_PARAM *p_param, RTP_EXT_HEADER_PARAM *p_ext_param, int8 *p_buf, int32 *p_buf_len);


#ifdef __cplusplus
}
#endif

#endif ///__RTP_H__
