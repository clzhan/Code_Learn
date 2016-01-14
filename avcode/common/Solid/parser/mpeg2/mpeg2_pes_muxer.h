/**
 * @file mpeg2_pes_muxer.h   MPEG2 PES Muxer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.08.25
 *
 *
 */


#ifndef __MPEG2_PES_MUXER_H__
#define __MPEG2_PES_MUXER_H__

#include <public/gen_int.h>

/** PES���� */
typedef struct tag_mpeg2_pes_header_param
{
	/** stream id */
	uint8  stream_id;
	/** ext flag */
	uint8  b_ext;
	/** pack len */
	uint16 pack_len;

	/** scramble control */
	uint8  scramble_control;
	/** priority */
	uint8  b_priority;
	/** data alignment indicator */
	uint8  b_data_align;
	/** copyright */
	uint8  b_copyright;

	/** original */
	uint8  b_original;
	/** pts dts flag */
	uint8  pts_dts_flag;
	/** ESCR */
	uint8  b_escr;
	/** ES rate */
	uint8  b_es_rate;

	/** DSM trick mode flag */
	uint8  b_dsm_trick_mode;
	/** additional copy info flag */
	uint8  b_copy_info;
	/** crc flag */
	uint8  b_crc;
	/** header data len */
	uint8  header_data_len;

	/** pts(low 32 bit) */
	uint32 pts_low;
	/** pts(high 32 bit) */
	uint32 pts_high;
	/** dts(low 32 bit) */
	uint32 dts_low;
	/** dts(high 32 bit) */
	uint32 dts_high;

} MPEG2_PES_HEADER_PARAM, *PMPEG2_PES_HEADER_PARAM;


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����PESͷ������(��ѡ����)����
 *
 * @param [in] p_param PESͷ������
 * @param [out] p_header_data_size ͷ�����ݳ��ȣ���λ���ֽ�
 * @return
 * 0���ɹ�
 * -1����������
 * @remark
 * 1�����������ͷ�����ݳ��Ƚ�������ѡ���ֵĳ��ȣ��мǣ�
 */
int32 mpeg2_calc_pes_header_data_size(MPEG2_PES_HEADER_PARAM *p_param, int32 *p_header_data_size);

/**  
 * @brief ����PESͷ������
 *
 * @param [in] p_param PESͷ������
 * @param [out] p_header_size ͷ�����ȣ���λ���ֽ�
 * @return
 * 0���ɹ�
 * -1����������
 * @remark
 * 1��p_param�е�header_data_len����ͨ��mpeg2_calc_pes_header_data_size�������
 */
int32 mpeg2_calc_pes_header_size(MPEG2_PES_HEADER_PARAM *p_param, int32 *p_header_size);

/**  
 * @brief ���PES��ͷ
 *
 * @param [in] p_param ����������
 * @param [in] p_buf ���ݻ����ַ
 * @param [in/out] p_buf_len ����������/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_len����
 */
int32 mpeg2_pes_mux(MPEG2_PES_HEADER_PARAM *p_param, uint8 *p_buf, int32 *p_buf_len);

/**  
 * @brief ����PES����
 *
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_len ��䳤��
 * @return
 * 0���ɹ�
 * -1����������
 * @remark
 * 1����䳤����С������MPEG2_PES_HEADER_MIN_SIZE������ܳ���MPEG2_PES_HEADER_MIN_SIZE + MPEG2_PES_MAX_PACK_SIZE
 */
int32 mpeg2_pes_padding_mux(uint8 *p_buf, int32 buf_len);

#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_PES_MUXER_H__
