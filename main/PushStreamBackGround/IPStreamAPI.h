#ifndef _IPSTREAMAPI_
#define _IPSTREAMAPI_

#include <map>
#include "ConfPara.h"
#ifdef __cplusplus
extern "C"	{
#endif    //__cplusplus

//�������������Ͷ���Ӧ�ͽ�����·һ��
enum VideoFormat
{
	AVC =       0,
	MPEG2 = AVC+1,
	HEVC = MPEG2+1,
};

typedef struct  _tagVideoEncConfPara
{
	VideoFormat videoFormat;
	int encode_preset;
	int encode_profile;
	int encode_level;
	int encode_gopSize;
	int encode_interlace_mode;
	int encode_bitrate;
	int encode_performance;
}VideoEncConfPara;

typedef struct _tagRenderConfPara
{
	char* cServerNic;
	char* cIP;
	DWORD dwPort;
	unsigned RenderType;
	int dektecCachebyte;
	char* dektec_serial_number;
	char* dektec_serial_number_bak;
	bool isRedundancy;
	char* cServerNic_bak;
	char* cIP_bak;
	DWORD dwPort_bak;
}RenderConfPara;

typedef struct _tagNetSourcePara
{
	char* cServerNic;
	char* cIP;
	DWORD dwPort;
}NetSourcePara;

enum RenderType
{
	MCRender = 0,
	FounderRender =1,
	DekTec = 2,
	DtRender = 3,
};

struct IPStream_API
{
	virtual bool vPlayCueWithData(
		 LPCWSTR lpwsClipPath,
		 __int64 som,
		 __int64 duration,
		 int videoFormat,
		 int audioFormat,
		 int audioGain,
		 int videoCacheCount,
		 int audioCacheCount) = 0;

	virtual int  vPlay()   = 0;
	virtual bool vRelease() = 0;
};

IPStream_API* __stdcall CreateInstanceIPStreamAPI(VideoEncConfPara* videoPara,AudioEncConfParas* audioParas,Mp2MuxConfPara* muxPara,RenderConfPara* renderPara, int nCacheFrames, LPCWSTR virtualSourceName);
IPStream_API* __stdcall CreateInstanceIPStreamRemuxAPI(NetSourcePara* netsourcePara,Mp2MuxConfPara* muxPara, RenderConfPara* renderPara);

#ifdef __cplusplus
};

#endif	//__cplusplus
#endif//_IPSTREAMAPI_