#ifndef MV_LINUX_DEFINITIONS_H
#define MV_LINUX_DEFINITIONS_H

//==============================================================================
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2007. All rights reserved.
//
//  This software code is subject to the terms and conditions outlined
//  in the non-disclosure agreement between Matrox and your company.
//  By accessing this code or using it in any way, you indicate your
//  acceptance of such terms and conditions.
//
//  All code and information is provided "as is" without warranty of any kind,
//  either expressed or implied, including but not limited to the implied
//  warranties of merchantability and/or fitness for a particular purpose.
//
//  Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make
//  changes in specifications and code at any time and without notice.
//  No responsibility is assumed by Matrox Electronic Systems Ltd. for
//  its use; nor for any infringements of patents or other rights of
//  third parties resulting from its use. No license is granted under
//  any patents or patent rights of Matrox Electronic Systems Ltd.
//
//==============================================================================

#pragma once

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>
#include <sstream>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdexcept>

#include "mvLinuxGuidDef.h"

typedef unsigned char u8;

// we don't need these anymore with the 3.5 kernel, but if we go back to 2.6 might need to put them back
//typedef signed char       int8_t;
//typedef signed short      int16_t;
//typedef signed int        int32_t;
//typedef signed long long  int64_t;

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long      uint64_t;

#ifndef __INTEL_COMPILER
   typedef signed int        __int32;
#endif

//TODO: Check that this is correct in 64 bits
#if __WORDSIZE==64
   typedef long  _int64;
   #ifndef __INTEL_COMPILER
      typedef long  __int64;
   #endif
#else
   typedef long long int  _int64;
   #ifndef __INTEL_COMPILER
      typedef long long int  __int64;
   #endif
#endif

//ULONG_PTR is used when casting a pointer to  a register long variable. This is bas code, but we must keep it.
#ifndef ULONG_PTR
	typedef unsigned long ULONG_PTR;
#endif

typedef ULONG_PTR * PULONG_PTR;

#define __ptr64

#define Ptr64ToPtr(x) (x)

typedef pid_t    HINSTANCE;
typedef int32_t  HRESULT;

typedef void                VOID;
typedef void*               HANDLE;
typedef void*               PVOID;
typedef HANDLE *            PHANDLE;
typedef PHANDLE             LPHANDLE;
typedef int32_t             BOOL;
typedef void *              LPVOID;
typedef long unsigned int   ULONG;
typedef unsigned char       BYTE;
typedef BYTE                BOOLEAN;
typedef unsigned char *     LPBYTE;
typedef unsigned char       byte;
typedef unsigned char       UCHAR;
typedef unsigned char *     PUCHAR;
typedef char                CHAR;
typedef char *              PCHAR;
typedef unsigned short      USHORT;
typedef unsigned short *    PUSHORT;
typedef short               SHORT;
typedef short *             PSHORT;
typedef long                LONG;
typedef uint64_t            ULONGLONG;
typedef LONG *              PLONG;
typedef PLONG               LPLONG;
typedef unsigned long int * PULONG;
typedef pthread_mutex_t     CRITICAL_SECTION;
typedef char *              LPSTR;
typedef char *              LPTSTR;
typedef char                TCHAR;
typedef uint32_t            DWORD;
typedef int64_t				 LONGLONG;
typedef uint64_t				 DWORDLONG;
typedef uint32_t            COLORREF;
typedef int                 INT_PTR;
typedef uint16_t            WORD;
typedef wchar_t             WCHAR;
typedef uint32_t *          DWORD_PTR;
typedef ULONG               __int3264;

// we don't need these anymore with the 3.5 kernel, but if we go back to 2.6 might need to put them back
//#ifndef MAC_PLATFORM
//typedef uint32_t            size_t;
//#endif

typedef size_t              SIZE_T;

typedef uint64_t ULONG64, * PULONG64;
typedef int64_t  DWORD64, * PDWORD64;

#define	CONST				const
typedef	int				INT;
typedef	wchar_t       *LPWSTR;
typedef	const wchar_t *LPCWSTR;

typedef	const char *	LPCSTR;
typedef  std::wstring   _bstr_t;

#define MAX_PATH (PATH_MAX)
#define _MAX_PATH (PATH_MAX)

#define TEXT(_A_) _A_
#define _T(_A_)   _A_

#define interface struct

#define OutputDebugString  puts
#define OutputDebugStringW(_WSTR_) fputws((_WSTR_), stdout)
#define AfxMessageBox      wprintf
#define wcscat_s(_DST_, _SIZE_, _SRC_)   wcsncat((_DST_), (_SRC_), (_SIZE_))
inline void wcscpy_s(wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource){wcsncpy(strDestination, strSource, numberOfElements);}
inline void wcscpy_s(wchar_t *strDestination, const wchar_t *strSource){wcscpy(strDestination, strSource);}
#define strtok_s(_TOK_, _DLM_, _CTX_) strtok((_TOK_), (_DLM_))
#define memcpy_s(_DST_, _SIZE_, _SRC_, _COUNT_) memcpy((_DST_), (_SRC_), (_COUNT_))
#define strcpy_s(_DST_, _SIZE_, _SRC_)   strncpy((_DST_), (_SRC_), (_SIZE_))
#define vsprintf_s(_DST_, _SIZE_, _FORMAT_,_ARG_)   vsprintf((_DST_), (_FORMAT_), (_ARG_))
#define vsnprintf_s(_DST_, _SIZE_, _CNT_,_FORMAT_,_ARG_)   vsnprintf((_DST_), _SIZE_, (_FORMAT_), (_ARG_))
#define _vsnprintf_s(_DST_, _SIZE_, _CNT_,_FORMAT_,_ARG_)   vsnprintf((_DST_), _SIZE_, (_FORMAT_), (_ARG_))
#define _vsnwprintf_s(_DST_, _SIZE_, _CNT_,_FORMAT_,_ARG_)  vswprintf((_DST_), _SIZE_, (_FORMAT_), (_ARG_))
#define _snprintf_s(_DST_, _SIZE_,_CNT_,  ...)  snprintf((_DST_), (_SIZE_),  __VA_ARGS__)
#define _snwprintf_s(_DST_, _SIZE_, _CNT_,  ...)  swprintf((_DST_), (_SIZE_),  __VA_ARGS__)
#define strncat_s(_DST_, _SIZE_, _CNT_,  _SRC_)  strncat((_DST_), (_CNT_), (_SRC_))
#define strcat_s(_DST_, _SIZE_, _SRC_)  strcat((_DST_), (_SRC_))
#define Sleep(_WAIT_)                    usleep((_WAIT_) * 1000)
#define _tcsstr     wcsstr
#define _vsnprintf  vsnprintf
#define _vsnwprintf vswprintf
#define _snwprintf  swprintf
#define _snprintf   snprintf
#define sprintf_s   snprintf
#define swprintf_s  swprintf
#define wsprintf    sprintf
#define lstrcmpiW	  wcscasecmp
#define sscanf_s    sscanf

#define _TRUNCATE ((size_t)-1)

inline void strncpy_s(char *strDest, size_t numberOfElements, const char *strSource, size_t count)
{
   if( count == ((size_t)-1) ) // #define _TRUNCATE ((size_t)-1)
   {
      strncpy(strDest, strSource, numberOfElements - 1); // Copy as much as you can
      strDest[numberOfElements - 1] = '\0'; // Terminate buffer with a null character
   }
   else if( count < numberOfElements )
   {
      strncpy(strDest,  strSource, count); // Copy the required count
      strDest[count] = '\0'; // Add a trailing null character
   }
   // Here the count is invalid but the source string fits in the destination buffer
   else if( strlen(strSource) < numberOfElements )
   {
      strcpy(strDest, strSource);
   }
   else
   {
      throw std::runtime_error("Invalid parameters passed to strncpy_s()");
   }
}

inline void wcsncpy_s(wchar_t *strDest, size_t numberOfElements, const wchar_t *strSource, size_t count)
{
   if( count == ((size_t)-1) ) // #define _TRUNCATE ((size_t)-1)
   {
      wcsncpy(strDest, strSource, numberOfElements - 1); // Copy as much as you can
      strDest[numberOfElements - 1] = '\0'; // Terminate buffer with a null character
   }
   else if( count < numberOfElements )
   {
      wcsncpy(strDest,  strSource, count); // Copy the required count
      strDest[count] = '\0'; // Add a trailing null character
   }
   // Here the count is invalid but the source string fits in the destination buffer
   else if( wcslen(strSource) < numberOfElements )
   {
      wcscpy(strDest, strSource);
   }
   else
   {
      throw std::runtime_error("Invalid parameters passed to strncpy_s()");
   }
}

#define _tcscmp      strcmp
#define _tcsrchr     strrchr
#define _tcsncmp     strncmp
#define _tcslen      strlen

#define CW2CA(_SRC_, _CODEPAGE_) \
   {\
      setlocale(LC_CTYPE, "en_US.UTF-8"); \
   }

#define lstrlen     strlen
#define lstrcpyn    strncpy
#define _stricmp    strcasecmp
#define _strnicmp   strncasecmp
#define _wcsicmp    wcscasecmp
#define gmtime_s(_TM_, _TIME_)     gmtime_r((_TIME_), (_TM_))
#define localtime_s(_TM_, _TIME_)  localtime_r((_TIME_), (_TM_))
#define WaitForSingleObjectEx(_A_, _B_, _C_) WaitForSingleObject((_A_), (_B_))

#ifdef NDEBUG
   #define ASSERT(_A_)
#else
   #define ASSERT(_EXPR_) \
   { \
      if (!(_EXPR_)) \
      { \
         fprintf(stderr, "%s: File %s, line %d, method: %s\n", __STRING(_EXPR_), __FILE__, __LINE__, __PRETTY_FUNCTION__); \
      } \
   }

#endif

#if defined (MAC_PLATFORM) || defined (LINUX_PLATFORM)
#define _ASSERT  ASSERT
#endif

#ifdef MAC_PLATFORM
#include <mvMacDefinitions.h>
#endif

#define EXTERN_C             extern "C"
#define PURE                 = 0
#define CLSCTX_INPROC_SERVER   (0x1)
#define CLSCTX_INPROC_HANDLER  (0x2)
#define CLSCTX_LOCAL_SERVER    (0x4)
#define CLSCTX_REMOTE_SERVER   (0x10)
#define CLSCTX_INPROC    (CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER)
#define CLSCTX_SERVER   (CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER)
#define CLSCTX_ALL      (CLSCTX_INPROC_HANDLER | CLSCTX_SERVER)

#define INFINITE              (0xFFFFFFFF)
#define IDOK                   0
#define MAXIMUM_WAIT_OBJECTS   64

#ifndef  FALSE
   #define  FALSE (0)
#endif

#ifndef  TRUE
   #define  TRUE  (!FALSE)
#endif

#define THREAD_BASE_PRIORITY_LOWRT  15  // value that gets a thread to LowRealtime-1
#define THREAD_BASE_PRIORITY_MAX    2   // maximum thread base priority boost
#define THREAD_BASE_PRIORITY_MIN    (-2)  // minimum thread base priority boost
#define THREAD_BASE_PRIORITY_IDLE   (-15) // value that gets a thread to idle


#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL    (THREAD_PRIORITY_LOWEST+1)
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    (THREAD_PRIORITY_HIGHEST-1)

#define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

#ifdef  MAC_PLATFORM
#define PTHREAD_MUTEX_RECURSIVE_NP      PTHREAD_MUTEX_RECURSIVE
#endif

#define DLL_PROCESS_DETACH 0
#define DLL_PROCESS_ATTACH 1

#define E_NOINTERFACE             ((HRESULT)0x80004002)
#define E_OUTOFMEMORY             ((HRESULT)0x8007000E)
#define E_POINTER                 ((HRESULT)0x80004003)
#define E_INVALIDARG              ((HRESULT)0x80070057)
#define E_FAIL                    ((HRESULT)0x80004005)
#define E_NOTIMPL                 ((HRESULT)0x80000001)
#define NO_ERROR                  ((HRESULT)0x00000000)
#define NOERROR                   0L
#define S_OK                      ((HRESULT)0x00000000)
#define S_FALSE                   ((HRESULT)0x00000001)
#define CLASS_E_CLASSNOTAVAILABLE ((HRESULT)0x80040110)
#define CO_E_NOTINITIALIZED       ((HRESULT)0x800401F0L)
#define ERROR_RESOURCE_DATA_NOT_FOUND   1812L

#define INVALID_HANDLE_VALUE      ((HANDLE)0xFFFFFFFF)

#define CoInitialize(_A_) NO_ERROR
#define CoInitializeEx(_A_, _B_) NO_ERROR
#define CoUninitialize() ((void) 0)

// In 64-bit there is only one calling convention (and 32-bit Linux is not supported)
#define __fastcall
#define __stdcall
#define _stdcall
#define THIS_
#define THIS  void
#define WINBASEAPI
#define IN
#define OUT
#define NEAR
#define FAR
#define STDAPICALLTYPE
#define STDMETHODCALLTYPE
#define STDMETHODIMP        HRESULT
#define STDMETHODIMP_(type) type
#define STDAPI              EXTERN_C HRESULT
#define WINAPI
#define CALLBACK
#define DECLARE_INTERFACE(a) interface a
#define VFT_DRV               0
#define VFT2_DRV_INSTALLABLE  0
#define __RPC_FAR


#define UNREFERENCED_PARAMETER(_A_)
#define COINIT_APARTMENTTHREADED 0
#define COINIT_MULTITHREADED 1

// Registry
#define REG_NONE                    ( 0 )   // No value type
#define REG_SZ                      ( 1 )   // Unicode nul terminated string
#define REG_EXPAND_SZ               ( 2 )   // Unicode nul terminated string
                                            // (with environment variable references)
#define REG_BINARY                  ( 3 )   // Free form binary
#define REG_DWORD                   ( 4 )   // 32-bit number
#define REG_DWORD_LITTLE_ENDIAN     ( 4 )   // 32-bit number (same as REG_DWORD)
#define REG_DWORD_BIG_ENDIAN        ( 5 )   // 32-bit number
#define REG_LINK                    ( 6 )   // Symbolic Link (unicode)
#define REG_MULTI_SZ                ( 7 )   // Multiple Unicode strings
#define REG_RESOURCE_LIST           ( 8 )   // Resource list in the resource map
#define REG_FULL_RESOURCE_DESCRIPTOR ( 9 )  // Resource list in the hardware description
#define REG_RESOURCE_REQUIREMENTS_LIST ( 10 )
#define REG_QWORD                   ( 11 )  // 64-bit number
#define REG_QWORD_LITTLE_ENDIAN     ( 11 )  // 64-bit number (same as REG_QWORD)

__inline bool operator ==(const GUID & refg, const GUID & srcg)
{
   if(&srcg != &refg)
   {
      if(refg.Data1 != srcg.Data1) return false;
      if(refg.Data2 != srcg.Data2) return false;
      if(refg.Data3 != srcg.Data3) return false;
      const unsigned int *p = (const unsigned int*) &srcg.Data4[0];
      const unsigned int *q = (const unsigned int*) &refg.Data4[0];
      return (*p == *q) && (*(p+1) == *(q+1));
   }
   return true;
}

__inline bool operator !=(const GUID & refg, const GUID & srcg)
{
   if(&srcg != &refg)
   {
      if(refg.Data1 != srcg.Data1) return true;
      if(refg.Data2 != srcg.Data2) return true;
      if(refg.Data3 != srcg.Data3) return true;
      const unsigned int *p = (const unsigned int*) &srcg.Data4[0];
      const unsigned int *q = (const unsigned int*) &refg.Data4[0];
      return (*p != *q) || (*(p+1) != *(q+1));
   }
   return false;
}

__inline bool operator <(const GUID & refg, const GUID & srcg)
{
   if(&srcg != &refg)
   {

      if(refg.Data1 != srcg.Data1)
      {
         return (refg.Data1 < srcg.Data1);
      }
      if(refg.Data2 != srcg.Data2)
      {
         return (refg.Data2 < srcg.Data2);
      }
      if(refg.Data3 != srcg.Data3)
      {
         return (refg.Data3 < srcg.Data3);
      }
      const uint64_t *p = (const uint64_t*)&srcg.Data4[0];
      const uint64_t *q = (const uint64_t*) &refg.Data4[0];

      return (*q < *p);


   }
   return false;
}

__inline bool operator >(const GUID & refg, const GUID & srcg)
{
   if(&srcg != &refg)
   {

      if(refg.Data1 != srcg.Data1)
      {
         return (refg.Data1 > srcg.Data1);
      }
      if(refg.Data2 != srcg.Data2)
      {
         return (refg.Data2 > srcg.Data2);
      }
      if(refg.Data3 != srcg.Data3)
      {
         return (refg.Data3 > srcg.Data3);
      }
      const uint64_t *p = (const uint64_t*)&srcg.Data4[0];
      const uint64_t *q = (const uint64_t*) &refg.Data4[0];

      return (*q > *p);


   }
   return false;
}


// A CLSID is also a GUID
typedef GUID        CLSID;
#define REFCLSID    const CLSID &

// An IID is also a GUID
typedef GUID        IID;
#define REFIID      const IID &

#define IsEqualGUID(rguid1, rguid2) (!memcmp(&(rguid1), &(rguid2), sizeof(GUID)))
#define IsEqualCLSID(rclsid1, rclsid2) IsEqualGUID(rclsid1, rclsid2)
#define IsEqualIID(riid1, riid2) IsEqualGUID(riid1, riid2)

//
// Define common GUIDs
//
EXTERN_C const GUID IID_IUnknown;
EXTERN_C const GUID IID_IClassFactory;


//
// The IUnknown interface for COM handling.
//
interface IUnknown
{
    public:
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void ** ppvObject) = 0;

    virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
    virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    virtual ~IUnknown(){};
};

typedef IUnknown * LPUNKNOWN;

//
// COM loader method
//
STDAPI CoCreateInstance(REFCLSID  in_rclsid,
                        LPUNKNOWN in_pUnkOuter,
                        DWORD     in_dwClsContext,
                        REFIID    in_riid,
                        LPVOID  * out_ppv);

//
// the IClass Factory for COM creation
//
class IClassFactory : public IUnknown
{
   public:
   virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *pUnkOuter, REFIID riid, void ** ppvObject) = 0;
   virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock) = 0;

   virtual ~IClassFactory() {};
};


//
// Define unused DirectX definitions.
//
#define D3DFVF_XYZ  0
#define D3DFVF_TEX1 0

//
// The IDirect3DDevice9 does not exist in Linux
//
interface IDirect3DDevice9
{
    public:

    virtual ~IDirect3DDevice9(){};
};


//
// The IDirect3DSurface9 does not exist in Linux
//
interface IDirect3DSurface9
{
    public:

    virtual ~IDirect3DSurface9(){};
};

//
// The IDirect3DVertexShader9 does not exist in Linux
//
interface IDirect3DVertexShader9
{
    public:

    virtual ~IDirect3DVertexShader9(){};
};

//
// The IDirect3DVertexDeclaration9 does not exist in Linux
//
interface IDirect3DVertexDeclaration9
{
    public:

    virtual ~IDirect3DVertexDeclaration9(){};
};

//
// The IDirect3DVertexBuffer9 does not exist in Linux
//
interface IDirect3DVertexBuffer9
{
    public:

    virtual ~IDirect3DVertexBuffer9(){};
};

//
// The IDirect3DTexture9 does not exist in Linux
//
interface IDirect3DTexture9
{
    public:

    virtual ~IDirect3DTexture9(){};
};

//
// The IDirect3DIndexBuffer9 does not exist in Linux
//
interface IDirect3DIndexBuffer9
{
    public:

    virtual ~IDirect3DIndexBuffer9(){};
};


//
// The IDirect3DPixelShader9 does not exist in Linux
//
interface IDirect3DPixelShader9
{
    public:

    virtual ~IDirect3DPixelShader9(){};
};

//
// Rectangle definitions
//
typedef struct tagRECT
{
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
} RECT, D3DLOCKED_RECT;

typedef struct _MEMORYSTATUS
{
    DWORD dwLength;
    DWORD dwMemoryLoad;
    SIZE_T dwTotalPhys;
    SIZE_T dwAvailPhys;
    SIZE_T dwTotalPageFile;
    SIZE_T dwAvailPageFile;
    SIZE_T dwTotalVirtual;
    SIZE_T dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

typedef struct _OSVERSIONINFOW
{
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    WCHAR szCSDVersion[ 128 ];     // Maintenance string for PSS usage
} OSVERSIONINFOW, *POSVERSIONINFOW, *LPOSVERSIONINFOW, RTL_OSVERSIONINFOW, *PRTL_OSVERSIONINFOW;
typedef OSVERSIONINFOW OSVERSIONINFO;
typedef POSVERSIONINFOW POSVERSIONINFO;
typedef LPOSVERSIONINFOW LPOSVERSIONINFO;

typedef struct _SYSTEM_INFO {
    union {
        DWORD dwOemId;          // Obsolete field...do not use
        struct {
            WORD wProcessorArchitecture;
            WORD wReserved;
        };
    };
    DWORD dwPageSize;
    LPVOID lpMinimumApplicationAddress;
    LPVOID lpMaximumApplicationAddress;
    DWORD_PTR dwActiveProcessorMask;
    DWORD dwNumberOfProcessors;
    DWORD dwProcessorType;
    DWORD dwAllocationGranularity;
    WORD wProcessorLevel;
    WORD wProcessorRevision;
} SYSTEM_INFO, *LPSYSTEM_INFO;

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef DWORD EXECUTION_STATE;

#define _aligned_malloc(a,b)  memalign(b,a)
#define _aligned_free(a)  free(a)

#define SEVERITY_ERROR     1
#define IS_ERROR(Status)     ((uint32_t)(Status) >> 31 == SEVERITY_ERROR)


#define SECTION_QUERY                0x0001
#define SECTION_MAP_WRITE            0x0002
#define SECTION_MAP_READ             0x0004
#define SECTION_MAP_EXECUTE          0x0008
#define SECTION_EXTEND_SIZE          0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT 0x0020 // not included in SECTION_ALL_ACCESS

#define SECTION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SECTION_QUERY|\
                            SECTION_MAP_WRITE |      \
                            SECTION_MAP_READ |       \
                            SECTION_MAP_EXECUTE |    \
                            SECTION_EXTEND_SIZE)
#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_WRITECOPY         0x08
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD            0x100
#define PAGE_NOCACHE          0x200
#define PAGE_WRITECOMBINE     0x400
#define MEM_COMMIT           0x1000
#define MEM_RESERVE          0x2000
#define MEM_DECOMMIT         0x4000
#define MEM_RELEASE          0x8000
#define MEM_FREE            0x10000
#define MEM_PRIVATE         0x20000
#define MEM_MAPPED          0x40000
#define MEM_RESET           0x80000
#define MEM_TOP_DOWN       0x100000
#define MEM_WRITE_WATCH    0x200000
#define MEM_PHYSICAL       0x400000
#define MEM_LARGE_PAGES  0x20000000
#define MEM_4MB_PAGES    0x80000000
#define SEC_FILE           0x800000
#define SEC_IMAGE         0x1000000
#define SEC_RESERVE       0x4000000
#define SEC_COMMIT        0x8000000
#define SEC_NOCACHE      0x10000000
#define SEC_LARGE_PAGES  0x80000000
#define MEM_IMAGE         SEC_IMAGE
#define WRITE_WATCH_FLAG_RESET 0x01

//
// Define access rights to files and directories
//

//
// The FILE_READ_DATA and FILE_WRITE_DATA constants are also defined in
// devioctl.h as FILE_READ_ACCESS and FILE_WRITE_ACCESS. The values for these
// constants *MUST* always be in sync.
// The values are redefined in devioctl.h because they must be available to
// both DOS and NT.
//

#define FILE_READ_DATA            ( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory

#define FILE_WRITE_DATA           ( 0x0002 )    // file & pipe
#define FILE_ADD_FILE             ( 0x0002 )    // directory

#define FILE_APPEND_DATA          ( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY     ( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE ( 0x0004 )    // named pipe


#define FILE_READ_EA              ( 0x0008 )    // file & directory

#define FILE_WRITE_EA             ( 0x0010 )    // file & directory

#define FILE_EXECUTE              ( 0x0020 )    // file
#define FILE_TRAVERSE             ( 0x0020 )    // directory

#define FILE_DELETE_CHILD         ( 0x0040 )    // directory

#define FILE_READ_ATTRIBUTES      ( 0x0080 )    // all

#define FILE_WRITE_ATTRIBUTES     ( 0x0100 )    // all

#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ         (STANDARD_RIGHTS_READ     |\
                                   FILE_READ_DATA           |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_READ_EA             |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_WRITE        (STANDARD_RIGHTS_WRITE    |\
                                   FILE_WRITE_DATA          |\
                                   FILE_WRITE_ATTRIBUTES    |\
                                   FILE_WRITE_EA            |\
                                   FILE_APPEND_DATA         |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_EXECUTE      (STANDARD_RIGHTS_EXECUTE  |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_EXECUTE             |\
                                   SYNCHRONIZE)

#define FILE_SHARE_READ                 0x00000001
#define FILE_SHARE_WRITE                0x00000002
#define FILE_SHARE_DELETE               0x00000004
#define FILE_ATTRIBUTE_READONLY             0x00000001
#define FILE_ATTRIBUTE_HIDDEN               0x00000002
#define FILE_ATTRIBUTE_SYSTEM               0x00000004
#define FILE_ATTRIBUTE_DIRECTORY            0x00000010
#define FILE_ATTRIBUTE_ARCHIVE              0x00000020
#define FILE_ATTRIBUTE_DEVICE               0x00000040
#define FILE_ATTRIBUTE_NORMAL               0x00000080
#define FILE_ATTRIBUTE_TEMPORARY            0x00000100
#define FILE_ATTRIBUTE_SPARSE_FILE          0x00000200
#define FILE_ATTRIBUTE_REPARSE_POINT        0x00000400
#define FILE_ATTRIBUTE_COMPRESSED           0x00000800
#define FILE_ATTRIBUTE_OFFLINE              0x00001000
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x00002000
#define FILE_ATTRIBUTE_ENCRYPTED            0x00004000
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_LAST_ACCESS  0x00000020
#define FILE_NOTIFY_CHANGE_CREATION     0x00000040
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
#define FILE_ACTION_ADDED                   0x00000001
#define FILE_ACTION_REMOVED                 0x00000002
#define FILE_ACTION_MODIFIED                0x00000003
#define FILE_ACTION_RENAMED_OLD_NAME        0x00000004
#define FILE_ACTION_RENAMED_NEW_NAME        0x00000005
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1)
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1)
#define FILE_CASE_SENSITIVE_SEARCH      0x00000001
#define FILE_CASE_PRESERVED_NAMES       0x00000002
#define FILE_UNICODE_ON_DISK            0x00000004
#define FILE_PERSISTENT_ACLS            0x00000008
#define FILE_FILE_COMPRESSION           0x00000010
#define FILE_VOLUME_QUOTAS              0x00000020
#define FILE_SUPPORTS_SPARSE_FILES      0x00000040
#define FILE_SUPPORTS_REPARSE_POINTS    0x00000080
#define FILE_SUPPORTS_REMOTE_STORAGE    0x00000100
#define FILE_VOLUME_IS_COMPRESSED       0x00008000
#define FILE_SUPPORTS_OBJECT_IDS        0x00010000
#define FILE_SUPPORTS_ENCRYPTION        0x00020000
#define FILE_NAMED_STREAMS              0x00040000
#define FILE_READ_ONLY_VOLUME           0x00080000

//
// File functions
//

#define _O_RDONLY O_RDONLY
#define _O_WRONLY O_WRONLY
#define _O_CREAT  O_CREAT
#define _O_TRUNC  O_TRUNC
#define _O_BINARY 0

#define _SH_DENYRW 0

#define _S_IREAD S_IRUSR

inline int _wsopen_s(int *out_piFileDesc, const wchar_t *in_wszFileName, int in_iOpenFlags, int /*in_iShareFlags*/, int in_iPermFlags)
{
   char szFileName[MAX_PATH];

   // make sure the buffer is large enough
   ASSERT(wcstombs(NULL, in_wszFileName, 0) < MAX_PATH - 1);

   // convert and return the number of bytes copied
   const size_t kiBytes = wcstombs(szFileName, in_wszFileName, MAX_PATH - 1);

   // make sure it is null-terminated
   szFileName[kiBytes] = '\0';

   *out_piFileDesc = open(szFileName, in_iOpenFlags, in_iPermFlags);

   if (*out_piFileDesc == -1)
      return errno;

   return 0;
}

inline int fopen_s( FILE **out_ppFile, const char *in_kszFileName, const char *in_kszMode )
{
   *out_ppFile = fopen( in_kszFileName, in_kszMode );

   if( *out_ppFile == NULL )
   {
      return errno;
   }
   else
   {
      return 0;
   }
}

#define _read  read
#define _write write
#define _close close

typedef struct _OVERLAPPED {
  ULONG_PTR Internal;
  ULONG_PTR InternalHigh;
  union {
    struct {
      DWORD Offset;
      DWORD OffsetHigh;
    };
    PVOID  Pointer;
  };
  HANDLE    hEvent;
} OVERLAPPED, *LPOVERLAPPED;

//
// Error code macro.  build error code and test error code
//
#define MAKE_HRESULT( _ERROR_, _FACILITY_, _CODE_ ) \
 ( (HRESULT)( ((_ERROR_) << 31) | ((_FACILITY_ << 16) & 0x7FFF0000) | (_CODE_ & 0x0000FFFF) ) )

#define SUCCEEDED(hr)       ((HRESULT)(hr) >= 0)
#define FAILED(hr)          ((HRESULT)(hr) < 0)
#define ResultFromScode(hr) ((HRESULT)(hr))

#define WAIT_OBJECT_0                  0x00000000
#define WAIT_ABANDONED_0               0x00000080
#define WAIT_ABANDONED                 0x00000080
#define WAIT_IO_COMPLETION             0x000000C0
#define WAIT_TIMEOUT                   0x00000102
#define WAIT_FAILED                    0xFFFFFFFF

#define EVENT_ALL_ACCESS               0x1f0003
#define SYNCHRONIZE                    0x00100000
#define EVENT_MODIFY_STATE             0x0002


//
// Critical section replacement
//
inline void InitializeCriticalSection(CRITICAL_SECTION * in_psCriticalSection)
{
    pthread_mutexattr_t sAttr;


    pthread_mutexattr_init (&sAttr);
    pthread_mutexattr_settype (&sAttr, PTHREAD_MUTEX_RECURSIVE_NP);

    pthread_mutex_init (in_psCriticalSection, &sAttr);

    pthread_mutexattr_destroy (&sAttr);
}

inline void DeleteCriticalSection(CRITICAL_SECTION * in_psCriticalSection)
{
    pthread_mutex_destroy (in_psCriticalSection);
}


inline void EnterCriticalSection(CRITICAL_SECTION * in_psCriticalSection)
{
   pthread_mutex_lock (in_psCriticalSection);
}

inline bool TryEnterCriticalSection(CRITICAL_SECTION * in_psCriticalSection)
{
    return (pthread_mutex_trylock(in_psCriticalSection) == 0);
}

inline void LeaveCriticalSection(CRITICAL_SECTION * in_psCriticalSection)
{
   pthread_mutex_unlock (in_psCriticalSection);
}

//
// Thread ID
//
#ifndef MAC_PLATFORM
inline uint32_t GetCurrentThreadId(void)
{
    return pthread_self();
}
#else
inline pthread_t GetCurrentThreadId(void)
{
    return pthread_self();
}
#endif

//
// Process ID
//
inline uint32_t GetCurrentProcessId(void)
{
    return getpid();
}

//
// Process Handle
//
inline HANDLE GetCurrentProcess(void)
{
    return NULL;
}

//---------------------------------------------------------------------------
//
// mvGuidToString()
//
//---------------------------------------------------------------------------
inline std::wstring mvGuidToString(const CLSID & in_rGuid)
{
   std::wostringstream strCLSID;

   strCLSID << '{';
   strCLSID.fill('0');
   strCLSID.width(8);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data1 << '-';
   strCLSID.fill('0');
   strCLSID.width(4);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data2 << '-';
   strCLSID.fill('0');
   strCLSID.width(4);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data3 << '-';
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[0];
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[1];
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[2];
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[3];
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[4];
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[5];
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[6];
   strCLSID.fill('0');
   strCLSID.width(2);
   strCLSID << std::hex << std::uppercase << in_rGuid.Data4[7] << '}';

   return strCLSID.str();
}

#ifndef _countof
#define _countof(array) (sizeof((array))/sizeof((array)[0]))
#endif

inline HRESULT GetLastError(void)
{
   return 0;
}

#define	ZeroMemory(x, y)	memset(x, 0, y)

#ifndef _FILETIME_
#define _FILETIME_
typedef struct _FILETIME
{
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#endif

typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } u;
    uint64_t QuadPart;
} ULARGE_INTEGER;

typedef union _LARGE_INTEGER {
    struct {
        uint32_t LowPart;
        int32_t  HighPart;
    } DUMMYSTRUCTNAME;
    struct {
        uint32_t LowPart;
        int32_t  HighPart;
    } u;
    int64_t QuadPart;
} LARGE_INTEGER;


typedef LARGE_INTEGER *PLARGE_INTEGER;
typedef ULARGE_INTEGER *PULARGE_INTEGER;
typedef int64_t REFERENCE_TIME;


#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)
#define FILE_SHARE_READ                 0x00000001
#define FILE_SHARE_WRITE                0x00000002


#if 0

//Additional COM definition
#ifdef __cplusplus
   #define EXTERN_C     extern "C"
#else
   #define EXTERN_C     extern
#endif

#define STDAPICALLTYPE     __stdcall
//   #define STDAPICALLTYPE     __export __stdcall
#define STDMETHODCALLTYPE     __stdcall
#define STDMETHODIMP     HRESULT STDMETHODCALLTYPE
#define STDMETHODIMP_(type)     type STDMETHODCALLTYPE

#define STDAPI     EXTERN_C HRESULT STDAPICALLTYPE


typedef GUID		IID;
#define REFIID		const IID &
typedef GUID		CLSID;
#define REFCLSID	const CLSID &

//Objbase from windows
#define interface struct
#define STDMETHOD(method)       virtual HRESULT STDMETHODCALLTYPE method
#define STDMETHOD_(type,method) virtual type STDMETHODCALLTYPE method
#define PURE                    = 0
#define THIS_
#define THIS                    void
#define DECLARE_INTERFACE(a) interface a
#define DECLARE_INTERFACE_(a, b) interface a : public b

//Macro to declare GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)	\
	EXTERN_C const GUID name

#define DEFINE_GUID_LINUX(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8)	\
	EXTERN_C const GUID __declspec(selectany) name = {l, w1, w2, {b1, b2, b3, b4, b5, b6, b7, b8}}

//Interface
interface IUnknown
{
	public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(
		REFIID riid,
		void ** ppvObject) = 0;

	virtual ULONG STDMETHODCALLTYPE AddRef(void) = 0;
	virtual ULONG STDMETHODCALLTYPE Release(void) = 0;

    virtual ~IUnknown(){};
};

typedef IUnknown * LPUNKNOWN;

//EXTERN_C const GUID IID_IUnknown;
DEFINE_GUID(IID_IUnknown, 0x00000000, 0x0000,0x000, 0xC0,0x0,0x0,0x0,0x0,0x0,0x0,0x46);


//JUST FOR Proof of Concept REMOVE THIS
#define InterlockedIncrement(a) (*a)++
#define InterlockedDecrement(a) (*a)--


DEFINE_GUID(CLSID_IDumbFactory, 0x0000beef,
   0x0000,0x000, 0xC0,0x0,0x0,0x0,0x0,0x0,0x8,0x02);

DEFINE_GUID(IID_IDumbFace,
	0x0000beef, 0x0000,0x000, 0xC0,0x0,0x0,0x0,0x0,0x0,0x0,0x01);

DEFINE_GUID(IID_IDumbFactory, 0x0000beef,
	0x0000,0x000, 0xC0,0x0,0x0,0x0,0x0,0x0,0x0,0x02);


#endif // 0

#endif // MV_LINUX_DEFINITIONS_H
