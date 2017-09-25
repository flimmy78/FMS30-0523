#pragma once


// Standard output functions.
void info_printf(const char * fmt, ...);
//
void warn_printf(const char * fmt, ...);
void error_printf(const char * fmt, ...);
void progress_printf(int32_t percent, const char * fmt, ...);
// resource functions dispatcher
void * get_rc(const char* name);

