/**
 * @file mpeg2_dvb_parser.h   MPEG2 DVB Parser
 * @author ���� <robert_3000@sina.com>
 * @version 0.1
 * @date 2010.11.15
 *
 *
 */


#ifndef __MPEG2_DVB_PARSER_H__
#define __MPEG2_DVB_PARSER_H__

#include <public/gen_int.h>
#include "mpeg2_dvb_public.h"
#include "mpeg2_ts_pack.h"

/** service descriptor */
typedef struct tag_dvb_service_descriptor
{
	/** type */
	int32  type;

	/** provider name */
	int8*  p_provider_name;
	/** provider name size */
	int32  provider_name_size;

	/** service name */
	int8*  p_service_name;
	/** service name size */
	int32  service_name_size;

} DVB_SERVICE_DESCRIPTOR, *PDVB_SERVICE_DESCRIPTOR;

/** SDS Section */
typedef struct tag_sds_section
{
	/** service id */
	int32  service_id;
	/** eit schedule flag */
	int32  eit_schedule_flag;
	/** eit present following flag */
	int32  eit_present_flag;
	/** running status */
	int32  running_status;

	/** descriptor data */
	uint8* p_descriptor_data;
	/** descriptor data size */
	int32  descriptor_data_size;

} SDS_SECTION, *PSDS_SECTION;

/** dvb sdt */
typedef struct tag_mpeg2_dvb_sdt
{
	/** table id */
	int32 table_id;

	union
	{
		/** data */
		uint8* p_data;

		/** sds section */
		SDS_SECTION* p_sds_section;

	} buf;

	union
	{
		/** data size, unit: byte */
		int32  data_size;

		/** sds section num, unit: number */
		int32  sds_section_num;

	} size;

} MPEG2_DVB_SDT, *PMPEG2_DVB_SDT;

/** SIT Section */
typedef struct tag_sit_section
{
	/** service id */
	int32  service_id;
	/** running status */
	int32  running_status;

	/** descriptor data */
	uint8* p_descriptor_data;
	/** descriptor data size */
	int32  descriptor_data_size;

} SIT_SECTION, *PSIT_SECTION;

/** dvb sit */
typedef struct tag_mpeg2_dvb_sit
{
	/** table id */
	int32 table_id;

	/** descriptor */
	uint8* p_descriptor;
	/** descriptor size */
	int32  descriptor_size;

	/** sit section */
	SIT_SECTION* p_section;
	/** sit section num, unit: number */
	int32  section_num;

} MPEG2_DVB_SIT, *PMPEG2_DVB_SIT;


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief ����SDT
 * @param [in] p_pack TS���
 * @param [in/out] p_sdt SDT���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����뻺�������Ȳ���
 * -3�����ݴ���
 * @remark
 * 1������ʱ���ⲿ��дp_sdt��buf.p_data��size.data_size�ֶΣ�������뻺�������Ȳ��㣬����ʱsize.data_size�ֶα�ʾʵ�����賤��
 * 2������ʱp_sdt��table_id�ֶξ�����data��size����Щ��ԱΪ��Ч
 */
int32 mpeg2_dvb_demux_sdt(MPEG2_TS_PACK *p_pack, MPEG2_DVB_SDT *p_sdt);

/**
 * @brief ����SIT
 * @param [in] p_pack TS���
 * @param [in/out] p_sit SIT���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����뻺�������Ȳ���
 * -3�����ݴ���
 * @remark
 * 1������ʱ���ⲿ��дp_sit��section_num�ֶΣ��������section�������㣬����ʱsection_num�ֶα�ʾʵ����������
 */
int32 mpeg2_dvb_demux_sit(MPEG2_TS_PACK *p_pack, MPEG2_DVB_SIT *p_sit);

/**
 * @brief ����service descriptor
 * @param [out] p_descriptor descriptor���
 * @param [in] p_buf �������ݵ�ַ
 * @param [in] len ���ݳ���
 * @return
 * 0���ɹ�
 * -1����������
 * -2�����뻺�������Ȳ���
 * -3�����ݴ���
 * @remark
 * 1���������ݰ���descriptor tag��length
 */
int32 mpeg2_dvb_demux_service_descriptor(DVB_SERVICE_DESCRIPTOR *p_descriptor, uint8 *p_buf, int32 len);


#ifdef __cplusplus
}
#endif

#endif ///__MPEG2_DVB_PARSER_H__
