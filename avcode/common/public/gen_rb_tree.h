/**
 * @file gen_rb_tree.h  Red Black Tree
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2010.06.09
 *
 *
 */

#ifndef __GEN_RB_TREE_H__
#define __GEN_RB_TREE_H__

#include <public/gen_int.h>
#include <public/gen_key.h>
#include <public/gen_allocator.h>
#include <public/gen_comparer.h>

/** �� */
#define GEN_RB_TREE_RED                                    (0)
/** �� */
#define GEN_RB_TREE_BLACK                                  (1)

/** ������ڵ� */
typedef struct tag_rb_tree_node
{
	/** ��ɫ */
	int32  color;

	/** �ڵ�߶� */
	int32  height;
	/** �������߶� */
	int32  left_height;
	/** �������߶� */
	int32  right_height;

	/** key pair */
	KEY_PAIR pair;

	/** ���ڵ� */
	struct tag_rb_tree_node *p_parent;
	/** ���ӽڵ� */
	struct tag_rb_tree_node *p_left;
	/** ���ӽڵ� */
	struct tag_rb_tree_node *p_right;

	/** ǰһ�ڵ� */
	struct tag_rb_tree_node *p_prev;
	/** ��һ�ڵ� */
	struct tag_rb_tree_node *p_next;

} RB_TREE_NODE, *PRB_TREE_NODE;

/** ����� */
typedef struct tag_gen_rb_tree
{
	/** allocator */
	GEN_ALLOCATOR allocator;
	/** comparer */
	GEN_COMPARER  comparer;

	/** �Ƿ��ʼ�� */
	int32  b_init;
	/** �ڵ���� */
	int32  node_num;

	/** ���ڵ� */
	RB_TREE_NODE* p_root;

	/** ͷ�ڵ�ָ�� */
	RB_TREE_NODE* p_head;
	/** β�ڵ�ָ�� */
	RB_TREE_NODE* p_rear;
	/** ͷ�ڵ� */
	RB_TREE_NODE  head;
	/** β�ڵ� */
	RB_TREE_NODE  rear;

} GEN_RB_TREE, *PGEN_RB_TREE;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ���������
 * @param [in] p_allocator ���������
 * @param [in] p_comparer �Ƚ������
 * @return
 * �ǿ�ֵ���ɹ�������ֵ��ʾ��Ӧ�������
 * NULL��ʧ��
 * @remark
 * 1������ıȽ����������Ϊ��!
 */
GEN_RB_TREE* gen_rb_tree_create(GEN_ALLOCATOR* p_allocator, GEN_COMPARER* p_comparer);

/**  
 * @brief ���ٺ����
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_rb_tree_destroy(GEN_RB_TREE* p_tree);

/**  
 * @brief ��ʼ����
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_rb_tree_init(GEN_RB_TREE* p_tree);

/**  
 * @brief ����ʼ����
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_rb_tree_deinit(GEN_RB_TREE* p_tree);

/**  
 * @brief �����
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_rb_tree_clear(GEN_RB_TREE* p_tree);

/**  
 * @brief ��ȡ���ڵ����
 * @param [in] p_tree �����
 * @return
 * �Ǹ�ֵ���ɹ�������ֵ��ʾ�ڵ����
 * -1��ʧ��
 */
int32 gen_rb_tree_get_node_num(GEN_RB_TREE* p_tree);

/**  
 * @brief ��ȡ���߶�
 * @param [in] p_tree �����
 * @return
 * �Ǹ�ֵ���ɹ�
 * -1��ʧ��
 */
int32 gen_rb_tree_get_height(GEN_RB_TREE* p_tree);

/**  
 * @brief ���ҽڵ�
 * @param [in] p_tree �����
 * @param [in] p_key �ڵ�ؼ���
 * @param [out] pp_node �ڵ��ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 */
int32 gen_rb_tree_find_node(GEN_RB_TREE* p_tree, void* p_key, RB_TREE_NODE** pp_node);

/**  
 * @brief ����key pair
 * @param [in] p_tree �����
 * @param [in] p_pair key pair
 * @param [out] pp_node �ڵ��ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���ڴ治��
 * -3���ڵ��Ѵ���
 * @remark
 * 1��pp_node����Ϊ�գ���ʾ����Ҫ��ö�Ӧ�Ľڵ�
 */
int32 gen_rb_tree_insert_pair(GEN_RB_TREE* p_tree, KEY_PAIR* p_pair, RB_TREE_NODE** pp_node);

/**  
 * @brief ɾ���ڵ�
 * @param [in] p_tree �����
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_rb_tree_delete_node(GEN_RB_TREE* p_tree, RB_TREE_NODE* p_node);

/**  
 * @brief ɾ����Ӧ�ؼ��ֵĽڵ�
 * @param [in] p_tree �����
 * @param [in] p_key �ؼ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 */
int32 gen_rb_tree_delete_key(GEN_RB_TREE* p_tree, void* p_key);

#ifdef __cplusplus
}
#endif


#endif ///__GEN_RB_TREE_H__
