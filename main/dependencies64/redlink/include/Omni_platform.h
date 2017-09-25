#ifndef Omni_PLATFORM_H
#define Omni_PLATFORM_H

/*******************************************************************************
* Copyright (c) 2016 Beijing Redlink Information Technology Co.,LTD
* 
* Beijing Redlink Information Technology Co.,LTD licenses this software under specific terms and
* conditions.  Use of any of the software or derivatives thereof in any
* product without a Beijing Redlink Information Technology Co.,LTD PCI card is strictly prohibited. 
* 
* Beijing Redlink Information Technology Co.,LTD provides this software AS IS, WITHOUT ANY WARRANTY,
* EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY OF
* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  Beijing Redlink Information Technology Co.,LTD makes no guarantee
* or representations regarding the use of, or the results of the use of,
* the software and documentation in terms of correctness, accuracy,
* reliability, currentness, or otherwise; and you rely on the software,
* documentation and results solely at your own risk.
* 
* IN NO EVENT SHALL Beijing Redlink Information Technology Co.,LTD BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
* LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
* OF ANY KIND.  IN NO EVENT SHALL Qualitune'S TOTAL LIABILITY EXCEED THE SUM
* PAID TO Beijing Redlink Information Technology Co.,LTD FOR THE PRODUCT LICENSED HEREUNDER.
* 
******************************************************************************/

/******************************************************************************
*
* File Name:
*
*     Omni_platform.h
*
* Description:
*
*
* √Ë ˆ:
*
*     .
* Revision:
*
*
******************************************************************************/


#if( !defined(LINUX_VER) || !defined(_LINUX_VER) )
 #ifndef _LINUX_VER
  #define _LINUX_VER
 #endif
#endif

#if( !defined(LINUX64) || !defined(_LINUX64) )
 #ifndef _LINUX64
  #define _LINUX64
 #endif
 #ifndef LINUX64
  #define LINUX64
 #endif
#endif


#if( (!defined(_LINUX_VER)) && (defined(_LINUX32) || defined(_LINUX64)) )
 #define _LINUX_VER
#endif

#if( defined(_MSC_VER) && defined(_LINUX_VER) )
 #undef _LINUX_VER
#endif

#if( defined(_LINUX_VER) && ( (!defined(_LINUX32)) && (!defined(_LINUX64)) ) )
 #define _LINUX64
#endif

#if( defined(_LINUX32) && defined(_LINUX64) )
 #undef _LINUX64
#endif

#if( defined(UNICODE) || defined(_UNICODE) )
 #ifndef _UNICODE
  #define _UNICODE
 #endif
 #ifndef UNICODE
  #define UNICODE
 #endif
#endif

typedef char     Om_INT8, *Om_PINT8;
typedef unsigned char   Om_UINT8, *Om_PUINT8;
typedef char     Om_CHAR, *Om_PCHAR;

typedef short     Om_INT16;
typedef unsigned short   Om_UINT16;
typedef Om_UINT16*   Om_PUINT16;

typedef int      Om_INT32;
typedef unsigned int   Om_UINT32;
typedef Om_INT32*   Om_PINT32;
typedef Om_UINT32*   Om_PUINT32;
typedef Om_INT32*   Om_LPINT32;
typedef Om_UINT32*   Om_LPUINT32;
typedef int      Om_BOOL;
//typedef int      Om_HRESULT;

typedef long     Om_INT32L;
typedef unsigned long   Om_UINT32L;

#ifdef _MSC_VER
 typedef __int64    Om_INT64;
 typedef unsigned __int64 Om_UINT64;
#else
 typedef long long   Om_INT64;
 typedef unsigned long long Om_UINT64;
#endif

#if( defined(_WIN64) || defined(_LINUX64) ) 
 typedef int     Om_HALF_PTR;
 typedef Om_INT64   Om_INT_PTR; 
 typedef Om_UINT64   Om_UINT_PTR; 
#else 
 typedef short    Om_HALF_PTR;
 typedef int     Om_INT_PTR;
 typedef unsigned int  Om_UINT_PTR; 
#endif

typedef float     Om_FLOAT;
typedef double     Om_DOUBLE;
typedef Om_DOUBLE*   Om_PDOUBLE;
typedef Om_DOUBLE*   Om_LPDOUBLE;

#define Om_CONST    const
#define Om_CALLBACK    __stdcall
#define Om_WINAPI    __stdcall

typedef void     Om_VOID;
typedef Om_VOID*    Om_PVOID;
typedef Om_VOID*    Om_LPVOID;
typedef Om_CONST void*  Om_LPCVOID;

typedef Om_PVOID    Om_HANDLE;

#define Om_INLINE   inline
#define Om_TRUE              1
#define Om_FALSE             0
#define Om_NULL              0


#endif // Omni_PLATFORM_H
