/**
 * @file mp4_live_writer.h   MP4 Live Writer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.07.28
 *
 *
 */

#ifndef __MP4_LIVE_WRITER_H__
#define __MP4_LIVE_WRITER_H__

//#ifndef VC_EXTRALEAN
//#define VC_EXTRALEAN
//#endif

#include <windows.h>

#include <public/gen_int.h>
#include <public/gen_deque.h>
#include <public/media_def.h>
#include "../iso/iso_media_file.h"


/** max track num */
#define MP4_LIVE_WRITER_MAX_TRACK_NUM                      (2)
/** max path size */
#define MP4_LIVE_WRITER_MAX_PATH_SIZE                      (512)



class CMp4LiveWriter
{
public:

	CMp4LiveWriter();
	~CMp4LiveWriter();

	int32 Init();
	int32 Deinit();
	int32 Reset();
	int32 EnableVideo(int32 b_enable);
	int32 EnableAudio(int32 b_enable);
	int32 SetTimescale(uint32 time_scale);
	int32 SetForceSync(int32 b_force_sync);
	int32 Start(int8 *p_file_path, int32 file_path_size);
	int32 Stop();
	int32 InputFrame(MEDIA_FRAME *p_frame);

	int32 Resync();
	int32 SetAvcDecConfig(uint8* p_buf, int32 p_buf_size);

	int32 WriteFileTypeBox();
	int32 WriteMovieBox();
	int32 WriteFragment();
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
	/** force sync */
	int32  m_bForceSync;

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
	int32  m_Track[MP4_LIVE_WRITER_MAX_TRACK_NUM];

	/** ��Ƶ���� */
	MEDIA_FRAME m_VideoFrame;
	/** ��Ƶ���� */
	MEDIA_FRAME m_AudioFrame;

	/** gop */
	int32  m_bGop;
	/** gop count */
	uint32 m_GopCount;
	/** write gop count */
	uint32 m_WriteGopCount;
	/** total gop count */
	uint32 m_TotalGopCount;
	/** last gop ts, unit: ms */
	uint64 m_LastGopTs;

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
	/** ��Ƶ��ʱ��, unit: scale */
	uint64 m_TotalVideoElapseTime;
	/** ��Ƶ��ʱ��, unit: ms */
	uint64 m_TotalVideoElapseTimeMs;

	/** ��Ƶfourcc */
	uint32 m_AudioFourcc;
	/** ��Ƶ֡�� */
	int32  m_AudioFrameCount;
	/** ��Ƶ��ʱ�� */
	uint64 m_TotalAudioElapseTime;
	/** ��Ƶ��ʱ��, unit: ms */
	uint64 m_TotalAudioElapseTimeMs;
	/** ��Ƶÿ֡������ */
	int32  m_AudioSamplePerFrame;
	/** ��Ƶ֡�ܲ����� */
	uint64 m_TotalAudioSampleCount;
	/** ��Ƶ֡�ܲ�������ʱ��, unit: timescale */
	uint64 m_TotalAudioSampleDuration;


	/** д�뻺���� */
	uint8* m_pWriteBuf;
	/** д�뻺������С */
	int32  m_WriteBufSize;
	/** д�뻺������ʹ�ô�С */
	int32  m_WriteBufUseSize;
	/** д�뻺����δʹ�ô�С */
	int32  m_WriteBufLeftSize;

	/** video buf */
	uint8*  m_pVideoBuf;
	/** video buf size */
	uint32  m_VideoBufSize;
	/** video buf use size */
	uint32  m_VideoBufUseSize;
	/** video buf left size */
	uint32  m_VideoBufLeftSize;

	/** video deque */
	GEN_DEQUE* m_pVideoDeque;
	/** video deque total size */
	int32   m_VideoDequeTotalSize;

	/** video sample size entry */
	ISO_TRACK_FRAGMENT_SAMPLE* m_pVideoSizeEntry;
	/** video sample size entry count */
	int32   m_VideoSizeEntryCount;

	/** audio buf */
	uint8*  m_pAudioBuf;
	/** audio buf size */
	uint32  m_AudioBufSize;
	/** audio buf use size */
	uint32  m_AudioBufUseSize;
	/** audio buf left size */
	uint32  m_AudioBufLeftSize;

	/** audio deque */
	GEN_DEQUE* m_pAudioDeque;
	/** audio deque total size */
	int32   m_AudioDequeTotalSize;

	/** audio sample size entry */
	ISO_TRACK_FRAGMENT_SAMPLE* m_pAudioSizeEntry;
	/** audio sample size entry count */
	int32   m_AudioSizeEntryCount;

	/** file count */
	uint32 m_FileCount;
	/** file dir path */
	int8   m_FileDirPath[MP4_LIVE_WRITER_MAX_PATH_SIZE];
	/** file handle */
	HANDLE m_hFile;
	/** total write size */
	uint32 m_TotalWriteSize;

};

#endif ///__MP4_LIVE_WRITER_H__
