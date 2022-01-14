/* ===== file header ===== */

/* ===== includes ===== */
#include <gtk/gtk.h>
#include "System.h"
#include "Main.h"
#include "Gui.h"
#include "Port.h"

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
  if (GuiInit() == false)
  {
    printf("GUI initalisation failed\n");
    return 1;
  }
  gtk_main ();
  return 0;
}

