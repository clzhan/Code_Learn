/**
 * @file mpeg2_ves_parser.h   MPEG2 VES Parser
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2008.05.15
 *
 *
 */


#ifndef __MPEG2_VES_PARSER_H__
#define __MPEG2_VES_PARSER_H__

#include <public/gen_int.h>

#include "mpeg2_public.h"

/** ��ƵES SEQ */
typedef struct tag_mpeg2_ves_seq
{
	/** profile */
	int32  profile;
	/** level */
	int32  level;

	/** ͼ����ʽ */
	int32  video_format;
	/** ͼ���ʽ */
	int32  chroma_format;

	/** ͼ���ȣ���λ������ */
	int32  width;
	/** ͼ��߶ȣ���λ������ */
	int32  height;
	/** ͼ����ʾ��ȣ���λ������ */
	int32  display_width;
	/** ͼ����ʾ�߶ȣ���λ������ */
	int32  display_height;
	/** ͼ����� */
	int32  aspect_ratio;

	/** ֡�� */
	int32  frame_rate;
	/** �����ʣ���λ��bps */
	int32  bit_rate;
	/** vbv buffer size */
	int32  vbv_buf_size;

	/** progressive_sequence */
	int32  progs_seq;
	/** low delay */
	int32  b_low_delay;
	
} MPEG2_VES_SEQ, *PMPEG2_VES_SEQ;

/** ��ƵES PIC */
typedef struct tag_mpeg2_ves_pic
{
	/** ֡���� */
	int32  type;
	/** temporal reference */
	int32  temp_ref;

	/** �Ƿ�������ʾ */
	int32  b_progressive;
	/** intra dc precision */
	int32  dc_precision;
	/** picture structure */
	int32  pic_struct;
	
} MPEG2_VES_PIC, *PMPEG2_VES_PIC;

/** ��ƵES״̬ */
typedef struct tag_mpeg2_ves_state
{
	/** ��ʼ���ַ */
	uint8  *p_start;
	/** ��ǰ��ʼ�� */
	int32  start_code;
	/** ��չID */
	int32  ext_id;

	/** seq */
	MPEG2_VES_SEQ seq;
	/** pic */
	MPEG2_VES_PIC pic;

} MPEG2_VES_STATE, *PMPEG2_VES_STATE;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ��ʼ��MPEG2��ƵES��״̬
 *
 * @param [in] p_state ��ƵES״̬���
 * @return
 * 0���ɹ�
 * -1����������
 */
int32 mpeg2_ves_init(MPEG2_VES_STATE *p_state);

/**  
 * @brief ����MPEG2��ƵES��
 *
 * @param [out] p_state ��ƵES״̬���
 * @param [in] p_buf �����ݵ�ַ
 * @param [in] buf_len �����ݳ���
 * @param [out] p_parse_len �ѽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2���������ݲ����Խ���
 */
int32 mpeg2_ves_parse(MPEG2_VES_STATE *p_state, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_VES_PARSER_H__
