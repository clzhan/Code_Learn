/**
 * @file net_sock.h  Net Sock
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2011.06.10
 *
 *
 */


#ifndef __NET_SOCK_H__
#define __NET_SOCK_H__

#include <public/gen_int.h>
#include "network_public.h"

/** ��Ч */
#define NET_SOCK_TYPE_INVALID                              (0)
/** TCP */
#define NET_SOCK_TYPE_TCP                                  (1)
/** UDP */
#define NET_SOCK_TYPE_UDP                                  (2)
/** SCTP */
#define NET_SOCK_TYPE_SCTP                                 (3)


#ifdef __cplusplus
extern "C"
{
#endif

/** 
 * @brief ��sock
 * @param [in/out] p_sock sock���
 * @param [in] type sock����
 * @param [in] b_block �Ƿ�����
 * @return
 * 0�� �ɹ�
 * -1��ʧ��
 * @remark
 * 1����������˵����p_sock��addr�ֶθ�������Ϊ�����ֽ��򣬷���ʱp_sock��sock�ֶα���򿪵�socket
 * 2��addr�ֶε�local_addr��ʾҪ�󶨵�IP��local_port��ʾҪ�󶨵Ķ˿ڣ��˿�Ϊ0��ʾ����
 */
int32 net_sock_open(NET_SOCK* p_sock, int32 type, int32 b_block);

/** 
 * @brief �ر�sock
 * @param [in] p_sock sock���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 net_sock_close(NET_SOCK* p_sock);

/** 
 * @brief �����鲥��
 * @param [in] p_sock sock���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 net_sock_join_group(NET_SOCK* p_sock);

/** 
 * @brief �˳��鲥��
 * @param [in] p_sock sock���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 net_sock_leave_group(NET_SOCK* p_sock);

/** 
 * @brief ����Դ�ض��鲥��
 * @param [in] p_sock sock���
 * @param [in] src_ip �鲥��ԴIP�������ֽ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
//int32 net_sock_join_src_group(NET_SOCK* p_sock, uint32 src_ip);

/** 
 * @brief �˳�Դ�ض��鲥��
 * @param [in] p_sock sock���
 * @param [in] src_ip �鲥��ԴIP�������ֽ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
//int32 net_sock_leave_src_group(NET_SOCK* p_sock, uint32 src_ip);

/** 
 * @brief ����
 * @param [in] p_sock sock���
 * @param [in] max_connect ���������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1������ǰ�����Ȱ󶨵�һ��ָ���Ķ˿�
 */
int32 net_sock_listen(NET_SOCK* p_sock, int32 max_connect);

/** 
 * @brief ��������
 * @param [in] p_sock sock���
 * @param [in] p_accept ���ӷ����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1����������ǰ�����ȼ���
 */
int32 net_sock_accept(NET_SOCK* p_sock, NET_SOCK* p_accept);

/** 
 * @brief ����Զ�̵�ַ
 * @param [in] p_sock sock���
 * @param [out] p_error_code ��������ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 net_sock_connect(NET_SOCK* p_sock, int32* p_error_code);


#ifdef __cplusplus
}
#endif

#endif ///__NET_SOCK_H__
