/**
 * @file mp4_avc_demux.h   MP4 AVC Demux
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.11.02
 *
 *
 */


#ifndef __MP4_AVC_DEMUX_H__
#define __MP4_AVC_DEMUX_H__

#include <public/gen_int.h>
#include "mp4_avc_file.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����Decoder Config Record
 * @param [in/out] p_record Record���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2���������ݲ����Խ���
 * -3������ȡֵ����
 * -4�������sps��pps���ϲ����Դ�Ž����������
 * @remark
 * 1����������sps��pps���ϲ��㣬ʵ�����������sps_count��pps_count����
 */
int32 mp4_avc_dec_config_record_demux(AVC_DEC_CONFIG_RECORD *p_record, uint8 *p_buf, uint32 *p_buf_size);




#ifdef __cplusplus
}
#endif

#endif ///__MP4_AVC_DEMUX_H__
