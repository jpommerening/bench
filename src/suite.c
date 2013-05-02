#include "internal.h"

test_result_t suite_run( const suite_t* suite ) {
  suite_status_t status = SUITE_STATUS_INIT(suite);
  listener_t* listener = listener_progress();

  return suite_status_run( &status, listener );
}

test_result_t suite_status_run( suite_status_t* status,
                                listener_t* listener ) {
  const suite_t* suite = status->suite;
  int i;

  listener_suite_start( listener, status );

  for( i=0; suite->tests[i] != NULL; i++ ) {
    test_status_t test = TEST_STATUS_INIT(suite->tests[i]);

    test_status_run( &test, listener );

    status->ms += test.ms;
    status->result = WORST_RESULT(status->ms, test.ms);
    status->count[ test.result ] += 1;

    listener_suite_step( listener, status );
  }

  listener_suite_end( listener, status );

  return status->result;
}

