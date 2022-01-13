/* EasyCODE V6.8 19.11.2009 23:21:16 */
/* EasyCODE O
If=horizontal
LevelNumbers=no
LineNumbers=no
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier,,100,1,-13,0,700,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier,Normal,100,4,-131,0,400,0,0,0,0,0,0,0,0,0,1,300,300
LastLevelId=4 */
/* EasyCODE ( 1 */
/* ===== File Header ===== */
/* not used */
/* EasyCODE - */
/* ===== Includes ===== */
#include <gtk/gtk.h>
#include "System.h"
#include "Main.h"
#include "Gui.h"
#include "Port.h"
/* EasyCODE - */
/* ===== Preprocessor Switches ===== */
/* not used */
/* EasyCODE - */
/* ===== Local Datatypes ===== */
/* not used */
/* EasyCODE - */
/* ===== Local Symbols ===== */
/* not used */
/* EasyCODE - */
/* ===== Local Constants ===== */
/* not used */
/* EasyCODE - */
/* ===== Global Constants ===== */
const UINT16 u16MainVersion = MAIN_VERSION;
/* EasyCODE - */
/* ===== Local Variables ===== */
/* not used */
/* EasyCODE - */
/* ===== Global Variables ===== */
/* not used */
/* EasyCODE - */
/* ===== Local Functions ===== */
/* not used */
/* EasyCODE - */
/* ===== Global Functions ===== */
/* EasyCODE ( 2
   main */
/* EasyCODE F */
int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
  if (GuiInit() == FALSE)
  {
    printf("GUI initalisation failed\n");
    return 1;
  }
  gtk_main ();
  return 0;
}
/* EasyCODE ) */
/* EasyCODE ) */
