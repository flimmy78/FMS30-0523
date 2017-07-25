#pragma once

#ifdef ENCODELINK_EXPORTS
#define ENCODELINK_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define ENCODELINK_API __declspec(dllimport)
#define EXPIMP_TEMPLATE
#endif

//复用参数
class ENCODELINK_API Mp2MuxConfPara
{
public:
	Mp2MuxConfPara();
	~Mp2MuxConfPara();
	void AddAudioPid(int iAudio, int audioPid);
	int GetAudioPid(int iAudio);

	int GetVideoPid();
	void SetVideoPid(int videoPid);

	long GetBitRate();
	void SetBitRate(long bitRate);

	bool GetPaddingOn();
	void SetPaddingOn(bool isPaddingOn);


private:
	class Impl;
	Impl* m_impl;
};

//音频编码
enum AudioFormat
{
	MPEG1_LAYER2 = 0,
	AC3 = MPEG1_LAYER2 + 1,
	AAC = MPEG1_LAYER2 + 2,
};

typedef struct _tagAudioEncConfPara
{
	AudioFormat audioFormat;
	int layer;
	int bitrate;
	bool hasMatchPid; //用于与音频pid匹配
}AudioEncConfPara;

class ENCODELINK_API AudioEncConfParas
{
public:
	AudioEncConfParas();
	~AudioEncConfParas();
	void AddAudioEncConfPara(int iAudio, const AudioEncConfPara& audioPara);
	AudioEncConfPara* GetAudioEncConfPara(int iAudio);
	int GetCount();//get audio count
private:
	class Impl;
	Impl* m_impl;
};
