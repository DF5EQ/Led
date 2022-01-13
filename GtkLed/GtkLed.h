#ifndef GTKLED_H
#define GTKLED_H
/* ===== file header ===== */
/*
   implementation of a LED widget for GTK
   2009-10-23 Peter Baegel (DF5EQ) first issue
*/

/* ===== Includes ===== */
#include <gtk/gtk.h>

/* ===== public datatypes ===== */
typedef enum {
  GTKLED_OFF,
  GTKLED_ON,
  GTKLED_BLINK
} GtkLedMode;

typedef enum {
  GTKLED_RED,
  GTKLED_GREEN,
  GTKLED_BLUE,
  GTKLED_YELLOW
} GtkLedColor;

typedef struct _GtkLed {
  guint             Number;     /* Number of LED             */
  GtkImage*         Image;      /* GTK widget to display LED */
  GtkLedColor       Color;      /* color of the LED          */
  const GdkPixdata* PixdataOn;  /* picture for on state      */
  const GdkPixdata* PixdataOff; /* picture for off state     */
  guint             Periode;    /* blink periode in ms       */
  guint             Duty;       /* duty time in percent      */
  GtkLedMode        Mode;       /* mode: on/off/blink        */
  gboolean          State;      /* actual state: on/off      */
  guint             Counter;    /* actual blink counter      */
  struct _GtkLed*   Next;       /* pointer to next LED       */
} GtkLed;

/* ===== public symbols ===== */

/* ===== public constants ===== */

/* ===== public variables ===== */

/* ===== public functions ===== */
GtkLed*     gtk_led_new         (GtkLedColor, GtkLedMode, GtkImage*);
void        gtk_led_destroy     (GtkLed*);

void        gtk_led_set_color   (GtkLed*, GtkLedColor);
GtkLedColor gtk_led_get_color   (GtkLed*);

void        gtk_led_set_mode    (GtkLed*, GtkLedMode);
GtkLedMode  gtk_led_get_mode    (GtkLed*);

void        gtk_led_set_periode (GtkLed*, guint);
guint       gtk_led_get_periode (GtkLed*);

void        gtk_led_set_duty    (GtkLed*, guint);
guint       gtk_led_get_duty    (GtkLed*);

#endif /* GTKLED_H */

