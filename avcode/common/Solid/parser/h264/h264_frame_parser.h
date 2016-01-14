/**
 * @file h264_frame_parser.h   H264 Frame Parser
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.03.09
 *
 *
 */


#ifndef __H264_FRAME_PARSER_H__
#define __H264_FRAME_PARSER_H__

#include <public/gen_int.h>
#include <public/media_def.h>

typedef void* H264_FRAME_PARSER;

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
H264_FRAME_PARSER h264_frame_parser_create();

/**  
 * @brief ����֡������
 *
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 h264_frame_parser_destroy(H264_FRAME_PARSER frame_parser);

/**  
 * @brief ��ʼ��֡������
 *
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 h264_frame_parser_init(H264_FRAME_PARSER frame_parser);

/**  
 * @brief ����ʼ��֡������
 *
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 h264_frame_parser_deinit(H264_FRAME_PARSER frame_parser);

/**  
 * @brief ����֡������
 *
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 h264_frame_parser_reset(H264_FRAME_PARSER frame_parser);

/**  
 * @brief ����H264 BS������֡
 * @param [in] frame_parser ֡���������
 * @param [out] p_frame ֡���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in] buf_len �������ݳ���
 * @param [out] p_parse_len �ѽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2���������ݲ����Խ���
 * @remark
 * 1�����۽����ɹ���񣬾�������ѽ�������
 */
int32 h264_frame_parse(H264_FRAME_PARSER frame_parser, MEDIA_FRAME *p_frame, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);

/**  
 * @brief ����H264 BS��
 * @param [in] frame_parser ֡���������
 * @param [out] p_frame ֡���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in] buf_len �������ݳ���
 * @param [out] p_parse_len �ѽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2���������ݲ����Խ���
 */
int32 h264_frame_parse2(H264_FRAME_PARSER frame_parser, MEDIA_FRAME *p_frame, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);


#ifdef __cplusplus
}
#endif

#endif ///__H264_FRAME_PARSER_H__
