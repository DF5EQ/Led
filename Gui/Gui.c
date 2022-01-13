/* ===== file header ===== */

/* ===== includes ===== */
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixdata.h>

#include "Gui.gtk"
#include "GtkLed.h"

/* ===== private datatypes ===== */

/* ===== private symbols ===== */

/* ===== private constants ===== */

/* ===== public constants ===== */

/* ===== private variables ===== */
static GtkBuilder* builder;
static GtkWidget*  window;
static GtkLed*     Led[8];

/* ===== public variables ===== */

/* ===== private functions ===== */

/* ===== callback functions ===== */

void on_window_destroy (GtkObject *object, gpointer user_data)
{
  gtk_main_quit ();
}

void button_pressed_cb (GtkButton* button, gpointer user_data)
{
  const gchar* name;
  gint n;

  name = gtk_buildable_get_name(GTK_BUILDABLE(button));
  printf("button pressed name: %s\n", name);

  n = atoi(strpbrk(name, "0123456789"));
  printf("button pressed number: %d\n", n);

  gtk_led_set_mode(Led[n], GTKLED_ON);
}

void button_released_cb (GtkButton* button, gpointer user_data)
{
  const gchar* name;
  gint n;

  name = gtk_buildable_get_name(GTK_BUILDABLE(button));
  printf("button released name: %s\n", name);

  n = atoi(strpbrk(name, "0123456789"));
  printf("button released number: %d\n", n);

  gtk_led_set_mode(Led[n], GTKLED_BLINK);
}

void periode_value_changed_cb (GtkSpinButton* spin, gpointer user_data)
{
  const gchar* name;
  gint n;
  gint periode;

  name = gtk_buildable_get_name(GTK_BUILDABLE(spin));
  printf( "spin periode changed name: %s\n", name );

  n = atoi( strpbrk(name, "0123456789") );
  printf("spin periode changed number: %d\n", n );

  periode = gtk_spin_button_get_value_as_int(spin);
  gtk_led_set_periode(Led[n], periode);
}

void duty_value_changed_cb (GtkSpinButton* spin, gpointer user_data)
{
  const gchar* name;
  gint n;
  gint duty;

  name = gtk_buildable_get_name(GTK_BUILDABLE(spin));
  printf( "spin duty changed name: %s\n", name );

  n = atoi( strpbrk(name, "0123456789") );
  printf("spin duty changed number: %d\n", n );

  duty = gtk_spin_button_get_value_as_int(spin);
  gtk_led_set_duty(Led[n], duty);
}

/* ===== public functions ===== */
gboolean GuiInit (void)
{
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_string (builder, Gui, -1, NULL) == 0)
  {
    return FALSE;
  }
  window = GTK_WIDGET (gtk_builder_get_object (builder,"MainWindow"));

  Led[0] = gtk_led_new (GTKLED_YELLOW, GTKLED_ON,    GTK_IMAGE (gtk_builder_get_object (builder,"led0")));
  Led[1] = gtk_led_new (GTKLED_RED,    GTKLED_ON,    GTK_IMAGE (gtk_builder_get_object (builder,"led1")));
  Led[2] = gtk_led_new (GTKLED_GREEN,  GTKLED_ON,    GTK_IMAGE (gtk_builder_get_object (builder,"led2")));
  Led[3] = gtk_led_new (GTKLED_BLUE,   GTKLED_BLINK, GTK_IMAGE (gtk_builder_get_object (builder,"led3")));
  Led[4] = gtk_led_new (GTKLED_YELLOW, GTKLED_BLINK, GTK_IMAGE (gtk_builder_get_object (builder,"led4")));
  Led[5] = gtk_led_new (GTKLED_RED,    GTKLED_OFF,   GTK_IMAGE (gtk_builder_get_object (builder,"led5")));
  Led[6] = gtk_led_new (GTKLED_GREEN,  GTKLED_OFF,   GTK_IMAGE (gtk_builder_get_object (builder,"led6")));
  Led[7] = gtk_led_new (GTKLED_BLUE,   GTKLED_OFF,   GTK_IMAGE (gtk_builder_get_object (builder,"led7")));

  gtk_builder_connect_signals (builder, NULL);

  gtk_widget_show (window);
  return TRUE;
}

