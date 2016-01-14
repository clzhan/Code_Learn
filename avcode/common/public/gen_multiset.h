/**
 * @file gen_multimultiset.h  �ظ�������
 *
 * Copyright (C) 2007-2012 ������ͨ��Ϣ�������޹�˾�����з��� 
 * 
 *
 * @author ���� <wengyan@bqvision.com>
 * @version 0.1
 * @date 2011.04.20
 *
 *
 */

#ifndef __GEN_MULTISET_H__
#define __GEN_MULTISET_H__

#include "../public/gen_int.h"
#include "../public/gen_allocator.h"
#include "../public/gen_comparer.h"


/** �� */
#define GEN_MULTISET_COLOR_RED                             (0)
/** �� */
#define GEN_MULTISET_COLOR_BLACK                           (1)

/** multiset�ڵ� */
typedef struct tag_multiset_node
{
	/** ��ɫ */
	int32  color;

	/** key */
	void*  p_key;

	/** ���ڵ� */
	struct tag_multiset_node *p_parent;
	/** ���ӽڵ� */
	struct tag_multiset_node *p_left;
	/** ���ӽڵ� */
	struct tag_multiset_node *p_right;

	/** ǰһ���нڵ� */
	struct tag_multiset_node *p_prev_seq;
	/** ��һ���нڵ� */
	struct tag_multiset_node *p_next_seq;

	/** �����ڵ���� */
	int32  twin_node_num;
	/** �Ƿ������ڵ� */
	int32  b_twin_node;
	/** ǰһ�����ڵ� */
	struct tag_multiset_node *p_prev_twin;
	/** ��һ�����ڵ� */
	struct tag_multiset_node *p_next_twin;
	/** ��һ�������ڵ� */
	struct tag_multiset_node *p_first_twin;
	/** ���һ�������ڵ� */
	struct tag_multiset_node *p_last_twin;

} MULTISET_NODE, *PMULTISET_NODE;

/** multiset */
typedef struct tag_gen_multiset
{
	/** allocator */
	GEN_ALLOCATOR allocator;
	/** comparer */
	GEN_COMPARER  comparer;

	/** �Ƿ��ʼ�� */
	int32  b_init;
	/** multiset���� */
	int32  multiset_size;
	/** �Ƿ������� */
	int32  b_descend;

	/** ���ڵ� */
	MULTISET_NODE* p_root;

	/** ����ͷ�ڵ�ָ�� */
	MULTISET_NODE* p_head;
	/** ����β�ڵ�ָ�� */
	MULTISET_NODE* p_rear;
	/** ����ͷ�ڵ� */
	MULTISET_NODE  head;
	/** ����β�ڵ� */
	MULTISET_NODE  rear;

} GEN_MULTISET, *PGEN_MULTISET;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����multiset
 * @param [in] p_allocator ���������
 * @param [in] p_comparer �Ƚ������
 * @return
 * �ǿ�ֵ���ɹ�������ֵ��ʾ��Ӧ��multiset���
 * NULL��ʧ��
 * @remark
 * 1������ıȽ����������Ϊ��!
 * 2��������������Ϊ�գ���ʹ��Ĭ�Ϸ�����(malloc)
 * 3��multiset��ʵ�ֻ��ں����
 */
GEN_MULTISET* gen_multiset_create(GEN_ALLOCATOR* p_allocator, GEN_COMPARER* p_comparer);

/**  
 * @brief ����multiset
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multiset_destroy(GEN_MULTISET* p_multiset);

/**  
 * @brief ��ʼ��multiset
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multiset_init(GEN_MULTISET* p_multiset);

/**  
 * @brief ����ʼ��multiset
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multiset_deinit(GEN_MULTISET* p_multiset);

/**  
 * @brief ���multiset
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multiset_clear(GEN_MULTISET* p_multiset);

/**  
 * @brief ��ȡmultiset����
 * @param [in] p_multiset multiset���
 * @return
 * �Ǹ�ֵ���ɹ�������ֵ��ʾmultiset����
 * -1��ʧ��
 */
int32 gen_multiset_get_size(GEN_MULTISET* p_multiset);

/**  
 * @brief ����multiset����˳��
 * @param [in] p_multiset multiset���
 * @param [in] b_descend �Ƿ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1����ʼ����Ĭ��Ϊ��������
 */
int32 gen_multiset_set_order(GEN_MULTISET* p_multiset, int32 b_descend);

/**  
 * @brief ���ҽڵ�
 * @param [in] p_multiset multiset���
 * @param [in] p_key �ڵ�ؼ���
 * @param [out] pp_node �ڵ��ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 */
int32 gen_multiset_find_node(GEN_MULTISET* p_multiset, void* p_key, MULTISET_NODE** pp_node);

/**  
 * @brief ����key
 * @param [in] p_multiset multiset���
 * @param [in] p_key key
 * @param [out] pp_node �ڵ��ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���ڴ治��
 * -3���ڵ��Ѵ���
 * @remark
 * 1��pp_node����Ϊ�գ���ʾ����Ҫ��ö�Ӧ�Ľڵ�
 */
int32 gen_multiset_insert_key(GEN_MULTISET* p_multiset, void* p_key, MULTISET_NODE** pp_node);

/**  
 * @brief ɾ���ڵ�
 * @param [in] p_multiset multiset���
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_multiset_delete_node(GEN_MULTISET* p_multiset, MULTISET_NODE* p_node);

/**  
 * @brief ɾ���ؼ���
 * @param [in] p_multiset multiset���
 * @param [in] p_key �ؼ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 */
int32 gen_multiset_delete_key(GEN_MULTISET* p_multiset, void* p_key);

#ifdef __cplusplus
}
#endif


#endif ///__GEN_MULTISET_H__
