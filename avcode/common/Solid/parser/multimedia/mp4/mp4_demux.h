/**
 * @file mp4_demux.h   MP4 Demux
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.05.19
 *
 *
 */


#ifndef __MP4_DEMUX_H__
#define __MP4_DEMUX_H__

#include <public/gen_int.h>
#include "mp4_demux_public.h"


#ifdef __cplusplus
extern "C"
{
#endif


/**  
 * @brief demux box
 * @param [out] p_box, box
 * @param [in] p_data, input data
 * @param [in] data_size, input data size
 * @param [out] p_demux_size, actual demux size
 * @return
 * 0: success
 * -1: invalid param
 * -2: input data not enough
 * -3: invalid value
 * @remark
 * 1��actual demux size is always update whether demux success or not
 */
int32 mp4_demux_box(MP4_BOX* p_box, uint8* p_data, uint32 data_size, uint32* p_demux_size);

/**  
 * @brief demux full box
 * @param [out] p_box, box
 * @param [in] p_data, input data
 * @param [in] data_size, input data size
 * @param [out] p_demux_size, actual demux size
 * @return
 * 0: success
 * -1: invalid param
 * -2: input data not enough
 * -3: invalid value
 * @remark
 */
int32 mp4_demux_full_box(MP4_BOX* p_box, uint8* p_data, uint32 data_size, uint32* p_demux_size);

/**  
 * @brief ����Movie Header Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_movie_header_box(ISO_MOVIE_HEADER_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Track Header Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_track_header_box(ISO_TRACK_HEADER_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Media Header Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_media_header_box(ISO_MEDIA_HEADER_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Handler Reference Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_handler_box(ISO_HANDLER_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Visual Sample Desc Box
 * @param [in/out] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ����Խ���
 * -3������ȡֵ����
 * -4��p_entry���Ȳ���
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 * 2��p_box�������ֶ����ⲿ��д
 *    entry_count
 *    p_entry
 *    �ڷ���ʱentry_count����Ϊʵ�ʵĸ���
 */
int32 mp4_demux_visual_sample_desc_box(ISO_VISUAL_SAMPLE_DESC_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Audio Sample Desc Box
 * @param [in/out] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ����Խ���
 * -3������ȡֵ����
 * -4��p_entry���Ȳ���
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 * 2��p_box�������ֶ����ⲿ��д
 *    entry_count
 *    p_entry
 *    �ڷ���ʱentry_count����Ϊʵ�ʵĸ���
 */
int32 mp4_demux_audio_sample_desc_box(ISO_AUDIO_SAMPLE_DESC_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief demux stts box
 * @param [in] p_box, box
 * @param [in] p_buf, input data
 * @param [in] buf_size, input data size
 * @param [out] p_demux_size, actual demux size
 * @return
 * 0: success
 * -1: invalid param
 * -2: input data not enough to demux
 * -3: wrong param
 * @remark
 */
int32 mp4_demux_time_to_sample_box(ISO_TIME_TO_SAMPLE_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief demux ctts box
 * @param [in] p_box, box
 * @param [in] p_buf, input data
 * @param [in] buf_size, input data size
 * @param [out] p_demux_size, actual demux size
 * @return
 * 0: success
 * -1: invalid param
 * -2: input data not enough to demux
 * -3: wrong param
 * @remark
 */
int32 mp4_demux_comp_time_to_sample_box(ISO_COMP_TIME_TO_SAMPLE_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Sample Size Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ����Խ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_sample_size_box(ISO_SAMPLE_SIZE_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Sample to Chunk Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ����Խ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_sample_to_chunk_box(ISO_SAMPLE_TO_CHUNK_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Chunk Offset Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ����Խ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_chunk_offset_box(ISO_CHUNK_OFFSET_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);

/**  
 * @brief ����Sync Sample Box
 * @param [in] p_box Box���
 * @param [in] p_buf ���ݵ�ַ
 * @param [in] buf_size ���ݳ���
 * @param [out] p_demux_size ʵ�ʽ�������
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����������Ȳ����Խ���
 * -3������ȡֵ����
 * @remark
 * 1�����۽����ɹ���񣬾������ʵ�ʽ�������
 */
int32 mp4_demux_sync_sample_box(ISO_SYNC_SAMPLE_BOX *p_box, uint8* p_buf, uint32 buf_size, uint32* p_demux_size);


#ifdef __cplusplus
}
#endif

#endif ///__MP4_DEMUX_H__
