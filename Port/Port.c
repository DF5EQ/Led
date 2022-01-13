/* ===== file header ===== */

/* ===== includes ===== */
#include <linux/ppdev.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "System.h"
#include "Port.h"

/* ===== private datatypes ===== */

/* ===== private symbols ===== */

/* ===== public constants ====== */

/* ===== private constants ====== */

/* ===== private variables ====== */
static UINT8 u8PortData;
static int port;

/* ===== public variables ====== */

/* ===== private functions ====== */

/* ===== public functions ====== */
void vPortInit(void)
{
  u8PortData = 0;

  port = open ("/dev/parport0", O_RDWR);
  ioctl( port, PPCLAIM, NULL );
  ioctl( port, PPWDATA, &u8PortData );

  /* Parallelport schliessen
  ioctl( port, PPRELEASE, NULL );
  close( port );
  */
}

UINT8 u8PortSet(UINT8 u8Mask)
{
  u8PortData |= u8Mask;

  ioctl( port, PPWDATA, &u8PortData );
  return u8PortData;
}

UINT8 u8PortGet(void)
{
  return u8PortData;
}

UINT8 u8PortClr(UINT8 u8Mask)
{
  u8PortData &= ~u8Mask;

  ioctl( port, PPWDATA, &u8PortData );
  return u8PortData;
}

UINT8 u8PortTog(UINT8 u8Mask)
{
  u8PortData ^= u8Mask;

  ioctl( port, PPWDATA, &u8PortData );
  return u8PortData;
}

