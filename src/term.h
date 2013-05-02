#ifndef _TEST_TERM_H_
#define _TEST_TERM_H_

#include <stdbool.h>

typedef struct term_s term_t;
struct term_s {
  short lines;
  short columns;
  short colors;
  bool unicode;
};

int termcap( term_t* term );

#endif
