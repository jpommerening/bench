#ifndef _TEST_LISTENER_H_
#define _TEST_LISTENER_H_
#include <stdarg.h>

typedef struct listener_s listener_t;

#include "internal.h"

typedef void (*listener_suite_cb)( listener_t* listener, const suite_status_t* suite );
typedef void (*listener_test_cb)( listener_t* listener, const test_status_t* test );
typedef void (*listener_log_cb)( listener_t* listener, const char* file, int line, const char* fmt, va_list vargs );

struct listener_s {
  listener_t* next;
  void* data;

  listener_suite_cb suite_start;
  listener_suite_cb suite_step;
  listener_suite_cb suite_end;
  listener_test_cb test_start;
  listener_test_cb test_step;
  listener_test_cb test_end;
  listener_log_cb log;
};

void listener_suite_start( listener_t* listener, const suite_status_t* suite );
void listener_suite_step( listener_t* listener, const suite_status_t* suite );
void listener_suite_end( listener_t* listener, const suite_status_t* suite );
void listener_test_start( listener_t* listener, const test_status_t* test );
void listener_test_step( listener_t* listener, const test_status_t* test );
void listener_test_end( listener_t* listener, const test_status_t* test );
void listener_log( listener_t* listener, const char* file, int line, const char* fmt, va_list vargs );

#endif
