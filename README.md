# test

> *Dead-simple, modern, fun, unit testing for C.*

## How to use this?

Compile your tests to a library and run it with the test-runner.

```console
you@yourbox$ utest yourlib.so
TEST this_test_passes: PASS [0.010ms]
TEST this_test_fails: ...
test/test-something-broken.c:30: This should work.
 ... this_test_fails: FAIL [0.140ms]
TEST this_test_will_be_skipped: SKIP [0.003ms]
RESULTS: 1 passed, 1 failed, 1 skipped
you@yourbox$ echo "$?"
1
```

Wait, where did those tests come from?

```C
#include "test.h"

TEST( this_test_passes ) {
  ASSERT(1, "Should be fine.");
}
TEST( this_test_fails ) {
  ASSERTEQ(1, 2, "This should work". );
}
TEST( this_test_will_be_skipped ) {
  SKIP;
}
```

## Options

* `-l <listener>` - use the given listener
* `-o <output>` - write to the given output file
* `-c <config>` - read commands from the given config file
* `-e <script>` - evaluate the given commands
* `-i` - interactive mode

## Commands

```
add listener <name> <output/options>
remove listener <name>
include <file>
run [all]
run test <testname>
run suite <suitename>
run match <test-pattern>
```

## [License](LICENSE-BSD)

Copyright &copy; 2013, Jonas Pommerening <jonas.pommerening@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1.  Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer. 
2.  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
