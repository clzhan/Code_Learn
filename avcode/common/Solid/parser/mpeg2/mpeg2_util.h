/**
 * @file mpeg2_util.h   MPEG2 Utility
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.10.21
 *
 *
 */


#ifndef __MPEG2_UTIL_H__
#define __MPEG2_UTIL_H__

#include <public/gen_int.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief ��MPEG2ϵͳʱ��ת��Ϊ��ʱ��
 *
 * @param [in/out] p_frame_time MPEG2ϵͳʱ��/��ʱ��
 * @return
 * 0���ɹ�
 * -1����������
 * @remark
 * 1��MPEG2ϵͳʱ�䵥λ��clock(1�� = 90000 clock)����ʱ�䵥λ������(1�� = 1000����)
 */
int32 mpeg2_sys2stream_time(int64 *p_frame_time);

/**
 * @brief ��MPEG2��ʱ��ת��Ϊϵͳʱ��
 *
 * @param [in/out] p_frame_time MPEG2��ʱ��/ϵͳʱ��
 * @return
 * 0���ɹ�
 * -1����������
 * @remark
 * 1��MPEG2ϵͳʱ�䵥λ��clock(1�� = 90000 clock)����ʱ�䵥λ������(1�� = 1000����)
 */
int32 mpeg2_stream2sys_time(int64 *p_frame_time);

#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_UTIL_H__
