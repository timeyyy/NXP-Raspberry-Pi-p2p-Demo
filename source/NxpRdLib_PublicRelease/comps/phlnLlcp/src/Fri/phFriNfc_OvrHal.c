/*
 *                    Copyright (c), NXP Semiconductors
 *
 *                       (C)NXP Electronics N.V.2005
 *         All rights are reserved. Reproduction in whole or in part is
 *        prohibited without the written consent of the copyright owner.
 *    NXP reserves the right to make changes without notice at any time.
 *   NXP makes no warranty, expressed, implied or statutory, including but
 *   not limited to any implied warranty of merchantability or fitness for any
 *  particular purpose, or that the use will not infringe any third party patent,
 *   copyright or trademark. NXP must not be liable for any loss or damage
 *                            arising from its use.
 *
 */

/*!
 * \file  phFriNfc_OvrHal.c
 * \brief Overlapped HAL
 *
 */
#include "phFriNfc_OvrHal.h"
#include "ph_Status.h"
#include "debug_frmwrk.h"
#include <phpalI18092mPI.h>

#define THREAD_ 0
#define NOTHREAD_ 1

typedef struct
{
   phFriNfc_CplRt_t               *CompletionInfo;
   uint8_t                        *SendBuf;
   uint16_t                        SendLength;
   uint8_t                        *RecvBuf;
   uint16_t                       *RecvLength;
} OvrHalTask_struct_t;

static uint8_t OvrHal_running;
static OvrHalTask_struct_t OvrHalTask_struct;

void phFriNfc_OvrHal_Init(void)
   {
   }

void phFriNfc_OvrHal_DeInit(void)
   {
   OvrHal_running = FALSE;
   while(!OvrHal_running) ;
   //mlsOsalDelayMs(100);
   }

NFCSTATUS phFriNfc_OvrHal_Transceive(void              *OvrHal,
      phFriNfc_CplRt_t               *CompletionInfo,
      phHal_sRemoteDevInformation_t  *RemoteDevInfo,
      phHal_uCmdList_t                Cmd,
      phHal_sDepAdditionalInfo_t     *DepAdditionalInfo,
      uint8_t                        *SendBuf,
      uint16_t                        SendLength,
      uint8_t                        *RecvBuf,
      uint16_t                       *RecvLength)
   {
   NFCSTATUS status = NFCSTATUS_PENDING;
   uint16_t length = 0;
   uint16_t i = 0;

   PHNFC_UNUSED_VARIABLE(DepAdditionalInfo);
   //PHNFC_UNUSED_VARIABLE(&Cmd);
#define _PRABAKARAN_20130227_
#ifdef  _PRABAKARAN_20130227_
   uint8_t hackBuf[] = {0x83, 0x04, 0x01, 0x10, 0x80, 0x0, 0x0, 0x0, 0x0};
   uint8_t tempBuf[] = {0x0, 0x0};
#endif // _PRABAKARAN_20130227_
   _DBG_("phFriNfc_OvrHal_Transceive");

   /* Check the Input Parameters */
   if ((NULL == OvrHal) || (NULL == CompletionInfo) || (NULL == RemoteDevInfo)
         || (NULL == (void*)SendBuf) || (NULL == RecvBuf) || (NULL == RecvLength)
         || ((phHal_eJewel_PICC != RemoteDevInfo->RemDevType) && (0 == SendLength)))

      {
      status = PHNFCSTVAL(CID_FRI_NFC_OVR_HAL, NFCSTATUS_INVALID_PARAMETER);
      }
   else
      {
      OvrHalTask_struct.CompletionInfo = CompletionInfo;
      OvrHalTask_struct.SendBuf = SendBuf;
      OvrHalTask_struct.SendLength = SendLength;
      OvrHalTask_struct.RecvBuf = RecvBuf;
      OvrHalTask_struct.RecvLength = RecvLength;

#if NOTHREAD_
      length = NFC_SendDEP(OvrHal,
            OvrHalTask_struct.SendBuf,
            OvrHalTask_struct.SendLength,
            &(OvrHalTask_struct.RecvBuf), 
            (OvrHalTask_struct.RecvLength));

      if (length != 0)
         {
         if (length == 2)
            {
#if _DEBUG_
            printf("Received a sym PDU \n");
            printf("Sending the frame again \n");
#endif /* _DEBUG_ */

#ifdef   _PRABAKARAN_20130227_
            length = NFC_SendDEP(
                  OvrHal,
                  tempBuf,
                  2,
                  &(OvrHalTask_struct.RecvBuf),
                  (OvrHalTask_struct.RecvLength));
#else
            length = NFC_SendDEP(
                  OvrHal,
                  OvrHalTask_struct.SendBuf,
                  OvrHalTask_struct.SendLength,
                  &(OvrHalTask_struct.RecvBuf),
                  (OvrHalTask_struct.RecvLength));
#endif // _PRABAKARAN_20130227_
            }

         if (length != 0)
            {
#if 0
            if ( OvrHalTask_struct.RecvBuf[0] == 0x83 &&
                  OvrHalTask_struct.RecvBuf[1] == 0x44 &&
                  OvrHalTask_struct.RecvBuf[2] == 0x01)
               {
               memcpy(RecvBuf, hackBuf, 8);
               *RecvLength = 8;
               }
            else
#endif
               {
               memcpy(RecvBuf, (OvrHalTask_struct.RecvBuf), length);
               *RecvLength = length;
               }
            CompletionInfo->CompletionRoutine(CompletionInfo->Context, NFCSTATUS_SUCCESS);
            status = NFCSTATUS_SUCCESS;
            }
         }
      else
         {
         printf("Transmit failed \n");
         }
#endif
      }

   return status;
   }

NFCSTATUS phFriNfc_OvrHal_Receive(
      void                          *OvrHal,
      phFriNfc_CplRt_t              *CompletionInfo,
      phHal_sRemoteDevInformation_t *RemoteDevInfo,
      uint8_t                       *RecvBuf,
      uint16_t                      *RecvLength)
   {
   NFCSTATUS status = NFCSTATUS_PENDING;

   PHNFC_UNUSED_VARIABLE(OvrHal);
   PHNFC_UNUSED_VARIABLE(CompletionInfo);
   PHNFC_UNUSED_VARIABLE(RemoteDevInfo);
   PHNFC_UNUSED_VARIABLE(RecvBuf);
   PHNFC_UNUSED_VARIABLE(RecvLength);

   _DBG("phFriNfc_OvrHal_Receive");
   return status;
   }

NFCSTATUS phFriNfc_OvrHal_Send(
      void                          *OvrHal,
      phFriNfc_CplRt_t              *CompletionInfo,
      phHal_sRemoteDevInformation_t *RemoteDevInfo,
      uint8_t                       *SendBuf,
      uint16_t                      SendLength)
   {
   NFCSTATUS status = NFCSTATUS_PENDING;

   PHNFC_UNUSED_VARIABLE(OvrHal);
   PHNFC_UNUSED_VARIABLE(CompletionInfo);
   PHNFC_UNUSED_VARIABLE(RemoteDevInfo);
   PHNFC_UNUSED_VARIABLE(SendBuf);
   PHNFC_UNUSED_VARIABLE(SendLength);

   _DBG("phFriNfc_OvrHal_Send");
   return status;
   }
// TODO : This function has to be reworked

NFCSTATUS NFC_SendDEP(
      void *      palI18092mPI,
      uint8_t *   command_buffer,
      uint16_t    command_size,
      uint8_t **  response_buffer,
      uint16_t *  response_buffer_size)
   {
   uint16_t result = 0;

   phStatus_t Status;
#if _DEBUG_
   printf("NFC_SendDEP sending \n");
#endif


   Status = phpalI18092mPI_Exchange(palI18092mPI, PH_EXCHANGE_DEFAULT,
         command_buffer, command_size, response_buffer, response_buffer_size);

#if _DEBUG_
   printf("DEP exchange completed %d \n", Status);
#endif

   if (PH_ERR_SUCCESS == Status)
      {
      if (*response_buffer_size > 2)
         {

#if _DEBUG_
         printf("received a CC pdu \n");
#endif
         }
      }
   else
      {
      /* Exchange not successful, reset the number of rxd bytes */
      *response_buffer_size = 0x00;
      // NOTE: Prabakaran has this expression without star before variable
      }

   /* update result */
   result = *response_buffer_size;

   return result;
   }
