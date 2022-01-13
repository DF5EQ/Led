/* EasyCODE V6.8 19.11.2009 22:12:53 */
/* EasyCODE O
If=horizontal
LevelNumbers=no
LineNumbers=no
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier,,100,1,-13,0,700,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier,Normal,100,4,-131,0,400,0,0,0,0,0,0,0,0,0,1,300,300
LastLevelId=9 */
/* EasyCODE ( 1 */
/* ===== File Header ===== */
/* EasyCODE - */
/* ===== Includes ===== */
#include <linux/ppdev.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "System.h"
#include "Port.h"
/* EasyCODE - */
/* ===== Preprocessor Switches ====== */
/* not used */
/* EasyCODE - */
/* ===== Local Datatypes ===== */
/* not used */
/* EasyCODE - */
/* ===== Local Symbols ===== */
/* not used */
/* EasyCODE - */
/* ===== Local Constants ====== */
/* not used */
/* EasyCODE - */
/* ===== Global Constants ====== */
/* not used */
/* EasyCODE - */
/* ===== Local Variables ====== */
static UINT8 u8PortData;
static int port;
/* EasyCODE - */
/* ===== Global Variables ====== */
/* not used */
/* EasyCODE - */
/* ===== Local Functions ====== */
/* not used */
/* EasyCODE - */
/* ===== Global Functions ====== */
/* EasyCODE ( 2
   vPortInit */
/* EasyCODE F */
void vPortInit(void)
{
  u8PortData = 0;
  /* EasyCODE - */
  port = open ("/dev/parport0", O_RDWR);
  /* EasyCODE - */
  ioctl( port, PPCLAIM, NULL );
  /* EasyCODE - */
  ioctl( port, PPWDATA, &u8PortData );
  /* EasyCODE - */
  /* Parallelport schliessen
  ioctl( port, PPRELEASE, NULL );
  close( port );
  */
}
/* EasyCODE ) */
/* EasyCODE ( 3
   u8PortSet */
/* EasyCODE F */
UINT8 u8PortSet(UINT8 u8Mask)
{
  u8PortData |= u8Mask;
  /* EasyCODE - */
  ioctl( port, PPWDATA, &u8PortData );
  return u8PortData;
}
/* EasyCODE ) */
/* EasyCODE ( 4
   u8PortGet */
/* EasyCODE F */
UINT8 u8PortGet(void)
{
  return u8PortData;
}
/* EasyCODE ) */
/* EasyCODE ( 5
   u8PortClr */
/* EasyCODE F */
UINT8 u8PortClr(UINT8 u8Mask)
{
  u8PortData &= ~u8Mask;
  /* EasyCODE - */
  ioctl( port, PPWDATA, &u8PortData );
  return u8PortData;
}
/* EasyCODE ) */
/* EasyCODE ( 6
   u8PortTog */
/* EasyCODE F */
UINT8 u8PortTog(UINT8 u8Mask)
{
  u8PortData ^= u8Mask;
  /* EasyCODE - */
  ioctl( port, PPWDATA, &u8PortData );
  return u8PortData;
}
/* EasyCODE ) */
/* EasyCODE ) */
