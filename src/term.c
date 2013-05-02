#include "term.h"

#if USE_TERMCAP
#include <termcap.h>
#elif USE_TERMIOS
#include <termios.h>
#include <sys/ioctl.h>
#endif

int termcap( term_t* term ) {
#if USE_TERMCAP
  static char termbuf[2048];
  char* term;
  if( (term=getenv("TERM")) != NULL && tgetent(termbuf, term) == 1 ) { 
    term->lines   = tgetnum("li");
    term->columns = tgetnum("co");
    term->colors  = tgetnum("Co");
    return 0;
  } else {
    return -1;
  }
#elif USE_TERMIOS
  struct winsize ws;
  if( ioctl(1, TIOCGWINSZ, &ws) != -1) {
    term->lines   = ws.ws_row;
    term->columns = ws.ws_col;
    return 0;
  } else {
    return -1;
  }
#endif
}
