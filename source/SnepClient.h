/*==============================================================================================
 *         Copyright (c), NXP Semiconductors
 *
 *       All rights are reserved. Reproduction in whole or in part is
 *      prohibited without the written consent of the copyright owner.
 *  NXP reserves the right to make changes without notice at any time.
 * NXP makes no warranty, expressed, implied or statutory, including but
 * not limited to any implied warranty of merchantability or fitness for any
 *particular purpose, or that the use will not infringe any third party patent,
 * copyright or trademark. NXP must not be liable for any loss or damage
 *                          arising from its use.
 */

/*==============================================================================================
 *   snepClient.h:  config file for example for NXP LPC122x Family
 *   Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2012.07.20   ver 1.00    First Release
 *   2013.03.15   ver 2.00    module rework to NxpRdLib
 *
 **********************************************************************************************/
#ifndef __SNEPCLIENT_H__
#define __SNEPCLIENT_H__

#include <ph_Status.h>
#include <phpalI18092mPI.h>
#include <phacDiscLoop.h>
#include <phOsal.h>
#include <phlnLlcp.h>
#include <phNfcHalTypes.h>
#include <phNfcTypes.h>
#include <ph_Status.h>

/*----------------------------------------------------------------------------------------------
 * Global macros and definitions
----------------------------------------------------------------------------------------------*/
#define  SS_Continue          0x80
#define  SS_Success           0x81
#define  SS_NotFound          0xC0
#define  SS_ExcessData        0xC1
#define  SS_BadRequest        0xC2
#define  SS_NotImplemented    0xE0
#define  SS_UnsuportedVersion 0xE1
#define  SS_Reject            0xFF

#define  SC_CONTINUE          0x00
#define  SC_GET               0x01
#define  SC_PUT               0x02
#define  SC_REJECT            0x7F

#define  SNEP_PROTOCOL_VER    0x10     // SNEP protocol version

#define  SEND_NOT_START       0
#define  SEND_START           1
#define  SEND_NOT_FINISHED    0
#define  SEND_FINISHED        1
#define  RECV_NOT_START       0
#define  RECV_START           1
#define  RECV_NOT_FINISHED    0
#define  RECV_FINISHED        1

#define  SAFETY_CNT_VAL       0x3FFF

#if 0
#define CHECK_SUCCESS(x)               \
   if ((x) != PH_ERR_SUCCESS)          \
       {                               \
       printf("Info (0x%04X)", (x));   \
       printf("\n");                   \
       }
#else
#define CHECK_SUCCESS(x)
#endif

// debugging switches
#ifdef _NDEBUG
   #define  PRINT_TRACE(x,y)
   #define  PRINT_TRACE_1(x,y)
   #define  PRINT_TRACE_2(x)
   #define  PRINT_TRACE_3(x,y)
   #define  PRINT_TRACE_6(x,y)
   #define  PRETTY_PRINTING(x,y)
#else
   #define  PRINT_TRACE(x,y)   printf(x,y);     // general printouts
   #define  PRINT_TRACE_1(x,y) printf("CB: ");  printf(x,y);     // Call-Back functions
   #define  PRINT_TRACE_2(x)   printf("C:  ");  printf(x);       // Client state machine
   #define  PRINT_TRACE_3(x,y) printf(x,y);     // deep degug printouts
// LLCP incoming message - defined directly in the "phFriNfc_LlcpTransport_Connection.c"
//   #define  PRINT_TRACE_4(x)
//   #define  PRINT_TRACE_5(x,y1,y2)
   #define  PRINT_TRACE_6(x,y)     PRINT_TRACE(x,y);

// nice printouts
#if 0
   #define  PRETTY_PRINTING(x,y)   PRINT_TRACE(x,y);
#else
   #define  PRETTY_PRINTING(x,y)
#endif

#endif
// debugging switches - end

typedef enum
{
   SC_start,
   SC_first,
   SC_recv,
   SC_next,
   SC_done,
   SC_disconnect,
   SC_rejected,
   SC_error
} HandleState_t;

typedef struct
{
    HandleState_t       Hstate;     // Hstate -> handle state
    uint16_t            SafetyCnt;
    uint8_t             bSendStart;    /**< Flag - fragment transmit started */
    uint8_t             bSendFinish;   /**< Flag - fragment transmit finished */
    uint8_t             bRecvStart;    /**< Flag - fragment receive started */
    uint8_t             bRecvFinish;   /**< Flag - fragment receive finished */
} SnepClientData_t;

extern uint8_t bSnepRx[];                                /**< SNEP RX buffer */
extern uint8_t bSnepTx[];                                /**< SNEP TX buffer */
extern uint8_t bRxBuffer[];                              /**< LLCP TX buffer */
extern uint8_t bTxBuffer[];                              /**< LLCP RX buffer */
extern uint8_t bLLCP_WorkingBuffer[];                    /**< LLCP working buffer */
extern uint8_t Llcp_running;                             /**< Flag indicating whether LLCP is running OR not */
extern uint8_t SocketConnected;                          /**< Flag indicating socket connection */
extern uint8_t Link_Activated;                           /**< Flag indicating link activation */

extern phNfc_sData_t sData;
extern phFriNfc_LlcpTransport_t         LlcpTransport;   /**< LLCP transport layer component */
extern phFriNfc_Llcp_sLinkParameters_t  LinkParam;       /**< LLCP link parameter */
extern phFriNfc_Llcp_t                  Llcp;            /**< LLCP pointer */
extern phHal_sRemoteDevInformation_t    RemoteInfo;      /**< Remote Info component */
extern phLibNfc_Llcp_sSocketOptions_t   sOptions;        /**< LLCP options */
extern phNfc_sData_t                    sWorkingBuffer;
extern phlnLlcp_Fri_DataParams_t        lnLlcpDataparams;
extern phFriNfc_LlcpTransport_Socket_t  *pSocket_Client;
extern phpalI18092mPI_Sw_DataParams_t   palI18092mPI;    /**< PAL MPI component */
#ifdef NXPBUILD__PH_OSAL_LPC12XX
extern phOsal_Lpc12xx_DataParams_t      osal;            /**< OSAL component holder for LPC12xx*/
#endif
#ifdef NXPBUILD__PH_OSAL_R_Pi
extern phOsal_R_Pi_DataParams_t         osal;            /**< OSAL component holder for RaspberryPi */
#endif
extern phacDiscLoop_Sw_DataParams_t     discLoop;        /**< Discovery loop component */

/* SNEP client data */
extern SnepClientData_t                 sSnepClientData;

/*----------------------------------------------------------------------------------------------
 * Global variables
----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------
 * Global function prototypes
----------------------------------------------------------------------------------------------*/
extern phStatus_t SNEPClientDemo(void);
extern void DisconnectCb(void* pContext,phStatus_t status);
extern phStatus_t NFC_LlcpClose(void);

#endif // __SNEPCLIENT_H__
/*----------------------------------------------------------------------------------------------
 * End of file
----------------------------------------------------------------------------------------------*/

