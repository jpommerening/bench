#include "test.h"
#include "internal.h"

int main( /* int argc, char* argv[] */ ) {
  suite_t suite = {
    "default",
    "",
    __DATE__,
    __TIME__,
    &(tests[0]),
  };
  
  return (suite_run( &suite ) == TEST_PASS) ? 0 : 1;
}
