#ifndef PORT_H
#define PORT_H
/* ===== file header ===== */

/* ===== includes ===== */
#include "System.h"

/* ===== public datatypes ===== */

/* ===== public symbols ===== */

/* ===== public constants ====== */

/* ===== public variables ====== */

/* ===== public functions ====== */
void  vPortInit (void);
UINT8 u8PortSet (UINT8 u8Mask);
UINT8 u8PortGet (void);
UINT8 u8PortClr (UINT8 u8Mask);
UINT8 u8PortTog (UINT8 u8Mask);

#endif /* PORT_H */

