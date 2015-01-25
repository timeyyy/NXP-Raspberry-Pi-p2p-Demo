/**
 * @file	: debug_frmwrk.h
 * @brief	: Contains some utilities that used for debugging through UART
 * @version	: 1.0
 * @date	: 18. Mar. 2009
 * @author	: HieuNguyen
 *----------------------------------------------------------------------------
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#ifndef DEBUG_FRMWRK_H_
#define DEBUG_FRMWRK_H_

/*#include <lpc17xx_uart.h>
#include "mlsAppConfig.h"*/

//#if 0 //KahLee
#if defined (MLSDEBUG_SELECT_DEBUGFRAMEWORK)
#define DEBUGFRMWRKPRINTF 	mlsDebugPrintf
#else
#define DEBUGFRMWRKPRINTF
#endif
//#endif

//#define DEBUGFRMWRKPRINTF 	mlsDebugPrintf

#define USED_UART_DEBUG_PORT	0
#define P2_FW_DEBUG		0				// 1 for direct live UART display. 2 for postponed display. 0 for no display
#define BLF_DEBUG_TRACE	1

#if (USED_UART_DEBUG_PORT==0)
#define DEBUG_UART_PORT	UART0
#elif (USED_UART_DEBUG_PORT==1)
#define DEBUG_UART_PORT	UART1
#endif

#if (BLF_DEBUG_TRACE==1)
#define _BFLDBGH_(x,y)		_DBGH_(x,y)
#define _BFLDBG(x)			_DBG(x)
#define _BFLDBG_(x)		_DBG_(x)
#define _BFLDBC(x)			_DBC(x)
#define _BFLDBD(x)			_DBD(x)
#define _BFLDBD16(x)		_DBD16(x)
#define _BFLDBD32(x)		_DBD32(x)
#define _BFLDBH(x)			_DBH(x)
#define _BFLDBH16(x)		_DBH16(x)
#define _BFLDBH32(x)		_DBH32(x)
#define _BFLDG				_DG
#else
#define _BFLDBGH_(x,y)
#define _BFLDBG(x)
#define _BFLDBG_(x)
#define _BFLDBC(x)
#define _BFLDBD(x)
#define _BFLDBD16(x)
#define _BFLDBD32(x)
#define _BFLDBH(x)
#define _BFLDBH16(x)
#define _BFLDBH32(x)
#define _BFLDG
#endif

#if (P2_FW_DEBUG==1)
#define _DBG_RESULT(s,x)	(_DBG("\n\r"),_DBG(x),(s)?(_DBG(" fail "),_DBH32(s),_DBG("\n\r")):(_DBG(" success\n\r")))
#define _DBGH_(x,y)   /*_db_mhex     (DEBUG_UART_PORT, (uint8_t *)x, y)*/
#define _DBG(x)	 	 /* _db_msg      (DEBUG_UART_PORT, x)*/
#define _DBG_(x)	/*  _db_msg_     (DEBUG_UART_PORT, x)*/
#define _DBC(x)	 	 /* _db_char     (DEBUG_UART_PORT, x)*/
#define _DBD(x)	 	 /* _db_dec      (DEBUG_UART_PORT, x)*/
#define _DBD16(x)	  /*_db_dec_16   (DEBUG_UART_PORT, x)*/
#define _DBD32(x)	  /* _db_dec_32  (DEBUG_UART_PORT, x)*/
#define _DBH(x)	 	   /*_db_hex     (DEBUG_UART_PORT, x)*/
#define _DBH16(x)	  /*_db_hex_16   (DEBUG_UART_PORT, x)*/
#define _DBH32(x)	  /*_db_hex_32   (DEBUG_UART_PORT, x)*/
#define _DG			  /*_db_get_char (DEBUG_UART_PORT)*/
#define _DBDISP()
#elif (P2_FW_DEBUG==2)
#define _DBG_RESULT(s,x)	(_DBG("\n\r"),_DBG(x),(s)?(_DBG(" fail "),_DBH32(s),_DBG("\n\r")):(_DBG(" success\n\r")))
#define _DBGH_(x,y)   _dbpb_mhex     ((uint8_t *)x, y)
#define _DBG(x)	 	  _dbpb_msg      (x)
#define _DBG_(x)	  _dbpb_msg_     (x)
#define _DBC(x)	 	  _dbpb_char     (x)
#define _DBD(x)	 	  _dbpb_dec      (x)
#define _DBD16(x)	  _dbpb_dec_16   (x)
#define _DBD32(x)	  _dbpb_dec_32   (x)
#define _DBH(x)	 	  _dbpb_hex      (x)
#define _DBH16(x)	  _dbpb_hex_16   (x)
#define _DBH32(x)	  _dbpb_hex_32   (x)
#define _DBDISP()	  _dbpb_disp_    (DEBUG_UART_PORT)
#else
#define _DBG_RESULT(s,x)
#define _DBGH_(x,y)
#define _DBG(x) //printf(x)
#define _DBG_(x)
#define _DBC(x)
#define _DBD(x)
#define _DBD16(x)
#define _DBD32(x)
#define _DBH(x)
#define _DBH16(x)
#define _DBH32(x)
#define _DG
#define _DBDISP()
#endif
#if 0
extern void (*_db_mhex)(UART_TypeDef *UARTx, uint8_t *s, uint32_t len);
extern void (*_db_msg)(UART_TypeDef *UARTx, const void *s);
extern void (*_db_msg_)(UART_TypeDef *UARTx, const void *s);
extern void (*_db_char)(UART_TypeDef *UARTx, uint8_t ch);
extern void (*_db_dec)(UART_TypeDef *UARTx, uint8_t decn);
extern void (*_db_dec_16)(UART_TypeDef *UARTx, uint16_t decn);
extern void (*_db_dec_32)(UART_TypeDef *UARTx, uint32_t decn);
extern void (*_db_hex)(UART_TypeDef *UARTx, uint8_t hexn);
extern void (*_db_hex_16)(UART_TypeDef *UARTx, uint16_t hexn);
extern void (*_db_hex_32)(UART_TypeDef *UARTx, uint32_t hexn);
extern uint8_t (*_db_get_char)(UART_TypeDef *UARTx);

extern void (*_dbpb_mhex)(uint8_t *s, uint32_t len);
extern void (*_dbpb_msg)(const void *s);
extern void (*_dbpb_msg_)(const void *s);
extern void (*_dbpb_char)(uint8_t ch);
extern void (*_dbpb_dec)(uint8_t decn);
extern void (*_dbpb_dec_16)(uint16_t decn);
extern void (*_dbpb_dec_32)(uint32_t decn);
extern void (*_dbpb_hex)(uint8_t hexn);
extern void (*_dbpb_hex_16)(uint16_t hexn);
extern void (*_dbpb_hex_32)(uint32_t hexn);
extern void (*_dbpb_disp_)();

void UARTPutHexMulti (UART_TypeDef *UARTx, uint8_t *s, uint32_t len);
void UARTPutChar (UART_TypeDef *UARTx, uint8_t ch);
void UARTPuts(UART_TypeDef *UARTx, const void *str);
void UARTPuts_(UART_TypeDef *UARTx, const void *str);
void UARTPutDec(UART_TypeDef *UARTx, uint8_t decnum);
void UARTPutDec16(UART_TypeDef *UARTx, uint16_t decnum);
void UARTPutDec32(UART_TypeDef *UARTx, uint32_t decnum);
void UARTPutHex (UART_TypeDef *UARTx, uint8_t hexnum);
void UARTPutHex16 (UART_TypeDef *UARTx, uint16_t hexnum);
void UARTPutHex32 (UART_TypeDef *UARTx, uint32_t hexnum);
uint8_t UARTGetChar (UART_TypeDef *UARTx);
void debug_frmwrk_init(void);
#endif
#endif /* DEBUG_FRMWRK_H_ */
