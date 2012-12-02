#include "template.h"
#include "test.h"

TEST( test_template ) {
  template_t template = TEMPLATE_INIT;
  ASSERT( 0, "Congratulations, your test fails!" );
  template_destroy( &template );
}

