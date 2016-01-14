/**
 * @file bit_stream_writer.h  Bit Stream Writer
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2009.08.25
 *
 *
 */


#ifndef __BIT_STREAM_WRITER_H__
#define __BIT_STREAM_WRITER_H__

#include <public/gen_int.h>
#include <public/gen_def.h>

/** ÿ������д��ı����� */
#define BS_MAX_WRITE_BITS                          (32)

/** ������д���� */
typedef struct tag_bit_stream_writer
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

} BIT_STREAM_WRITER, *PBIT_STREAM_WRITER;


#ifdef __cplusplus
extern "C"
{
#endif

/** bit mask table(low bit) */
extern uint32 bs_writer_low_bm_table[];
/** bit mask table(high bit) */
extern uint32 bs_writer_high_bm_table[];

/**  
 * @brief ��ʼ��������
 *
 * @param [in] p_writer �����
 * @param [in] p_buf ���ݻ�����
 * @param [in] size ����������
 * @param [in] bit_pos ��ǰ����λ��ȡֵ��Χ1-8
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static inline int32 bs_writer_init(BIT_STREAM_WRITER *p_writer, uint8 *p_buf, int32 size, int32 bit_pos);

/**  
 * @brief �������д�����
 *
 * @param [in] p_writer �����
 * @param [in] value д���ֵ
 * @param [in] bits д��ı�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������ݲ���
 * @remark
 * 1��ÿ��д��ı��������ܳ���32λ!
 */
static inline int32 bs_write_bits(BIT_STREAM_WRITER *p_writer, uint32 value, int32 bits);

/**  
 * @brief �ӱ������������ɱ���
 *
 * @param [in] p_writer �����
 * @param [in] bits �����ı�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������ݲ���
 */
static inline int32 bs_writer_skip_bits(BIT_STREAM_WRITER *p_writer, int32 bits);

/**  
 * @brief �ж�ʣ�±������Ƿ���������ı�����
 *
 * @param [in] p_writer �����
 * @param [in] bits ��Ҫ�ı�����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 * -2�����������ݲ���
 */
static inline int32 bs_writer_need_bits(BIT_STREAM_WRITER *p_writer, int32 bits);

/**  
 * @brief ����ǰ������λ�ö��뵽�ֽڱ߽�
 *
 * @param [in] p_writer �����
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static inline int32 bs_writer_align(BIT_STREAM_WRITER *p_writer);

/**  
 * @brief ��ǰ�����������ĵ��ֽ���
 *
 * @param [in] p_stream �����
 * @param [out] bytes ���ĵ��ֽ���
 * @return
 * 0���ɹ�
 * -1��ʧ��
 */
static inline int32 bs_writer_get_use_bytes(BIT_STREAM_WRITER *p_writer, int32 *p_use_bytes);


static inline int32 bs_writer_init(BIT_STREAM_WRITER *p_writer, uint8 *p_buf, int32 size, int32 bit_pos)
{
	p_writer->p_buf = p_buf;
	p_writer->p_cur = p_buf;
	p_writer->buf_size = size;
	p_writer->total_bits = (size-1) * GEN_BYTE_BIT + bit_pos;
	p_writer->left_bits = p_writer->total_bits;
	p_writer->cur_bit_pos = bit_pos;

	return 0;
}

static inline int32 bs_write_bits(BIT_STREAM_WRITER *p_writer, uint32 value, int32 bits)
{
	int32  left_bits;

	//uint32 temp_value;

	if( bits < 0 || bits > BS_MAX_WRITE_BITS )
	{
		return -1;
	}

	if( p_writer->left_bits < bits )
	{
		return -2;
	}

	left_bits = bits;
	while( left_bits > 0 )
	{
		if( p_writer->cur_bit_pos >= left_bits )
		{
			/** ֱ��д�� */
			//bit_mask = 0xFF >> (GEN_BYTE_BIT - left_bits);
			//temp_value = value & bit_mask;
			//p_writer->p_cur[0] =
			//	(p_writer->p_cur[0] & (0xFF << p_writer->cur_bit_pos)) | (temp_value << (p_writer->cur_bit_pos - left_bits));
			p_writer->p_cur[0] =
				(p_writer->p_cur[0] & bs_writer_high_bm_table[p_writer->cur_bit_pos]) | ((value & bs_writer_low_bm_table[left_bits]) << (p_writer->cur_bit_pos - left_bits));

			p_writer->cur_bit_pos -= left_bits;
			if( p_writer->cur_bit_pos == 0 )
			{
				p_writer->p_cur++;
				p_writer->cur_bit_pos = GEN_BYTE_BIT;
			}

			break;

		}else
		{
			//bit_mask = 0xFF >> (GEN_BYTE_BIT - p_writer->cur_bit_pos);
			//p_writer->p_cur[0] =
			//	(p_writer->p_cur[0] & (0xFF << p_writer->cur_bit_pos)) | ((value >> (left_bits - p_writer->cur_bit_pos)) & bit_mask);
			p_writer->p_cur[0] =
				(p_writer->p_cur[0] & bs_writer_high_bm_table[p_writer->cur_bit_pos]) | ((value >> (left_bits - p_writer->cur_bit_pos)) & bs_writer_low_bm_table[p_writer->cur_bit_pos]);

			left_bits -= p_writer->cur_bit_pos;
			p_writer->p_cur++;
			p_writer->cur_bit_pos = GEN_BYTE_BIT;
		}
	}

	p_writer->left_bits -= bits;

	return 0;
}

static inline int32 bs_writer_skip_bits(BIT_STREAM_WRITER *p_writer, int32 bits)
{
	int32 left_bits = bits;

	if( p_writer->left_bits < bits )
	{
		return -2;
	}

	while( left_bits > 0 )
	{
		if( p_writer->cur_bit_pos >= left_bits )
		{
			p_writer->cur_bit_pos -= left_bits;
			if( p_writer->cur_bit_pos == 0 )
			{
				p_writer->p_cur++;
				p_writer->cur_bit_pos = GEN_BYTE_BIT;
			}

			break;

		}else
		{
			left_bits -= p_writer->cur_bit_pos;

			p_writer->p_cur++;
			p_writer->cur_bit_pos = GEN_BYTE_BIT;
		}
	}

	p_writer->left_bits -= bits;

	return 0;
}

static inline int32 bs_writer_need_bits(BIT_STREAM_WRITER *p_writer, int32 bits)
{
	if( p_writer->left_bits < bits )
	{
		return -2;
	}

	return 0;
}

static inline int32 bs_writer_align(BIT_STREAM_WRITER *p_writer)
{
	if( p_writer->cur_bit_pos != GEN_BYTE_BIT )
	{
		p_writer->p_cur++;
		p_writer->cur_bit_pos = GEN_BYTE_BIT;
	}

	return 0;
}

static inline int32 bs_writer_get_use_bytes(BIT_STREAM_WRITER *p_writer, int32 *p_use_bytes)
{
	*p_use_bytes = p_writer->p_cur - p_writer->p_buf;

	return 0;
}

#ifdef __cplusplus
}
#endif

#endif ///__BIT_STREAM_WRITER_H__
