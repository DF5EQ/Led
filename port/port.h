#ifndef PORT_H
#define PORT_H
/* ===== file header ===== */

/* ===== includes ===== */
#include "system.h"

/* ===== public datatypes ===== */

/* ===== public symbols ===== */

/* ===== public constants ====== */

/* ===== public variables ====== */

/* ===== public functions ====== */
void    port_init (void);
uint8_t port_set  (uint8_t mask);
uint8_t port_get  (void);
uint8_t port_clr  (uint8_t mask);
uint8_t port_tog  (uint8_t mask);

#endif /* PORT_H */

