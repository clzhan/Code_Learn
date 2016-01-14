/**
 * @file mpeg2_aes_parser.h   MPEG2 AES Parser
 * @author Robert Weng <robert_3000@sina.com>
 * @version 0.1
 * @date 2008.05.21
 *
 *
 */

#ifndef __MPEG2_AES_PARSER_H__
#define __MPEG2_AES_PARSER_H__

#include <public/gen_int.h>

#include "mpeg2_public.h"

/** ��ƵESͷ */
typedef struct tag_mpeg2_aes_header
{
	/** ��Ƶͷ��ʼ��ַ */
	int8   *p_start;

	/** layer */
	int32  layer;

	/** ����λ�� */
	int32  bits;
	/** ������ */
	int32  freq;
	/** ������ */
	int32  chn;

	/** �����ʣ���λ��kbit/s */
	int32  bit_rate;

	/** �Ƿ���� */
	int32  b_padding;

} MPEG2_AES_HEADER, *PMPEG2_AES_HEADER;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ��ʼ��MPEG2��ƵESͷ
 *
 * @param [in] p_header ��ƵESͷ
 * @return
 * 0���ɹ�
 * -1����������
 */
int32 mpeg2_aes_init(MPEG2_AES_HEADER *p_header);

/**  
 * @brief ����MPEG2��ƵESͷ
 *
 * @param [out] p_header ��ƵESͷ���
 * @param [in] p_buf �����ݵ�ַ
 * @param [in] buf_len �����ݳ���
 * @param [out] p_parse_len �ѽ����ĳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����ݲ����Խ���
 */
int32 mpeg2_aes_parse(MPEG2_AES_HEADER *p_header, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_AES_PARSER_H__
