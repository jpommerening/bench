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


