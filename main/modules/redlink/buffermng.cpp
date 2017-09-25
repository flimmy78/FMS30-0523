#include "buffermng.h"
#include "memory.h"

CBufMng::CBufMng(unsigned int vidSize, unsigned int audSize, unsigned int bufCount)
	: mFreeList(0)
	, mDataList(0)
{
	SData sDat;
	for (Om_UINT8 i = 0; i<bufCount; i++)
	{
		sDat.pV = new unsigned char[vidSize + 16];
		sDat.wid = 0;
		sDat.hig = 0;
		sDat.pitch = 0;
		sDat.pA = new unsigned char[audSize];
		sDat.audLen = 0;
		memset(sDat.pV, 0, vidSize);
		memset(sDat.pA, 0, audSize);
		mFreeList.push_back(sDat);
	}
}

CBufMng::~CBufMng()
{
	std::deque<SData>::iterator Iter;
	SData *p;
	mtFree.lock();
	for (Iter = mFreeList.begin(); Iter != mFreeList.end(); ++Iter)
	{
		p = &(*Iter);
		if (p->pV)
		{
			delete[]p->pV;
			p->pV = NULL;
			p->wid = 0;
			p->hig = 0;
			p->pitch = 0;
		}
		if (p->pA)
		{
			delete[]p->pA;
			p->pA = NULL;
			p->audLen = 0;
		}

	}
	mFreeList.clear();
	mtFree.unlock();;

	mtData.lock();
	for (Iter = mDataList.begin(); Iter != mDataList.end(); ++Iter)
	{
		p = &(*Iter);
		if (p->pV)
		{
			delete[]p->pV;
			p->pV = NULL;
			p->wid = 0;
			p->hig = 0;
			p->pitch = 0;
		}
		if (p->pA)
		{
			delete[]p->pA;
			p->pA = NULL;
			p->audLen = 0;
		}
	}
	mDataList.clear();
	mtData.unlock();
}

void CBufMng::GetFreeBuf(SData *p)
{
	mtFree.lock();
	if (!mFreeList.empty())
	{
		*p = mFreeList.front();
		mFreeList.pop_front();
	}
	else
	{
		p->pV = NULL;
		p->wid = 0;
		p->hig = 0;
		p->pitch = 0;
		p->pA = NULL;
		p->audLen = 0;
	}
	mtFree.unlock();
}

void CBufMng::PutFreeBuf(SData *p)
{
	mtFree.lock();
	mFreeList.push_back(*p);
	mtFree.unlock();
}

void CBufMng::GetDataBuf(SData *p)
{
	mtData.lock();
	if (!mDataList.empty())
	{
		*p = mDataList.front();
		mDataList.pop_front();
	}
	else
	{
		p->pV = NULL;
		p->wid = 0;
		p->hig = 0;
		p->pitch = 0;
		p->pA = 0;
		p->audLen = 0;
	}
	mtData.unlock();
}

void CBufMng::PutDataBuf(SData *p)
{
	mtData.lock();
	mDataList.push_back(*p);
	mtData.unlock();
}
		


