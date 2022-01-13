/* ===== file header ===== */
/*
  implementation of a LED widget for GTK
  2009-10-23 Peter Baegel (DF5EQ) first issue
*/

/* ===== includes ===== */
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixdata.h>

#include "GtkLed.h"
#include "Port.h"

/* ===== private datatypes ===== */

/* ===== private symbols ===== */

/* periode of the callback timer in ms */
#define TIME_CB_PERIODE 10

/* number of defined colors and states */
#define GTKLED_NUMBER_OF_COLORS 4
#define GTKLED_NUMBER_OF_STATES 2

/* ===== private constants ===== */

/* the constant picture data are declared in a separate file */
#include "led-c-16.h"

/* set of picture data for indexed access */
static const GdkPixdata* Pixdata [GTKLED_NUMBER_OF_COLORS] [GTKLED_NUMBER_OF_STATES] =
{
  { &led_red_off   , &led_red_on    },
  { &led_green_off , &led_green_on  },
  { &led_blue_off  , &led_blue_on   },
  { &led_yellow_off, &led_yellow_on }
};

/* ===== public constants ===== */

/* ===== private variables ===== */
static GtkLed* FirstLed = NULL;
static GtkLed* LastLed  = NULL;

/* ===== public variables ===== */

/* ===== private functions ===== */
static void gtk_led_update_image (GtkLed* Led)
{
  if (Led->State == TRUE)
  {
    gtk_image_set_from_pixbuf( Led->Image, gdk_pixbuf_from_pixdata( Led->PixdataOn, FALSE, NULL ));
    u8PortSet(1<<Led->Number);
  }
  else
  {
    gtk_image_set_from_pixbuf( Led->Image, gdk_pixbuf_from_pixdata( Led->PixdataOff, FALSE, NULL ));
    u8PortClr(1<<Led->Number);
  }
}

/* ===== callback functions ===== */
int gtk_led_time_cb (gpointer data)
/*
  called periodically from a timer
  maintains the blink counter for all LEDs
  update all LED's state to implement blinking
  
  data - not used, must be declared for a callback function
  
  return - TRUE stops further processing of the callback
           FALSE proceed with default processing of the callback
*/
{
  GtkLed* led;

  /* scan the linked list of LEDs */
  for (led  = FirstLed;
       led != NULL;
       led = led->Next)
  {
    /* count up to 'periode' and then wrap around to 0 */

    led->Counter++;;
    if (led->Counter >= led->Periode)
    {
      led->Counter = 0;
    }
    if (led->Mode == GTKLED_BLINK)
    {
      if (/* count is less than duty time */
          led->Counter < led->Periode * led->Duty / 100)
      {
        led->State = GTKLED_ON;
      }
      else
      {
        led->State = GTKLED_OFF;
      }
      gtk_led_update_image (led);
    }
  }
  return TRUE;
}

/* ===== public functions ===== */

GtkLed* gtk_led_new( GtkLedColor Color, GtkLedMode Mode, GtkImage* Image)
/*
  returns a pointer to a new LED structure
  the LED is initialised according to the parameters
  and with some default values 
  
  Color   - one of the GtkLedColor colors
  Mode    - one of the GtkLedMode modes
  Image   - the GTK image widget which shows the LED
  
  return -  NULL no free memory for the new LED
           !NULL pointer to the new LED structure
*/
{
  GtkLed* Led;

  /* allocate memory for the new structure */
  Led = (GtkLed*)g_malloc (sizeof(GtkLed));

  /* initialise the new structure with values according */
  /* to the parameters and with some default values     */
  Led->Image      = Image;
  Led->Color      = Color;
  Led->Mode       = Mode;
  Led->PixdataOn  = Pixdata[Color][GTKLED_ON];
  Led->PixdataOff = Pixdata[Color][GTKLED_OFF];
  Led->Periode    = 1000/TIME_CB_PERIODE;    /* 1000 ms */
  Led->Duty       = 50;                      /*   50 %  */
  Led->State      = Mode ? TRUE : FALSE;
  Led->Counter    = 0;
  Led->Next       = NULL;

  /* for the first LED some special actions must be taken */
  if (FirstLed == NULL)
  {
    /* the first LED gets the number 0 */
    Led->Number = 0;

    /* start of the linked list */
    FirstLed = Led;

    /* install the timer for blinking */
    g_timeout_add
    (
      TIME_CB_PERIODE,
      gtk_led_time_cb,
      NULL
    );

    vPortInit();
  }
  else
  {
    /* assign the next number to the new LED */
    Led->Number = LastLed->Number + 1;

    /* append the new LED to the linked list */
    LastLed->Next = Led;
  }

  /* pointer to last LED in the linked list */
  LastLed = Led;

  gtk_led_update_image (Led);
  return Led;
}

void gtk_led_destroy (GtkLed* Led)
{
  /* TODO */
}

void gtk_led_set_mode( GtkLed* Led, GtkLedMode Mode)
/*
  set the mode of a LED
  
  Led  - pointer to the LED to modify
  Mode - new mode of the LED
*/
{
  Led->Mode = Mode;

  /* update the state according to the mode */
  switch (Mode)
  {
    case GTKLED_ON:
      Led->State = TRUE;
      break;
    case GTKLED_OFF:
      Led->State = FALSE;
      break;
    case GTKLED_BLINK:
      Led->State = TRUE;
      break;
    default:
      break;
  }
  gtk_led_update_image (Led);
}

void gtk_led_set_color( GtkLed* Led, GtkLedColor Color )
/*
  change the color of a LED
  
  Led   - pointer to the LED
  Color - new color for the LED
*/
{
  Led->Color = Color;
  gtk_led_update_image (Led);
}

GtkLedColor gtk_led_get_color( GtkLed* Led )
/*
  read the actual color of a LED
  
  Led - pointer to the LED
*/
{
  return Led->Color;
}

void gtk_led_set_periode( GtkLed* Led, guint Periode )
/*
  change the periode time of a blinking LED
  
  Led     - pointer to the LED
  Periode - new periode time in ms
*/
{
  Led->Periode = Periode/TIME_CB_PERIODE;
}

guint gtk_led_get_periode( GtkLed* Led )
/*
  read the actual periode time of a LED
  
  Led - pointer to the LED
*/
{
  return Led->Periode;
}

void gtk_led_set_duty( GtkLed* Led, guint Duty )
/*
  change the duty time of a blinking LED
  
  Led  - pointer to the LED
  Duty - new duty cycle in percent
*/
{
  /* limit duty to 100% */
  if (Duty > 100)
  {
    Led->Duty = 100;
  }
  else
  {
    Led->Duty = Duty;
  }
  switch (Led->Duty)
  {
    case 0:
      /* switch off LED */
      Led->State = FALSE;
      break;
    case 100:
      /* switch on LED */
      Led->State = TRUE;
      break;
    default:
      break;
  }
  gtk_led_update_image (Led);
}

guint gtk_led_get_duty( GtkLed* Led)
/*
  read the actual duty of a LED
  
  Led - pointer to the LED
*/
{
  return Led->Duty;
}

