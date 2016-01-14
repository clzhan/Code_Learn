
#include <stdlib.h>
#include <string.h>

#include "gen_multiset.h"

/////////////////////////////////// allocator /////////////////////////////////
static void* gen_multiset_inner_malloc(uint32 size, void* p_param)
{
	return malloc(size);
}

static int32 gen_multiset_inner_free(void *p_buf, void* p_param)
{
	free(p_buf);

	return 0;
}

/**  
 * @brief Ѱ�Ҳ���λ��
 * @param [in] p_multiset multiset���
 * @param [in] p_key �ؼ���
 * @param [out] pp_node �ڵ���
 * @param [out] p_left �Ƿ�������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -3���ڵ��Ѵ���
 * @remark
 * 1������ֵΪ0��ʾҪ���ҵĹؼ��ֶ�Ӧ�Ľڵ㲻���ڣ���ʱ*pp_node��ʾ����λ�õĸ��ڵ��������*pp_nodeΪ�գ���ʾ����λ��Ϊ���ڵ�
 * 2������ֵΪ-3��ʾҪ���ҵĹؼ��ֶ�Ӧ�Ľڵ��Ѵ��ڣ���ʱ*pp_node��ʾ�ҵ��ĵ�һ���ڵ���
 */
static int32 gen_multiset_find_insert_pos(GEN_MULTISET* p_multiset, void* p_key, MULTISET_NODE** pp_node, int32* p_left)
{
	MULTISET_NODE* p_parent;
	MULTISET_NODE* p_node;

	int32 b_find;
	int32 result;

	int32 ret;

	p_parent = NULL;
	p_node = p_multiset->p_root;
	b_find = 0;

	while( p_node )
	{
		ret = p_multiset->comparer.compare(p_key, p_node->p_key, p_multiset->comparer.p_param, &result);
		if( result == 0 )
		{
			/** ���ж�Ӧ�ڵ� */
			b_find = 1;
			break;
		}

		p_parent = p_node;
		if( result < 0 )
		{
			p_node = p_node->p_left;
			*p_left = 1;

		}else
		{
			p_node = p_node->p_right;
			*p_left = 0;
		}
	}

	if( b_find )
	{
		*pp_node = p_node;
		return -3;

	}else
	{
		*pp_node = p_parent;
		return 0;
	}
}

/**  
 * @brief Ѱ��ɾ��λ��
 * @param [in] p_multiset �����
 * @param [in] p_node Ҫɾ���Ľڵ���
 * @param [out] pp_node ʵ��ɾ��λ�ö�Ӧ�Ľڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��Ҫɾ���Ľڵ�����������ǿ�!
 */
static int32 gen_multiset_find_delete_pos(GEN_MULTISET* p_multiset, MULTISET_NODE* p_node, MULTISET_NODE** pp_node)
{
	MULTISET_NODE* p_current = p_node;
	MULTISET_NODE* p_temp_node;

	void* p_temp_key;

	int32 ret;

	/** Ѱ�������������ҽڵ㣬�ýڵ��������������ڵ� */
	p_temp_node = p_current->p_left;
	while( p_temp_node->p_right )
	{
		p_temp_node = p_temp_node->p_right;
	}

	/** ������ǰ�ڵ������ڵ� */
	p_temp_key = p_temp_node->p_key;
	p_temp_node->p_key = p_current->p_key;
	p_current->p_key = p_temp_key;

	*pp_node = p_temp_node;

	return 0;
}

/**  
 * @brief ����ת
 * @param [in] p_multiset �����
 * @param [in] p_a ���Ƚڵ���
 * @param [in] p_b ���ڵ���
 * @param [in] p_x �ӽڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��
 * ����ǰ�Ľڵ�λ�ù�ϵ��
 *                              a
 *                             /
 *                            b
 *                           /
 *                          x
 * ������Ľڵ�λ�ù�ϵ��
 *                              b
 *                             / \
 *                            x   a
 */
static int32 gen_multiset_left_rotate(GEN_MULTISET* p_multiset, MULTISET_NODE* p_a, MULTISET_NODE* p_b, MULTISET_NODE* p_x)
{
	if( p_b->p_right )
	{
		p_b->p_right->p_parent = p_a;
	}
	p_a->p_left = p_b->p_right;
	p_b->p_right = p_a;

	if( p_a->p_parent == NULL )
	{
		/** ���ڵ� */
		p_multiset->p_root = p_b;

	}else
	{
		/** �Ǹ��ڵ� */
		if( p_a == p_a->p_parent->p_left )
		{
			/** ������ */
			p_a->p_parent->p_left = p_b;

		}else
		{
			/** ������ */
			p_a->p_parent->p_right = p_b;
		}
	}

	p_b->p_parent = p_a->p_parent;
	p_a->p_parent = p_b;

	return 0;
}

/**  
 * @brief �����
 * @param [in] p_multiset �����
 * @param [in] p_a ���Ƚڵ���
 * @param [in] p_b ���ڵ���
 * @param [in] p_x �ӽڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��
 * ����ǰ�Ľڵ�λ�ù�ϵ��
 *                              a
 *                             /
 *                            b
 *                             \
 *                              x
 * ������Ľڵ�λ�ù�ϵ��
 *                              a
 *                             /
 *                            x
 *                           /
 *                          b
 */
static int32 gen_multiset_left_adjust(GEN_MULTISET* p_multiset, MULTISET_NODE* p_a, MULTISET_NODE* p_b, MULTISET_NODE* p_x)
{
	p_a->p_left = p_x;

	if( p_x->p_left )
	{
		p_x->p_left->p_parent = p_b;
	}
	p_b->p_right = p_x->p_left;
	p_x->p_left = p_b;

	p_b->p_parent = p_x;
	p_x->p_parent = p_a;

	return 0;
}

/**  
 * @brief ����ת
 * @param [in] p_multiset �����
 * @param [in] p_a ���ڵ���
 * @param [in] p_b ��ǰ�ڵ���
 * @param [in] p_x �ӽڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��
 * ����ǰ�Ľڵ�λ�ù�ϵ��
 *                              a
 *                               \
 *                                b
 *                                 \
 *                                  x
 * ������Ľڵ�λ�ù�ϵ��
 *                              b
 *                             / \
 *                            a   x
 */
static int32 gen_multiset_right_rotate(GEN_MULTISET* p_multiset, MULTISET_NODE* p_a, MULTISET_NODE* p_b, MULTISET_NODE* p_x)
{
	if( p_b->p_left )
	{
		p_b->p_left->p_parent = p_a;
	}
	p_a->p_right = p_b->p_left;
	p_b->p_left = p_a;

	if( p_a->p_parent == NULL )
	{
		/** ���ڵ� */
		p_multiset->p_root = p_b;

	}else
	{
		/** �Ǹ��ڵ� */
		if( p_a == p_a->p_parent->p_left )
		{
			/** ������ */
			p_a->p_parent->p_left = p_b;

		}else
		{
			/** ������ */
			p_a->p_parent->p_right = p_b;
		}
	}

	p_b->p_parent = p_a->p_parent;
	p_a->p_parent = p_b;

	return 0;
}

/**  
 * @brief �ҵ���
 * @param [in] p_multiset �����
 * @param [in] p_a ���Ƚڵ���
 * @param [in] p_b ���ڵ���
 * @param [in] p_x �ӽڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��
 * ����ǰ�Ľڵ�λ�ù�ϵ��
 *                              a
 *                               \
 *                                b
 *                               /
 *                              x
 * ������Ľڵ�λ�ù�ϵ��
 *                              a
 *                               \
 *                                x
 *                                 \
 *                                  b
 */
static int32 gen_multiset_right_adjust(GEN_MULTISET* p_multiset, MULTISET_NODE* p_a, MULTISET_NODE* p_b, MULTISET_NODE* p_x)
{
	p_a->p_right = p_x;

	if( p_x->p_right )
	{
		p_x->p_right->p_parent = p_b;
	}
	p_b->p_left = p_x->p_right;
	p_x->p_right = p_b;

	p_b->p_parent = p_x;
	p_x->p_parent = p_a;

	return 0;
}

/**  
 * @brief ��������ƽ��
 * @param [in] p_multiset �����
 * @param [in] p_node ����ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��ʵ�ֲο�http://en.wikipedia.org/wiki/Red-black_tree
 */
static int32 gen_multiset_insert_balance(GEN_MULTISET* p_multiset, MULTISET_NODE* p_node)
{
	MULTISET_NODE* p_ancestor;

	MULTISET_NODE* p_uncle;
	MULTISET_NODE* p_current;

	int32 ret;

	p_current = p_node;

	while( 1 )
	{
		if( p_current->p_parent == NULL )
		{
			/** case 1 */
			p_current->color = GEN_MULTISET_COLOR_BLACK;
			break;
		}

		if( p_current->p_parent->color == GEN_MULTISET_COLOR_BLACK )
		{
			/** case 2 */
			break;
		}

		//p_parent = p_current->p_parent;
		p_ancestor = p_current->p_parent->p_parent;
		if( p_ancestor == NULL )
		{
 			break;
		}

		if( p_current->p_parent == p_ancestor->p_left )
		{
			p_uncle = p_ancestor->p_right;

		}else
		{
			p_uncle = p_ancestor->p_left;
		}

		/** from above, parent always red, ancestor always black */
		if( p_uncle && p_uncle->color == GEN_MULTISET_COLOR_RED )
		{
			/** case 3 */
			p_ancestor->color = GEN_MULTISET_COLOR_RED;
			p_current->p_parent->color = GEN_MULTISET_COLOR_BLACK;
			p_uncle->color = GEN_MULTISET_COLOR_BLACK;

			p_current = p_ancestor;
			continue;
		}

		/** from above, uncle is null or always black */
		if( (p_current == p_current->p_parent->p_right) && (p_current->p_parent == p_ancestor->p_left) )
		{
			/** case 4(left) */
			ret = gen_multiset_left_adjust(p_multiset, p_ancestor, p_current->p_parent, p_current);
			p_current = p_current->p_left;

		}else if( (p_current == p_current->p_parent->p_left) && (p_current->p_parent == p_ancestor->p_right) )
		{
			/** case 4(right) */
			ret = gen_multiset_right_adjust(p_multiset, p_ancestor, p_current->p_parent, p_current);
			p_current = p_current->p_right;
		}

		p_current->p_parent->color = GEN_MULTISET_COLOR_BLACK;
		p_ancestor->color = GEN_MULTISET_COLOR_RED;

		if( (p_current == p_current->p_parent->p_left) && (p_current->p_parent == p_ancestor->p_left) )
		{
			/** case 5(left) */
			ret = gen_multiset_left_rotate(p_multiset, p_ancestor, p_current->p_parent, p_current);

		}else
		{
			/** case 5(right) */
			ret = gen_multiset_right_rotate(p_multiset, p_ancestor, p_current->p_parent, p_current);
		}

		break;
	}

	return 0;
}

/**  
 * @brief ����ɾ��ƽ��
 * @param [in] p_multiset �����
 * @param [in] p_node ��ʼ�ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��ʵ�ֲο�http://en.wikipedia.org/wiki/Red-black_tree
 */
static int32 gen_multiset_delete_balance(GEN_MULTISET* p_multiset, MULTISET_NODE* p_node)
{
	//MULTISET_NODE* p_parent;
	MULTISET_NODE* p_sibling;
	MULTISET_NODE* p_sibling_left;
	MULTISET_NODE* p_sibling_right;
	MULTISET_NODE* p_current;

	int32 ret;

	/** from above, p_node is black */
	p_current = p_node;

	while( 1 )
	{
		if( p_current->p_parent == NULL )
		{
			/** case 1 */
			//p_current->color = GEN_MULTISET_COLOR_BLACK;
			break;
		}

		//p_parent = p_current->p_parent;
		if( p_current == p_current->p_parent->p_left )
		{
			p_sibling = p_current->p_parent->p_right;

		}else
		{
			p_sibling = p_current->p_parent->p_left;
		}

		if( p_sibling == NULL )
		{
			break;
		}

		p_sibling_left = p_sibling->p_left;
		p_sibling_right = p_sibling->p_right;
		if( p_sibling->color == GEN_MULTISET_COLOR_RED )
		{
			/** case 2 */
			p_current->p_parent->color = GEN_MULTISET_COLOR_RED;
			p_sibling->color = GEN_MULTISET_COLOR_BLACK;

			if( p_current == p_current->p_parent->p_left )
			{
				ret = gen_multiset_right_rotate(p_multiset, p_current->p_parent, p_sibling, p_sibling->p_right);
				p_sibling = p_sibling_left;

			}else
			{
				ret = gen_multiset_left_rotate(p_multiset, p_current->p_parent, p_sibling, p_sibling->p_left);
				p_sibling = p_sibling_right;
			}
		}

		/** from above, sibling always black */
		if( (p_current->p_parent->color == GEN_MULTISET_COLOR_BLACK)
			&& (p_sibling->color == GEN_MULTISET_COLOR_BLACK)
			&& (p_sibling->p_left == NULL || p_sibling->p_left->color == GEN_MULTISET_COLOR_BLACK)
			&& (p_sibling->p_right == NULL || p_sibling->p_right->color == GEN_MULTISET_COLOR_BLACK) )
		{
			/** case 3 */
			p_sibling->color = GEN_MULTISET_COLOR_RED;
			p_current = p_current->p_parent;
			continue;
		}

		if( (p_current->p_parent->color == GEN_MULTISET_COLOR_RED)
			&& (p_sibling->color == GEN_MULTISET_COLOR_BLACK)
			&& (p_sibling->p_left == NULL || p_sibling->p_left->color == GEN_MULTISET_COLOR_BLACK)
			&& (p_sibling->p_right == NULL || p_sibling->p_right->color == GEN_MULTISET_COLOR_BLACK) )
		{
			/** case 4 */
			p_sibling->color = GEN_MULTISET_COLOR_RED;
			p_current->p_parent->color = GEN_MULTISET_COLOR_BLACK;

			break;
		}

		/** from case 3 & 4, sibling's child can not both be null */
		p_sibling_left = p_sibling->p_left;
		p_sibling_right = p_sibling->p_right;
		//if( p_sibling->color == GEN_MULTISET_COLOR_BLACK )
		{
			if( (p_current == p_current->p_parent->p_left)
				&& (p_sibling->p_right == NULL || p_sibling->p_right->color == GEN_MULTISET_COLOR_BLACK)
				&& (p_sibling_left && p_sibling->p_left->color == GEN_MULTISET_COLOR_RED) )
			{
				/** case 5(left) */
				p_sibling->color = GEN_MULTISET_COLOR_RED;
				p_sibling->p_left->color = GEN_MULTISET_COLOR_BLACK;
				ret = gen_multiset_left_rotate(p_multiset, p_sibling, p_sibling->p_left, p_sibling->p_left->p_left);

				p_sibling = p_sibling_left;

			}else if( (p_current == p_current->p_parent->p_right)
				&& (p_sibling->p_left == NULL || p_sibling->p_left->color == GEN_MULTISET_COLOR_BLACK)
				&& (p_sibling_right && p_sibling->p_right->color == GEN_MULTISET_COLOR_RED) )
			{
				/** case 5(right) */
				p_sibling->color = GEN_MULTISET_COLOR_RED;
				p_sibling->p_right->color = GEN_MULTISET_COLOR_BLACK;
				ret = gen_multiset_right_rotate(p_multiset, p_sibling, p_sibling->p_right, p_sibling->p_right->p_right);

				p_sibling = p_sibling_right;
			}
		}

		p_sibling->color = p_current->p_parent->color;
		p_current->p_parent->color = GEN_MULTISET_COLOR_BLACK;

		if( p_current == p_current->p_parent->p_left )
		{
			/** case 6(left) */
			if( p_sibling->p_right )
			{
				p_sibling->p_right->color = GEN_MULTISET_COLOR_BLACK;
			}

			ret = gen_multiset_right_rotate(p_multiset, p_current->p_parent, p_sibling, p_sibling->p_right);

		}else
		{
			/** case 6(right) */
			if( p_sibling->p_left )
			{
				p_sibling->p_left->color = GEN_MULTISET_COLOR_BLACK;
			}

			ret = gen_multiset_left_rotate(p_multiset, p_current->p_parent, p_sibling, p_sibling->p_left);
		}

		break;
	}

	return 0;
}

/**  
 * @brief ���������ɾ��ƽ��2(��Ӧ�ڵ�Ϊ��)
 * @param [in] p_multiset �����
 * @param [in] p_parent ���ڵ���
 * @param [in] b_left �Ƿ�Ϊ���ڵ�������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��ʵ�ֲο�http://en.wikipedia.org/wiki/Red-black_tree
 */
static int32 gen_multiset_delete_balance2(GEN_MULTISET* p_multiset, MULTISET_NODE* p_parent, int32 b_left)
{
	MULTISET_NODE* p_sibling;
	MULTISET_NODE* p_sibling_left;
	MULTISET_NODE* p_sibling_right;

	int32 ret;

	if( p_parent == NULL )
	{
		/** case 1 */
		return 0;
	}

	if( b_left )
	{
		p_sibling = p_parent->p_right;

	}else
	{
		p_sibling = p_parent->p_left;
	}

	if( p_sibling == NULL )
	{
		return 0;
	}

	p_sibling_left = p_sibling->p_left;
	p_sibling_right = p_sibling->p_right;
	if( p_sibling->color == GEN_MULTISET_COLOR_RED )
	{
		/** case 2 */
		p_parent->color = GEN_MULTISET_COLOR_RED;
		p_sibling->color = GEN_MULTISET_COLOR_BLACK;

		if( b_left )
		{
			ret = gen_multiset_right_rotate(p_multiset, p_parent, p_sibling, p_sibling->p_right);
			p_sibling = p_sibling_left;

		}else
		{
			ret = gen_multiset_left_rotate(p_multiset, p_parent, p_sibling, p_sibling->p_left);
			p_sibling = p_sibling_right;
		}
	}

	/** from above, sibling always black */
	if( (p_parent->color == GEN_MULTISET_COLOR_BLACK)
		&& (p_sibling->color == GEN_MULTISET_COLOR_BLACK)
		&& (p_sibling->p_left == NULL || p_sibling->p_left->color == GEN_MULTISET_COLOR_BLACK)
		&& (p_sibling->p_right == NULL || p_sibling->p_right->color == GEN_MULTISET_COLOR_BLACK) )
	{
		/** case 3 */
		p_sibling->color = GEN_MULTISET_COLOR_RED;

		return gen_multiset_delete_balance(p_multiset, p_parent);
	}

	if( (p_parent->color == GEN_MULTISET_COLOR_RED)
		&& (p_sibling->color == GEN_MULTISET_COLOR_BLACK)
		&& (p_sibling->p_left == NULL || p_sibling->p_left->color == GEN_MULTISET_COLOR_BLACK)
		&& (p_sibling->p_right == NULL || p_sibling->p_right->color == GEN_MULTISET_COLOR_BLACK) )
	{
		/** case 4 */
		p_sibling->color = GEN_MULTISET_COLOR_RED;
		p_parent->color = GEN_MULTISET_COLOR_BLACK;

		return 0;
	}

	/** from case 3 & 4, sibling's child can not both be null */
	p_sibling_left = p_sibling->p_left;
	p_sibling_right = p_sibling->p_right;

	if( (b_left)
		&& (p_sibling->p_right == NULL || p_sibling->p_right->color == GEN_MULTISET_COLOR_BLACK)
		&& (p_sibling_left && p_sibling->p_left->color == GEN_MULTISET_COLOR_RED) )
	{
		/** case 5(left) */
		p_sibling->color = GEN_MULTISET_COLOR_RED;
		p_sibling->p_left->color = GEN_MULTISET_COLOR_BLACK;
		ret = gen_multiset_left_rotate(p_multiset, p_sibling, p_sibling->p_left, p_sibling->p_left->p_left);

		p_sibling = p_sibling_left;

	}else if( (!b_left)
		&& (p_sibling->p_left == NULL || p_sibling->p_left->color == GEN_MULTISET_COLOR_BLACK)
		&& (p_sibling_right && p_sibling->p_right->color == GEN_MULTISET_COLOR_RED) )
	{
		/** case 5(right) */
		p_sibling->color = GEN_MULTISET_COLOR_RED;
		p_sibling->p_right->color = GEN_MULTISET_COLOR_BLACK;
		ret = gen_multiset_right_rotate(p_multiset, p_sibling, p_sibling->p_right, p_sibling->p_right->p_right);

		p_sibling = p_sibling_right;
	}

	p_sibling->color = p_parent->color;
	p_parent->color = GEN_MULTISET_COLOR_BLACK;

	if( b_left )
	{
		/** case 6(left) */
		if( p_sibling->p_right )
		{
			p_sibling->p_right->color = GEN_MULTISET_COLOR_BLACK;
		}

		ret = gen_multiset_right_rotate(p_multiset, p_parent, p_sibling, p_sibling->p_right);

	}else
	{
		/** case 6(right) */
		if( p_sibling->p_left )
		{
			p_sibling->p_left->color = GEN_MULTISET_COLOR_BLACK;
		}

		ret = gen_multiset_left_rotate(p_multiset, p_parent, p_sibling, p_sibling->p_left);
	}

	return 0;
}

/**  
 * @brief ɾ�������ӽڵ�(�ݹ鷽ʽ)
 * @param [in] p_multiset �����
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_delete_child_node(GEN_MULTISET* p_multiset, MULTISET_NODE* p_node)
{
	MULTISET_NODE* p_temp;
	MULTISET_NODE* p_node2;

	int32 i;
	int32 ret;

	/** ɾ�������� */
	if( p_node->p_left )
	{
		ret = gen_multiset_delete_child_node(p_multiset, p_node->p_left);

		/** ɾ�����������ڵ� */
		p_temp = p_node->p_left->p_first_twin;
		i = 0;
		while( i < p_node->p_left->twin_node_num )
		{
			p_node2 = p_temp->p_next_twin;

			ret = p_multiset->allocator.deallocate(p_temp, p_multiset->allocator.p_param);

			i++;
			p_temp = p_node2;
		}

		p_node->p_left = NULL;
	}

	/** ɾ�������� */
	if( p_node->p_right )
	{
		ret = gen_multiset_delete_child_node(p_multiset, p_node->p_right);

		p_temp = p_node->p_right->p_first_twin;
		i = 0;
		while( i < p_node->p_right->twin_node_num )
		{
			p_node2 = p_temp->p_next_twin;

			ret = p_multiset->allocator.deallocate(p_temp, p_multiset->allocator.p_param);

			i++;
			p_temp = p_node2;
		}

		p_node->p_right = NULL;
	}

	return 0;
}

/**  
 * @brief ��ʼ��������
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2���ڴ治��
 */
static int32 gen_multiset_list_init(GEN_MULTISET* p_multiset)
{
	p_multiset->p_head = &p_multiset->head;
	p_multiset->p_rear = &p_multiset->rear;

	memset(p_multiset->p_head, 0, sizeof(MULTISET_NODE));
	p_multiset->p_head->p_prev_seq = NULL;
	p_multiset->p_head->p_next_seq = p_multiset->p_rear;

	memset(p_multiset->p_rear, 0, sizeof(MULTISET_NODE));
	p_multiset->p_rear->p_prev_seq = p_multiset->p_head;
	p_multiset->p_rear->p_next_seq = NULL;

	return 0;
}

/**  
 * @brief ����ʼ��������
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_list_deinit(GEN_MULTISET* p_multiset)
{
	int32 ret;

	if( p_multiset->p_head )
	{
		p_multiset->p_head = NULL;
	}

	if( p_multiset->p_rear )
	{
		p_multiset->p_rear = NULL;
	}

	return 0;
}

/**  
 * @brief ���������
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_list_clear(GEN_MULTISET* p_multiset)
{
	p_multiset->p_head->p_next_seq = p_multiset->p_rear;
	p_multiset->p_rear->p_prev_seq = p_multiset->p_head;

	return 0;
}

/**  
 * @brief ���������ײ�����ڵ�
 * @param [in] p_multiset multiset���
 * @param [in] p_node �ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_list_push_front_node(GEN_MULTISET *p_multiset, MULTISET_NODE *p_node)
{
	p_node->p_prev_seq = p_multiset->p_head;
	p_node->p_next_seq = p_multiset->p_head->p_next_seq;
	p_multiset->p_head->p_next_seq->p_prev_seq = p_node;
	p_multiset->p_head->p_next_seq = p_node;

	return 0;
}

/**  
 * @brief ����������ָ���ڵ�֮ǰ����ڵ�
 * @param [in] p_multiset multiset���
 * @param [in] p_node �ڵ���
 * @param [in] p_before ָ���ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_list_insert_before_node(GEN_MULTISET *p_multiset, MULTISET_NODE *p_node, MULTISET_NODE *p_before)
{
	p_node->p_prev_seq = p_before->p_prev_seq;
	p_node->p_next_seq = p_before;
	p_before->p_prev_seq->p_next_seq = p_node;
	p_before->p_prev_seq = p_node;

	return 0;
}

/**  
 * @brief ����������ָ���ڵ�֮�����ڵ�
 * @param [in] p_multiset multiset���
 * @param [in] p_node �ڵ���
 * @param [in] p_after ָ���ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_list_insert_after_node(GEN_MULTISET *p_multiset, MULTISET_NODE *p_node, MULTISET_NODE *p_after)
{
	p_node->p_prev_seq = p_after;
	p_node->p_next_seq = p_after->p_next_seq;
	p_after->p_next_seq->p_prev_seq = p_node;
	p_after->p_next_seq = p_node;

	return 0;
}

/**  
 * @brief ɾ����������ָ���ڵ�
 * @param [in] p_multiset multiset���
 * @param [in] p_node �ڵ���
 * @param [in] p_after ָ���ڵ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_list_delete_node(GEN_MULTISET *p_multiset, MULTISET_NODE *p_node)
{
	p_node->p_prev_seq->p_next_seq = p_node->p_next_seq;
	p_node->p_next_seq->p_prev_seq = p_node->p_prev_seq;

	return 0;
}

/**  
 * @brief ����������
 * @param [in] p_multiset multiset���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static int32 gen_multiset_list_reverse(GEN_MULTISET *p_multiset)
{
	MULTISET_NODE *p_current = NULL;
	MULTISET_NODE *p_node  = NULL;
	MULTISET_NODE *p_node2 = NULL;
	MULTISET_NODE *p_first_node = NULL;

	int32 ret;

	if( p_multiset->multiset_size < 2 )
	{
		/** ������� */
		return 0;
	}

	p_current = p_multiset->p_head->p_next_seq;
	p_node = p_current->p_next_seq;
	while( p_node != p_multiset->p_rear )
	{
		p_node2 = p_node->p_next_seq;

		p_node->p_next_seq = p_current;
		p_current->p_prev_seq = p_node;

		p_current = p_node;
		p_node = p_node2;
	}

	p_first_node = p_multiset->p_head->p_next_seq;
	p_multiset->p_head->p_next_seq = p_multiset->p_rear->p_prev_seq;
	p_multiset->p_rear->p_prev_seq = p_first_node;

	p_multiset->p_head->p_next_seq->p_prev_seq = p_multiset->p_head;
	p_multiset->p_rear->p_prev_seq->p_next_seq = p_multiset->p_rear;

	return 0;
}

///////////////////////////////////�ⲿ�ӿ�////////////////////////////////////////
GEN_MULTISET* gen_multiset_create(GEN_ALLOCATOR* p_allocator, GEN_COMPARER* p_comparer)
{
	GEN_MULTISET *p_multiset = NULL;

	if( p_comparer == NULL )
	{
		return NULL;
	}

	if( p_allocator )
	{
		p_multiset = (GEN_MULTISET *)p_allocator->allocate(sizeof(GEN_MULTISET), p_allocator->p_param);

	}else
	{
		p_multiset = (GEN_MULTISET *)malloc( sizeof(GEN_MULTISET) );
	}

	if( p_multiset == NULL )
	{
		return NULL;
	}

	memset(p_multiset, 0, sizeof(GEN_MULTISET));

	if( p_allocator )
	{
		memcpy(&p_multiset->allocator, p_allocator, sizeof(p_multiset->allocator));

	}else
	{
		p_multiset->allocator.allocate = &gen_multiset_inner_malloc;
		p_multiset->allocator.deallocate = &gen_multiset_inner_free;
		p_multiset->allocator.p_param = p_multiset;
	}

	p_multiset->comparer = *p_comparer;

	return p_multiset;
}


int32 gen_multiset_destroy(GEN_MULTISET *p_multiset)
{
	int32 ret;

	if( p_multiset == NULL )
	{
		return -1;
	}

	if( p_multiset->b_init )
	{
		gen_multiset_deinit(p_multiset);
	}

	ret = p_multiset->allocator.deallocate(p_multiset, p_multiset->allocator.p_param);

	return 0;
}

int32 gen_multiset_init(GEN_MULTISET *p_multiset)
{
	int32 ret;

	if( p_multiset == NULL )
	{
		return -1;
	}

	if( p_multiset->b_init )
	{
		return 0;
	}

	p_multiset->multiset_size = 0;
	p_multiset->b_descend = 0;
	p_multiset->p_root = NULL;

	ret = gen_multiset_list_init(p_multiset);
	if( ret )
	{
		gen_multiset_deinit(p_multiset);
		return -3;
	}

	p_multiset->b_init = 1;

	return 0;
}

int32 gen_multiset_deinit(GEN_MULTISET *p_multiset)
{
	MULTISET_NODE* p_temp;
	MULTISET_NODE* p_node2;

	int32 i;
	int32 ret;

	if( p_multiset == NULL )
	{
		return -1;
	}

	/** ɾ�����ڵ� */
	if( p_multiset->p_root )
	{
		ret = gen_multiset_delete_child_node(p_multiset, p_multiset->p_root);

		p_temp = p_multiset->p_root->p_first_twin;
		i = 0;
		while( i < p_multiset->p_root->twin_node_num )
		{
			p_node2 = p_temp->p_next_twin;

			ret = p_multiset->allocator.deallocate(p_temp, p_multiset->allocator.p_param);

			i++;
			p_temp = p_node2;
		}

		p_multiset->p_root = NULL;
	}

	gen_multiset_list_deinit(p_multiset);

	p_multiset->multiset_size = 0;
	p_multiset->b_init = 0;

	return 0;
}

int32 gen_multiset_clear(GEN_MULTISET *p_multiset)
{
	MULTISET_NODE* p_temp;
	MULTISET_NODE* p_node2;

	int32 i;
	int32 ret;

	if( p_multiset == NULL )
	{
		return -1;
	}

	if( !p_multiset->b_init )
	{
		return -3;
	}

	if( p_multiset->p_root )
	{
		ret = gen_multiset_delete_child_node(p_multiset, p_multiset->p_root);

		p_temp = p_multiset->p_root->p_first_twin;
		i = 0;
		while( i < p_multiset->p_root->twin_node_num )
		{
			p_node2 = p_temp->p_next_twin;

			ret = p_multiset->allocator.deallocate(p_temp, p_multiset->allocator.p_param);

			i++;
			p_temp = p_node2;
		}

		p_multiset->p_root = NULL;
	}

	gen_multiset_list_clear(p_multiset);

	p_multiset->multiset_size = 0;

	return 0;
}

int32 gen_multiset_get_size(GEN_MULTISET *p_multiset)
{
	if( p_multiset == NULL )
	{
		return -1;
	}

	if( !p_multiset->b_init )
	{
		return -1;
	}

	return p_multiset->multiset_size;
}

int32 gen_multiset_set_order(GEN_MULTISET* p_multiset, int32 b_descend)
{
	int32 ret;

	if( p_multiset == NULL )
	{
		return -1;
	}

	if( !p_multiset->b_init )
	{
		return -1;
	}

	if( p_multiset->b_descend )
	{
		/** ���� */
		if( !b_descend )
		{
			ret = gen_multiset_list_reverse(p_multiset);
		}

	}else
	{
		/** ���� */
		if( b_descend )
		{
			ret = gen_multiset_list_reverse(p_multiset);
		}
	}

	p_multiset->b_descend = b_descend;

	return 0;
}

int32 gen_multiset_find_node(GEN_MULTISET* p_multiset, void* p_key, MULTISET_NODE** pp_node)
{
	int32 b_left;
	int32 ret;

	if( p_multiset == NULL || pp_node == NULL )
	{
		return -1;
	}

	if( !p_multiset->b_init )
	{
		return -1;
	}

	ret = gen_multiset_find_insert_pos(p_multiset, p_key, pp_node, &b_left);
	if( ret == 0 )
	{
		*pp_node = NULL;
		return -4;

	}else
	{
		return 0;
	}
}

int32 gen_multiset_insert_key(GEN_MULTISET* p_multiset, void* p_key, MULTISET_NODE** pp_node)
{
	MULTISET_NODE* p_parent = NULL;
	MULTISET_NODE* p_node = NULL;
	MULTISET_NODE* p_first_child = NULL;

	int32 b_left;
	int32 b_duplicate;

	int32 ret;

	if( p_multiset == NULL )
	{
		return -1;
	}

	if( !p_multiset->b_init )
	{
		return -1;
	}

	b_duplicate = 0;
	ret = gen_multiset_find_insert_pos(p_multiset, p_key, &p_parent, &b_left);
	if( ret )
	{
		b_duplicate = 1;
	}

	p_node = (MULTISET_NODE*)p_multiset->allocator.allocate(sizeof(MULTISET_NODE), p_multiset->allocator.p_param);

	if( p_node == NULL )
	{
		return -2;
	}

	p_node->color = GEN_MULTISET_COLOR_RED;

	p_node->p_key = p_key;

	p_node->p_parent = p_parent;
	p_node->p_left = NULL;
	p_node->p_right = NULL;

	p_node->p_prev_seq = NULL;
	p_node->p_next_seq = NULL;

	p_node->twin_node_num = 1;
	p_node->b_twin_node = 0;
	p_node->p_prev_twin = NULL;
	p_node->p_next_twin = NULL;
	p_node->p_first_twin = p_node;
	p_node->p_last_twin = p_node;

	if( b_duplicate )
	{
		/** add twin node */
		p_first_child = p_parent;
		p_first_child->twin_node_num++;

		if( p_multiset->b_descend )
		{
			ret = gen_multiset_list_insert_before_node(p_multiset, p_node, p_first_child->p_last_twin);

		}else
		{
			ret = gen_multiset_list_insert_after_node(p_multiset, p_node, p_first_child->p_last_twin);
		}

		p_first_child->p_last_twin->p_next_twin = p_node;
		p_node->p_prev_twin = p_first_child->p_last_twin;
		p_first_child->p_last_twin = p_node;

		p_node->p_parent = p_first_child->p_parent;
		p_node->b_twin_node = 1;
		p_node->p_first_twin = p_first_child;

	}else
	{
		/** add not twin node */
		if( p_parent == NULL )
		{
			/** ������ڵ� */
			p_node->color = GEN_MULTISET_COLOR_BLACK;
			p_multiset->p_root = p_node;
			ret = gen_multiset_list_push_front_node(p_multiset, p_node);

		}else
		{
			/** ����Ǹ��ڵ� */
			if( b_left )
			{
				/** ������ */
				p_parent->p_left = p_node;

				if( p_multiset->b_descend )
				{
					ret = gen_multiset_list_insert_after_node(p_multiset, p_node, p_parent->p_first_twin);

				}else
				{
					ret = gen_multiset_list_insert_before_node(p_multiset, p_node, p_parent->p_first_twin);
				}

			}else
			{
				/** ������ */
				p_parent->p_right = p_node;

				if( p_multiset->b_descend )
				{
					ret = gen_multiset_list_insert_before_node(p_multiset, p_node, p_parent->p_last_twin);

				}else
				{
					ret = gen_multiset_list_insert_after_node(p_multiset, p_node, p_parent->p_last_twin);
				}
			}
		}

		ret = gen_multiset_insert_balance(p_multiset, p_node);
	}

	p_multiset->multiset_size++;

	if( pp_node )
	{
		*pp_node = p_node;
	}

	return 0;
}

int32 gen_multiset_delete_node(GEN_MULTISET* p_multiset, MULTISET_NODE* p_node)
{
	MULTISET_NODE *p_node2 = NULL;
	MULTISET_NODE *p_child = NULL;

	int32 b_left = 0;

	int32 ret;

	if( p_multiset == NULL || p_node == NULL )
	{
		return -1;
	}

	if( !p_multiset->b_init )
	{
		return -3;
	}

	if( p_node->b_twin_node )
	{
		/** twin node */
		p_node->p_prev_twin->p_next_twin = p_node->p_next_twin;
		if( p_node->p_next_twin )
		{
			p_node->p_next_twin->p_prev_twin = p_node->p_prev_twin;

		}else
		{
			/** delete last twin */
			p_node->p_first_twin->p_last_twin = p_node->p_prev_twin;
		}

		p_node->p_first_twin->twin_node_num--;

	}else
	{
		/** not twin node */
		if( p_node->twin_node_num > 1 )
		{
			/** has twin */
			p_node2 = p_node->p_next_twin;
			p_node->p_key = p_node2->p_key;

			p_node->p_next_twin = p_node2->p_next_twin;
			if( p_node2->p_next_twin )
			{
				p_node2->p_next_twin->p_prev_twin = p_node;

			}else
			{
				/** delete last twin */
				p_node->p_last_twin = p_node2->p_prev_twin;
			}

			p_node->twin_node_num--;
			p_node = p_node2;

		}else
		{
			/** not has twin */
			if( p_node->p_left == NULL )
			{
				/** ������Ϊ�� */
				if( p_node->p_parent == NULL )
				{
					/** ���ڵ� */
					p_multiset->p_root = p_node->p_right;

				}else
				{
					/** �Ǹ��ڵ� */
					if( p_node == p_node->p_parent->p_left )
					{
						p_node->p_parent->p_left = p_node->p_right;
						b_left = 1;

					}else
					{
						p_node->p_parent->p_right = p_node->p_right;
						b_left = 0;
					}
				}

				if( p_node->p_right )
				{
					p_node->p_right->p_parent = p_node->p_parent;
				}

				p_child = p_node->p_right;

			}else
			{
				/** �������ǿ� */
				ret = gen_multiset_find_delete_pos(p_multiset, p_node, &p_node2);
				p_node = p_node2;

				/** �ýڵ���������ȻΪ�� */
				if( p_node == p_node->p_parent->p_left )
				{
					p_node->p_parent->p_left = p_node->p_left;
					b_left = 1;

				}else
				{
					p_node->p_parent->p_right = p_node->p_left;
					b_left = 0;
				}

				if( p_node->p_left )
				{
					p_node->p_left->p_parent = p_node->p_parent;
				}

				p_child = p_node->p_left;
			}

			if( p_node->color != GEN_MULTISET_COLOR_RED )
			{
				/** Ҫɾ���Ľڵ��Ǻ�ɫ */
				if( p_child == NULL )
				{
					/** �ӽڵ�Ϊ�� */
					ret = gen_multiset_delete_balance2(p_multiset, p_node->p_parent, b_left);

				}else
				{
					/** �ӽڵ�ǿ� */
					if( p_child->color == GEN_MULTISET_COLOR_RED )
					{
						/** �ӽڵ��Ǻ�ɫ */
						p_child->color = GEN_MULTISET_COLOR_BLACK;

					}else
					{
						/** �ӽڵ��Ǻ�ɫ */
						ret = gen_multiset_delete_balance(p_multiset, p_child);
					}
				}
			}
		}
	}


	ret = gen_multiset_list_delete_node(p_multiset, p_node);

	ret = p_multiset->allocator.deallocate(p_node, p_multiset->allocator.p_param);

	p_multiset->multiset_size--;

	return 0;
}

int32 gen_multiset_delete_key(GEN_MULTISET* p_multiset, void* p_key)
{
	MULTISET_NODE *p_node = NULL;
	MULTISET_NODE *p_node2 = NULL;
	MULTISET_NODE *p_child = NULL;
	MULTISET_NODE *p_temp = NULL;

	int32 b_left;

	int32 i;
	int32 ret;

	if( p_multiset == NULL )
	{
		return -1;
	}

	if( !p_multiset->b_init )
	{
		return -3;
	}

	ret = gen_multiset_find_insert_pos(p_multiset, p_key, &p_node, &b_left);
	if( ret == 0 )
	{
		/** δ�ҵ���Ӧ�ڵ� */
		return -4;
	}

	if( p_node->twin_node_num > 1 )
	{
		/** delete all twin */
		p_temp = p_node->p_next_twin;
		i = 1;
		while( i < p_node->twin_node_num )
		{
			p_node2 = p_temp->p_next_twin;

			ret = gen_multiset_list_delete_node(p_multiset, p_temp);

			ret = p_multiset->allocator.deallocate(p_temp, p_multiset->allocator.p_param);

			p_multiset->multiset_size--;
			i++;
			p_temp = p_node2;
		}

		p_node->twin_node_num = 1;
		p_node->p_next_twin = NULL;
		p_node->p_last_twin = p_node;
	}

	if( p_node->p_left == NULL )
	{
		/** ������Ϊ�� */
		if( p_node->p_parent == NULL )
		{
			/** ���ڵ� */
			p_multiset->p_root = p_node->p_right;

		}else
		{
			/** �Ǹ��ڵ� */
			if( p_node == p_node->p_parent->p_left )
			{
				p_node->p_parent->p_left = p_node->p_right;
				b_left = 1;

			}else
			{
				p_node->p_parent->p_right = p_node->p_right;
				b_left = 0;
			}
		}

		if( p_node->p_right )
		{
			p_node->p_right->p_parent = p_node->p_parent;
		}

		p_child = p_node->p_right;

	}else
	{
		/** �������ǿ� */
		ret = gen_multiset_find_delete_pos(p_multiset, p_node, &p_node2);
		p_node = p_node2;

		/** �ýڵ���������ȻΪ�� */
		if( p_node == p_node->p_parent->p_left )
		{
			p_node->p_parent->p_left = p_node->p_left;
			b_left = 1;

		}else
		{
			p_node->p_parent->p_right = p_node->p_left;
			b_left = 0;
		}

		if( p_node->p_left )
		{
			p_node->p_left->p_parent = p_node->p_parent;
		}

		p_child = p_node->p_left;
	}

	if( p_node->color != GEN_MULTISET_COLOR_RED )
	{
		/** Ҫɾ���Ľڵ��Ǻ�ɫ */
		if( p_child == NULL )
		{
			/** �ӽڵ�Ϊ�� */
			ret = gen_multiset_delete_balance2(p_multiset, p_node->p_parent, b_left);

		}else
		{
			/** �ӽڵ�ǿ� */
			if( p_child->color == GEN_MULTISET_COLOR_RED )
			{
				/** �ӽڵ��Ǻ�ɫ */
				p_child->color = GEN_MULTISET_COLOR_BLACK;

			}else
			{
				/** �ӽڵ��Ǻ�ɫ */
				ret = gen_multiset_delete_balance(p_multiset, p_child);
			}
		}
	}

	ret = gen_multiset_list_delete_node(p_multiset, p_node);

	ret = p_multiset->allocator.deallocate(p_node, p_multiset->allocator.p_param);

	p_multiset->multiset_size--;

	return 0;
}
