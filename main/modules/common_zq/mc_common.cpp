#pragma once
#include <common/log.h>

void info_printf(const char * fmt, ...)
{
	char lst[1024];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(info) << lst;
}

void warn_printf(const char * fmt, ...)
{
	char lst[2048];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(warning) << lst;
}

void error_printf(const char * fmt, ...)
{
	char lst[256];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(error) << lst;
}

void progress_printf(int32_t percent, const char * fmt, ...)
{
	char lst[256];
	va_list marker;

	va_start(marker, fmt);
	vsnprintf(lst, sizeof(lst), fmt, marker);
	va_end(marker);

	CASPAR_LOG(info) << percent << L" - " << lst;
}

void* mmalloc(size_t _Size) {
	return malloc(_Size);
}

void mfree(void* _Block) {
	free(_Block);
}

// resource functions dispatcher
void * get_rc(const char* name)
{
	if (!strcmp(name, "err_printf"))
		return (void*)error_printf;
	else if (!strcmp(name, "prg_printf"))
		return (void*)progress_printf;
	else if (!strcmp(name, "wrn_printf"))
		return (void*)warn_printf;
	else if (!strcmp(name, "inf_printf"))
		return (void*)info_printf;
	else if (!strcmp(name, "malloc"))
		return (void*)mmalloc;
	else if (!strcmp(name, "free"))
		return (void*)mfree;

	return nullptr;
}
