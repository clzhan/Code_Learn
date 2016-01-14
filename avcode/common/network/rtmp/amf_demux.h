/**
 * @file amf_demux.h   AMF Demux
 * @author Robert Weng <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.10.18
 *
 *
 */


#ifndef __AMF_DEMUX_H__
#define __AMF_DEMUX_H__

#include <public/gen_int.h>
#include "amf_public.h"


#ifdef __cplusplus
extern "C"
{
#endif


/**  
 * @brief number
 * @param [out] p_amf_type, type
 * @param [in] p_buf, input data
 * @param [in] buf_size, input data size
 * @param [out] p_demux_size, actual demux size
 * @return
 * 0: success
 * other: fail
 * @remark
 * 1. whether success or not, p_demux_size always updated
 */
int32 amf_demux_number(AMF_NUMBER* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief bool
 * @param [out] p_amf_type, type
 * @param [in] p_buf, input data
 * @param [in] buf_size, input data size
 * @param [out] p_demux_size, actual demux size
 * @return
 * 0: success
 * other: fail
 * @remark
 * 1. whether success or not, p_demux_size always updated
 */
int32 amf_demux_bool(AMF_BOOL* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief string
 * @param [out] p_amf_type, type
 * @param [in] p_buf, input data
 * @param [in] buf_size, input data size
 * @param [out] p_demux_size, actual demux size
 * @return
 * 0: success
 * other: fail
 * @remark
 * 1. whether success or not, p_demux_size always updated
 */
int32 amf_demux_string(AMF_STRING* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����object����
 * @param [in/out] p_amf_type type���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 * 2������ʱp_amf_type��prop_count��ʾʵ�ʵ�prop����
 */
int32 amf_demux_calc_obj_size(AMF_OBJ* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����object
 * @param [in/out] p_amf_type type���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * -4������prop���ϲ����Դ�Ž�������������
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 * 2���������prop�����Դ�Ž������ݣ�����ʱp_amf_type��prop_count��ʾʵ�������prop����
 */
int32 amf_demux_obj(AMF_OBJ* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����ref
 * @param [out] p_amf_type type���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 amf_demux_ref(AMF_REF* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����ecma array
 * @param [in/out] p_amf_type type���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * -4������prop���ϲ����Դ�Ž�������������
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 * 2���������prop�����Դ�Ž������ݣ�����ʱp_amf_type��prop_count��ʾʵ�������prop����
 */
int32 amf_demux_ecma_array(AMF_ECMA_ARRAY* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����strict array
 * @param [in/out] p_amf_type type���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * -4������value���ϲ����Դ�Ž�������������
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 * 2���������value�����Դ�Ž������ݣ�����ʱp_amf_type��value_count��ʾʵ�������value����
 */
int32 amf_demux_strict_array(AMF_STRICT_ARRAY* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����long string
 * @param [out] p_amf_type type���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 amf_demux_long_string(AMF_LONG_STRING* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����xml doc
 * @param [out] p_amf_type type���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 amf_demux_xml_doc(AMF_XML_DOC* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);


/**  
 * @brief ����xml doc
 * @param [out] p_amf_type type���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in] buf_size �������ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * -4������prop���ϲ����Դ�Ž�������������
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 * 2���������prop�����Դ�Ž������ݣ�����ʱp_amf_type->obj.prop_count��ʾʵ�������prop����
 * 3��p_buf[0] should be amf type
 */
int32 amf_demux_data_type(AMF_DATA* p_amf_type, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);


#ifdef __cplusplus
}
#endif

#endif ///__AMF_DEMUX_H__
