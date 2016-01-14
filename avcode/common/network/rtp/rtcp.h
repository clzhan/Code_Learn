/**
 * @file rtcp.h   RTCP��
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

#ifndef __RTCP_H__
#define __RTCP_H__

#include "../public/gen_int.h"

#include "rtp_public.h"

/** RTCPͷ */
typedef struct tag_rtcp_header
{
	/** ��־ */
	uint8      flag;
	/** PAYLOAD TYPE */
	uint8      pt;
	/** RTCP�����ȼ�1����λ��4�ֽ� */
	uint16     len;

} RTCP_HEADER, *PRTCP_HEADER;

/** RTCP Report Block */
typedef struct tag_rtcp_rb
{
	/** SSRC */
	uint32     ssrc;
	/** fraction lost */
	uint8      frac_lost;
	/** packet lost */
	uint8      pack_lost[3];
	/** extended highest sequence number received */
	uint32     ext_sn;
	/** �����ռ������ */
	uint32     jitter;
	/** last SR */
	uint32     last_sr;
	/** delay since last SR */
	uint32     delay_sr;

} RTCP_RB, *PRTCP_RB;

#define RTCP_RB_SIZE                               (sizeof(RTCP_RB))

/** RTCP SR */
typedef struct tag_rtcp_sr
{
	/** SSRC */
	uint32     ssrc;

	/** NTP timestamp, high 32 bit */
	uint32     ntp_ts_high;
	/** NTP timestamp, low 32 bit */
	uint32     ntp_ts_low;
	/** RTP timestamp */
	uint32     rtp_ts;
	/** �ѷ��Ͱ����� */
	uint32     pack_send;
	/** �ѷ����ֽ��� */
	uint32     bytes_send;

} RTCP_SR, *PRTCP_SR;

#define RTCP_SR_SIZE                               (sizeof(RTCP_SR))

/** RTCP RR */
typedef struct tag_rtcp_rr
{
	/** SSRC */
	uint32     ssrc;

} RTCP_RR, *PRTCP_RR;

#define RTCP_RR_SIZE                               (sizeof(RTCP_RR))

/** RTCP SDES item */
typedef struct tag_rtcp_item
{
	/** item */
	uint8      type;
	/** len */
	uint8      len;
	/** ���� */
	uint16     resv;
	/** content */
	int8       *p_text;

} RTCP_ITEM, *PRTCP_ITEM;

/** RTCP SDES chunk */
typedef struct tag_rtcp_chunk
{
	/** SSRC */
	uint32     ssrc;

} RTCP_CHUNK, *PRTCP_CHUNK;

#define RTCP_CHUNK_SIZE                            (sizeof(RTCP_CHUNK))

/** RTCP SDES */
typedef struct tag_rtcp_sdes
{
	/** ������ */
	RTCP_CHUNK *p_chunk;

} RTCP_SDES, *PRTCP_SDES;

#define RTCP_SDES_SIZE                             (sizeof(RTCP_SDES))

/** RTCP BYE */
typedef struct tag_rtcp_bye
{
	/** ��־ */
	uint8      flag;
	/** PAYLOAD TYPE */
	uint8      pt;
	/** RTCP�����ȼ�1����λ��4�ֽ� */
	uint16     len;

	/** SSRC�б� */
	uint32     *p_ssrc;

} RTCP_BYE, *PRTCP_BYE;

#define RTCP_BYE_SIZE                              (sizeof(RTCP_BYE))

/** RTCP SR���� */
typedef struct tag_rtcp_sr_param
{
	/** SSRC */
	uint32     ssrc;

	/** NTPʱ���, ��32λ */
	uint32     ntp_ts_high;
	/** NTPʱ���, ��32λ */
	uint32     ntp_ts_low;
	/** RTPʱ��� */
	uint32     rtp_ts;
	/** �ѷ��Ͱ����� */
	uint32     pack_send;
	/** �ѷ����ֽ��� */
	uint32     bytes_send;

	/** report block */
	RTCP_RB    report_block[RTCP_MAX_SSRC_NUM];

} RTCP_SR_PARAM, *PRTCP_SR_PARAM;

/** RTCP RR���� */
typedef struct tag_rtcp_rr_param
{
	/** SSRC */
	uint32     ssrc;

	/** report block */
	RTCP_RB    report_block[RTCP_MAX_SSRC_NUM];

} RTCP_RR_PARAM, *PRTCP_RR_PARAM;

/** RTCP SDES chunk */
typedef struct tag_rtcp_chunk_param
{
	/** SSRC */
	uint32     ssrc;
	/** item���� */
	int32      item_cnt;
	/** item�б� */
	RTCP_ITEM  item[RTCP_MAX_ITEM];

} RTCP_CHUNK_PARAM, *PRTCP_CHUNK_PARAM;

/** RTCP SDES���� */
typedef struct tag_rtcp_sdes_param
{
	/** chunk�б� */
	RTCP_CHUNK_PARAM chunk[RTCP_MAX_SSRC_NUM];

} RTCP_SDES_PARAM, *PRTCP_SDES_PARAM;

/** RTCP BYE���� */
typedef struct tag_rtcp_bye_param
{
	/** SSRC�б� */
	uint32     ssrc[RTCP_MAX_SSRC_NUM];

} RTCP_BYE_PARAM, *PRTCP_BYE_PARAM;

/** RTCP������ */
typedef struct tag_rtcp_pack
{
	/** �汾 */
	uint8      version;
	/** ����־ */
	uint8      b_pad;
	/** SSRC/CSRC���� */
	uint8      ssrc_cnt;
	/** �غ����� */
	uint8      pt;
	/** �����ȣ���λ���ֽ� */
	uint16     len;
	/** ���� */
	uint16     resv;

	union 
	{
		RTCP_SR_PARAM    sr;
		RTCP_RR_PARAM    rr;
		RTCP_SDES_PARAM  sdes;
		RTCP_BYE_PARAM   bye;

	} body;

} RTCP_PACK, *PRTCP_PACK;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief ����RTCP��Ϣ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�����ɳ���
 * @param [out] p_pack RTCP�������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ��㣬ʵ�����賤����p_len����
 * -3��RTCP������Ч
 */
int32 rtcp_pack(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack);

/**
 * @brief ����RTCP��Ϣ
 *
 * @param [in] p_buf ��������ַ
 * @param [in/out] p_len �������ܳ���/ʵ�ʽ�������
 * @param [out] p_pack RTCP�������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������Ȳ��㣬ʵ�����賤����p_len����
 */
int32 rtcp_unpack(int8 *p_buf, int32 *p_len, RTCP_PACK *p_pack);

#ifdef __cplusplus
}
#endif

#endif// __RTCP_H__
