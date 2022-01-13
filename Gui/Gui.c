/* EasyCODE V6.8 21.10.2012 11:33:56 */
/* EasyCODE O
If=horizontal
LevelNumbers=no
LineNumbers=no
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier,,100,1,-13,0,700,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier,Normal,100,4,-131,0,400,0,0,0,0,0,0,0,0,0,1,300,300
LastLevelId=127 */
/* EasyCODE ( 1
   Gui.c */
/* EasyCODE ( 65
   ===== File Header ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 66
   ===== Includes ===== */
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixdata.h>
/* EasyCODE - */
#include "Gui.gtk"
#include "GtkLed.h"
/* EasyCODE ) */
/* EasyCODE ( 67
   ===== Preprocessor Switches ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 68
   ===== Local Datatypes ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 69
   ===== Local Symbols ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 70
   ===== Local Constants ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 71
   ===== Global Constants ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 72
   ===== Local Variables ===== */
static GtkBuilder* builder;
/* EasyCODE - */
static GtkWidget* window;
static GtkLed*    Led[8];
/* EasyCODE ) */
/* EasyCODE ( 73
   ===== Global Variables ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 74
   ===== Local Functions ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 75
   ===== Callback Functions ===== */
/* EasyCODE ( 2
   on_window_destroy */
/* EasyCODE F */
void on_window_destroy (GtkObject *object, gpointer user_data)
{
  gtk_main_quit ();
}
/* EasyCODE ) */
/* EasyCODE ( 91
   button_pressed_cb */
/* EasyCODE F */
void button_pressed_cb (GtkButton* button, gpointer user_data)
{
  const gchar* name;
  gint n;
  /* EasyCODE - */
  name = gtk_buildable_get_name(GTK_BUILDABLE(button));
  /* EasyCODE - */
  printf("button pressed name: %s\n", name);
  /* EasyCODE - */
  n = atoi(strpbrk(name, "0123456789"));
  /* EasyCODE - */
  printf("button pressed number: %d\n", n);
  /* EasyCODE - */
  gtk_led_set_mode(Led[n], GTKLED_ON);
}
/* EasyCODE ) */
/* EasyCODE ( 90
   button_released_cb */
/* EasyCODE F */
void button_released_cb (GtkButton* button, gpointer user_data)
{
  const gchar* name;
  gint n;
  /* EasyCODE - */
  name = gtk_buildable_get_name(GTK_BUILDABLE(button));
  /* EasyCODE - */
  printf("button released name: %s\n", name);
  /* EasyCODE - */
  n = atoi(strpbrk(name, "0123456789"));
  /* EasyCODE - */
  printf("button released number: %d\n", n);
  /* EasyCODE - */
  gtk_led_set_mode(Led[n], GTKLED_BLINK);
}
/* EasyCODE ) */
/* EasyCODE ( 64
   periode_value_changed_cb */
/* EasyCODE F */
void periode_value_changed_cb (GtkSpinButton* spin, gpointer user_data)
{
  const gchar* name;
  gint n;
  gint periode;
  /* EasyCODE - */
  name = gtk_buildable_get_name(GTK_BUILDABLE(spin));
  /* EasyCODE - */
  printf( "spin periode changed name: %s\n", name );
  /* EasyCODE - */
  n = atoi( strpbrk(name, "0123456789") );
  /* EasyCODE - */
  printf("spin periode changed number: %d\n", n );
  /* EasyCODE - */
  periode = gtk_spin_button_get_value_as_int(spin);
  /* EasyCODE - */
  gtk_led_set_periode(Led[n], periode);
}
/* EasyCODE ) */
/* EasyCODE ( 77
   duty_value_changed_cb */
/* EasyCODE F */
void duty_value_changed_cb (GtkSpinButton* spin, gpointer user_data)
{
  const gchar* name;
  gint n;
  gint duty;
  /* EasyCODE - */
  name = gtk_buildable_get_name(GTK_BUILDABLE(spin));
  /* EasyCODE - */
  printf( "spin duty changed name: %s\n", name );
  /* EasyCODE - */
  n = atoi( strpbrk(name, "0123456789") );
  /* EasyCODE - */
  printf("spin duty changed number: %d\n", n );
  /* EasyCODE - */
  duty = gtk_spin_button_get_value_as_int(spin);
  /* EasyCODE - */
  gtk_led_set_duty(Led[n], duty);
}
/* EasyCODE ) */
/* EasyCODE ) */
/* EasyCODE ( 76
   ===== Global Functions ===== */
/* EasyCODE F */
gboolean GuiInit (void)
{
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_string (builder, Gui, -1, NULL) == 0)
  {
    return FALSE;
  }
  window = GTK_WIDGET (gtk_builder_get_object (builder,"MainWindow"));
  /* EasyCODE - */
  Led[0] = gtk_led_new (GTKLED_YELLOW, GTKLED_ON,    GTK_IMAGE (gtk_builder_get_object (builder,"led0")));
  Led[1] = gtk_led_new (GTKLED_RED,    GTKLED_ON,    GTK_IMAGE (gtk_builder_get_object (builder,"led1")));
  Led[2] = gtk_led_new (GTKLED_GREEN,  GTKLED_ON,    GTK_IMAGE (gtk_builder_get_object (builder,"led2")));
  Led[3] = gtk_led_new (GTKLED_BLUE,   GTKLED_BLINK, GTK_IMAGE (gtk_builder_get_object (builder,"led3")));
  Led[4] = gtk_led_new (GTKLED_YELLOW, GTKLED_BLINK, GTK_IMAGE (gtk_builder_get_object (builder,"led4")));
  Led[5] = gtk_led_new (GTKLED_RED,    GTKLED_OFF,   GTK_IMAGE (gtk_builder_get_object (builder,"led5")));
  Led[6] = gtk_led_new (GTKLED_GREEN,  GTKLED_OFF,   GTK_IMAGE (gtk_builder_get_object (builder,"led6")));
  Led[7] = gtk_led_new (GTKLED_BLUE,   GTKLED_OFF,   GTK_IMAGE (gtk_builder_get_object (builder,"led7")));
  /* EasyCODE - */
  gtk_builder_connect_signals (builder, NULL);
  /* EasyCODE - */
  gtk_widget_show (window);
  return TRUE;
}
/* EasyCODE ) */
/* EasyCODE ) */
