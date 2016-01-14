/**
 * @file mp4_mux.h   MP4 Mux
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.04.28
 *
 *
 */


#ifndef __MP4_MUX_H__
#define __MP4_MUX_H__

#include <public/gen_int.h>
#include "../iso/iso_media_file.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����File Type Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ���:
 *   brand_count
 */
int32 mp4_calc_file_type_box_total_size(ISO_FILE_TYPE_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����File Type Box
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
 * 2���ⲿ��д�ֶΰ���:
 *   box.siz
 *   major_brand
 *   minor_version
 *   p_brand
 *   brand_count
 */
int32 mp4_file_type_box_mux(ISO_FILE_TYPE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Box
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
int32 mp4_movie_box_mux(ISO_MOVIE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Media Data Box
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
int32 mp4_media_data_box_mux(ISO_MEDIA_DATA_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Movie Header Box
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
 *   creation_time
 *   modification_time
 *   time_scale
 *   duration
 *   next_track_id
 */
int32 mp4_movie_header_box_mux(ISO_MOVIE_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Box
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
int32 mp4_track_box_mux(ISO_TRACK_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Header Box
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
 *   box.version_flag.value
 *   creation_time
 *   modification_time
 *   track_id
 *   duration
 *   volume
 *   width
 *   height
 */
int32 mp4_track_header_box_mux(ISO_TRACK_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Media Box
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
int32 mp4_media_box_mux(ISO_MEDIA_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Media Header Box
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
 *   creation_time
 *   modification_time
 *   time_scale
 *   duration
 *   language
 */
int32 mp4_media_header_box_mux(ISO_MEDIA_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Handler Reference Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   name_size
 *   ����name_size���������β��'\0'
 */
int32 mp4_calc_handler_box_total_size(ISO_HANDLER_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   handler_type
 *   p_name
 *   name_size
 *   ����name_size���������β��'\0'
 */
int32 mp4_handler_box_mux(ISO_HANDLER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Media Information Box
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
int32 mp4_media_info_box_mux(ISO_MEDIA_INFO_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Video Media Header Box
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
 */
int32 mp4_video_media_header_box_mux(ISO_VIDEO_MEDIA_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Sound Media Header Box
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
 */
int32 mp4_sound_media_header_box_mux(ISO_SOUND_MEDIA_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Data Information Box
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
int32 mp4_data_info_box_mux(ISO_DATA_INFO_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Data Reference Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 *   p_entry
 *   ���и���p_entry��entry_type�ֶβ�ͬ��url��urn����Ӧ���ֶ�ҲҪ��д������
 *   p_name
 *   name_size
 *   p_location
 *   location_size
 *   �ӿڷ���ʱ���޸�url��urn���full_box.box.size�ֶ�
 */
int32 mp4_calc_data_ref_box_total_size(ISO_DATA_REF_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   entry_count
 *   p_entry
 *   ���и���p_entry��entry_type�ֶβ�ͬ��url��urn����Ӧ���ֶ�ҲҪ��д������
 *   full_box.box.size
 *   full_box.version_flag.value
 *   p_name
 *   name_size
 *   p_location
 *   location_size
 */
int32 mp4_data_ref_box_mux(ISO_DATA_REF_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Sample Table Box
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
int32 mp4_sample_table_box_mux(ISO_SAMPLE_TABLE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Time to Sample Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1����������ֻ��box���ȣ�������p_entry����
 */
int32 mp4_calc_time_to_sample_box_size(ISO_TIME_TO_SAMPLE_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Time to Sample Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 */
int32 mp4_calc_time_to_sample_box_total_size(ISO_TIME_TO_SAMPLE_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   entry_count
 */
int32 mp4_time_to_sample_box_mux(ISO_TIME_TO_SAMPLE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Visual Sample Description Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1����������ֻ��box���ȣ�������p_entry����
 */
int32 mp4_calc_visual_sample_desc_box_size(ISO_VISUAL_SAMPLE_DESC_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Visual Sample Description Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 */
int32 mp4_calc_visual_sample_desc_box_total_size(ISO_VISUAL_SAMPLE_DESC_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   entry_count
 *   p_entry
 *   ����p_entry��Ӧ���ֶ�ҲҪ��д������
 *   entry.box.type
 *   entry.data_ref_index
 *   width
 *   height
 *   compressor_name
 */
int32 mp4_visual_sample_desc_box_mux(ISO_VISUAL_SAMPLE_DESC_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Audio Sample Description Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1����������ֻ��box���ȣ�������p_entry����
 */
int32 mp4_calc_audio_sample_desc_box_size(ISO_AUDIO_SAMPLE_DESC_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Audio Sample Description Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 */
int32 mp4_calc_audio_sample_desc_box_total_size(ISO_AUDIO_SAMPLE_DESC_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   entry_count
 *   p_entry
 *   ����p_entry��Ӧ���ֶ�ҲҪ��д������
 *   entry.box.type
 *   entry.data_ref_index
 *   sample_rate
 */
int32 mp4_audio_sample_desc_box_mux(ISO_AUDIO_SAMPLE_DESC_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Sample Size Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1����������ֻ��box���ȣ�������p_entry����
 */
int32 mp4_calc_sample_size_box_size(ISO_SAMPLE_SIZE_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Sample Size Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   sample_size
 *   sample_count
 */
int32 mp4_calc_sample_size_box_total_size(ISO_SAMPLE_SIZE_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Sample Size Box
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
 *   sample_size
 *   sample_count
 */
int32 mp4_sample_size_box_mux(ISO_SAMPLE_SIZE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Sample to Chunk Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1����������ֻ��box���ȣ�������p_entry����
 */
int32 mp4_calc_sample_to_chunk_box_size(ISO_SAMPLE_TO_CHUNK_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Sample to Chunk Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 */
int32 mp4_calc_sample_to_chunk_box_total_size(ISO_SAMPLE_TO_CHUNK_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   entry_count
 *   p_entry
 */
int32 mp4_sample_to_chunk_box_mux(ISO_SAMPLE_TO_CHUNK_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Chunk Offset Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1������������box���ȣ�������p_entry����
 */
int32 mp4_calc_chunk_offset_box_size(ISO_CHUNK_OFFSET_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Chunk Offset Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 */
int32 mp4_calc_chunk_offset_box_total_size(ISO_CHUNK_OFFSET_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Chunk Offset Box
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
 *   entry_count
 */
int32 mp4_chunk_offset_box_mux(ISO_CHUNK_OFFSET_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Sync Sample Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1������������box���ȣ�������p_entry����
 */
int32 mp4_calc_sync_sample_box_size(ISO_SYNC_SAMPLE_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Sync Sample Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   entry_count
 */
int32 mp4_calc_sync_sample_box_total_size(ISO_SYNC_SAMPLE_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Sync Sample Box
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
 *   entry_count
 */
int32 mp4_sync_sample_box_mux(ISO_SYNC_SAMPLE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Free Space Box
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
int32 mp4_free_space_box_mux(ISO_FREE_SPACE_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_movie_extend_box_mux(ISO_MOVIE_EXTEND_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_movie_extend_header_box_mux(ISO_MOVIE_EXTEND_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_track_extend_box_mux(ISO_TRACK_EXTEND_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_movie_fragment_box_mux(ISO_MOVIE_FRAGMENT_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_movie_fragment_header_box_mux(ISO_MOVIE_FRAGMENT_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_track_fragment_box_mux(ISO_TRACK_FRAGMENT_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Fragment Header Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   full_box.version_flag
 */
int32 mp4_calc_track_fragment_header_box_size(ISO_TRACK_FRAGMENT_HEADER_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   full_box.version_flag
 *   track_id
 *   base_data_offset
 *   sample_desc_index
 *   def_sample_duration
 *   def_sample_size
 *   def_sample_flag
 */
int32 mp4_track_fragment_header_box_mux(ISO_TRACK_FRAGMENT_HEADER_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Fragment Run Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   full_box.version_flag
 *   sample_count
 */
int32 mp4_calc_track_fragment_run_box_size(ISO_TRACK_FRAGMENT_RUN_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
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
int32 mp4_track_fragment_run_box_mux(ISO_TRACK_FRAGMENT_RUN_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_movie_fragment_random_access_box_mux(ISO_MOVIE_FRAGMENT_RANDOM_ACCESS_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Track Fragment Random Access Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   mixture
 *   entry_num
 *   p_entry
 */
int32 mp4_calc_track_fragment_random_access_box_size(ISO_TRACK_FRAGMENT_RANDOM_ACCESS_BOX *p_box, uint32 *p_size);

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
int32 mp4_track_fragment_random_access_box_mux(ISO_TRACK_FRAGMENT_RANDOM_ACCESS_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

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
int32 mp4_movie_fragment_random_access_offset_box_mux(ISO_MOVIE_FRAGMENT_RANDOM_ACCESS_OFFSET_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);

/**  
 * @brief ����Meta Box����
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1������������box���ȣ��������������ֳ���
 */
int32 mp4_calc_meta_box_size(ISO_META_BOX *p_box, uint32 *p_size);

/**  
 * @brief ����Meta Box�ܳ���
 * @param [in] p_box Box���
 * @param [out] p_size �ܳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -3������ȡֵ����
 * @remark
 * 1���ⲿ��д�ֶΰ�����
 *   handler_box.full_box.box.size
 *   handler_box.name_size
 *   ����name_size���������β��'\0'
 */
int32 mp4_calc_meta_box_total_size(ISO_META_BOX *p_box, uint32 *p_size);

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
 *   full_box.box.size
 *   handler_box
 *   ����handler_box��Ӧ�ֶ�ҲҪ��д������
 *   full_box.box.size
 *   handler_type
 *   p_name
 *   name_size
 *   ����name_size���������β��'\0'
 */
int32 mp4_meta_box_mux(ISO_META_BOX *p_box, uint8 *p_buf, int32 *p_buf_size);


#ifdef __cplusplus
}
#endif

#endif ///__MP4_MUX_H__
