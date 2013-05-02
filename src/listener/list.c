#include "listener.h"
#include "log.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct context_s context_t;
struct context_s {
  log_t* log;
};

static void list_suite_start( listener_t* listener, const suite_status_t* suite ) {
}

static void list_suite_step( listener_t* listener, const suite_status_t* suite ) {
}

static void list_suite_end( listener_t* listener, const suite_status_t* suite ) {
  context_t* context = listener->data;
  log_fmt( context->log, "RESULTS: %i passed, %i failed, %i skipped [%.3lfms]\n",
                         suite->count[TEST_PASS],
                         suite->count[TEST_FAIL],
                         suite->count[TEST_SKIP],
                         suite->ms );
}

static void list_test_start( listener_t* listener, const test_status_t* test ) {
  context_t* context = listener->data;
  log_fmt( context->log, "TEST %s: ", test->test->name );
}

static void list_test_step( listener_t* listener, const test_status_t* test ) {
}

static void list_test_end( listener_t* listener, const test_status_t* test ) {
  context_t* context = listener->data;
  log_fmt( context->log, "done [%.3lfms]\n", test->ms );
}

static void list_log( listener_t* listener, const char* file, int line, const char* fmt, va_list vargs ) {
  context_t* context = listener->data;
  log_fmt( context->log, "\n%s:%i: ", file, line );
  log_vfmt( context->log, fmt, vargs );
}

listener_t* listener_list( void ) {
  static log_t log;
  static context_t context = {
    &log
  };
  static listener_t list = {
    NULL,
    &context,
    &list_suite_start,
    &list_suite_step,
    &list_suite_end,
    &list_test_start,
    &list_test_step,
    &list_test_end,
    &list_log
  };
  log_open( &log, "stdout" );
  return &list;
}
