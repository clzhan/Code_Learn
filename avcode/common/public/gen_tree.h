/**
 * @file gen_tree.h  Tree
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2010.04.27
 *
 *
 */

#ifndef __GEN_TREE_H__
#define __GEN_TREE_H__

#include <public/gen_int.h>

/** ���ڵ� */
typedef struct tag_tree_node
{
	/** �Ƿ��ڲ��ڵ� */
	int32  b_inner;
	/** �ڵ�Ķ�(�ӽڵ���) */
	int32  degree;

	/** ���ڵ� */
	struct tag_tree_node *p_parent;
	/** ǰһ���ֵܽڵ� */
	struct tag_tree_node *p_prev;
	/** ��һ���ֵܽڵ� */
	struct tag_tree_node *p_next;
	/** ��һ���ӽڵ� */
	struct tag_tree_node *p_first_child;
	/** ���һ���ӽڵ� */
	struct tag_tree_node *p_last_child;

	/** �ڵ����� */
	void*  p_data;

} TREE_NODE, *PTREE_NODE;

/** �� */
typedef struct tag_gen_tree
{
	/** �Ƿ��ʼ�� */
	int32     b_init;
	/** ���ڵ���� */
	int32     tree_node_num;
	/** ����� */
	int32     tree_depth;

	/** ���ڵ� */
	TREE_NODE *p_root;

} GEN_TREE, *PGEN_TREE;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ������
 * @return
 * �ǿ�ֵ���ɹ�������ֵ��ʾ�����
 * NULL��ʧ��
 */
GEN_TREE* gen_tree_create();

/**  
 * @brief ������
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1�������ڲ�����Ľڵ�ᱻ�ڲ��ͷţ��ⲿ����Ľڵ���Ҫ�ⲿ���д����м�!
 */
int32 gen_tree_destroy(GEN_TREE *p_tree);

/**  
 * @brief ��ʼ����
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_tree_init(GEN_TREE *p_tree);

/**  
 * @brief ����ʼ����
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_tree_deinit(GEN_TREE *p_tree);

/**  
 * @brief �����
 * @param [in] p_tree �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1�������ڲ�����Ľڵ�ᱻ�ڲ��ͷţ��ⲿ����Ľڵ���Ҫ�ⲿ���д����м�!
 */
int32 gen_tree_clear(GEN_TREE *p_tree);

/**  
 * @brief ��ȡ���ڵ����
 * @param [in] p_tree �����
 * @return
 * �Ǹ�ֵ���ɹ�
 * -1��ʧ��
 */
int32 gen_tree_get_node_num(GEN_TREE *p_tree);

/**  
 * @brief ��ȡ�����
 * @param [in] p_tree �����
 * @return
 * �Ǹ�ֵ���ɹ�
 * -1��ʧ��
 */
int32 gen_tree_get_depth(GEN_TREE *p_tree);

/**  
 * @brief ����ӽڵ�
 * @param [in] p_tree �����
 * @param [in] p_parent ���ڵ���
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1����ӵĽڵ������ⲿ�ڵ�
 */
int32 gen_tree_add_node(GEN_TREE *p_tree, TREE_NODE *p_parent, TREE_NODE *p_node);

/**  
 * @brief ��ӽڵ�����
 * @param [in] p_tree �����
 * @param [in] p_parent ���ڵ���
 * @param [out] pp_node �ڵ��ַ
 * @param [in] p_data �ڵ�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_tree_add_data(GEN_TREE *p_tree, TREE_NODE *p_parent, TREE_NODE **pp_node, void *p_data);

/**  
 * @brief ɾ���ڵ�
 * @param [in] p_tree �����
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_tree_delete_node(GEN_TREE *p_tree, TREE_NODE *p_node);


#ifdef __cplusplus
}
#endif


#endif ///__GEN_TREE_H__
