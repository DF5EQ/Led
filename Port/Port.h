/* EasyCODE V6.8 19.11.2009 22:43:29 */
/* EasyCODE O
If=horizontal
LevelNumbers=no
LineNumbers=no
Colors=16777215,0,12582912,12632256,0,0,0,16711680,8388736,0,33023,32768,0,0,0,0,0,32768,12632256,255,65280,255,255,16711935
ScreenFont=Courier,,100,1,-13,0,700,0,0,0,0,0,0,3,2,1,49,96,96
PrinterFont=Courier,Normal,100,4,-131,0,400,0,0,0,0,0,0,0,0,0,1,300,300
LastLevelId=1 */
/* EasyCODE ( 1 */
#ifndef PORT_H
#define PORT_H
/* EasyCODE - */
/* ===== File Header ===== */
/* not used */
/* EasyCODE - */
/* ===== Includes ===== */
#include "System.h"
/* EasyCODE - */
/* ===== Global Datatypes ===== */
/* not used */
/* EasyCODE - */
/* ===== Global Defines ===== */
#define PORT_VERSION 0
/* EasyCODE - */
/* ===== Global Constants ====== */
extern const UINT16 u16PortVersion;
/* EasyCODE - */
/* ===== Global Variables ====== */
/* not used */
/* EasyCODE - */
/* ===== Global Functions ====== */
void vPortInit(void);
UINT8 u8PortSet(UINT8 u8Mask);
UINT8 u8PortGet(void);
UINT8 u8PortClr(UINT8 u8Mask);
UINT8 u8PortTog(UINT8 u8Mask);
/* EasyCODE - */
#endif
/* EasyCODE ) */
