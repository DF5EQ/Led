/* ===== file header ===== */

/* ===== includes ===== */
#include <stdio.h>
#include <unistd.h>
#include <libftdi1/ftdi.h>
#include "System.h"
#include "Port.h"

/* ===== private datatypes ===== */

/* ===== private symbols ===== */
#define USB_VID 0x0403
#define USB_PID 0x6001

/* ===== private constants ====== */

/* ===== public constants ====== */

/* ===== private variables ====== */
static UINT8  u8PortData;
static struct ftdi_context ctx;

/* ===== public variables ====== */

/* ===== private functions ====== */

/* ===== public functions ====== */
void vPortInit(void)
{
    u8PortData = 0;

    ftdi_init(&ctx);

    /* open FTDI devices based on FTDI VID/PID */
    if(ftdi_usb_open(&ctx, USB_VID, USB_PID) < 0)
    {
        puts("Can't open device");
        return;
    }

    /* Enable bitbang mode with a single output line */
    ftdi_set_bitmode(&ctx, 0xff, BITMODE_BITBANG);
}

UINT8 u8PortSet(UINT8 u8Mask)
{
    u8PortData |= u8Mask;

    /* write to output */
    ftdi_write_data(&ctx, &u8PortData, 1);

    return u8PortData;
}

UINT8 u8PortGet(void)
{
  return u8PortData;
}

UINT8 u8PortClr(UINT8 u8Mask)
{
  u8PortData &= ~u8Mask;

    /* write to output */
    ftdi_write_data(&ctx, &u8PortData, 1);

    return u8PortData;
}

UINT8 u8PortTog(UINT8 u8Mask)
{
  u8PortData ^= u8Mask;

    /* write to output */
    ftdi_write_data(&ctx, &u8PortData, 1);

    return u8PortData;
}

