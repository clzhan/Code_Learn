/**
 * @file riff_muxer.h   RIFF Muxer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.10.26
 *
 *
 */


#ifndef __RIFF_MUXER_H__
#define __RIFF_MUXER_H__

#include <public/gen_int.h>
#include "riff_header.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����LIST��ͷ
 *
 * @param [in] p_header �������
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ����������/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_len����
 */
int32 riff_list_header_mux(RIFF_LIST_HEADER *p_header, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����CHUNK��ͷ
 *
 * @param [in] p_header �������
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ����������/ʵ�ʴ������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_len����
 */
int32 riff_chunk_header_mux(RIFF_CHUNK_HEADER *p_header, uint8 *p_buf, int32 *p_buf_size);

#ifdef __cplusplus
}
#endif

#endif ///__RIFF_MUXER_H__
