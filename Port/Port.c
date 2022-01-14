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
static uint8_t             PortData;
static struct ftdi_context ctx;

/* ===== public variables ====== */

/* ===== private functions ====== */

/* ===== public functions ====== */
void PortInit(void)
{
    PortData = 0;

    ftdi_init(&ctx);

    /* open FTDI devices based on FTDI VID/PID */
    if(ftdi_usb_open(&ctx, USB_VID, USB_PID) < 0)
    {
        puts("Can't open device");
        return;
    }

    /* Enable bitbang mode for all output lines */
    ftdi_set_bitmode(&ctx, 0xff, BITMODE_BITBANG);
}

uint8_t PortSet(uint8_t Mask)
{
    PortData |= Mask;

    /* write to output */
    ftdi_write_data(&ctx, &PortData, 1);

    return PortData;
}

uint8_t PortGet(void)
{
  return PortData;
}

uint8_t PortClr(uint8_t Mask)
{
  PortData &= ~Mask;

    /* write to output */
    ftdi_write_data(&ctx, &PortData, 1);

    return PortData;
}

uint8_t PortTog(uint8_t Mask)
{
  PortData ^= Mask;

    /* write to output */
    ftdi_write_data(&ctx, &PortData, 1);

    return PortData;
}

