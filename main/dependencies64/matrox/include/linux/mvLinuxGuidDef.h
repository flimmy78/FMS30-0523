/* 
 * File:   mvLinuxGuidDef.h
 * Author: mbujold
 *
 * Created on May 23, 2014, 2:54 PM
 */

//
// GUID definition for all interfaces
//
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
{
    unsigned int   Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];

} GUID;
#endif

#ifdef INITGUID
   #define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)  \
       extern "C" const GUID name = {l, w1, w2, {b1, b2, b3, b4, b5, b6, b7, b8}}
#else
   #define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)    \
       extern "C" const GUID name
#endif


