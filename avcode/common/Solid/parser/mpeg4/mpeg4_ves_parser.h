/**
 * @file mpeg4_ves_parser.h   MPEG4 VES Parser
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2008.05.15
 *
 *
 */


#ifndef __MPEG4_VES_PARSER_H__
#define __MPEG4_VES_PARSER_H__

#include <public/gen_int.h>
#include "mpeg4_public.h"
#include "mpeg4_video_def.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ��ʼ��MPEG4��ƵES״̬
 * @param [in] p_state ��ƵES״̬���
 * @return
 * 0���ɹ�
 * -1����������
 */
int32 mpeg4_ves_init(MPEG4_VES_STATE *p_state);

/**  
 * @brief ����MPEG4��ƵES
 * @param [out] p_state ��ƵES״̬���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in] buf_len �������ݳ���
 * @param [out] p_parse_len �ѽ������ݳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����ݲ����Խ���
 * @remark
 * 1�����۽����Ƿ�ɹ����������p_parse_len����
 */
int32 mpeg4_ves_parse(MPEG4_VES_STATE *p_state, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);

/**  
 * @brief ����MPEG4��ƵES(��������������)
 * @param [out] p_state ��ƵES״̬���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in] buf_len �������ݳ���
 * @param [out] p_parse_len �ѽ������ݳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����ݲ����Խ���
 * -12�����ݲ����Խ����������ܰ���������Ч����
 * @remark
 * 1�����۽����Ƿ�ɹ����������p_parse_len����
 */
int32 mpeg4_ves_parse2(MPEG4_VES_STATE *p_state, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG4_VES_PARSER_H__
