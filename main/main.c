/* ===== file header ===== */

/* ===== includes ===== */
#include <stdbool.h>
#include <gtk/gtk.h>

#include "main.h"
#include "gui.h"
#include "port.h"

/* ===== private datatypes ===== */

/* ===== private symbols ===== */

/* ===== private constants ===== */

/* ===== public constants ===== */

/* ===== private variables ===== */

/* ===== public variables ===== */

/* ===== private functions ===== */

/* ===== public functions ===== */
int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
  if (gui_init() == false)
  {
    printf("GUI initalisation failed\n");
    return 1;
  }
  gtk_main ();
  return 0;
}

