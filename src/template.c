#define _IN_TEMPLATE_
#include "template.h"
#include "internal.h"

#include <stdlib.h>

void template_init( template_t* template ) {
  template->data = NULL;
}

void template_destroy( template_t* template ) {
  if( template->data != NULL ) {
    free( template->data );
  }
}

