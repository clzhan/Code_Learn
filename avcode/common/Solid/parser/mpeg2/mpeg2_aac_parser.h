/**
 * @file mpeg2_aac_parser.h   MPEG2 AAC Parser
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.09.27
 *
 *
 */


#ifndef __MPEG2_AAC_PARSER_H__
#define __MPEG2_AAC_PARSER_H__

#include <public/gen_int.h>
#include "mpeg2_aac_const.h"

/** ADTS�̶�ͷ */
typedef struct tag_adts_fix_header
{
	/** protection_absent */
	int32  b_protection_absent;
	/** profile */
	int32  profile;
	/** sample_freq */
	int32  sample_freq;
	/** channel_configuration */
	int32  chn_config;

} ADTS_FIX_HEADER, *PADTS_FIX_HEADER;

/** ADTS�ɱ�ͷ */
typedef struct tag_adts_var_header
{
	/** copyright */
	int32  b_copyright;
	/** copyright_start */
	int32  b_copyright_start;
	/** frame_length */
	int32  frame_len;
	/** buffer_fullness */
	int32  buf_fullness;
	/** number_of_raw_data_blocks_in_frame */
	int32  rdb_num;

} ADTS_VAR_HEADER, *PADTS_VAR_HEADER;

/** ADTS�� */
typedef struct tag_adts_pack
{
	/** ��ʼ��ַ */
	uint8   *p_start;

	/** fix header */
	ADTS_FIX_HEADER  fix_header;
	/** var header */
	ADTS_VAR_HEADER  var_header;

} ADTS_PACK, *PADTS_PACK;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ��ʼ��AAC ADTS��
 *
 * @param [in] p_pack ADTS��
 * @return
 * 0���ɹ�
 * -1����������
 */
int32 aac_adts_init(ADTS_PACK *p_pack);

/**  
 * @brief ����AAC ADTS��
 * @param [out] p_pack ADTS�����
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_len ���ݳ���
 * @param [out] p_parse_len �ѽ����ĳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����ݲ����Խ���
 * @remark
 * 1�����۽����ɹ����p_parse_len���᷵��ʵ�ʽ�������
 */
int32 aac_adts_parse(ADTS_PACK *p_pack, uint8 *p_buf, int32 buf_len, int32 *p_parse_len);

/**  
 * @brief ��ȡAAC��Ӧ�Ĳ���������
 * @param [in] sample_freq ������
 * @param [out] p_index ��Ӧ������
 * @return
 * 0���ɹ�
 * -1����������
 * -3��δ�ҵ���Ӧ����
 */
int32 aac_get_sample_freq_index(int32 sample_freq, int32 *p_index);

#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_AAC_PARSER_H__
