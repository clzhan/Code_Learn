/**
 * @file gen_stack.h  Stack
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2010.11.05
 *
 *
 */

#ifndef __GEN_STACK_H__
#define __GEN_STACK_H__

#include <public/gen_int.h>
#include <public/gen_allocator.h>

/** ջ�ڵ� */
typedef struct tag_stack_node
{
	/** �ڵ����� */
	void*  p_data;

} STACK_NODE, *PSTACK_NODE;

/** ջ */
typedef struct tag_gen_stack
{
	/** allocator */
	GEN_ALLOCATOR* p_allocator;

	/** �Ƿ��ʼ�� */
	int32  b_init;
	/** �Ƿ��ѷ����ڴ� */
	int32  b_alloc_mem;
	/** ջ��ǰ���� */
	int32  stack_size;

	/** �ڵ����� */
	STACK_NODE *p_array;
	/** ������С���ȣ���λ���� */
	int32  array_min_size;
	/** ������󳤶ȣ���λ���� */
	int32  array_max_size;
	/** �����ܳ��ȣ���λ���� */
	int32  array_total_size;
	/** ������Ч���ȣ���λ���� */
	int32  array_valid_size;
	/** ջ��λ�� */
	int32  top_pos;
	/** ջ��λ�� */
	int32  bottom_pos;

} GEN_STACK, *PGEN_STACK;

#ifdef __cplusplus
extern "C"
{
#endif

/**  
 * @brief ����ջ
 * @param [in] p_allocator ���������
 * @return
 * �ǿ�ֵ���ɹ�������ֵ��ʾջ���
 * NULL��ʧ��
 * @remark
 * 1�����������Ϊ�գ���ô��ʹ��Ĭ�Ϸ��䷽��(malloc)
 */
GEN_STACK* gen_stack_create(GEN_ALLOCATOR* p_allocator);

/**  
 * @brief ����ջ
 * @param [in] p_stack ջ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_destroy(GEN_STACK *p_stack);

/**  
 * @brief ��ʼ��ջ
 * @param [in] p_stack ջ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_init(GEN_STACK *p_stack);

/**  
 * @brief ����ʼ��ջ
 * @param [in] p_stack ջ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_deinit(GEN_STACK *p_stack);

/**  
 * @brief ���ջ
 * @param [in] p_stack ջ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_clear(GEN_STACK *p_stack);

/**  
 * @brief �����������
 * @param [in] p_stack ���о��
 * @param [in] min_size ��С���ȣ���λ����
 * @param [in] max_size ��󳤶ȣ���λ����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1���������ֻ����δ�����ڴ�ʱ���ã�Ĭ����С����Ϊ1024����󳤶�Ϊ1024
 * 2����󳤶ȱ�����ڵ�����С���ȣ������󳤶ȵ�����С���ȣ�ջ�����Զ�����
 */
int32 gen_stack_set_array_param(GEN_STACK *p_stack, int32 min_size, int32 max_size);

/**  
 * @brief Ԥ�����ڴ�
 * @param [in] p_stack ջ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_alloc_mem(GEN_STACK *p_stack);

/**  
 * @brief �ͷ�Ԥ�����ڴ�
 * @param [in] p_stack ջ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_free_mem(GEN_STACK *p_stack);

/**  
 * @brief ��ȡ��ǰջ����
 * @param [in] p_stack ջ���
 * @param [out] p_size ջ����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_get_size(GEN_STACK *p_stack, int32 *p_size);

/**  
 * @brief ��ȡջ��
 * @param [in] p_stack ջ���
 * @param [out] pp_data �ڵ�ֵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2����ջ
 */
int32 gen_stack_get_top(GEN_STACK *p_stack, void **pp_data);

/**  
 * @brief ��ȡջ��
 * @param [in] p_stack ջ���
 * @param [out] pp_data �ڵ����ݵ�ַ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_get_bottom(GEN_STACK *p_stack, void **pp_data);

/**  
 * @brief ��ջ
 * @param [in] p_stack ջ���
 * @param [in] p_data �ڵ�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���ڴ治��
 * -4��ջ����
 */
int32 gen_stack_push(GEN_STACK *p_stack, void *p_data);

/**  
 * @brief ��ջ
 * @param [in] p_stack ջ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
int32 gen_stack_pop(GEN_STACK *p_stack);



#ifdef __cplusplus
}
#endif


#endif ///__GEN_STACK_H__
