/*   ===== File Header ===== */
/* not used */

/*   ===== Includes ===== */
#include <stdio.h>
#include "System.h"

/*   ===== Preprocessor Switches ===== */
/* not used */

/*   ===== Local Datatypes ===== */
/* not used */

/*   ===== Local Symbols ===== */
/* not used */

/*   ===== Local Constants ===== */
/* not used */

/*   ===== Global Constants ===== */
const UINT16 u16SystemVersion = SYSTEM_VERSION;

/*   ===== Local Variables ===== */
/* not used */

/*   ===== Global Variables ===== */
/* not used */

/*   ===== Local Functions ===== */
/* not used */

/*   ===== Global Functions ===== */
void vSystemInit (void)
{
  /* switch of buffering for stdin */  
  setvbuf( stdin, NULL, _IONBF , 0);

  /* switch of buffering for stdout */  
  setvbuf( stdout, NULL, _IONBF , 0);

  /* switch of buffering for stderr */  
  setvbuf( stderr, NULL, _IONBF , 0);
}

