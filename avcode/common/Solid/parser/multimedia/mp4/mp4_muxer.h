/**
 * @file mp4_muxer.h   MP4 Muxer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.05.05
 *
 *
 */


#ifndef __MP4_MUXER_H__
#define __MP4_MUXER_H__

#include <public/gen_int.h>
#include "../iso/iso_media_file.h"
#include "mp4_avc_file.h"
#include "mp4_aac_file.h"
#include "mp4_public.h"



#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����File Type Box
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ���:
 *   major_brand
 *   minor_version
 *   p_brand
 *   brand_count
 */
int32 mp4_make_file_type_box(ISO_FILE_TYPE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Handler Reference Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   handler_type
 *   p_name
 *   name_size
 *   ����name_size���������β��'\0'
 */
int32 mp4_make_handler_box(ISO_HANDLER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Data Reference Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry_count
 *   p_entry
 *   ���и���p_entry��entry_type�ֶβ�ͬ��url��urn����Ӧ���ֶ�ҲҪ��д������
 *   full_box.version_flag.value
 *   p_name
 *   name_size
 *   p_location
 *   location_size
 */
int32 mp4_make_data_ref_box(ISO_DATA_REF_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Time to Sample Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry_count
 *   p_entry
 */
int32 mp4_make_time_to_sample_box(ISO_TIME_TO_SAMPLE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Visual Sample Description Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry_count
 *   p_entry
 *   ����p_entry��Ӧ���ֶ�ҲҪ��д������
 *   entry.box.type
 *   entry.data_ref_index
 *   width
 *   height
 *   compressor_name
 */
int32 mp4_make_visual_sample_desc_box(ISO_VISUAL_SAMPLE_DESC_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����AVC Sample Description Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry.visual.entry.data_ref_index
 *   entry.visual.width
 *   entry.visual.height
 *   entry.visual.compressor_name
 *   entry.config.record.profile
 *   entry.config.record.profile_compat
 *   entry.config.record.level
 *   entry.config.record.len_size_minus_1
 *   entry.config.record.sps_count
 *   entry.config.record.p_sps
 *   entry.config.record.pps_count
 *   entry.config.record.p_pps
 */
int32 mp4_make_avc_sample_desc_box(AVC_SAMPLE_DESC_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Audio Sample Description Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry_count
 *   p_entry
 *   ����p_entry��Ӧ���ֶ�ҲҪ��д������
 *   entry.box.type
 *   entry.data_ref_index
 *   sample_rate
 */
int32 mp4_make_audio_sample_desc_box(ISO_AUDIO_SAMPLE_DESC_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����AAC Sample Description Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry_count
 *   p_entry->audio
 *   p_entry->es_box
 */
int32 mp4_make_aac_sample_desc_box(AAC_SAMPLE_DESC_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Sample to Chunk Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   entry_count
 *   p_entry
 */
int32 mp4_make_sample_to_chunk_box(ISO_SAMPLE_TO_CHUNK_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Extend Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   box.size
 */
int32 mp4_make_movie_extend_box(ISO_MOVIE_EXTEND_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Extend Header Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   fragment_duration
 */
int32 mp4_make_movie_extend_header_box(ISO_MOVIE_EXTEND_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Extend Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   track_id
 *   def_sample_desc_index
 *   def_sample_duration
 *   def_sample_size
 *   def_sample_flag
 */
int32 mp4_make_track_extend_box(ISO_TRACK_EXTEND_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Fragment Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   box.size
 */
int32 mp4_make_movie_fragment_box(ISO_MOVIE_FRAGMENT_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Fragment Header Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   seq_no
 */
int32 mp4_make_movie_fragment_header_box(ISO_MOVIE_FRAGMENT_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Fragment Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   box.size
 */
int32 mp4_make_track_fragment_box(ISO_TRACK_FRAGMENT_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Fragment Header Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   full_box.version_flag
 *   track_id
 *   base_data_offset
 *   sample_desc_index
 *   def_sample_duration
 *   def_sample_size
 *   def_sample_flag
 */
int32 mp4_make_track_fragment_header_box(ISO_TRACK_FRAGMENT_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Fragment Run Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   full_box.version_flag
 *   sample_count
 *   data_offset
 *   first_sample_flag
 *   p_sample->sample_duration
 *   p_sample->sample_size
 *   p_sample->sample_flag
 *   p_sample->sample_composition_time_offset
 *  ������Ч�����ֶ���full_box.version_flag����
 */
int32 mp4_make_track_fragment_run_box(ISO_TRACK_FRAGMENT_RUN_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Fragment Random Access Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   box.size
 */
int32 mp4_make_movie_fragment_random_access_box(ISO_MOVIE_FRAGMENT_RANDOM_ACCESS_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Fragment Random Access Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   full_box.box.size
 *   track_id
 *   mixture
 *   entry_num
 *   p_entry
 */
int32 mp4_make_track_fragment_random_access_box(ISO_TRACK_FRAGMENT_RANDOM_ACCESS_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Fragment Random Access Offset Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   size
 */
int32 mp4_make_movie_fragment_random_access_offset_box(ISO_MOVIE_FRAGMENT_RANDOM_ACCESS_OFFSET_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Meta Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in/out] p_buf_size ���볤��/ʵ��ʹ�ó���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1��������������Ȳ��㣬ʵ�����賤����p_buf_size����
 * 2���ⲿ��д�ֶΰ�����
 *   handler_box
 *   ����handler_box��Ӧ�ֶ�ҲҪ��д������
 *   handler_type
 *   p_name
 *   name_size
 *   ����name_size���������β��'\0'
 */
int32 mp4_make_meta_box(ISO_META_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MP4_FILE_MUXER_H__
