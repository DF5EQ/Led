/* ===== file header ===== */

/* ===== includes ===== */
#include <stdio.h>
#include "system.h"

/* ===== provate datatypes ===== */

/* ===== private symbols ===== */

/* ===== private constants ===== */

/* ===== public constants ===== */

/* ===== private variables ===== */

/* ===== public variables ===== */

/* ===== private functions ===== */

/*===== public functions ===== */
void system_init (void)
{
  /* switch of buffering for stdin */  
  setvbuf( stdin, NULL, _IONBF , 0);

  /* switch of buffering for stdout */  
  setvbuf( stdout, NULL, _IONBF , 0);

  /* switch of buffering for stderr */  
  setvbuf( stderr, NULL, _IONBF , 0);
}

