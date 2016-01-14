/**
 * @file mpeg2_ps_frame_muxer.h   MPEG2 PS Frame Muxer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.10.16
 *
 *
 */


#ifndef __MPEG2_PS_FRAME_MUXER_H__
#define __MPEG2_PS_FRAME_MUXER_H__

#include <public/gen_int.h>
#include "mpeg2_ps_param.h"
#include "mpeg2_frame_param.h"

/** PS������ */
typedef void* MPEG2_PS_FRAME_MUXER;


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����֡������
 *
 * @return
 * �ǿ�ֵ���ɹ�
 * NULL��ʧ��
 */
MPEG2_PS_FRAME_MUXER mpeg2_ps_frame_muxer_create();

/**  
 * @brief ����֡������
 *
 * @param [in] frame_muxer ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 mpeg2_ps_frame_muxer_destroy(MPEG2_PS_FRAME_MUXER frame_muxer);

/**  
 * @brief ��ʼ��֡������
 *
 * @param [in] frame_muxer ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 mpeg2_ps_frame_muxer_init(MPEG2_PS_FRAME_MUXER frame_muxer);

/**  
 * @brief ����ʼ��֡������
 *
 * @param [in] frame_muxer ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 mpeg2_ps_frame_muxer_deinit(MPEG2_PS_FRAME_MUXER frame_muxer);

/**  
 * @brief ����֡������
 *
 * @param [in] frame_muxer ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 mpeg2_ps_frame_muxer_reset(MPEG2_PS_FRAME_MUXER frame_muxer);

/**  
 * @brief ������Ƶes����
 *
 * @param [in] frame_muxer ֡���������
 * @param [in] p_param ��Ƶes����
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1����ز����μ�mpeg2_public.h
 * 2��Ĭ����Ƶes����Ϊ��stream id = 0xe0
 */
int32 mpeg2_ps_set_ves_param(MPEG2_PS_FRAME_MUXER frame_muxer, MPEG2_PS_STREAM_PARAM *p_param);

/**  
 * @brief ������Ƶes����
 *
 * @param [in] frame_muxer ֡���������
 * @param [in] p_param ��Ƶes����
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1����ز����μ�mpeg2_public.h
 * 2��Ĭ����Ƶes����Ϊ��stream id = 0xc0
 */
int32 mpeg2_ps_set_aes_param(MPEG2_PS_FRAME_MUXER frame_muxer, MPEG2_PS_STREAM_PARAM *p_param);

/**  
 * @brief ����PSͷ��
 *
 * @param [in] frame_muxer ֡���������
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
int32 mpeg2_ps_make_ps_header_pack(MPEG2_PS_FRAME_MUXER frame_muxer, MPEG2_PS_HEADER_PARAM *p_param, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����ϵͳͷ��
 *
 * @param [in] frame_muxer ֡���������
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
int32 mpeg2_ps_make_sys_header_pack(MPEG2_PS_FRAME_MUXER frame_muxer, MPEG2_SYS_HEADER_PARAM *p_param, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����PS֡
 *
 * @param [in] frame_muxer ֡���������
 * @param [in] p_param ֡����
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���ݳ���/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2��Ҫ�����֡���ݱ�����es��
 */
int32 mpeg2_ps_make_frame_pack(MPEG2_PS_FRAME_MUXER frame_muxer, MPEG2_FRAME_PARAM *p_param, uint8 *p_buf, int32 *p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_PS_FRAME_MUXER_H__
