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
void    PortInit (void);
uint8_t PortSet  (uint8_t Mask);
uint8_t PortGet  (void);
uint8_t PortClr  (uint8_t Mask);
uint8_t PortTog  (uint8_t Mask);

#endif /* PORT_H */

