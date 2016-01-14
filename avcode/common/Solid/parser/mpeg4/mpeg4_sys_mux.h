/**
 * @file mpeg4_muxer.h   MPEG4 System Muxer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.05.11
 *
 *
 */


#ifndef __MPEG4_SYS_MUX_H__
#define __MPEG4_SYS_MUX_H__

#include <public/gen_int.h>
#include "mpeg4_def.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����Base Descriptor����
 * @param [in] p_desc Descriptor���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   size.bit_size
 */
int32 mpeg4_calc_base_desc_size(MPEG4_BASE_DESCRIPTOR *p_desc, uint32 *p_size);

/**  
 * @brief ����Base Descriptor
 * @param [in] p_desc Descriptor���
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
 *   tag
 *   size.value
 *   size.bit_siz
 */
int32 mpeg4_base_desc_mux(MPEG4_BASE_DESCRIPTOR *p_desc, uint8 *p_buf, uint32 *p_buf_size);

/**  
 * @brief ����SL Config Descriptor����
 * @param [in] p_desc Descriptor���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   base.size.bit_size
 */
int32 mpeg4_calc_sl_config_desc_size(MPEG4_SL_CONFIG_DESCRIPTOR *p_desc, uint32 *p_size);

/**  
 * @brief ����SL Descriptor
 * @param [in] p_desc Descriptor���
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
 *   base
 *   predefine
 *   ����base����Ӧ�ֶ�ҲҪ��д������
 *   base.size.bit_siz
 */
int32 mpeg4_sl_config_desc_mux(MPEG4_SL_CONFIG_DESCRIPTOR *p_desc, uint8 *p_buf, uint32 *p_buf_size);

/**  
 * @brief ����Video Decoder Specific Info����
 * @param [in] p_info Info���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   vos
 *   visual_obj
 *   vol
 *   ���и��Ӳ��ֵ�����ֶ�ҲҪ��д������
 *   vos.profile
 *   visual_obj.is_visual_obj
 *   visual_obj.type
 *   visual_obj.signal_type
 *   visual_obj.color_desc
 *   vol.video_obj_type_indication
 *   vol.is_obj_layer
 *   vol.aspect_ratio
 *   vol.vol_ctrl_param
 *   vol.vbv_param
 *   vol.shape
 */
int32 mpeg4_calc_vdec_spec_info_size(MPEG4_VDEC_SPEC_INFO *p_info, uint32 *p_size);

/**  
 * @brief ����Decoder Config Descriptor����
 * @param [in] p_desc Descriptor���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   base
 *   vdec_spec_info_size
 *   ����base����ֶ�ҲҪ��д������
 *   base.size.bit_size
 */
int32 mpeg4_calc_dec_config_desc_size(MPEG4_DEC_CONFIG_DESCRIPTOR *p_desc, uint32 *p_size);

/**  
 * @brief ����Decoder Config Descriptor
 * @param [in] p_desc Descriptor���
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
 *   base
 *   obj_type
 *   stream_type
 *   buf_size
 *   max_bitrate
 *   avg_bitrate
 *   p_vdec_spec_info
 *   vdec_spec_info_size
 *   ����base����ֶ�ҲҪ��д������
 *   base.size.bit_size
 */
int32 mpeg4_dec_config_desc_mux(MPEG4_DEC_CONFIG_DESCRIPTOR *p_desc, uint8 *p_buf, uint32 *p_buf_size);

/**  
 * @brief ����ES Descriptor����
 * @param [in] p_desc Descriptor���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   base.size.bit_size
 *   dec_config.base
 *   dec_config.vdec_spec_info_size
 *   sl_config.base
 * 2������ʱ���޸�base.size.value�ֶ�
 */
int32 mpeg4_calc_es_desc_size(MPEG4_ES_DESCRIPTOR *p_desc, uint32 *p_size);

/**  
 * @brief ����ES Descriptor
 * @param [in] p_desc Descriptor���
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
 *   base.size.bit_size
 *   es_id
 *   stream_depend_flag
 *   url_flag
 *   ocr_stream_flag
 *   stream_priority
 *   dec_config.base.size.bit_size
 *   dec_config.obj_type
 *   dec_config.stream_type
 *   dec_config.buf_size
 *   dec_config.max_bitrate
 *   dec_config.avg_bitrate
 *   dec_config.p_vdec_spec_info
 *   dec_config.vdec_spec_info_size
 *   sl_config.base.size.bit_size
 *   sl_config.predefine
 */
int32 mpeg4_es_desc_mux(MPEG4_ES_DESCRIPTOR *p_desc, uint8 *p_buf, uint32 *p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG4_SYS_MUX_H__
