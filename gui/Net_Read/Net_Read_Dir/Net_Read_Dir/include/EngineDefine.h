//*******************************************************************************************************************************
//
//	File name:				EngineStruct.h
//
//	File type:				C header file
//
//	File description:		引擎定义结构头文件，主要描述凌声芯识别网络制作和使用时通用结构
//
//	History:				DATA				ACTION			AUTHOR				MEMO
//							2009/12/5			Create			Xushuo
//*******************************************************************************************************************************

#ifndef _ENGINE_STRUCT_H_
#define _ENGINE_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define VO_MAX_SPLIT_REDEFINE_MAX							128

//  音标类型定义
typedef enum _VO_PHONETIC_TYPE
{
	VO_PHONETIC_TYPE_IPA = 0,								//	国际音标
	CNT_VO_PHONETIC_TYPE
}VO_PHONETIC_TYPE;


//	生成数据定义
//	语调（升降调）
#define	GENERATION_DATA_TONE								0x00000001
//	语句流利度
#define	GENERATION_DATA_FLUENCY								0x00000002
//	语速
#define	GENERATION_DATA_SPEED								0x00000004
//	句重读（发音上重读词）
#define	GENERATION_DATA_STATEMENT_STRESS					0x00000008
//	词重音
#define	GENERATION_DATA_STRESS								0x00000010
//	重点词(加重惩罚的词，不来源于生成)
#define	GENERATION_DATA_STRESS_WORD							0x00000020


//	文本拆分项
typedef struct _TEXT_SPLIT_ITEM_
{
	int nStart;												// 在原始文本中的起始位置
	int nLen;												// 在原始文本中的长度
	char sRedefinition[VO_MAX_SPLIT_REDEFINE_MAX];			// 重定义文本，对该文本串的重定义文本，取用文本串时如此项存在取用此项，否则在原始文本中取用，
	// 缺省此项为NULL;
}TEXT_SPLIT_ITEM, * PTEXT_SPLIT_ITEM;

//	加密码数据结构
typedef struct _MN_ECODE
{
	unsigned char tblCode[8];
}MN_ECODE, * PMN_ECODE;

#ifdef __cplusplus
}
#endif

#endif
//*******************************************************************************************************************************
// File end
//*******************************************************************************************************************************
