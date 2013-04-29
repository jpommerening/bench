#include "listener.h"

#define EACH(listener) for( ; listener != NULL ; listener = listener->next )

void listener_suite_start( listener_t* listener, const suite_status_t* suite ) {
  EACH(listener)
    (listener->suite_start)( listener, suite );
}

void listener_suite_step( listener_t* listener, const suite_status_t* suite ) {
  EACH(listener)
    (listener->suite_step)( listener, suite );
}

void listener_suite_end( listener_t* listener, const suite_status_t* suite ) {
  EACH(listener)
    (listener->suite_end)( listener, suite );
}

void listener_test_start( listener_t* listener, const test_status_t* test ) {
  EACH(listener)
    (listener->test_start)( listener, test );
}

void listener_test_step( listener_t* listener, const test_status_t* test ) {
  EACH(listener)
    (listener->test_step)( listener, test );
}

void listener_test_end( listener_t* listener, const test_status_t* test ) {
  EACH(listener)
    (listener->test_end)( listener, test );
}

void listener_log( listener_t* listener, const char* file, int line, const char* fmt, va_list vargs ) {
  va_list vargs_copy;
  EACH(listener) {
    va_copy( vargs_copy, vargs );
    (listener->log)( listener, file, line, fmt, vargs_copy );
  }
}

