#ifndef _TEST_INTERNAL_H_
#define _TEST_INTERNAL_H_
#include "test.h"

typedef struct test_status_s test_status_t;
struct test_status_s {
  const test_t* test;
  test_result_t result;
  double ms;
};
#define TEST_STATUS_INIT(test) { \
  test, \
  TEST_UNKNOWN, \
  0. \
}

typedef struct suite_status_s suite_status_t;
struct suite_status_s {
  const suite_t* suite;
  test_result_t result;
  double ms;
  int count[TEST_RESULT_MAX];
};
#define SUITE_STATUS_INIT(suite) { \
  suite, \
  TEST_UNKNOWN, \
  0., \
  { 0, 0, 0, 0, 0, 0 } \
}

#define WORST_RESULT(a,b) ((a>b) ? (a) : (b))

#include "listener.h"

test_result_t run( const test_t* test, const void* data, listener_t* listener );

test_result_t suite_run( const suite_t* suite );
test_result_t suite_status_run( suite_status_t* status,
                                listener_t* listener );

test_result_t test_run( const test_t* test );
test_result_t test_status_run( test_status_t* status,
                               listener_t* listener );

#endif
