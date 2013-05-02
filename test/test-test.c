#include "test.h"
#include "test.h"

TEST( pass ) {
  MSG( "Everything's fine." );
}
TEST( warn ) {
  WARN( "Oops. Oh, oh." );
}
TEST( skip ) {
  SKIP( "I'm so in trouble." );
}
TEST( fail ) {
  FAIL( "" );
}

typedef struct test_data_s test_data_t;
struct test_data_s {
  const char* str;
  int num;
};

test_data_t test_data[] = {
  { "One", 1 },
  { "Two", 2 },
  { "Three", 3 }
};

TEST( data_pass, test_data, test_data_t* data ) {
  ASSERT( data->num < 4 );
}
