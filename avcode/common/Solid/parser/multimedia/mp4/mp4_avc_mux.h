/**
 * @file mp4_avc_mux.h   MP4 AVC Mux
 * @author Robert Weng <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.08.19
 *
 *
 */

#ifndef __MP4_AVC_MUX_H__
#define __MP4_AVC_MUX_H__

#include <public/gen_int.h>
#include "mp4_avc_file.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief calc dec config record total size
 * @param [in] p_record, record
 * @param [out] p_size, total size
 * @return
 * 0: success
 * other: fail
 * @remark
 * 1. caller must filling following member:
 *   sps_count
 *   p_sps->nalu_len
 *   pps_count
 *   p_pps->nalu_len
 */
int32 mp4_avc_calc_dec_config_record_total_size(AVC_DEC_CONFIG_RECORD* p_record, uint32* p_size);

/**  
 * @brief dec config record
 * @param [in] p_record, record
 * @param [in] p_buf, input buf
 * @param [in/out] p_buf_size, input buf size/actual mux size
 * @return
 * 0: success
 * other: fail
 * @remark
 * 1. if input buf size not enough, p_buf_size hold actual need size.
 * 2. caller must filling following member:
 *   profile
 *   profile_compat
 *   level
 *   len_size_minus_1
 *   sps_count
 *   p_sps
 *   pps_count
 *   p_pps
 */
int32 mp4_avc_dec_config_record_mux(AVC_DEC_CONFIG_RECORD* p_record, uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����Config Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   record.sps_count
 *   record.p_sps->nalu_len
 *   record.pps_count
 *   record.p_pps->nalu_len
 */
int32 mp4_avc_calc_config_box_total_size(AVC_CONFIG_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Config Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ���:
 *   box.size
 *   record.profile
 *   record.profile_compat
 *   record.level
 *   record.len_size_minus_1
 *   record.sps_count
 *   record.p_sps
 *   record.pps_count
 *   record.p_pps
 */
int32 mp4_avc_config_box_mux(AVC_CONFIG_BOX *p_box, uint8 *p_buf, uint32 *p_buf_size);

/**  
 * @brief ����AVC Sample Entry�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   config.record.sps_count
 *   config.record.p_sps->nalu_len
 *   config.record.pps_count
 *   config.record.p_pps->nalu_len
 */
int32 mp4_avc_calc_sample_entry_total_size(AVC_SAMPLE_ENTRY *p_box, uint32 *p_size);

/**  
 * @brief ����AVC Sample Entry
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   visual.entry.box.size
 *   visual.entry.data_ref_index
 *   visual.width
 *   visual.height
 *   visual.compressor_name
 *   config.box.size
 *   config.record.profile
 *   config.record.profile_compat
 *   config.record.level
 *   config.record.len_size_minus_1
 *   config.record.sps_count
 *   config.record.p_sps
 *   config.record.pps_count
 *   config.record.p_pps
 */
int32 mp4_avc_sample_entry_mux(AVC_SAMPLE_ENTRY* p_box, uint8 *p_buf, uint32 *p_buf_size);

/**  
 * @brief ����AVC Sample Description Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry(�μ�mp4_avc_calc_sample_entry_total_size)
 */
int32 mp4_avc_calc_sample_desc_box_total_size(AVC_SAMPLE_DESC_BOX* p_box, uint32* p_size);

/**  
 * @brief ����AVC Sample Description Box�ܳ���
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry(�μ�mp4_avc_sample_entry_mux)
 */
int32 mp4_avc_sample_desc_box_mux(AVC_SAMPLE_DESC_BOX* p_box, uint8* p_buf, uint32* p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MP4_AVC_MUX_H__
