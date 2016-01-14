/**
 * @file rtp_const.h   RTP Constant
 * @author Robert Weng <robert_3000@sina.com>
 * @version 0.1
 * @date 2010.02.25
 *
 *
 */

#ifndef __RTP_CONST_H__
#define __RTP_CONST_H__

/** RTP�汾 */
#define RTP_VERSION                                (2)
/** ����غ��������� */
#define RTP_MAX_PAYLOAD_TYPE                       (127)
/** ���CSRC���� */
#define RTP_MAX_CSRC_NUM                           (15)
/** CSRC���ݳ��ȼ��㵥λ */
#define RTP_CSRC_SIZE                              (4)
/** RTPͷ���ȣ���λ���ֽ� */
#define RTP_HEADER_SIZE                            (12)
/** RTP��չͷ���ȣ���λ���ֽ� */
#define RTP_EXT_HEADER_SIZE                        (8)

/** G711U */
#define RTP_PT_G711U                               (0)
/** G711A */
#define RTP_PT_G711A                               (8)
/** G722 */
#define RTP_PT_G722                                (9)
/** MPEG Audio */
#define RTP_PT_MPEG_AUDIO                          (14)
/** MPEG Video */
#define RTP_PT_MPEG_VIDEO                          (32)
/** MPEG2 TS */
#define RTP_PT_MPEG2_TS                            (33)

/** RTCP���ݳ��ȼ��㵥λ */
#define RTCP_BASE_UNIT                             (4)
/** ���SSRC���� */
#define RTCP_MAX_SSRC_NUM                          (32)
/** ���item���� */
#define RTCP_MAX_ITEM                              (8)

/** sender report */
#define RTCP_PT_SR                                 (200)
/** receiver report */
#define RTCP_PT_RR                                 (201)
/** sdes */
#define RTCP_PT_SDES                               (202)
/** bye */
#define RTCP_PT_BYE                                (203)
/** app */
#define RTCP_PT_APP                                (204)

/** end */
#define RTCP_SDES_END                              (0)
/** cname */
#define RTCP_SDES_CNAME                            (1)
/** name */
#define RTCP_SDES_NAME                             (2)
/** email */
#define RTCP_SDES_EMAIL                            (3)
/** phone */
#define RTCP_SDES_PHONE                            (4)
/** location */
#define RTCP_SDES_LOC                              (5)
/** tool */
#define RTCP_SDES_TOOL                             (6)
/** note */
#define RTCP_SDES_NOTE                             (7)

/** �ɹ� */
//#define RTP_SUCCESS                                (0)
/** һ����� */
//#define RTP_ERR_NORMAL                             (-1)
/** ������Ч */
//#define RTP_ERR_INVALID_PARAM                      (-2)
/** �ڴ����ʧ�� */
//#define RTP_ERR_NO_MEM                             (-3)
/** ���������Ȳ��� */
//#define RTP_ERR_NO_ENOUGH_BUF                      (-4)
/** PTֵ���� */
//#define RTP_ERR_PT_NOT_FOUND                       (-5)
/** RTP��ͷ��ʽ���� */
//#define RTP_ERR_INVALID_FORMAT                     (-6)


#endif ///__RTP_CONST_H__
