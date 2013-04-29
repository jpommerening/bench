#include "test.h"
#include "test.h"

TEST( test_test ) {
  test_t test = TEST_INIT;
  ASSERT( 0, "Congratulations, your test fails!" );
  test_destroy( &test );
}

