/* ===== file header ===== */

/* ===== includes ===== */
#include <stdio.h>
#include "System.h"

/* ===== provate datatypes ===== */

/* ===== private symbols ===== */

/* ===== private constants ===== */

/* ===== public constants ===== */

/* ===== private variables ===== */

/* ===== public variables ===== */

/* ===== private functions ===== */

/*===== public functions ===== */
void SystemInit (void)
{
  /* switch of buffering for stdin */  
  setvbuf( stdin, NULL, _IONBF , 0);

  /* switch of buffering for stdout */  
  setvbuf( stdout, NULL, _IONBF , 0);

  /* switch of buffering for stderr */  
  setvbuf( stderr, NULL, _IONBF , 0);
}

