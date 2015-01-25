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
 *
 * File name:  snepClient.c
 *
 *  Created on:  March, 2013
 *      Author:  Igor Vitaz
 *
 *     Hystory:  2013.03.26  ver 1.00    initial version
 */

/*----------------------------------------------------------------------------------------------
 * Includes
 ---------------------------------------------------------------------------------------------*/
#ifdef NXPBUILD__PH_OSAL_LPC12XX
#ifdef __USE_CMSIS
#include "LPC122x.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

#ifndef NDEBUG
#include <stdio.h>
#endif
#include <driver_config.h>
#include <hw_config.h>
#include <gpio.h>
#include <RegCtl_SpiHw.h>

#endif

#include <stdio.h>

#include <ph_TypeDefs.h>
#include <ph_Status.h>

#include "ndef_message.h"
#include "SnepClient.h"


/*----------------------------------------------------------------------------------------------
 * Local function prototypes
 ---------------------------------------------------------------------------------------------*/
phStatus_t SnepClientHandle(SnepClientData_t *pClientData);
phStatus_t HandleSnepStart(SnepClientData_t *pClientData);
phStatus_t HandleSendFirst(SnepClientData_t *pClientData);
phStatus_t HandleRecv(SnepClientData_t *pClientData);
phStatus_t HandleSendNext(SnepClientData_t *pClientData);
phStatus_t HandleDone(SnepClientData_t *pClientData);
phStatus_t HandleDisconnect(SnepClientData_t *pClientData);
phStatus_t HandleReject(SnepClientData_t *pClientData);
phStatus_t HandleError(SnepClientData_t *pClientData);

/*----------------------------------------------------------------------------------------------
 * Local macros and definitions
 ---------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------
 * Local variables
 * -------------------------------------------------------------------------------------------*/
Convert32To4 sui32;
uint32_t wLength;
uint32_t payindex;
uint16_t index_out;

/*----------------------------------------------------------------------------------------------
 * Global variables
 * -------------------------------------------------------------------------------------------*/
uint8_t bSnepRx[8];                                /**< SNEP RX buffer */
uint8_t bSnepTx[128];                              /**< SNEP TX buffer */
uint8_t bRxBuffer[256];                            /**< LLCP TX buffer */
uint8_t bTxBuffer[256];                            /**< LLCP RX buffer */
uint8_t bLLCP_WorkingBuffer[800];                  /**< LLCP working buffer */
uint8_t Llcp_running;                              /**< Flag indicating whether LLCP is running OR not */
uint8_t SocketConnected;                           /**< Flag indicating socket connection */
uint8_t Link_Activated = 0;                        /**< Flag indicating link activation */

phNfc_sData_t sData;
phFriNfc_LlcpTransport_t         LlcpTransport;    /**< LLCP transport layer component */
phFriNfc_Llcp_sLinkParameters_t  LinkParam;        /**< LLCP link parameter */
phFriNfc_Llcp_t                  Llcp;             /**< LLCP pointer */
phHal_sRemoteDevInformation_t    RemoteInfo;       /**< Remote Info component */
phLibNfc_Llcp_sSocketOptions_t   sOptions = {128, 1}; /**< LLCP options */
phNfc_sData_t                    sWorkingBuffer = {bLLCP_WorkingBuffer, sizeof(bLLCP_WorkingBuffer)};
phlnLlcp_Fri_DataParams_t        lnLlcpDataparams;
phFriNfc_LlcpTransport_Socket_t  *pSocket_Client;
phpalI18092mPI_Sw_DataParams_t   palI18092mPI;     /**< PAL MPI component */
#ifdef NXPBUILD__PH_OSAL_LPC12XX
phOsal_Lpc12xx_DataParams_t      osal;            /**< OSAL component holder for LPC12xx*/
#endif
#ifdef NXPBUILD__PH_OSAL_R_Pi
phOsal_R_Pi_DataParams_t         osal;            /**< OSAL component holder for RaspberryPi */
#endif
phacDiscLoop_Sw_DataParams_t     discLoop;         /**< Discovery loop component */

/* SNEP client data */
SnepClientData_t                 sSnepClientData;

/*=====================================
 * SNEP client related functionalities
 *=====================================*/

/*==============================================================================================
 *  FUNCTION:  ErrCb
 *  PURPOSE:   Error call back
 *
 ---------------------------------------------------------------------------------------------*/
static void ErrCb (
      void* pContext,       /**< Error context */
      uint8_t nErrCode      /**< Error code sent */
)
   {
   PRINT_TRACE_1("ErrCb = %d\n", nErrCode);
   }

/*==============================================================================================
 *  FUNCTION:  CheckCb
 *  PURPOSE:   Check LLCP call back
 *
 ---------------------------------------------------------------------------------------------*/
static void CheckCb (
      void* pContext,       /**< Call back status */
      phStatus_t status     /**< status code of call back */
)
   {
   PRINT_TRACE_1("CheckCb = %d\n", status);
   if(status != NFCSTATUS_SUCCESS)
      {
      PRINT_TRACE_3("phFriNfc_Llcp_ChkLlcp callback function status = %d \n", status);
      }
   }

/*==============================================================================================
 *  FUNCTION:  LinkCb
 *  PURPOSE:   Link call back
 *
 ---------------------------------------------------------------------------------------------*/
static void LinkCB (
      void* pContext,                            /**< Context of the link call back */
      phFriNfc_Llcp_eLinkStatus_t eLinkStatus    /**< Link status */
)
   {
//   PRINT_TRACE("CB: LinkCb = %d\n", eLinkStatus); // this is main printout

   if (eLinkStatus == phFriNfc_LlcpMac_eLinkDeactivated)
      {
      PRINT_TRACE_1("LinkCb = Deactivated\n",NULL);
      Llcp_running = FALSE;
      }
   else if (eLinkStatus == phFriNfc_LlcpMac_eLinkActivated)
      {
      PRINT_TRACE_1("LinkCb = Activated\n",NULL);
      }
   else
      {
      PRINT_TRACE_1("LinkCb = Default\n",NULL);
      }
   }

/*==============================================================================================
 *  FUNCTION:  ConnectCb
 *  PURPOSE:   connection call back
 *
 ---------------------------------------------------------------------------------------------*/
static void ConnectCb (
      void* pContext,       /**< Context of the connect call back */
      uint8_t nErrCode,     /**< Error code */
      phStatus_t status     /**< status code */
)
   {
   PRINT_TRACE_1("ConnectCb = %d\n", status);

   if(status != PH_ERR_SUCCESS)
      {
      PRINT_TRACE("phFriNfc_LlcpTransport_Connect callback function status = %d \n", status);
      PRINT_TRACE(" errorCode = %d \n", nErrCode);
      }
   else
      {
      SocketConnected = TRUE;
      }
   }

/*==============================================================================================
 *  FUNCTION:  SendCb
 *  PURPOSE:   send SNEP call back
 *
 ---------------------------------------------------------------------------------------------*/
static void SendCb (
      void* pContext,       /**< Context of the send call back */
      phStatus_t status     /**< Status code with which this call back is called  */
)
   {
   PRINT_TRACE_1("SendCb = %d\n", status);
//   if (PRINT_TRACE_5) printf("CB: SendNULLCb\n");

   /* Send action completed */
   sSnepClientData.bSendStart = SEND_NOT_START;
   sSnepClientData.bSendFinish = SEND_FINISHED;
   }

/*==============================================================================================
 *  FUNCTION:  SendNULLCb
 *  PURPOSE:   send SNEP call back
 *
 ---------------------------------------------------------------------------------------------*/
static void SendNULLCb (
      void* pContext,       /**< Context of the send call back */
      phStatus_t status     /**< Status code with which this call back is called  */
)
   {
   PRINT_TRACE_1("SendNULLCb\n", NULL);

   /* Send action completed */
   sSnepClientData.bSendStart = SEND_NOT_START;
   sSnepClientData.bSendFinish = SEND_FINISHED;
   }
/*==============================================================================================
 *  FUNCTION:  RecvCb
 *  PURPOSE:   receive SNEP call back
 *
 ---------------------------------------------------------------------------------------------*/
static void RecvCb (
      void* pContext,       /**< Context of the send call back */
      phStatus_t status     /**< Status code with which this call back is called  */
)
   {
   uint8_t count;
   PRINT_TRACE_1("RecvCb = 0x ", NULL);
   for(count = 0; count < 6; count++) PRINT_TRACE_3("%X ", sData.buffer[count]);
   PRINT_TRACE_3("length = %d",sData.length);
   PRINT_TRACE_1("/n", NULL)
   /* set the state machine receiving is finished and
    * from now is possible to start receiving next message
    */
   sSnepClientData.bRecvStart = RECV_NOT_START;
   sSnepClientData.bRecvFinish = RECV_FINISHED;
   }

/*==============================================================================================
 *  FUNCTION:  DisconnectCb
 *  PURPOSE:   Disconnect call back
 *
 ---------------------------------------------------------------------------------------------*/
void DisconnectCb (
      void* pContext,       /**< Context of the receive call back */
      phStatus_t status     /**< status code */
)
   {
   PRINT_TRACE_1("DisconnectCb = %d \n", status);
   }

/*==============================================================================================
 *  FUNCTION:  NFC_LLCPSend
 *  PURPOSE:   send the message over LLCP
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t NFC_LLCPSend(
      phFriNfc_LlcpTransport_Socket_t *pSocket,
      uint8_t *buf,
      uint32_t len,
      pphFriNfc_LlcpTransportSocketSendCb_t pSndCb
)
   {
   static phNfc_sData_t sData;
   phStatus_t status;

   /* set the call-back function */
   if(pSndCb == NULL) pSndCb = &SendCb;

   sData.buffer = buf;
   sData.length = len;

   status = phlnLlcp_Transport_Send(
         &lnLlcpDataparams,
         pSocket,
         &sData,
         pSndCb,
         pSocket);
   CHECK_SUCCESS(status);

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  NFC_LLCPRecv
 *  PURPOSE:   receive the message over LLCP
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t NFC_LLCPRecv(
      phFriNfc_LlcpTransport_Socket_t *pSocket,
      phNfc_sData_t *psData,
      uint8_t *buf,
      uint32_t len,
      pphFriNfc_LlcpTransportSocketSendCb_t pRecvCb
)
   {
   phStatus_t status;

   /* set the call-back function */
   if(pRecvCb == NULL) pRecvCb = &RecvCb;

   psData->buffer = buf;
   psData->length = len;

   /**
    * \brief Read data on a socket
    * \return Status code
    * \retval #PH_ERR_SUCCESS Operation successful.
    * \retval Other Depending on implementation and underlaying component.
    */
   status = phlnLlcp_Transport_Recv(
         &lnLlcpDataparams,
         pSocket,
         psData,
         pRecvCb,
         (void*)psData);
   CHECK_SUCCESS(status);

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  NFC_LLCPInitialize
 *  PURPOSE:   Initialize the LLCP for communication
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t NFC_LLCPInitialize(void)
   {
   uint32_t            DummyContext;
   phStatus_t status = PH_ERR_SUCCESS;

   Llcp_running = TRUE;

   LinkParam.miu = 128;      // The remote Maximum Information Unit (NOTE: this is MIU, not MIUX !)
   LinkParam.lto = 100;      // remote link timeout [ms]
   LinkParam.wks = 0x0001;    // The remote Well-Known Services
   LinkParam.option = 0x02;   // The remote options

   status = phlnLlcp_Fri_Init(
         &lnLlcpDataparams,
         sizeof(lnLlcpDataparams),
         &Llcp,
         &LinkParam,
         &LlcpTransport,
         &RemoteInfo,
         bTxBuffer,
         sizeof(bTxBuffer),
         bRxBuffer,
         sizeof(bRxBuffer),
         &palI18092mPI);

   CHECK_SUCCESS(status);

   status = phlnLlcp_Reset(
         &lnLlcpDataparams,
         &LinkCB,
         &DummyContext);

   CHECK_SUCCESS(status);

   status = phlnLlcp_Transport_Reset(&lnLlcpDataparams);
   CHECK_SUCCESS(status);

   /* Assign the osal pointer to LLCP after reset*/
   Llcp.osal = &osal;

   status = phlnLlcp_ChkLlcp(
         &lnLlcpDataparams,
         &CheckCb,
         (void*) &DummyContext);
   CHECK_SUCCESS(status);

   status = phlnLlcp_Activate(&lnLlcpDataparams);
   CHECK_SUCCESS(status);

   if (status == NFCSTATUS_SUCCESS)
      {
      Link_Activated = 1;
      }

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  SnepClientInit
 *  PURPOSE:   Initialize the SNEP client service
 *
 ---------------------------------------------------------------------------------------------*/
static void SnepClientInit(SnepClientData_t   * pClientData)
   {
   pClientData->Hstate = SC_start;
   pClientData->bSendStart =  SEND_NOT_START;
   pClientData->bSendFinish = SEND_NOT_FINISHED;
   pClientData->bRecvStart =  RECV_NOT_START;
   pClientData->bRecvFinish = RECV_NOT_FINISHED;
   //   pClientData->MsgData = MsgData;
   //   pClientData->MsgLen  = MsgLen;
   //   pClientData->Index = 0;
   //   pClientData->SafetyCnt = SAFETY_CNT_VAL;

   }

/*==============================================================================================
 *  FUNCTION:  NFC_LLCPCreateClient
 *  PURPOSE:   Create the LLCP socket and connect
 *
 ---------------------------------------------------------------------------------------------*/
static phStatus_t NFC_LLCPCreateClient(phFriNfc_LlcpTransport_Socket_t **ppSocket, phNfc_sData_t *psUri)
   {
   phStatus_t status = NFCSTATUS_SUCCESS;
   uint32_t            DummyContext;

   status = phlnLlcp_Transport_Socket(
         &lnLlcpDataparams,
         phFriNfc_LlcpTransport_eConnectionOriented,
         &sOptions,
         &sWorkingBuffer,
         ppSocket,
         &ErrCb,
         (void*) &DummyContext);
   CHECK_SUCCESS(status);

   (*ppSocket)->socket_dSap = 1;
   SocketConnected = FALSE;

   status = phlnLlcp_Transport_ConnectByUri(
         &lnLlcpDataparams,
         *ppSocket,
         psUri,
         &ConnectCb,
         (void*) &DummyContext);
   CHECK_SUCCESS(status);

   /* Wait for connection completed or LLCP link deactivation */
   while(!SocketConnected && Llcp_running);

   PRINT_TRACE("NFC LLCP Create Client\n", NULL);

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  NFC_LlcpClose
 *  PURPOSE:   Function to clean the LLCP states
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t NFC_LlcpClose(void)
   {
   phStatus_t status = PH_ERR_SUCCESS;
   uint32_t            DummyContext;

   status = phlnLlcp_Transport_Disconnect(
         &lnLlcpDataparams,
         pSocket_Client,
         DisconnectCb,
         (void*) &DummyContext);

   status = phlnLlcp_Transport_Close(
         &lnLlcpDataparams,
         pSocket_Client);
   CHECK_SUCCESS(status);

   status = phpalI18092mPI_Deselect(&palI18092mPI, PHPAL_I18092MPI_DESELECT_DSL);
   CHECK_SUCCESS(status);

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  SnepClientHandle
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t SnepClientHandle(SnepClientData_t *pClientData)
   {
   phStatus_t status = PH_ERR_SUCCESS;
   switch ( pClientData->Hstate )
      {
      case SC_start:
         /* create client = create socket + create connect */
         status = HandleSnepStart(pClientData);
         break;

      case SC_first:
         /* start sending based PUT Request */
         status = HandleSendFirst(pClientData);
         break;

      case SC_recv:
         /* receive CONTINUE Response */
         status = HandleRecv(pClientData);
         break;

      case SC_next:
         /* transmit remain fragments */
         status = HandleSendNext(pClientData);
         break;

      case SC_done:
         /* transmitting has been done - link could close*/
         status = HandleDone(pClientData);
         break;

      case SC_disconnect:
         /* client close */
         status = HandleDisconnect(pClientData);
         break;

      case SC_rejected:
         /* client close */
         status = HandleReject(pClientData);
         break;

      case SC_error:
         /* client close */
         status = HandleError(pClientData);
         break;
      }
   return status;
   }

/*==============================================================================================
 *  FUNCTION:  HandleSnepStart
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleSnepStart(SnepClientData_t *pClientData)
   {
   uint8_t Uri[] = "urn:nfc:sn:snep";
   phNfc_sData_t sUri;
   phStatus_t status = PH_ERR_SUCCESS;

   sUri.buffer = (uint8_t *)&Uri;
   sUri.length = sizeof(Uri)-1;

   /* Create the LLCP socket and connect */
   status = NFC_LLCPCreateClient(&pSocket_Client, &sUri);
   CHECK_SUCCESS(status);

   if (status != PH_ERR_SUCCESS)
      {
      PRINT_TRACE_2("Start->Error\n");
      pClientData->Hstate = SC_error;
      }
   else
      {
      PRINT_TRACE_2("Start -> SendFirst\n");
      pClientData->Hstate = SC_first;
      }

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  HandleSendFirst
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleSendFirst(SnepClientData_t *pClientData)
   {
   phStatus_t status = PH_ERR_SUCCESS;

   if (pClientData->bSendStart == SEND_NOT_START)
      {
      /*prepare SNEP and NDEF header of message*/
      st_snep.buffer = &bSnepTx[SNEP_HEADER];
      Ndef_Decide(&st_snep, &n_mess[0]);
      st_snep.buffer = &bSnepTx[0];    // back to begin buffer
      bSnepTx[0] = SNEP_PROTOCOL_VER;  // SNEP protocol version
      bSnepTx[1] = SC_PUT;             // request command type
      sui32.val = st_snep.payload_len + st_snep.payload_start;
      reverse32(&bSnepTx[2], &sui32);
      st_snep.snep_len = sui32.val + SNEP_HEADER; // length of full SNEP

      index_out = SNEP_HEADER + st_snep.payload_start;
      wLength = 128 - index_out;
      if(wLength > st_snep.payload_len)
         {
         wLength = st_snep.payload_len;
         }
      memcpy(&st_snep.buffer[index_out], &st_snep.picture[0], wLength);
      payindex = wLength;
      wLength = wLength + index_out;

      /* set state machine switches */
      pClientData->bSendStart = SEND_START;
      pClientData->bSendFinish = SEND_NOT_FINISHED;
      pClientData->SafetyCnt = SAFETY_CNT_VAL;
      /* start fragment sending */
      status = NFC_LLCPSend(pSocket_Client, bSnepTx, wLength, NULL);
      st_snep.snep_len -= wLength;
      }

   // next state decision
   if (pClientData->bSendFinish == SEND_FINISHED)
      {
      if (status != PH_ERR_SUCCESS)
         {
         pClientData->Hstate = SC_error;
         PRINT_TRACE_2("ERROR !\n");
         }
      else
         {
         /* start receive action */
         if (pClientData->bRecvStart == RECV_NOT_START)
            {
            /* set state machine switches */
            pClientData->bRecvStart = RECV_START;
            pClientData->bRecvFinish = RECV_NOT_FINISHED;
            pClientData->SafetyCnt = SAFETY_CNT_VAL;
            /* start receiving response from server application */
            status = NFC_LLCPRecv(pSocket_Client, &sData, bSnepRx, sizeof(bSnepRx), NULL);
            /* set state machine switches */
            pClientData->bSendStart = SEND_START;
            pClientData->bSendFinish = SEND_NOT_FINISHED;
            pClientData->SafetyCnt = SAFETY_CNT_VAL;
            /* start NULL message sending */
            status = NFC_LLCPSend(pSocket_Client, NULL, NULL, &SendNULLCb);
            }
         /* check length of the message */
         pClientData->Hstate = SC_recv;
         PRINT_TRACE_2("SendFirst -> Recv\n");
         }
      }
   else
      {
      pClientData->SafetyCnt--;
      if (!pClientData->SafetyCnt)
         {
         pClientData->Hstate = SC_disconnect;
         PRINT_TRACE_2("counter reset\n");
         }
      }

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  HandleRecvFirst
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleRecv(SnepClientData_t *pClientData)
   {
   phStatus_t  status = PH_ERR_SUCCESS;
   uint8_t     bRespCode;

   if (pClientData->bRecvFinish == RECV_FINISHED)
      {
      if (status != PH_ERR_SUCCESS)
         {
         pClientData->Hstate = SC_error;
         PRINT_TRACE_2("ERROR ! \n");
         }
      else
         {
         if (sData.length > 0)
            {
            if (sData.length != 6)
               {
               pClientData->Hstate = SC_disconnect;
               PRINT_TRACE_2("length != 6\n");
               return status;
               }

            /* read incoming server response */
            bRespCode = sData.buffer[1];

            switch ( bRespCode )
               {
               case SS_Continue:
                  pClientData->Hstate = SC_next;
                  PRINT_TRACE_2("CONTINUE\n");
//                  PRINT_TRACE_2("Recv -> SendNext\n");
                  break;

               case SS_Success:
                  /* PUT - information field shall not be present */
                  /* GET - not implemented  - contain NDEF msg. */
                  pClientData->Hstate = SC_done;
                  PRINT_TRACE_2("SUCCESS\n");
                  PRINT_TRACE_2("Recv -> Done\n");
                  break;

               case SS_NotFound:
                  /* not relevant answer on the request */
                  pClientData->Hstate = SC_disconnect;
                  PRINT_TRACE_2("NOT FOUND\n");
                  break;

               case SS_ExcessData:
                  /* too data which exceed the capacity of client */
                  pClientData->Hstate = SC_disconnect;
                  PRINT_TRACE_2("EXCESS DATA\n");
                  break;

               case SS_BadRequest:
                  /* request is not understood - malformed syntax */
                  pClientData->Hstate = SC_disconnect;
                  PRINT_TRACE_2("BAD REQUEST\n");
                  break;

               case SS_NotImplemented:
                  /* request code doesn't recognized */
                  pClientData->Hstate = SC_disconnect;
                  PRINT_TRACE_2("NOT IMPLEMENTED\n");
                  break;

               case SS_UnsuportedVersion:
                  /* SNEP protocol version doesn't support */
                  pClientData->Hstate = SC_disconnect;
                  PRINT_TRACE_2("UNSUPPORTED VERSION \n");
                  break;

               case SS_Reject:
                  pClientData->Hstate = SC_rejected;
                  PRINT_TRACE_2("REJECT !\n");
                  PRINT_TRACE_2("Recv -> Reject\n");
                  break;

               default:
                  pClientData->Hstate = SC_disconnect;
                  PRINT_TRACE_2("DEFAULT !\n");
                  PRINT_TRACE_2("Recv -> Disconect\n");
                  break;
               }  // switch
            }     // length > 0
         }        // status OK
      }           // receive finished
   else
      {
      pClientData->SafetyCnt--;
      if (!pClientData->SafetyCnt)
         {
         pClientData->Hstate = SC_disconnect;
         PRINT_TRACE_2("counter reset\n");
         PRINT_TRACE_2("Recv -> Disconect\n");
         }
      }
   return status;
   }

/*==============================================================================================
 *  FUNCTION:  HandleSnepNext
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleSendNext(SnepClientData_t *pClientData)
   {
   phStatus_t  status = PH_ERR_SUCCESS;
   uint8_t     bLastSend = 0;

   if (pClientData->bSendFinish == SEND_FINISHED)
      {
      if(st_snep.snep_len > 128)
         {
         /* set maximum length for transmit buffer */
         wLength = 128;
         }
      else
         {
         /* set remain length for transmit buffer */
         wLength = st_snep.snep_len;
         bLastSend = 1;
         }

      memcpy(&st_snep.buffer[0], &st_snep.picture[payindex], wLength);

      /* set state machine switches */
      pClientData->bSendStart = SEND_START;
      pClientData->bSendFinish = SEND_NOT_FINISHED;
      pClientData->SafetyCnt = SAFETY_CNT_VAL;
      /* start fragment sending */
      status = NFC_LLCPSend(pSocket_Client, bSnepTx, wLength, NULL);
      PRINT_TRACE("Rest len: %d\n",st_snep.snep_len);
      st_snep.snep_len -= wLength;
      payindex += wLength;
      status = phOsal_Timer_Wait(&osal, 1, 20);
      }
   else
      {
      pClientData->SafetyCnt--;
      if (!pClientData->SafetyCnt)
         {
         pClientData->Hstate = SC_disconnect;
         PRINT_TRACE_2("counter reset\n");
         PRINT_TRACE("safety counter !!!!!!!!!!!!!\n",NULL)
         }
      }

   // next state decision
   if ( bLastSend )
      {
      pClientData->Hstate = SC_recv;
      /* set next step after last sending */
      PRINT_TRACE_2("SendNext -> Recv\n");
      /* set state machine switches */
      pClientData->bRecvStart = RECV_START;
      pClientData->bRecvFinish = RECV_NOT_FINISHED;
      pClientData->SafetyCnt = SAFETY_CNT_VAL;
      /* start receiving response from server application */
      status = NFC_LLCPRecv(pSocket_Client, &sData, bSnepRx, sizeof(bSnepRx), NULL);
      /* set state machine switches */
      pClientData->bSendStart = SEND_START;
      pClientData->bSendFinish = SEND_NOT_FINISHED;
      pClientData->SafetyCnt = SAFETY_CNT_VAL;
      /* start NULL message sending */
      status = NFC_LLCPSend(pSocket_Client, NULL, NULL, &SendNULLCb);
      }

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  HandleDone
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleDone(SnepClientData_t *pClientData)
   {
   phStatus_t status = PH_ERR_SUCCESS;

   pClientData->Hstate = SC_disconnect;
   PRINT_TRACE_2("Done -> Disconnect \n");

   return status;
   }


/*==============================================================================================
 *  FUNCTION:  Handle
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleDisconnect(SnepClientData_t *pClientData)
   {
   phStatus_t status = PH_ERR_SUCCESS;

   status = NFC_LlcpClose();

   PRINT_TRACE("NFC LLCP Close\n", NULL);

   if (status != PH_ERR_SUCCESS)
      {
      PRINT_TRACE_2("ERROR ! \n");
      }
   else
      {
      PRINT_TRACE_2("DISCONNECT ! \n");
      }

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  HandleReject
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleReject(SnepClientData_t *pClientData)
   {
   phStatus_t status = PH_ERR_SUCCESS;

   pClientData->Hstate = SC_disconnect;
   PRINT_TRACE_2("Reject -> Disconnect \n");

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  HandleError
 *  PURPOSE:
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t HandleError(SnepClientData_t *pClientData)
   {
   phStatus_t status = PH_ERR_SUCCESS;

   pClientData->Hstate = SC_disconnect;
   PRINT_TRACE_2("Error -> Disconnect \n");

   return status;
   }

/*==============================================================================================
 *  FUNCTION:  SNEPClientDemo
 *  PURPOSE:   Function to demonstrate SNEP client application
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t SNEPClientDemo(void)
   {
   phStatus_t status = PH_ERR_SUCCESS;

   /* Initialize the LLCP layer */
   status = NFC_LLCPInitialize();
   CHECK_SUCCESS(status);

   PRINT_TRACE ("NFC LLCP Initialize\n", NULL);

   /* -----------------------------------------------------------------------
    * INIT SNEP data
    * ---------------------------------------------------------------------*/
   SnepClientInit(&sSnepClientData);

   status = PH_ERR_SUCCESS;

   /* -----------------------------------------------------------------------
    * STATE MACHINE
    * ---------------------------------------------------------------------*/
   PRINT_TRACE("\nSNEP client Start ...\n", NULL);

   while ((status == PH_ERR_SUCCESS) && (sSnepClientData.Hstate != SC_disconnect))
      {
      status = SnepClientHandle(&sSnepClientData);
      CHECK_SUCCESS(status);
      }

   if (sSnepClientData.Hstate == SC_disconnect)
      {
      status = SnepClientHandle(&sSnepClientData);
      }

   PRINT_TRACE("SNEP Client finished  ...\n\n", NULL);

   /* -----------------------------------------------------------------------
    * STATE MACHINE - END
    * ---------------------------------------------------------------------*/

   return status;
   }

/* ---------------------------------------------------------------------------------------------
 *   End of File
 ---------------------------------------------------------------------------------------------*/


