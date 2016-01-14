/**
 * @file gen_multimultimap.h  �ظ�������
 *
 * Copyright (C) 2007-2012 ������ͨ��Ϣ�������޹�˾�����з��� 
 * 
 *
 * @author ���� <wengyan@bqvision.com>
 * @version 0.1
 * @date 2011.04.19
 *
 *
 */

#ifndef __GEN_MULTIMAP_H__
#define __GEN_MULTIMAP_H__

#include "../public/gen_int.h"
#include "../public/gen_key.h"
#include "../public/gen_allocator.h"
#include "../public/gen_comparer.h"


/** �� */
#define GEN_MULTIMAP_COLOR_RED                             (0)
/** �� */
#define GEN_MULTIMAP_COLOR_BLACK                           (1)

/** multimap�ڵ� */
typedef struct tag_multimap_node
{
	/** ��ɫ */
	int32  color;

	/** key pair */
	KEY_PAIR pair;

	/** ���ڵ� */
	struct tag_multimap_node *p_parent;
	/** ���ӽڵ� */
	struct tag_multimap_node *p_left;
	/** ���ӽڵ� */
	struct tag_multimap_node *p_right;

	/** ǰһ���нڵ� */
	struct tag_multimap_node *p_prev_seq;
	/** ��һ���нڵ� */
	struct tag_multimap_node *p_next_seq;

} MULTIMAP_NODE, *PMULTIMAP_NODE;

/** multimap */
typedef struct tag_gen_multimap
{
	/** allocator */
	GEN_ALLOCATOR allocator;
	/** comparer */
	GEN_COMPARER  comparer;

	/** �Ƿ��ʼ�� */
	int32  b_init;
	/** multimap���� */
	int32  multimap_size;
	/** �Ƿ������� */
	int32  b_descend;

	/** ���ڵ� */
	MULTIMAP_NODE* p_root;

	/** ����ͷ�ڵ�ָ�� */
	MULTIMAP_NODE* p_head;
	/** ����β�ڵ�ָ�� */
	MULTIMAP_NODE* p_rear;
	/** ����ͷ�ڵ� */
	MULTIMAP_NODE  head;
	/** ����β�ڵ� */
	MULTIMAP_NODE  rear;

} GEN_MULTIMAP, *PGEN_MULTIMAP;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����multimap
 * @param [in] p_allocator ���������
 * @param [in] p_comparer �Ƚ������
 * @return
 * �ǿ�ֵ���ɹ�������ֵ��ʾ��Ӧ��multimap���
 * NULL��ʧ��
 * @remark
 * 1������ıȽ����������Ϊ��!
 * 2��������������Ϊ�գ���ʹ��Ĭ�Ϸ�����(malloc)
 * 3��multimap��ʵ�ֻ��ں����
 */
GEN_MULTIMAP* gen_multimap_create(GEN_ALLOCATOR* p_allocator, GEN_COMPARER* p_comparer);

/**  
 * @brief ����multimap
 * @param [in] p_multimap multimap���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multimap_destroy(GEN_MULTIMAP* p_multimap);

/**  
 * @brief ��ʼ��multimap
 * @param [in] p_multimap multimap���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multimap_init(GEN_MULTIMAP* p_multimap);

/**  
 * @brief ����ʼ��multimap
 * @param [in] p_multimap multimap���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multimap_deinit(GEN_MULTIMAP* p_multimap);

/**  
 * @brief ���multimap
 * @param [in] p_multimap multimap���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multimap_clear(GEN_MULTIMAP* p_multimap);

/**  
 * @brief ��ȡmultimap����
 * @param [in] p_multimap multimap���
 * @return
 * �Ǹ�ֵ���ɹ�������ֵ��ʾmultimap����
 * -1��ʧ��
 */
int32 gen_multimap_get_size(GEN_MULTIMAP* p_multimap);

/**  
 * @brief ����multimap����˳��
 * @param [in] p_multimap multimap���
 * @param [in] b_descend �Ƿ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1����ʼ����Ĭ��Ϊ��������
 */
int32 gen_multimap_set_order(GEN_MULTIMAP* p_multimap, int32 b_descend);

/**  
 * @brief ���ҽڵ�
 * @param [in] p_multimap multimap���
 * @param [in] p_key �ڵ�ؼ���
 * @param [out] pp_node �ڵ��ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 * @remark
 * 1���ýӿڷ����ҵ��ĵ�һ��ƥ��ڵ�
 */
int32 gen_multimap_find_node(GEN_MULTIMAP* p_multimap, void* p_key, MULTIMAP_NODE** pp_node);

/**  
 * @brief ����key pair
 * @param [in] p_multimap multimap���
 * @param [in] p_pair key pair
 * @param [out] pp_node �ڵ��ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���ڴ治��
 * @remark
 * 1��pp_node����Ϊ�գ���ʾ����Ҫ��ö�Ӧ�Ľڵ�
 */
int32 gen_multimap_insert_pair(GEN_MULTIMAP* p_multimap, KEY_PAIR* p_pair, MULTIMAP_NODE** pp_node);

/**  
 * @brief ɾ���ڵ�
 * @param [in] p_multimap multimap���
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multimap_delete_node(GEN_MULTIMAP* p_multimap, MULTIMAP_NODE* p_node);

/**  
 * @brief ɾ��ָ���ؼ���
 * @param [in] p_multimap multimap���
 * @param [in] p_key �ؼ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 */
int32 gen_multimap_delete_key(GEN_MULTIMAP* p_multimap, void* p_key);

/**  
 * @brief ɾ�����з�������ָ���ؼ���
 * @param [in] p_multimap multimap���
 * @param [in] p_key �ؼ���
 * @param [out] p_count ʵ��ɾ������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��p_count����Ϊ��
 */
int32 gen_multimap_delete_all_key(GEN_MULTIMAP* p_multimap, void* p_key, int32* p_count);


#ifdef __cplusplus
}
#endif


#endif ///__GEN_MULTIMAP_H__
