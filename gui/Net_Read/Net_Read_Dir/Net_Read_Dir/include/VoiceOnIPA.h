//*******************************************************************************************************************************
//
//	File name:				VoiceOnIPA.h
//
//	File type:				C header file
//
//	File description:		凌声芯课件制作国际音标头文件
//
//	History:				DATA				ACTION			AUTHOR				MEMO
//							2009/11/9			Create			Xushuo
//
//*******************************************************************************************************************************

#pragma once

//*******************************************************************************************************************************
//	Area of definition
//*******************************************************************************************************************************

// 音标位标示掩码定义及含义定义
// 类型掩码
#define IPA_BIT_MASK_TYPE					0xF0000000
// 特殊类型
#define		IPA_BIT_TYPE_SP					0x00000000
// 标识类型
#define		IPA_BIT_TYPE_SIGN				0xf0000000
// 元音类型
#define		IPA_BIT_TYPE_VOWEL				0x10000000
// 辅音类型
#define		IPA_BIT_TYPE_CONSONANT			0x20000000

// 子类型掩码
#define IPA_BIT_MASK_SUBTYPE				0x0FF00000
// 未标明的子类型
#define IPA_BIT_SUBTYPE_NONE				0x00000000
// 其他子类型尚未定义

// 数值掩码
#define IPA_BIT_MASK_NUM					0x0000FFFF

// 音标标识和特殊符号定义
#define VO_IPA_END							0x00000000
#define VO_IPA_SPACE						0x00000020
#define	VO_IPA_RETURN						0x0000000A

#define VO_IPA_STRESS						0xf0000000
#define VO_IPA_LIGHT						0xf0000001

// 音标数值定义
// 见“国际音标对应值说明.docx”
