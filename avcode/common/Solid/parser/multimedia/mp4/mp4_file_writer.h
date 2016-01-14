/**
 * @file mp4_file_writer.h   MP4 File Writer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.05.12
 *
 *
 */

#ifndef __MP4_FILE_WRITER_H__
#define __MP4_FILE_WRITER_H__

#include <public/gen_int.h>
#include <public/media_def.h>
#include <public/gen_file.h>
#include "../iso/iso_media_file.h"

#include "../include/IMultiMediaFileWriter.h"

/** ���Track���� */
#define MP4_FILE_WRITER_MAX_TRACK_NUM                      (2)


class CMp4FileWriter : public IMultiMediaFileWriter
{
public:

	CMp4FileWriter();
	~CMp4FileWriter();

	int32 Init();
	int32 Deinit();
	int32 Reset();
	int32 EnableVideo(int32 b_enable);
	int32 EnableAudio(int32 b_enable);
	int32 SetTimescale(uint32 time_scale);
	//int32 SetVideoFps(int32 fps);
	//int32 SetAudioFrameTs(int32 frame_ts);
	int32 Start(int8 *p_file_path, int32 file_path_size);
	int32 Stop();
	int32 InputFrame(MEDIA_FRAME *p_frame);

	int32 SetAvcDecConfig(uint8* p_buf, int32 p_buf_size);

	int32 WriteFileTypeBox();
	int32 WriteMovieBox();
	int32 MakeAudioDecSpecInfo(uint8* p_buf, int32* p_buf_size);

	/** ��ʼ����־ */
	int32  m_bInit;
	/** �ڲ������� */
	void*  m_Muxer;

	/** �Ƿ�ʹ����Ƶ */
	int32  m_bEnableVideo;
	/** �Ƿ�ʹ����Ƶ */
	int32  m_bEnableAudio;

	/** timescale */
	uint32 m_TimeScale;

	/** �Ƿ�ʼ */
	int32  m_bStart;
	/** �Ƿ���I֡ */
	int32  m_bFindKeyFrame;
	/** first video frame */
	int32  m_bFirstVideoFrame;
	/** first audio frame */
	int32  m_bFirstAudioFrame;
	/** first fragment */
	int32  m_bFirstFragment;
	/** write movie box */
	int32  m_bWriteMovieBox;

	/** �Ƿ�����Ƶ */
	int32  m_bHasVideo;
	/** �Ƿ�����Ƶ */
	int32  m_bHasAudio;
	/** Track���� */
	int32  m_TrackNum;
	/** Track�б� */
	int32  m_Track[MP4_FILE_WRITER_MAX_TRACK_NUM];

	/** ��Ƶ���� */
	MEDIA_FRAME m_VideoFrame;
	/** ��Ƶ���� */
	MEDIA_FRAME m_AudioFrame;

	/** get avc dec config */
	int32  m_bGetAvcDecConfig;
	/** avc dec config buf */
	uint8* m_pAvcDecConfigBuf;
	/** avc dec config buf size */
	int32  m_AvcDecConfigBufSize;
	/** avc dec config buf use size */
	int32  m_AvcDecConfigBufUseSize;

	/** profile */
	int32  m_Profile;
	/** profile compat */
	int32  m_ProfileCompat;
	/** level */
	int32  m_Level;

	/** get sps */
	int32  m_bGetSps;
	/** sps */
	uint8* m_pSPSBuf;
	/** sps buf size */
	int32  m_SPSBufSize;
	/** sps nalu size */
	int32  m_SPSNaluSize;

	/** get pps */
	int32  m_bGetPps;
	/** pps */
	uint8* m_pPPSBuf;
	/** pps buf size */
	int32  m_PPSBufSize;
	/** pps nalu size */
	int32  m_PPSNaluSize;

	/** ��Ƶfourcc */
	uint32 m_VideoFourcc;
	/** ��Ƶ֡�� */
	int32  m_VideoFrameCount;
	/** ��Ƶ��ʱ��, unit: timescale */
	int64  m_TotalVideoElapseTime;
	/** ��Ƶ��ʱ��, unit: ms */
	int64  m_TotalVideoElapseTimeMs;
	/** ��Ƶ֡�ۼƳ��� */
	uint32 m_TotalVideoFrameSize;

	/** ��Ƶfourcc */
	uint32 m_AudioFourcc;
	/** ��Ƶ֡�� */
	int32  m_AudioFrameCount;
	/** ��Ƶ��ʱ��, unit: timescale */
	int64  m_TotalAudioElapseTime;
	/** ��Ƶ��ʱ��, unit: ms */
	int64  m_TotalAudioElapseTimeMs;
	/** ��Ƶÿ֡������ */
	int32  m_AudioSamplePerFrame;
	/** ��Ƶ֡�ܲ����� */
	int64  m_TotalAudioSampleCount;
	/** ��Ƶ֡�ܲ�������ʱ��, unit: timescale */
	int64  m_TotalAudioSampleDuration;
	/** ��Ƶ֡�ۼƳ��� */
	uint32 m_TotalAudioFrameSize;
	/** ����֡�ۼƳ��� */
	uint32 m_TotalFrameSize;

	/** д�뻺���� */
	uint8* m_pWriteBuf;
	/** д�뻺������С */
	int32  m_WriteBufSize;
	/** д�뻺������ʹ�ô�С */
	int32  m_WriteBufUseSize;
	/** д�뻺����δʹ�ô�С */
	int32  m_WriteBufLeftSize;

	/** video time to sample entry */
	ISO_TIME_TO_SAMPLE_ENTRY* m_pVideoTimeEntry;
	/** video sample size entry */
	ISO_SAMPLE_SIZE_ENTRY* m_pVideoSizeEntry;
	/** video sample size entry count */
	//int32  m_VideoSizeEntryCount;
	/** video chunk offset entry */
	ISO_CHUNK_OFFSET_ENTRY* m_pVideoOffsetEntry;
	/** video chunk offset entry count */
	//int32  m_VideoOffsetEntryCount;
	/** video sync sample entry */
	ISO_SYNC_SAMPLE_ENTRY* m_pVideoSyncEntry;
	/** video sync sample entry count */
	int32  m_VideoSyncEntryCount;

	/** audio time to sample entry */
	ISO_TIME_TO_SAMPLE_ENTRY* m_pAudioTimeEntry;
	/** audio sample size entry */
	ISO_SAMPLE_SIZE_ENTRY* m_pAudioSizeEntry;
	/** audio sample size entry count */
	int32  m_AudioSizeEntryCount;
	/** audio chunk offset entry */
	ISO_CHUNK_OFFSET_ENTRY* m_pAudioOffsetEntry;
	/** audio chunk offset entry count */
	int32  m_AudioOffsetEntryCount;

	/** file */
	GEN_FILE_H m_hFile;
	/** total write size */
	uint32 m_TotalWriteSize;
	/** media data offset */
	uint32 m_MediaDataOffset;
	/** media data box size */
	uint32 m_MediaDataBoxSize;
};

#endif ///__MP4_FILE_WRITER_H__
