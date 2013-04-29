#include "internal.h"
#include <sys/time.h>

static void test__run( test_status_t* status, const void* data, listener_t* listener ) {
  struct timeval start, finish;
  test_result_t result;

  gettimeofday( &start, NULL );
  result = run( status->test, data, listener );
  gettimeofday( &finish, NULL );

  status->ms += 1000. * (finish.tv_sec  - start.tv_sec)
              + 0.001 * (finish.tv_usec - start.tv_usec);
  status->result = WORST_RESULT( status->result, result );
}

test_result_t test_run( const test_t* test ) {
  test_status_t status = TEST_STATUS_INIT(test);
  listener_t* listener = NULL;

  return test_status_run( &status, listener );
}

test_result_t test_status_run( test_status_t* status,
                               listener_t* listener ) {
  const test_t* test = status->test;
  int i;

  listener_test_start( listener, status );

  for( i=0; (unsigned)i<test->datalength; i++ ) {
    test__run( status, (const char*)test->data + (i*test->datastep), listener );
    listener_test_step( listener, status );
  }

  listener_test_end( listener, status );

  return status->result;
}

