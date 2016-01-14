/**
 * @file h264_bs_parser.h   H264 Bit Stream Parser
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.02.26
 *
 *
 */


#ifndef __H264_BS_PARSER_H__
#define __H264_BS_PARSER_H__


#include "h264_def.h"



#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ��ʼ��H264 BS��״̬
 * @param [in] p_pack BS״̬���
 * @return
 * 0���ɹ�
 * -1����������
 */
int32 h264_bs_init(H264_BS_PACK *p_pack);

/**  
 * @brief ����H264 BS��
 * @param [out] p_pack BS���
 * @param [in] p_buf ����ַ
 * @param [in] buf_len ������
 * @param [out] p_parse_len �ѽ��������ݳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����ݲ����Խ���
 * @remark
 * 1�����۽����ɹ���񣬾������p_parse_len����
 */
int32 h264_parse_bs(H264_BS_PACK *p_pack, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);

/**  
 * @brief ����H264 BS��(��������������)
 * @param [out] p_pack BS���
 * @param [in] p_buf ����ַ
 * @param [in] buf_len ������
 * @param [out] p_parse_len �ѽ��������ݳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����ݲ����Խ���
 * -12�����ݲ����Խ����������ܰ���������Ч����
 * @remark
 * 1�����۽����ɹ���񣬾������p_parse_len����
 */
int32 h264_parse_bs2(H264_BS_PACK *p_pack, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);

#ifdef __cplusplus
}
#endif

#endif ///__H264_BS_PARSER_H__
