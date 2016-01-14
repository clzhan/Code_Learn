/**
 * @file mpeg2_ps_muxer.h   MPEG2 PS Muxer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.10.16
 *
 *
 */


#ifndef __MPEG2_PS_MUXER_H__
#define __MPEG2_PS_MUXER_H__

#include <public/gen_int.h>
#include "mpeg2_ps_param.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����PSͷ������
 *
 * @param [in] p_param PSͷ������
 * @param [out] p_header_size ͷ������
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 */
int32 mpeg2_calc_ps_header_size(MPEG2_PS_HEADER_PARAM *p_param, int32 *p_header_size);

/**  
 * @brief ����PSͷ��
 *
 * @param [in] p_param PSͷ������
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���ݳ���/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 */
int32 mpeg2_ps_header_mux(MPEG2_PS_HEADER_PARAM *p_param, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����ϵͳͷ������
 *
 * @param [in] p_param ϵͳͷ������
 * @param [out] p_header_size ϵͳͷ������
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 */
int32 mpeg2_calc_sys_header_size(MPEG2_SYS_HEADER_PARAM *p_param, int32 *p_header_size);

/**  
 * @brief ����ϵͳͷ��
 *
 * @param [in] p_param ϵͳͷ������
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���ݳ���/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 */
int32 mpeg2_sys_header_mux(MPEG2_SYS_HEADER_PARAM *p_param, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����PSβ��
 *
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���ݳ���/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 */
int32 mpeg2_ps_end_mux(uint8 *p_buf, int32 *p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_PS_MUXER_H__
