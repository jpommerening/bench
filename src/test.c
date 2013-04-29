#define _IN_TEST_
#include "test.h"
#include "internal.h"

#include <stdlib.h>

void test_init( test_t* test ) {
  test->data = NULL;
}

void test_destroy( test_t* test ) {
  if( test->data != NULL ) {
    free( test->data );
  }
}

