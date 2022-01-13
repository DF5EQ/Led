/* EasyCODE V6.8 19.11.2009 23:21:19 */
/* EasyCODE O
If=horizontal
LevelNumbers=no
LineNumbers=no
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier,,100,1,-13,0,700,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier,Normal,100,4,-131,0,400,0,0,0,0,0,0,0,0,0,1,300,300
LastLevelId=131 */
/* EasyCODE ( 1
   GtkLed.c */
/* EasyCODE ( 117
   ===== File Header ===== */
/*
  implementation of a LED widget for GTK
  
  2009-10-23 Peter Baegel (DF5EQ)
    first issue
*/
/* EasyCODE ) */
/* EasyCODE ( 118
   ===== Includes ===== */
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixdata.h>
/* EasyCODE - */
#include "Gui.gtk"
#include "GtkLed.h"
#include "Port.h"
/* EasyCODE ) */
/* EasyCODE ( 119
   ===== Preprocessor Switches ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 120
   ===== Local Datatypes ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 121
   ===== Local Symbols ===== */
/* periode of the callback timer in ms */
#define TIME_CB_PERIODE 10
/* EasyCODE - */
/* number of defined colors and states */
#define GTKLED_NUMBER_OF_COLORS 4
#define GTKLED_NUMBER_OF_STATES 2
/* EasyCODE ) */
/* EasyCODE ( 122
   ===== Local Constants ===== */
/* the constant picture data are */
/* declared in a separate file   */
#include "led-c-16.h"
/* EasyCODE - */
/* EasyCODE < */
/* set of picture data */
/* for indexed access  */
static const GdkPixdata* Pixdata
  [GTKLED_NUMBER_OF_COLORS]
  [GTKLED_NUMBER_OF_STATES] =
{
  { &led_red_off   , &led_red_on    },
  { &led_green_off , &led_green_on  },
  { &led_blue_off  , &led_blue_on   },
  { &led_yellow_off, &led_yellow_on }
};
/* EasyCODE > */
/* EasyCODE ) */
/* EasyCODE ( 123
   ===== Global Constants ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 124
   ===== Local Variables ===== */
static GtkLed* FirstLed = NULL;
static GtkLed* LastLed  = NULL;
/* EasyCODE ) */
/* EasyCODE ( 125
   ===== Global Variables ===== */
/* not used */
/* EasyCODE ) */
/* EasyCODE ( 126
   ===== Local Functions ===== */
/* EasyCODE ( 81
   gtk_led_update_image */
/* EasyCODE F */
static void gtk_led_update_image (GtkLed* Led)
{
  if (Led->State == TRUE)
  {
    gtk_image_set_from_pixbuf
    (
      Led->Image,
      gdk_pixbuf_from_pixdata
      (
        Led->PixdataOn,
        FALSE,
        NULL
      )
    );
    /* EasyCODE - */
    u8PortSet(1<<Led->Number);
  }
  else
  {
    gtk_image_set_from_pixbuf
    (
      Led->Image,
      gdk_pixbuf_from_pixdata
      (
        Led->PixdataOff,
        FALSE,
        NULL
      )
    );
    /* EasyCODE - */
    u8PortClr(1<<Led->Number);
  }
}
/* EasyCODE ) */
/* EasyCODE ) */
/* EasyCODE ( 127
   ===== Callback Functions ===== */
/* EasyCODE ( 101
   gtk_led_time_cb */
/* EasyCODE F */
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
  /* EasyCODE - */
  /* scan the linked list of LEDs */
  for (led  = FirstLed;
       led != NULL;
       led = led->Next)
  {
    /* count up to 'periode' and then wrap around to 0 */
    /* EasyCODE - */
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
/* EasyCODE ) */
/* EasyCODE ) */
/* EasyCODE ( 128
   ===== Global Functions ===== */
/* EasyCODE ( 79
   gtk_led_new */
/* EasyCODE F */
GtkLed* gtk_led_new
(
  GtkLedColor Color,
  GtkLedMode  Mode,
  GtkImage*   Image
)
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
  /* EasyCODE - */
  /* allocate memory for the new structure */
  Led = (GtkLed*)g_malloc (sizeof(GtkLed));
  /* EasyCODE - */
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
  /* EasyCODE - */
  /* for the first LED some special actions must be taken */
  if (FirstLed == NULL)
  {
    /* the first LED gets the number 0 */
    Led->Number = 0;
    /* EasyCODE - */
    /* start of the linked list */
    FirstLed = Led;
    /* EasyCODE - */
    /* install the timer for blinking */
    gtk_timeout_add
    (
      TIME_CB_PERIODE,
      gtk_led_time_cb,
      NULL
    );
    /* EasyCODE - */
    vPortInit();
  }
  else
  {
    /* assign the next number */
    /* to the new LED         */
    Led->Number = LastLed->Number + 1;
    /* EasyCODE - */
    /* append the new LED */
    /* to the linked list */
    
    LastLed->Next = Led;
  }
  /* pointer to last LED in the linked list */
  LastLed = Led;
  /* EasyCODE - */
  gtk_led_update_image (Led);
  return Led;
}
/* EasyCODE ) */
/* EasyCODE ( 80
   gtk_led_destroy */
/* EasyCODE F */
void gtk_led_destroy (GtkLed* Led)
{
  /* to be filled */
}
/* EasyCODE ) */
/* EasyCODE ( 116
   gtk_led_set_mode */
/* EasyCODE F */
void gtk_led_set_mode
(
  GtkLed*    Led,
  GtkLedMode Mode
)
/*
  set the mode of a LED
  
  Led  - pointer to the LED to modify
  Mode - new mode of the LED
*/
{
  Led->Mode = Mode;
  /* EasyCODE - */
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
/* EasyCODE ) */
/* EasyCODE ( 78
   gtk_led_set_color */
/* EasyCODE F */
void gtk_led_set_color
(
  GtkLed*     Led,
  GtkLedColor Color
)
/*
  change the color of a LED
  
  Led   - pointer to the LED
  Color - new color for the LED
*/
{
  Led->Color = Color;
  /* EasyCODE - */
  gtk_led_update_image (Led);
}
/* EasyCODE ) */
/* EasyCODE ( 77
   gtk_led_get_color */
/* EasyCODE F */
GtkLedColor gtk_led_get_color
(
  GtkLed* Led
)
/*
  read the actual color of a LED
  
  Led - pointer to the LED
*/
{
  return Led->Color;
}
/* EasyCODE ) */
/* EasyCODE ( 129
   gtk_led_set_periode */
/* EasyCODE F */
void gtk_led_set_periode
(
  GtkLed* Led,
  guint   Periode
)
/*
  change the periode time of a blinking LED
  
  Led     - pointer to the LED
  Periode - new periode time in ms
*/
{
  Led->Periode = Periode/TIME_CB_PERIODE;
}
/* EasyCODE ) */
/* EasyCODE ( 130
   gtk_led_get_periode */
/* EasyCODE F */
guint gtk_led_get_periode
(
  GtkLed* Led
)
/*
  read the actual periode time of a LED
  
  Led - pointer to the LED
*/
{
  return Led->Periode;
}
/* EasyCODE ) */
/* EasyCODE ( 76
   gtk_led_set_duty */
/* EasyCODE F */
void gtk_led_set_duty
(
  GtkLed* Led,
  guint   Duty
)
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
/* EasyCODE ) */
/* EasyCODE ( 75
   gtk_led_get_duty */
/* EasyCODE F */
guint gtk_led_get_duty
(
  GtkLed* Led
)
/*
  read the actual duty of a LED
  
  Led - pointer to the LED
*/
{
  return Led->Duty;
}
/* EasyCODE ) */
/* EasyCODE ) */
/* EasyCODE ) */
