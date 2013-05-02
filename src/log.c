#include "log.h"
#include "term.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define N_ELEM(a) (int)(sizeof(a)/sizeof(a[0]))


void log_open( log_t* log, const char* name ) {
  static struct {
    const char* name;
    int fd;
  } special[] = {
    { "stdout", 1 },
    { "-", 1 },
    { "stderr", 2 }
  };
  int i, fd = -1;

  term_t term;

  log->file = NULL;
  log->isatty = false;

  term.lines = 1;
  term.columns = 132;
  term.colors = 2;
  term.unicode = true;

  for( i=0; i<N_ELEM(special); i++ ) {
    if( strcmp(special[i].name, name) == 0 ) {
      fd = special[i].fd;
      break;
    }
  }
  if( fd == -1 ) {
    fd = open(name, O_WRONLY);
  }
  if( fd >= 0 ) {
    log->file   = fdopen(fd, "w+");
    log->isatty = isatty(fd);
  }
  if( log->isatty && termcap( &term ) == 0 ) {
    log->lines   = term.lines;
    log->columns = term.columns;
    log->colors  = term.colors;
    log->unicode = term.unicode;
  }
  log_fmt( log, "colors: %hi, lines: %hi, columns: %i\n", log->colors, log->lines, log->columns );
}

void log_close( log_t* log ) {
  if( log->file ) {
    fclose( log->file );
    log->file = NULL;
  }
}

void log_fmt( log_t* log, const char* fmt, ... ) {
  va_list vargs;
  va_start(vargs, fmt);
  log_vfmt( log, fmt, vargs );
  va_end(vargs);
}

void log_vfmt( log_t* log, const char* fmt, va_list vargs ) {
  vfprintf( log->file, fmt, vargs );
}
