/**
 * @file mp4_aac_mux.h   MP4 AAC Mux
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.08.26
 *
 *
 */


#ifndef __MP4_AAC_MUX_H__
#define __MP4_AAC_MUX_H__

#include <public/gen_int.h>
#include "mp4_aac_file.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����Es Desc Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   es_desc(see also mpeg4_calc_es_desc_size)
 */
int32 mp4_aac_calc_es_desc_box_total_size(AAC_ES_DESC_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Es Desc Box
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
 *   full_box.box.size
 *   es_desc(see also mpeg4_es_desc_mux)
 */
int32 mp4_aac_es_desc_box_mux(AAC_ES_DESC_BOX *p_box, uint8 *p_buf, uint32 *p_buf_size);

/**  
 * @brief ����AAC Sample Entry�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   es_box.es_desc(see also mpeg4_calc_es_desc_mux)
 */
int32 mp4_aac_calc_sample_entry_total_size(AAC_SAMPLE_ENTRY *p_box, uint32 *p_size);

/**  
 * @brief ����AAC Sample Entry
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
 *   audio.entry.box.size
 *   es_box.full_box.box.size
 *   es_box.es_desc(see also mpeg4_es_desc_mux)
 */
int32 mp4_aac_sample_entry_mux(AAC_SAMPLE_ENTRY* p_box, uint8 *p_buf, uint32 *p_buf_size);

/**  
 * @brief ����AAC Sample Description Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 */
int32 mp4_aac_calc_sample_desc_box_total_size(AAC_SAMPLE_DESC_BOX* p_box, uint32* p_size);

/**  
 * @brief ����AAC Sample Description Box�ܳ���
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
 *   full_box.box.size
 *   entry_count
 *   p_entry(see also @mp4_aac_sample_entry_mux)
 */
int32 mp4_aac_sample_desc_box_mux(AAC_SAMPLE_DESC_BOX* p_box, uint8* p_buf, uint32* p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MP4_AAC_MUX_H__
