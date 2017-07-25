#pragma once


typedef enum  LOGIN_DOG_RES_
{
	//��¼ʧ��
	LOGIN_DOG_ERROR	= 0	,

	// 2ͨ��SDI
	LOGIN_DOG_1_CHANNEL = 100	,

	// 4ͨ��SDI
	LOGIN_DOG_2_CHANNEL = 101	,

	//1ͨ��IP
	LOGIN_DOG_3_CHANNEL = 102 ,

	//3ͨ��IP
	LOGIN_DOG_4_CHANNEL = 103 ,

	LOGIN_DOG_5_CHANNEL = 104,
	LOGIN_DOG_6_CHANNEL = 105,

}LOGIN_DOG_RES;

#if !defined (_WIN32) && !defined (_WIN64)
#define LINUX
#else
#define WINDOWS
#endif
#if defined (WINDOWS)
#define _DLL_EXPORT	__declspec(dllexport)

typedef int (*LoginDog_)(int);

LoginDog_		Login_Dog = NULL;

HMODULE		g_LDKDogLib = NULL;

void					FreeBaseLib();

extern "C" _DLL_EXPORT int  LoginLDKDog(__in int ProcType);

BOOL LoadBaseLib()
{
	g_LDKDogLib = LoadLibraryA("LDKDogLicens.dll");
	if (NULL == g_LDKDogLib)
	{
		return FALSE;
	}

	Login_Dog = (LoginDog_)GetProcAddress(g_LDKDogLib, "LoginLDKDog");

	if (!Login_Dog)
	{
		FreeBaseLib();
		return FALSE;
	}
	return TRUE;
}

void FreeBaseLib()
{
	FreeLibrary(g_LDKDogLib);
	g_LDKDogLib = NULL;
	Login_Dog = NULL;
}

//��̬����
int  LoginLDKDogEx(__in int ProcType)
{
	int  nRes = 0;
	if (!LoadBaseLib())
	{
		return 0;
	}
	nRes = Login_Dog(ProcType);

// 	if (!nRes)
// 	{
// 		FreeBaseLib();
// 		return FALSE;
// 	}

	FreeBaseLib();
	return nRes;
}
#endif
#if defined (LINUX)
#include "hasp_api_cpp.h"
#include "vendor_code.h"
#ifndef LINUXDOG
#define LINUXDOG
int LoginLDKDog(int type)
{
	haspStatus status;
	Chasp hasp(ChaspFeature::fromFeature(type));
	status = hasp.login(vendorCode);
	if (!HASP_SUCCEEDED(status))
	{
		//displayCloseMessage();
		return 0;
	}
	return type;
}
#endif
#endif