#ifndef BUFFERMNG_H
#define BUFFERMNG_H
#include <deque>
#include "Omni_TypeDef.h"
#include "os_supports.h"

//[Omni_SDK] 16字节对齐的宏
#define GET_ALIGN_ADDR_16(P) (((reinterpret_cast<Om_UINT_PTR>(P)+0x0f) & (((Om_UINT_PTR)(-1)) << 4)))

#define AUD_SIZE (128*1024)
//节点结构定义
struct SData
{
	uint8_t* pV; //unsigned char *pV;
	unsigned int wid;
	unsigned int hig;
	unsigned int pitch;
	Omn_COLOR_FORMAT clr;

	unsigned char *pA;
	unsigned int audLen;
};

//Buffer管理
class CBufMng
{
	std::deque <SData> mFreeList;
	std::deque <SData> mDataList;
	CPrivateMutex mtFree;
	CPrivateMutex mtData;

public:
	CBufMng(unsigned int vidSize, unsigned int audSize = AUD_SIZE, unsigned int bufCount = 10);
	~CBufMng();
	void GetFreeBuf(SData *p);
	void PutFreeBuf(SData *p);
	void GetDataBuf(SData *p);
	void PutDataBuf(SData *p);
};

#endif
