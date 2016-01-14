/**
 * @file aac_frame_parser.h   AAC Frame Parser
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2010.10.14
 *
 *
 */

#ifndef __AAC_FRAME_PARSER_H__
#define __AAC_FRAME_PARSER_H__

#include <public/gen_int.h>
#include <Liquid/public/media_def.h>

typedef void* AAC_FRAME_PARSER;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����֡������
 * @return
 * �ǿ�ֵ���ɹ�
 * NULL��ʧ��
 */
AAC_FRAME_PARSER aac_frame_parser_create();

/**  
 * @brief ����֡������
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 aac_frame_parser_destroy(AAC_FRAME_PARSER frame_parser);

/**  
 * @brief ��ʼ��֡������
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 aac_frame_parser_init(AAC_FRAME_PARSER frame_parser);

/**  
 * @brief ����ʼ��֡������
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 aac_frame_parser_deinit(AAC_FRAME_PARSER frame_parser);

/**  
 * @brief ����֡������
 * @param [in] frame_parser ֡���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 aac_frame_parser_reset(AAC_FRAME_PARSER frame_parser);

/**  
 * @brief aac��֡
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
int32 aac_frame_parse(AAC_FRAME_PARSER frame_parser, MEDIA_FRAME *p_frame, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);

#ifdef __cplusplus
}
#endif

#endif ///__AAC_FRAME_PARSER_H__
