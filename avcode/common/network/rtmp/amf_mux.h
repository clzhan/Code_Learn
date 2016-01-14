/**
 * @file amf_mux.h  AMF Mux
 * @author Robert Weng <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.10.19
 *
 *
 */


#ifndef __AMF_MUX_H__
#define __AMF_MUX_H__

#include <public/gen_int.h>
#include "amf_public.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief number
 * @param [in] p_amf_type, type
 * @param [in] p_buf, input buf
 * @param [in/out] p_buf_size, input buf total size/actual use size
 * @return
 * 0: success
 * other: fail
 * @remark
 * 1. if buf size not enough, p_buf_size means actual need size
 * 2. caller must fill:
 *   value
 */
int32 amf_mux_number(AMF_NUMBER* p_amf_type, uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����bool
 * @param [in] p_amf_type type���
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
 *   b_true
 */
int32 amf_mux_bool(AMF_BOOL* p_amf_type, uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����string
 * @param [in] p_amf_type type���
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
 *   data_size
 *   p_data
 */
int32 amf_mux_string(AMF_STRING* p_amf_type, uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����obj���賤��
 * @param [in] p_amf_type type���
 * @param [out] p_size ���賤��
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   prop_count
 *   p_prop
 */
int32 amf_calc_obj_size(AMF_OBJ* p_amf_type, uint32* p_size);

/**  
 * @brief ����obj
 * @param [in] p_amf_type type���
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
 *   prop_count
 *   p_prop
 */
int32 amf_mux_obj(AMF_OBJ* p_amf_type, uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����null
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 */
int32 amf_mux_null(uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����undef
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 */
int32 amf_mux_undef(uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����ref
 * @param [in] p_amf_type type���
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
 *   index
 */
int32 amf_mux_ref(AMF_REF* p_amf_type, uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����long string
 * @param [in] p_amf_type type���
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
 *   data_size
 *   p_data
 */
int32 amf_mux_long_string(AMF_LONG_STRING* p_amf_type, uint8* p_buf, uint32* p_buf_size);

/**  
 * @brief ����xml doc
 * @param [in] p_amf_type type���
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
 *   data_size
 *   p_data
 */
int32 amf_mux_xml_doc(AMF_XML_DOC* p_amf_type, uint8* p_buf, uint32* p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__AMF_MUX_H__
