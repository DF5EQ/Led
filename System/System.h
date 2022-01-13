#ifndef SYSTEM_H
#define SYSTEM_H

/* ===== file header ===== */

/* ===== includes ===== */

/* ===== public datatypes ===== */

/* 8 bit types */
typedef signed char        SINT8;  /*  s8 */
typedef unsigned char      UINT8;  /*  u8 */

/* 16 bit types */
typedef signed short       SINT16; /* s16 */
typedef unsigned short     UINT16; /* u16 */

/* 32 bit types */
typedef signed int         SINT32; /* s32 */
typedef unsigned int       UINT32; /* u32 */

/* 64 bit types */
typedef signed long long   SINT64; /* s64 */
typedef unsigned long long UINT64; /* u64 */

/* ===== public symbols ===== */
#ifndef FALSE
  #define FALSE 0
#endif

#ifndef TRUE
  #define TRUE  1
#endif

/* ===== public constants ===== */

/* ===== public variables ===== */

/* ===== public functions ===== */
void vSystemInit (void);

#endif /* SYSTEM_H */

