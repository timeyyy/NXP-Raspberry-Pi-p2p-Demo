/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/**
 * \file  phFriNfc_LlcpTransport_Connectionless.c
 * \brief 
 *
 * Project: NFC-FRI
 *
 */
/*include files*/
//#include <phOsalNfc.h>
#include "phLibNfcStatus.h"
#include "phLibNfc.h"
#include "phNfcLlcpTypes.h"
#include "phFriNfc_LlcpTransport.h"
#include "phFriNfc_Llcp.h"
#include <phOsal.h>

static void phFriNfc_LlcpTransport_Connectionless_SendTo_CB(void*        pContext,
                                                            NFCSTATUS    status);

static void phFriNfc_LlcpTransport_Connectionless_TriggerSendCb(phFriNfc_LlcpTransport_Socket_t  *pLlcpSocket,
                                                                NFCSTATUS                        status)
{
   pphFriNfc_LlcpTransportSocketSendCb_t  pfSendCb;
   void*                                  pSendContext;

   if (pLlcpSocket->pfSocketSend_Cb != NULL)
   {
      /* Copy CB + context in local variables */
      pfSendCb = pLlcpSocket->pfSocketSend_Cb;
      pSendContext = pLlcpSocket->pSendContext;

      /* Reset CB + context */
      pLlcpSocket->pfSocketSend_Cb = NULL;
      pLlcpSocket->pSendContext = NULL;

      /* Perform callback */
      pfSendCb(pSendContext, status);
   }
}

static void phFriNfc_LlcpTransport_Connectionless_TriggerRecvFromCb(phFriNfc_LlcpTransport_Socket_t  *pLlcpSocket,
                                                                    uint8_t                          ssap,
                                                                    NFCSTATUS                        status)
{
   pphFriNfc_LlcpTransportSocketRecvFromCb_t  pfSocketRecvFrom_Cb;
   void*                                      pRecvContext;

   /* TODO: use phFriNfc_LlcpTransport_Connectionless_TriggerRecvFromCb? */
   if (pLlcpSocket->pfSocketRecvFrom_Cb != NULL)
   {
      /* Copy CB + context in local variables */
      pfSocketRecvFrom_Cb = pLlcpSocket->pfSocketRecvFrom_Cb;
      pRecvContext = pLlcpSocket->pRecvContext;

      /* Reset CB + context */
      pLlcpSocket->pfSocketRecvFrom_Cb = NULL;
      pLlcpSocket->pfSocketRecv_Cb = NULL;
      pLlcpSocket->pRecvContext = NULL;

      /* Perform callback */
      pfSocketRecvFrom_Cb(pRecvContext, ssap, status);
   }
}

NFCSTATUS phFriNfc_LlcpTransport_Connectionless_HandlePendingOperations(phFriNfc_LlcpTransport_Socket_t *pSocket)
{
   NFCSTATUS status = NFCSTATUS_FAILED;

   /* Check if something is pending and if transport layer is ready to send */
   if ((pSocket->pfSocketSend_Cb != NULL) &&
       (pSocket->psTransport->bSendPending == FALSE))
   {
      /* Fill the psLlcpHeader stuture with the DSAP,PTYPE and the SSAP */
      pSocket->sLlcpHeader.dsap  = pSocket->socket_dSap;
      pSocket->sLlcpHeader.ptype = PHFRINFC_LLCP_PTYPE_UI;
      pSocket->sLlcpHeader.ssap  = pSocket->socket_sSap;

      /* Send to data to the approiate socket */
      status =  phFriNfc_LlcpTransport_LinkSend(pSocket->psTransport,
                                   &pSocket->sLlcpHeader,
                                   NULL,
                                   &pSocket->sSocketSendBuffer,
                                   phFriNfc_LlcpTransport_Connectionless_SendTo_CB,
                                   pSocket);
   }
   else
   {
      /* Cannot send now, retry later */
   }

   return status;
}


/* TODO: comment function Handle_Connectionless_IncommingFrame */
void Handle_Connectionless_IncommingFrame(phFriNfc_LlcpTransport_t      *pLlcpTransport,
                                          phNfc_sData_t                 *psData,
                                          uint8_t                       dsap,
                                          uint8_t                       ssap)
{
   phFriNfc_LlcpTransport_Socket_t * pSocket = NULL;
   uint8_t                           i       = 0;
   uint8_t                           writeIndex;

   /* Look through the socket table for a match */
   for(i=0;i<PHFRINFC_LLCP_NB_SOCKET_MAX;i++)
   {
      if(pLlcpTransport->pSocketTable[i].socket_sSap == dsap)
      {
         /* Socket found ! */
         pSocket = &pLlcpTransport->pSocketTable[i];

         /* Forward directly to application if a read is pending */
         if (pSocket->bSocketRecvPending == TRUE)
         {
            /* Reset the RecvPending variable */
            pSocket->bSocketRecvPending = FALSE;

            /* Copy the received buffer into the receive buffer */
            memcpy(pSocket->sSocketRecvBuffer->buffer, psData->buffer, psData->length);

            /* Update the received length */
            *pSocket->receivedLength = psData->length;

            /* call the recv callback */
            phFriNfc_LlcpTransport_Connectionless_TriggerRecvFromCb(pSocket, ssap, NFCSTATUS_SUCCESS);
         }
         /* If no read is pending, try to bufferize for later reading */
         else
         {
            if((pSocket->indexRwWrite - pSocket->indexRwRead) < pSocket->localRW)
            {
               writeIndex = pSocket->indexRwWrite % pSocket->localRW;
               /* Save SSAP */
               pSocket->sSocketRwBufferTable[writeIndex].buffer[0] = ssap;
               /* Save UI frame payload */
               memcpy(pSocket->sSocketRwBufferTable[writeIndex].buffer + 1,
                      psData->buffer,
                      psData->length);
               pSocket->sSocketRwBufferTable[writeIndex].length = psData->length;
               
               /* Update the RW write index */
               pSocket->indexRwWrite++;
            }
            else
            {
               /* Unable to bufferize the packet, drop it */
            }
         }
         break;
      }
   }
}

/* TODO: comment function phFriNfc_LlcpTransport_Connectionless_SendTo_CB */
static void phFriNfc_LlcpTransport_Connectionless_SendTo_CB(void*        pContext,
                                                            NFCSTATUS    status)
{
   phFriNfc_LlcpTransport_Socket_t   *pLlcpSocket = (phFriNfc_LlcpTransport_Socket_t*)pContext;

   /* Reset the SendPending variable */
   pLlcpSocket->bSocketSendPending = FALSE;

   /* Call the send callback */
   phFriNfc_LlcpTransport_Connectionless_TriggerSendCb(pLlcpSocket,status);
}

static void phFriNfc_LlcpTransport_Connectionless_Abort(phFriNfc_LlcpTransport_Socket_t* pLlcpSocket)
{
   phFriNfc_LlcpTransport_Connectionless_TriggerSendCb(pLlcpSocket, NFCSTATUS_ABORTED);
   phFriNfc_LlcpTransport_Connectionless_TriggerRecvFromCb(pLlcpSocket, 0, NFCSTATUS_ABORTED);
   pLlcpSocket->pAcceptContext = NULL;
   pLlcpSocket->pfSocketAccept_Cb = NULL;
   pLlcpSocket->pListenContext = NULL;
   pLlcpSocket->pfSocketListen_Cb = NULL;
   pLlcpSocket->pConnectContext = NULL;
   pLlcpSocket->pfSocketConnect_Cb = NULL;
   pLlcpSocket->pDisonnectContext = NULL;
   pLlcpSocket->pfSocketDisconnect_Cb = NULL;
}

/**
* \ingroup grp_fri_nfc
* \brief <b>Close a socket on a LLCP-connectionless device</b>.
*
* This function closes a LLCP socket previously created using phFriNfc_LlcpTransport_Socket.
*
* \param[in]  pLlcpSocket                    A pointer to a phFriNfc_LlcpTransport_Socket_t.

* \retval NFCSTATUS_SUCCESS                  Operation successful.
* \retval NFCSTATUS_INVALID_PARAMETER        One or more of the supplied parameters
*                                            could not be properly interpreted.
* \retval NFCSTATUS_FAILED                   Operation failed.
*/
NFCSTATUS phFriNfc_LlcpTransport_Connectionless_Close(phFriNfc_LlcpTransport_Socket_t*   pLlcpSocket)
{
   /* Reset the pointer to the socket closed */
   pLlcpSocket->eSocket_State                      = phFriNfc_LlcpTransportSocket_eSocketDefault;
   pLlcpSocket->eSocket_Type                       = phFriNfc_LlcpTransport_eDefaultType;
   pLlcpSocket->pContext                           = NULL;
   pLlcpSocket->pSocketErrCb                       = NULL;
   pLlcpSocket->socket_sSap                        = PHFRINFC_LLCP_SAP_DEFAULT;
   pLlcpSocket->socket_dSap                        = PHFRINFC_LLCP_SAP_DEFAULT;
   pLlcpSocket->bSocketRecvPending                 = FALSE;
   pLlcpSocket->bSocketSendPending                 = FALSE;
   pLlcpSocket->bSocketListenPending               = FALSE;
   pLlcpSocket->bSocketDiscPending                 = FALSE;
   pLlcpSocket->RemoteBusyConditionInfo            = FALSE;
   pLlcpSocket->ReceiverBusyCondition              = FALSE;
   pLlcpSocket->socket_VS                          = 0;
   pLlcpSocket->socket_VSA                         = 0;
   pLlcpSocket->socket_VR                          = 0;
   pLlcpSocket->socket_VRA                         = 0;

   phFriNfc_LlcpTransport_Connectionless_Abort(pLlcpSocket);

   memset(&pLlcpSocket->sSocketOption, 0x00, sizeof(phFriNfc_LlcpTransport_sSocketOptions_t));

   if (pLlcpSocket->sServiceName.buffer != NULL) {
       phOsal_FreeMemory(pLlcpSocket->psTransport->pLlcp->osal,
           pLlcpSocket->sServiceName.buffer);
   }
   pLlcpSocket->sServiceName.buffer = NULL;
   pLlcpSocket->sServiceName.length = 0;

   return NFCSTATUS_SUCCESS;
}

/**
* \ingroup grp_fri_nfc
* \brief <b>Send data on a socket to a given destination SAP</b>.
*
* This function is used to write data on a socket to a given destination SAP.
* This function can only be called on a connectionless socket.
* 
*
* \param[in]  pLlcpSocket        A pointer to a LlcpSocket created.
* \param[in]  nSap               The destination SAP.
* \param[in]  psBuffer           The buffer containing the data to send.
* \param[in]  pSend_RspCb        The callback to be called when the 
*                                operation is completed.
* \param[in]  pContext           Upper layer context to be returned in
*                                the callback.
*
* \retval NFCSTATUS_SUCCESS                  Operation successful.
* \retval NFCSTATUS_INVALID_PARAMETER        One or more of the supplied parameters
*                                            could not be properly interpreted.
* \retval NFCSTATUS_PENDING                  Reception operation is in progress,
*                                            pSend_RspCb will be called upon completion.
* \retval NFCSTATUS_INVALID_STATE            The socket is not in a valid state, or not of 
*                                            a valid type to perform the requsted operation.
* \retval NFCSTATUS_NOT_INITIALISED          Indicates stack is not yet initialized.
* \retval NFCSTATUS_SHUTDOWN                 Shutdown in progress.
* \retval NFCSTATUS_FAILED                   Operation failed.
*/
NFCSTATUS phFriNfc_LlcpTransport_Connectionless_SendTo(phFriNfc_LlcpTransport_Socket_t             *pLlcpSocket,
                                                       uint8_t                                     nSap,
                                                       phNfc_sData_t*                              psBuffer,
                                                       pphFriNfc_LlcpTransportSocketSendCb_t       pSend_RspCb,
                                                       void*                                       pContext)
{
   NFCSTATUS status = NFCSTATUS_FAILED;

   /* Store send callback  and context*/
   pLlcpSocket->pfSocketSend_Cb = pSend_RspCb;
   pLlcpSocket->pSendContext    = pContext;

   /* Test if a send is already pending at transport level */
   if(pLlcpSocket->psTransport->bSendPending == TRUE)
   {
      /* Save the request so it can be handled in phFriNfc_LlcpTransport_Connectionless_HandlePendingOperations() */
      pLlcpSocket->sSocketSendBuffer = *psBuffer;
      pLlcpSocket->socket_dSap      = nSap;
      status = NFCSTATUS_PENDING;
   }
   else
   {
      /* Fill the psLlcpHeader stuture with the DSAP,PTYPE and the SSAP */
      pLlcpSocket->sLlcpHeader.dsap  = nSap;
      pLlcpSocket->sLlcpHeader.ptype = PHFRINFC_LLCP_PTYPE_UI;
      pLlcpSocket->sLlcpHeader.ssap  = pLlcpSocket->socket_sSap;

      /* Send to data to the approiate socket */
      status =  phFriNfc_LlcpTransport_LinkSend(pLlcpSocket->psTransport,
                                   &pLlcpSocket->sLlcpHeader,
                                   NULL,
                                   psBuffer,
                                   phFriNfc_LlcpTransport_Connectionless_SendTo_CB,
                                   pLlcpSocket);
   }

   return status;
}


 /**
* \ingroup grp_lib_nfc
* \brief <b>Read data on a socket and get the source SAP</b>.
*
* This function is the same as phLibNfc_Llcp_Recv, except that the callback includes
* the source SAP. This functions can only be called on a connectionless socket.
* 
*
* \param[in]  pLlcpSocket        A pointer to a LlcpSocket created.
* \param[in]  psBuffer           The buffer receiving the data.
* \param[in]  pRecv_RspCb        The callback to be called when the 
*                                operation is completed.
* \param[in]  pContext           Upper layer context to be returned in
*                                the callback.
*
* \retval NFCSTATUS_SUCCESS                  Operation successful.
* \retval NFCSTATUS_INVALID_PARAMETER        One or more of the supplied parameters
*                                            could not be properly interpreted.
* \retval NFCSTATUS_PENDING                  Reception operation is in progress,
*                                            pRecv_RspCb will be called upon completion.
* \retval NFCSTATUS_INVALID_STATE            The socket is not in a valid state, or not of 
*                                            a valid type to perform the requsted operation.
* \retval NFCSTATUS_NOT_INITIALISED          Indicates stack is not yet initialized.
* \retval NFCSTATUS_SHUTDOWN                 Shutdown in progress.
* \retval NFCSTATUS_FAILED                   Operation failed.
*/
NFCSTATUS phLibNfc_LlcpTransport_Connectionless_RecvFrom(phFriNfc_LlcpTransport_Socket_t                   *pLlcpSocket,
                                                         phNfc_sData_t*                                    psBuffer,
                                                         pphFriNfc_LlcpTransportSocketRecvFromCb_t         pRecv_Cb,
                                                         void                                              *pContext)
{
   NFCSTATUS   status = NFCSTATUS_PENDING;
   uint8_t     readIndex;
   uint8_t     ssap;

   if(pLlcpSocket->bSocketRecvPending)
   {
      status = PHNFCSTVAL(CID_FRI_NFC_LLCP_TRANSPORT, NFCSTATUS_REJECTED);
   }
   else
   {
      /* Check if pending packets in RW */
      if(pLlcpSocket->indexRwRead != pLlcpSocket->indexRwWrite)
      {
         readIndex = pLlcpSocket->indexRwRead % pLlcpSocket->localRW;

         /* Extract ssap and buffer from RW buffer */
         ssap = pLlcpSocket->sSocketRwBufferTable[readIndex].buffer[0];
         memcpy(psBuffer->buffer,
                pLlcpSocket->sSocketRwBufferTable[readIndex].buffer + 1,
                pLlcpSocket->sSocketRwBufferTable[readIndex].length);
         psBuffer->length = pLlcpSocket->sSocketRwBufferTable[readIndex].length;

         /* Reset RW buffer length */
         pLlcpSocket->sSocketRwBufferTable[readIndex].length = 0;

         /* Update Value Rw Read Index */
         pLlcpSocket->indexRwRead++;

         /* call the recv callback */
         pRecv_Cb(pContext, ssap, NFCSTATUS_SUCCESS);

         status = NFCSTATUS_SUCCESS;
      }
      /* Otherwise, wait for a packet to come */
      else
      {
         /* Store the callback and context*/
         pLlcpSocket->pfSocketRecvFrom_Cb  = pRecv_Cb;
         pLlcpSocket->pRecvContext         = pContext;

         /* Store the pointer to the receive buffer */
         pLlcpSocket->sSocketRecvBuffer   =  psBuffer;
         pLlcpSocket->receivedLength      =  &psBuffer->length;

         /* Set RecvPending to TRUE */
         pLlcpSocket->bSocketRecvPending = TRUE;
      }
   }
   return status;
}
