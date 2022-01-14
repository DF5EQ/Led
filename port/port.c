/* ===== file header ===== */

/* ===== includes ===== */
#include <stdio.h>
#include <libftdi1/ftdi.h>

#include "port.h"

/* ===== private datatypes ===== */

/* ===== private symbols ===== */
#define USB_VID 0x0403
#define USB_PID 0x6001

/* ===== private constants ====== */

/* ===== public constants ====== */

/* ===== private variables ====== */
static uint8_t             port_data;
static struct ftdi_context ctx;

/* ===== public variables ====== */

/* ===== private functions ====== */

/* ===== public functions ====== */
void port_init(void)
{
    port_data = 0;

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

uint8_t port_set(uint8_t mask)
{
    port_data |= mask;

    /* write to output */
    ftdi_write_data(&ctx, &port_data, 1);

    return port_data;
}

uint8_t port_get(void)
{
  return port_data;
}

uint8_t port_clr(uint8_t mask)
{
    port_data &= ~mask;

    /* write to output */
    ftdi_write_data(&ctx, &port_data, 1);

    return port_data;
}

uint8_t port_tog(uint8_t mask)
{
    port_data ^= mask;

    /* write to output */
    ftdi_write_data(&ctx, &port_data, 1);

    return port_data;
}

