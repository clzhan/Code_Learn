/**
 * @file mpeg2_dvb_muxer.h   MPEG2 DVB Muxer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.04.06
 *
 *
 */


#ifndef __MPEG2_DVB_MUXER_H__
#define __MPEG2_DVB_MUXER_H__

#include <public/gen_int.h>
#include "mpeg2_dvb_param.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����SIT���ݳ���
 * @param [in] p_param SIT�������
 * @param [out] p_buf_size ���賤��
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 */
int32 mpeg2_dvb_calc_sit_size(MPEG2_DVB_SIT_PARAM *p_param, int32 *p_buf_size);

/**  
 * @brief ����SIT�ֶ�
 * @param [in] p_param SIT�������
 * @param [in] p_buf ���ݻ����ַ
 * @param [in/out] p_buf_size ����������/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 */
int32 mpeg2_dvb_mux_sit(MPEG2_DVB_SIT_PARAM *p_param, uint8 *p_buf, int32 *p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_DVB_MUXER_H__
