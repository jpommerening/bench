#include "internal.h"
#include <stdarg.h>
#include <setjmp.h>

typedef struct test_context_s test_context_t;
struct test_context_s {
  listener_t* listener;
  test_result_t result;
  jmp_buf* env;
};

void test__log( void* data, const char* file, int line, const char* fmt, ... ) {
  test_context_t* context = data;
  va_list vargs;

  va_start(vargs, fmt);
  listener_log( context->listener, file, line, fmt, vargs );
  va_end(vargs);
}

void test__result( void* data, test_result_t result ) {
  test_context_t* context = data;
  context->result = WORST_RESULT( context->result, result );
}

void test__exit( void* data ) {
  test_context_t* context = data;
  longjmp(*(context->env), 1);
}

test_result_t run( const test_t* test, const void* data, listener_t* listener ) {
  jmp_buf env;
  test_context_t context = { listener, TEST_UNKNOWN, &env };
  const test_api_t api = { &context, &test__log, &test__result, &test__exit };

  if( setjmp(env) ) {

  } else if( data ) {
    (test->callback.data_cb)( &api, data );
  } else {
    (test->callback.void_cb)( &api );
  }

  return context.result;
}
