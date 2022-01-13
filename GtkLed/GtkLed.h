/* EasyCODE V6.8 19.11.2009 22:38:26 */
/* EasyCODE O
If=horizontal
LevelNumbers=no
LineNumbers=no
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier,,100,1,-13,0,700,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier,Normal,100,4,-131,0,400,0,0,0,0,0,0,0,0,0,1,300,300
LastLevelId=82 */
/* EasyCODE ( 1
   GtkLed.h */
#ifndef GTKLED_H
#define GTKLED_H
/* EasyCODE ( 76
   ===== File Header ===== */
/*
  implementation of a LED widget for GTK
  
  2009-10-23 Peter Baegel (DF5EQ)
    first issue
*/
/* EasyCODE ) */
/* EasyCODE ( 77
   ===== Includes ===== */
#include <gtk/gtk.h>
/* EasyCODE ) */
/* EasyCODE ( 78
   ===== Global Datatypes ===== */
/* EasyCODE ( 72
   GtkLedMode */
/* EasyCODE C */
/* EasyCODE < */
typedef enum
/* EasyCODE > */
{
  /* EasyCODE < */
  GTKLED_OFF,
  GTKLED_ON,
  GTKLED_BLINK
  /* EasyCODE > */
} GtkLedMode;
/* EasyCODE E */
/* EasyCODE ) */
/* EasyCODE ( 73
   GtkLedColor */
/* EasyCODE C */
/* EasyCODE < */
typedef enum
/* EasyCODE > */
{
  /* EasyCODE < */
  GTKLED_RED,
  GTKLED_GREEN,
  GTKLED_BLUE,
  GTKLED_YELLOW
  /* EasyCODE > */
} GtkLedColor;
/* EasyCODE E */
/* EasyCODE ) */
/* EasyCODE ( 74
   GtkLed */
/* must not be accessed directly */
/* contains only private data   */
/* EasyCODE C */
typedef struct _GtkLed
{
  guint Number;           /* Number of LED             */
  /* EasyCODE - */
  GtkImage* Image;        /* GTK widget to display LED */
  /* EasyCODE - */
  GtkLedColor Color;      /* color of the LED          */
  /* EasyCODE - */
  const  GdkPixdata* PixdataOn;  /* picture for on state      */
  const  GdkPixdata* PixdataOff; /* picture for off state     */
  /* EasyCODE - */
  guint Periode;          /* blink periode in ms       */
  guint Duty;             /* duty time in percent      */
  /* EasyCODE - */
  GtkLedMode Mode;        /* mode: on/off/blink        */
  /* EasyCODE - */
  gboolean State;         /* actual state: on/off      */
  /* EasyCODE - */
  guint Counter;          /* actual blink counter      */
  /* EasyCODE - */
  struct _GtkLed* Next;   /* pointer to next LED       */
} GtkLed;
/* EasyCODE E */
/* EasyCODE ) */
/* EasyCODE ) */
/* EasyCODE ( 79
   ===== Global Defines ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 80
   ===== Global Constants ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 81
   ===== Global Variables ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 82
   ===== Global Functions ===== */
GtkLed*     gtk_led_new         (GtkLedColor, GtkLedMode, GtkImage*);
void        gtk_led_destroy     (GtkLed*);
/* EasyCODE - */
void        gtk_led_set_color   (GtkLed*, GtkLedColor);
GtkLedColor gtk_led_get_color   (GtkLed*);
/* EasyCODE - */
void        gtk_led_set_mode    (GtkLed*, GtkLedMode);
GtkLedMode  gtk_led_get_mode    (GtkLed*);
/* EasyCODE - */
void        gtk_led_set_periode (GtkLed*, guint);
guint       gtk_led_get_periode (GtkLed*);
/* EasyCODE - */
void        gtk_led_set_duty    (GtkLed*, guint);
guint       gtk_led_get_duty    (GtkLed*);
/* EasyCODE ) */
#endif
/* EasyCODE ) */
