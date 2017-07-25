
#include "common.h"
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
namespace caspar {
	namespace sdiopi_20226 {

		void OutputString(const char* format, ...)
		{
			va_list args;
			va_start(args, format);
			char buf[256];
			vsnprintf_s(buf, 232, format, args);
			OutputDebugString((LPCWSTR)buf);
			va_end(args);
		}
	}
}