#ifndef _TEST_LOG_H_
#define _TEST_LOG_H_
#if !defined(_POSIX_SOURCE)
#define _POSIX_SOURCE 1
#endif
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

typedef struct log_s log_t;
struct log_s {
  FILE* file;
  bool isatty;
  bool unicode;

  short lines;
  short columns;
  short colors;
};

void log_open( log_t* log, const char* name );
void log_close( log_t* log );

void log_fmt( log_t* log, const char* fmt, ... )
              __attribute__((format (printf,2,3)));
void log_vfmt( log_t* log, const char* fmt, va_list vargs );

#endif
