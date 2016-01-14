/**
 * @file gen_set.h  Set
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2010.06.22
 *
 *
 */

#ifndef __GEN_SET_H__
#define __GEN_SET_H__

#include <public/gen_int.h>
#include <public/gen_allocator.h>
#include <public/gen_comparer.h>


/** �� */
#define GEN_SET_COLOR_RED                                  (0)
/** �� */
#define GEN_SET_COLOR_BLACK                                (1)

/** set�ڵ� */
typedef struct tag_set_node
{
	/** ��ɫ */
	int32  color;

	/** �ڵ�߶� */
	int32  height;
	/** �������߶� */
	int32  left_height;
	/** �������߶� */
	int32  right_height;

	/** key */
	void*  p_key;

	/** ���ڵ� */
	struct tag_set_node *p_parent;
	/** ���ӽڵ� */
	struct tag_set_node *p_left;
	/** ���ӽڵ� */
	struct tag_set_node *p_right;

	/** ǰһ�ڵ� */
	struct tag_set_node *p_prev;
	/** ��һ�ڵ� */
	struct tag_set_node *p_next;

} SET_NODE, *PSET_NODE;

/** set */
typedef struct tag_gen_set
{
	/** allocator */
	GEN_ALLOCATOR allocator;
	/** comparer */
	GEN_COMPARER  comparer;

	/** �Ƿ��ʼ�� */
	int32  b_init;
	/** set���� */
	int32  set_size;
	/** �Ƿ������� */
	int32  b_descend;

	/** ���ڵ� */
	SET_NODE* p_root;

	/** ͷ�ڵ�ָ�� */
	SET_NODE* p_head;
	/** β�ڵ�ָ�� */
	SET_NODE* p_rear;
	/** ͷ�ڵ� */
	SET_NODE  head;
	/** β�ڵ� */
	SET_NODE  rear;

} GEN_SET, *PGEN_SET;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����set
 * @param [in] p_allocator ���������
 * @param [in] p_comparer �Ƚ������
 * @return
 * �ǿ�ֵ���ɹ�������ֵ��ʾ��Ӧ��set���
 * NULL��ʧ��
 * @remark
 * 1������ıȽ����������Ϊ��!
 * 2��set��ʵ�ֻ��ں����
 */
GEN_SET* gen_set_create(GEN_ALLOCATOR* p_allocator, GEN_COMPARER* p_comparer);

/**  
 * @brief ����set
 * @param [in] p_set set���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_set_destroy(GEN_SET* p_set);

/**  
 * @brief ��ʼ��set
 * @param [in] p_set set���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_set_init(GEN_SET* p_set);

/**  
 * @brief ����ʼ��set
 * @param [in] p_set set���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_set_deinit(GEN_SET* p_set);

/**  
 * @brief ���set
 * @param [in] p_set set���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_set_clear(GEN_SET* p_set);

/**  
 * @brief ��ȡset����
 * @param [in] p_set set���
 * @return
 * �Ǹ�ֵ���ɹ�������ֵ��ʾset����
 * -1��ʧ��
 */
int32 gen_set_get_size(GEN_SET* p_set);

/**  
 * @brief ����set����˳��
 * @param [in] p_set set���
 * @param [in] b_descend �Ƿ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1����ʼ����Ĭ��Ϊ��������
 */
int32 gen_set_set_order(GEN_SET* p_set, int32 b_descend);

/**  
 * @brief ���ҽڵ�
 * @param [in] p_set set���
 * @param [in] p_key �ڵ�ؼ���
 * @param [out] pp_node �ڵ��ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 */
int32 gen_set_find_node(GEN_SET* p_set, void* p_key, SET_NODE** pp_node);

/**  
 * @brief ����key
 * @param [in] p_set set���
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
int32 gen_set_insert_key(GEN_SET* p_set, void* p_key, SET_NODE** pp_node);

/**  
 * @brief ɾ���ڵ�
 * @param [in] p_set set���
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_set_delete_node(GEN_SET* p_set, SET_NODE* p_node);

/**  
 * @brief ɾ���ؼ���
 * @param [in] p_set set���
 * @param [in] p_key �ؼ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -4���ڵ㲻����
 */
int32 gen_set_delete_key(GEN_SET* p_set, void* p_key);

#ifdef __cplusplus
}
#endif


#endif ///__GEN_SET_H__
