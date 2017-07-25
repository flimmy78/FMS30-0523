#pragma once
namespace caspar {
	namespace sdiopi_20226 {
#define AUDIO_GROUPS     4
#define AUDIO_CHANNELS  16
#define AUDIO_SAMPLES_PER_FRAME_CHANNEL (48000 / 25)

		enum FRAME {
			PAL,
			PAL1080,
			OTHER
		};

		typedef void(*RECEIVE_DATA)(void* p, int size, void* caller);

		void OutputString(const char* format, ...);
	}
}