/**
 * @file bit_stream_reader.h  Bit Stream Reader
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2008.07.25
 *
 *
 */


#ifndef __BIT_STREAM_READER_H__
#define __BIT_STREAM_READER_H__

#include <public/gen_int.h>
#include <public/gen_def.h>

/** ÿ�����ɶ�ȡ�ı����� */
#define BS_MAX_READ_BITS                           (32)

/** ��������ȡ�� */
typedef struct tag_bit_stream_reader
{
	/** ��������ʼ��ַ */
	uint8  *p_buf;
	/** �������ܳ��ȣ���λ���ֽ� */
	int32  buf_size;
	/** �������ܳ��ȣ���λ������ */
	int32  total_bits;
	/** ������ʣ�೤�ȣ���λ������ */
	int32  left_bits;

	/** ��ǰ�ֽ� */
	uint8  *p_cur;
	/** ��ǰ����λ��1-8 */
	int32  cur_bit_pos;

} BIT_STREAM_READER, *PBIT_STREAM_READER;



#ifdef __cplusplus
extern "C"
{
#endif

/** bit mask table */
extern uint32 bs_reader_bm_table[];
/** se(v) table */
extern int32  bs_reader_se_table[];


/**  
 * @brief ��ʼ��������
 *
 * @param [in] p_reader �����
 * @param [in] p_buf ���ݻ�����
 * @param [in] size ����������
 * @param [in] bit_pos ��ǰ����λ��ȡֵ��Χ1-8
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static inline int32 bs_reader_init(BIT_STREAM_READER *p_reader, uint8 *p_buf, int32 size, int32 bit_pos);

/**  
 * @brief �ӱ�������ȡ����
 *
 * @param [in] p_reader �����
 * @param [out] p_value �������
 * @param [in] bits ��ȡ�ı�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������ݲ���
 * @remark
 * 1����ȡ�ı��������ܳ���32λ!
 */
static inline int32 bs_read_bits(BIT_STREAM_READER *p_reader, int32 *p_value, int32 bits);

/**  
 * @brief �ӱ������Ƴ�����
 *
 * @param [in] p_reader �����
 * @param [in] bits ��ȡ�ı�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������ݲ���
 */
static inline int32 bs_reader_skip_bits(BIT_STREAM_READER *p_reader, int32 bits);

/**  
 * @brief �жϱ������Ƿ���������ı�����
 *
 * @param [in] p_reader �����
 * @param [in] bits ��Ҫ�ı�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������ݲ���
 */
static inline int32 bs_reader_need_bits(BIT_STREAM_READER *p_reader, int32 bits);

/**  
 * @brief �����������ǰλ�õ���һ��1����λ��֮���0����
 *
 * @param [in] p_reader �����
 * @param [out] p_zero_bits ǰ׺0�ĸ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2��������ֱ������δ����ֵΪ1�ı���λ
 */
static inline int32 bs_reader_count_zero_bits(BIT_STREAM_READER *p_reader, uint32 *p_zero_bits);

/**
 * @brief �ӱ�������ȡ�޷��ű䳤ֵ
 *
 * @param [in] p_reader �����
 * @param [out] p_value �������
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������ݲ���
 * @remark
 * 1���޷��ű䳤ֵ�ĺ���μ�H264�ĵ�˵��
 */
static inline int32 bs_read_uv_bits(BIT_STREAM_READER *p_reader, int32 *p_value);

/**
 * @brief ����se(v)ֵ
 *
 * @param [in] p_reader �����
 * @param [in] input_value ����ֵ
 * @param [out] p_value ���ֵ
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * @remark
 * 1��se(v)ֵ�ĺ���μ�H264��׼�����˵��
 */
static inline int32 bs_reader_calc_se_var(BIT_STREAM_READER *p_reader, uint32 input_value, int32 *p_value);

/**  
 * @brief ����������ǰ���ض��뵽�ֽڱ߽�
 *
 * @param [in] p_reader �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static inline int32 bs_reader_align(BIT_STREAM_READER *p_reader);

/**  
 * @brief ��ǰ�����������ĵ��ֽ���
 *
 * @param [in] p_reader �����
 * @param [out] bytes ���ĵ��ֽ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static inline int32 bs_reader_get_use_bytes(BIT_STREAM_READER *p_reader, int32 *p_use_bytes);


static inline int32 bs_reader_init(BIT_STREAM_READER *p_reader, uint8 *p_buf, int32 size, int32 bit_pos)
{
	p_reader->p_buf = p_buf;
	p_reader->p_cur = p_buf;
	p_reader->buf_size = size;
	p_reader->total_bits = (size-1) * GEN_BYTE_BIT + bit_pos;
	p_reader->left_bits = p_reader->total_bits;
	p_reader->cur_bit_pos = bit_pos;

	return 0;
}

static inline int32 bs_read_bits(BIT_STREAM_READER *p_reader, int32 *p_value, int32 bits)
{
	int32 value = 0;
	/** δ��ȡ�ı����� */
	int32 left_bits = bits;
	/** ����λ���� */
	//int32 bit_mask;

	*p_value = 0;
	if( p_reader->left_bits < bits )
	{
		return -2;
	}

	if( bits > BS_MAX_READ_BITS )
	{
		return -1;
	}

	while( left_bits > 0 )
	{
		if( p_reader->cur_bit_pos >= left_bits )
		{
			//bit_mask = 0xFF >> (GEN_BYTE_BIT - left_bits);
			//value |= ( p_reader->p_cur[0] >> (p_reader->cur_bit_pos - left_bits) ) & bit_mask;
			value |= ( p_reader->p_cur[0] >> (p_reader->cur_bit_pos - left_bits) ) & bs_reader_bm_table[left_bits];
			p_reader->cur_bit_pos -= left_bits;
			if( p_reader->cur_bit_pos == 0 )
			{
				p_reader->p_cur++;
				p_reader->cur_bit_pos = GEN_BYTE_BIT;
			}

			break;

		}else
		{
			//bit_mask = 0xFF >> (GEN_BYTE_BIT - p_reader->cur_bit_pos);
			left_bits -= p_reader->cur_bit_pos;

			//value |= ((p_reader->p_cur[0] & bit_mask) << left_bits);
			value |= ((p_reader->p_cur[0] & bs_reader_bm_table[p_reader->cur_bit_pos]) << left_bits);

			p_reader->p_cur++;
			p_reader->cur_bit_pos = GEN_BYTE_BIT;
		}
	}

	p_reader->left_bits -= bits;
	*p_value = value;

	return 0;
}

static inline int32 bs_reader_skip_bits(BIT_STREAM_READER *p_reader, int32 bits)
{
	/** δ��ȡ�ı����� */
	int32 left_bits = bits;

	if( p_reader->left_bits < bits )
	{
		return -2;
	}

	while( left_bits > 0 )
	{
		if( p_reader->cur_bit_pos >= left_bits )
		{
			p_reader->cur_bit_pos -= left_bits;
			if( p_reader->cur_bit_pos == 0 )
			{
				p_reader->p_cur++;
				p_reader->cur_bit_pos = GEN_BYTE_BIT;
			}

			break;

		}else
		{
			left_bits -= p_reader->cur_bit_pos;

			p_reader->p_cur++;
			p_reader->cur_bit_pos = GEN_BYTE_BIT;
		}
	}

	p_reader->left_bits -= bits;

	return 0;
}

static inline int32 bs_reader_need_bits(BIT_STREAM_READER *p_reader, int32 bits)
{
	if( p_reader->left_bits < bits )
	{
		return -2;
	}

	return 0;
}

static inline int32 bs_reader_count_zero_bits(BIT_STREAM_READER *p_reader, uint32 *p_zero_bits)
{
	int32 value;
	/** δ��ȡ�ı����� */
	int32 left_bits;
	/** ����λ���� */
	//int32 bit_mask;
	int32 zero_bits = 0;

	uint8 *p_cur;
	int32 cur_pos;
	int32 fore_pos;
	int32 b_find = 0;

	left_bits = p_reader->left_bits;
	p_cur = p_reader->p_cur;
	cur_pos = p_reader->cur_bit_pos;

	if( p_reader->left_bits < 1 )
	{
		return -2;
	}

	/** ȡ��ǰ�ֽ���Ч���� */
	//bit_mask = 0xFF >> (GEN_BYTE_BIT - cur_pos);
	//value = p_cur[0] & bit_mask;
	value = p_cur[0] & bs_reader_bm_table[cur_pos];
	if( value != 0 )
	{
		/** ��ǰ�ֽ���Ч���ֲ�Ϊ0 */
		cur_pos--;
		fore_pos = cur_pos;
		while( cur_pos >= 0 )
		{
			if( (value >> cur_pos) != 0 )
			{
				b_find = 1;
				break;
			}

			cur_pos--;
		}

		*p_zero_bits = (fore_pos - cur_pos);

		return 0;
	}

	p_cur++;
	left_bits -= cur_pos;
	zero_bits += cur_pos;

	while( left_bits > 0 )
	{
		/** �жϵ�ǰ�ֽڵ�ֵ */
		//value = p_cur[0];
		if( p_cur[0] != 0 )
		{
			/** ��ǰ�ֽڲ�Ϊ0 */
			cur_pos = GEN_BYTE_BIT - 1;
			fore_pos = cur_pos;
			while( cur_pos >= 0 )
			{
				if( (p_cur[0] >> cur_pos) != 0 )
				{
					b_find = 1;
					break;
				}

				cur_pos--;
			}

			if( b_find )
			{
				zero_bits += (fore_pos - cur_pos);
				*p_zero_bits = zero_bits;

				return 0;
			}
		}

		p_cur++;
		left_bits -= GEN_BYTE_BIT;
		zero_bits += GEN_BYTE_BIT;
	}

	*p_zero_bits = zero_bits;

	return -2;
}

static inline int32 bs_read_uv_bits(BIT_STREAM_READER *p_reader, int32 *p_value)
{
	int32  read_bits;
	uint32 zero_bits;

	int32 ret;

	ret = bs_reader_count_zero_bits(p_reader, &zero_bits);
	if( ret || zero_bits > (BS_MAX_READ_BITS-1)/2 )
	{
		return ret;
	}

	//read_bits = zero_bits * 2 + 1;
	read_bits = (zero_bits << 1) + 1;
	ret = bs_read_bits(p_reader, p_value, read_bits);

	if( ret )
	{
		return ret;
	}

	(*p_value)--;

	return 0;
}

static inline int32 bs_reader_calc_se_var(BIT_STREAM_READER *p_reader, uint32 input_value, int32 *p_value)
{
	if( input_value <= 6 )
	{
		*p_value = bs_reader_se_table[input_value];

	}else
	{
		if( input_value & 0x1 )
		{
			/** ���� */
			*p_value = input_value >> 1;

		}else
		{
			/** ż�� */
			*p_value = (~(input_value >> 1) + 1);
		}
	}

	return 0;
}

static inline int32 bs_reader_align(BIT_STREAM_READER *p_reader)
{
	if( p_reader->cur_bit_pos != GEN_BYTE_BIT )
	{
		p_reader->p_cur++;
		p_reader->cur_bit_pos = GEN_BYTE_BIT;
	}

	return 0;
}

static inline int32 bs_reader_get_use_bytes(BIT_STREAM_READER *p_reader, int32 *p_use_bytes)
{
	*p_use_bytes = p_reader->p_cur - p_reader->p_buf;

	return 0;
}


#ifdef __cplusplus
}
#endif

#endif ///__BIT_STREAM_READER_H__
