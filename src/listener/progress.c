#include "listener.h"
#include "log.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct context_s context_t;
struct context_s {
  log_t* log;
  bool v;
};

static void progress_suite_start( listener_t* listener, const suite_status_t* suite ) {
  log_t* log = listener->data;
  log_fmt( log, "\033[s" );
}

static void progress_suite_step( listener_t* listener, const suite_status_t* suite ) {
}

static void progress_suite_end( listener_t* listener, const suite_status_t* suite ) {
  log_t* log = listener->data;
  log_fmt( log, "\033[0m\n" );
}

static void progress_test_start( listener_t* listener, const test_status_t* test ) {
  log_t* log = listener->data;
  log_fmt( log, "\033[u\033[K\033[s\033[32mTEST %s", test->test->name );
}

static void progress_test_step( listener_t* listener, const test_status_t* test ) {
  log_t* log = listener->data;
  log_fmt( log, "." );
}

static void progress_test_end( listener_t* listener, const test_status_t* test ) {
  log_t* log = listener->data;
  if( test->result != TEST_PASS ) {
    log_fmt( log, "\033[u\033[K\033[31mTEST %s failed(%i) [%.3lfms]\033[0m\n\033[s", test->test->name, test->result, test->ms );
  }
}

static void progress_log( listener_t* listener, const char* file, int line, const char* fmt, va_list vargs ) {
  log_t* log = listener->data;
  log_fmt( log, "\033[u\033[K\033[0m%s:%i: ", file, line );
  log_vfmt( log, fmt, vargs );
  log_fmt( log, "\n\033[s" );
}

listener_t* listener_progress( void ) {
  static log_t log;
  static listener_t progress = {
    NULL,
    &log,
    &progress_suite_start,
    &progress_suite_step,
    &progress_suite_end,
    &progress_test_start,
    &progress_test_step,
    &progress_test_end,
    &progress_log
  };
  log_open( &log, "stdout" );
  return &progress;
}
