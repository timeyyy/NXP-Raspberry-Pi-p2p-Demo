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
/*
 * Copyright (c) 2009 Trusted Logic S.A.
 * All Rights Reserved.
 *
 * This software is the confidential and proprietary information of
 * Trusted Logic S.A. ("Confidential Information"). You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered
 * into with Trusted Logic S.A.
 *
 * TRUSTED LOGIC S.A. MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE
 * SUITABILITY OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT. TRUSTED LOGIC S.A. SHALL
 * NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

/**
 * \file  phFriNfc_OvrHal.h
 * \brief Overlapped HAL
 *
 * Project: NFC-FRI
 * Creator: Gerald Kersch
 *
 * $Date: Mon Dec  3 09:40:02 2012 $
 * Changed by: $Author: prabakaran.c $
 * $Revision: 1.5 $
 * $Aliases:  $
 *
 */

#ifndef PHFRINFC_OVRHAL_H
#define PHFRINFC_OVRHAL_H

#include "phFriNfc.h"
#include "phNfcHalTypes.h"
#include <ph_Status.h>

/**
 *  \name Overlapped HAL
 *
 * File: \ref phFriNfc_OvrHal.h
 *
 */
/*@{*/
#define PH_FRINFC_OVRHAL_FILEREVISION "$Revision: 1.5 $" /** \ingroup grp_file_attributes */
#define PH_FRINFC_OVRHAL_FILEALIASES  "$Aliases:  $"      /** \ingroup grp_file_attributes */
/*@}*/


/** \defgroup grp_fri_nfc_ovr_hal Overlapped HAL
 *
 *  This component encapsulates the HAL functions, suited for the NFC-FRI overlapped way of operation. The HAL itself
 *  is used as it is, wrapped by this component. The purpose of the wrapper is to de-couple a blocking I/O, as used by
 *  the HAL, from the overlapped I/O operation mode the FRI is using.
 *
 *  \par Device Based Functions
 *  NFC Device Based Functions are used to address the NFC device (local device) directly.
 *  These are all functions that use no Remote Device Information.
 *
 *  \par Connection Based Functions
 *  Connection Based Functions use the Remote Device Information to describe a connection
 *  to a certain Remote Device.
 *
 *  \par Component Instance Sharing
 *  FRI components accessing one NFC device share one instance of the Overlapped HAL. Therefore
 *  each calling FRI component must specify - together with the call - where to deliver the
 *  response of the overlapped operation.
 *
 *  \par Lowest Layer
 *  The Overlapped HAL represents the NFC Device, the lowest layer of the FRI components.
 *
 *  \par Completion Forced
 *  The \b HAL \b functions (and underlying functions) of this library must complete before a new call can
 *  be issued. No HAL operation must be pending.
 *
 */
/*@{*/

/**
 *  \name OVR HAL Constants
 */
/*@{*/
#define PH_FRINFC_OVRHAL_MAX_NUM_MOCKUP_PARAM           255    /**< Number of mockup indices that are are prepared. */
/* Harsha: changed from 48 to 128, to work with the Mifare 4k TCs */
#define PH_FRINFC_OVRHAL_MAX_NUM_MOCKUP_RDI             4     /**< Max. number of mockup RDIs. */
#define PH_FRINFC_OVRHAL_MAX_TEST_DELAY                 1000  /**< Max. test delay in OVR HAL. */
#define PH_FRINFC_OVRHAL_POLL_PAYLOAD_LEN               5     /**< Length of the POLL payload. */ /* @GK/5.6.06 */
/*@}*/
/*@}*/ /* defgroup... */

/** \defgroup grp_ovr_hal_cmd Overlapped HAL Command List
 *  \ingroup grp_fri_nfc_ovr_hal
 *  These are the command definitions for the Overlapped HAL. They are used internally by the
 *  implementation of the component.
 */
/*@{*/
#define PH_FRINFC_OVRHAL_NUL             (0)     /**< \brief We're in NO command */

#define PH_FRINFC_OVRHAL_ENU             (1)     /**< \brief Enumerate */
#define PH_FRINFC_OVRHAL_OPE             (2)     /**< \brief Open */
#define PH_FRINFC_OVRHAL_CLO             (3)     /**< \brief Close */
#define PH_FRINFC_OVRHAL_GDC             (4)     /**< \brief Get Dev Caps */
#define PH_FRINFC_OVRHAL_POL             (5)     /**< \brief Poll */
#define PH_FRINFC_OVRHAL_CON             (6)     /**< \brief Connect */
#define PH_FRINFC_OVRHAL_DIS             (7)     /**< \brief Disconnect */
#define PH_FRINFC_OVRHAL_TRX             (8)     /**< \brief Transceive */
#define PH_FRINFC_OVRHAL_STM             (9)     /**< \brief Start Target Mode */
#define PH_FRINFC_OVRHAL_SND             (10)     /**< \brief Send */
#define PH_FRINFC_OVRHAL_RCV             (11)    /**< \brief Receive */
#define PH_FRINFC_OVRHAL_IOC             (12)    /**< \brief IOCTL */

#define PH_FRINFC_OVRHAL_TST             (255)   /**< \brief OVR HAL test-related command */

/** \ingroup grp_fri_nfc_ovr_hal
 *  \brief Post Message Function for Overlapped HAL
 *
 *  \copydoc page_reg
 *
 * This is required by the Overlapped HAL in order to call the blocking (original HAL) in another
 * thread. This function is required in addition to \ref pphFriNfc_OvrHalPresetParm to be
 * implemented in the integrating software.
 *
 * \par First Parameter: Context of the Integration
 *      Set to the value, the Integration has provided when initialising this component.
 */
typedef void (*pphFriNfc_OvrHalPostMsg_t)(void*);

/** \ingroup grp_fri_nfc_ovr_hal
 *  \brief Abort Function (to be defined/implemented by the Integration)
 *
 *  \copydoc page_reg
 *
 * This is required by the Overlapped HAL in order abort a pending Overlapped HAL operation. This funtion will be
 * internally called by the \ref phFriNfc_OvrHal_Abort function.
 *
 * \par First Parameter: Context of the Integration
 *      Set to the value, the Integration has provided when initialising this component.
 *
 * \par Return value:
 *      As defined by the integration
 */
typedef NFCSTATUS (*pphFriNfc_OvrHalAbort_t)(void*);


typedef void (*pphOvrHal_CB_t) (phHal_sRemoteDevInformation_t *RemoteDevHandle,
                                NFCSTATUS status,
                                phNfc_sData_t  *pRecvdata,
                                void *context);

/** \ingroup grp_fri_nfc_ovr_hal
 *  \brief Preset Function to prepare the parameters in the HAL
 *
 *  \copydoc page_reg
 *
 * This function (pointer) is called by the Overlapped HAL to prepare the function call parameters
 * in the HAL before posting the start message. As we have an asynchronously running FRI, but a
 * synchronous HAL, the calls need to be "decoupled". This means, the HAL needs to run under
 * a different time-base (or thread/task etc.). The consequence is that the data exchange between
 * FRI and HAL must be done as required by the integration/system itself. The declaration
 * of the function pointer allows for the integrating software to implement whatever functionality
 * is required to convey the data.
 *
 *
 * \par First Parameter
 *      Context of the Integration Set to the value, the Integration has provided when initialising
 *      this component.
 *
 * \par Second Parameter:
 *      \b HAL \b Command, as defined in the module \ref grp_ovr_hal_cmd.
 *
 * \par Third Parameter:
 *      \b Pointers to a specific structure containing the parameters of the HAL functions to be
 *      called.
 *
 * \par Forth parameter:
 *      Immediate Operation result (not the result of the HAL operation). Usually this is
 *      \ref NFCSTATUS_PENDING (for a successfully triggered HAL I/O or an error value that is
 *      returned by the HAL immediately, such as \ref NFCSTATUS_INVALID_PARAMETER.
 *
 * \par Return value:
 *      A boolean (\ref grp_special_conventions) value. The integration implementation must ensure
 *      that, if the function \b succeeds, the return value is \b TRUE, otherwise false.
 */
typedef uint8_t (*pphFriNfc_OvrHalPresetParm)(void*, uint16_t, void*, NFCSTATUS*);

void phFriNfc_OvrHal_Init(void);
void phFriNfc_OvrHal_DeInit(void);

/**
 * \ingroup grp_fri_nfc_ovr_hal
 *
 * \brief Transceive Data to/from a Remote Device
 *
 * \copydoc page_ovr
 *
 * \param[in]      OvrHal               Component Context.
 * \param[in]      CompletionInfo       \copydoc phFriNfc_OvrHal_t::TemporaryCompletionInfo
 * \param[in,out]  RemoteDevInfo        Remote Device Information.
 * \param[in]      Cmd                  Command to perform.
 * \param[out]     DepAdditionalInfo    Protocol Information.
 * \param[in]      SendBuf              Pointer to the data to send.
 * \param[in]      SendLength           Length, in bytes, of the Send Buffer.
 * \param[out]     RecvBuf              Pointer to the buffer that receives the data.
 * \param[in,out]  RecvLength           Length, in bytes, of the received data.
 *
 * \retval NFCSTATUS_PENDING                The operation is pending.
 * \retval NFCSTATUS_INVALID_DEVICE_REQUEST \copydoc phFriNfc_OvrHal_t::Operation
 * \retval NFCSTATUS_SUCCESS                Success.
 * \retval NFCSTATUS_INVALID_PARAMETER      One or more of the supplied parameters could not be
 *                                          properly interpreted.
 * \retval NFCSTATUS_INVALID_DEVICE         The device has not been opened or has been disconnected
 *                                          meanwhile.
 * \retval NFCSTATUS_CMD_ABORTED            The caller/driver has aborted the request.
 * \retval NFCSTATUS_BUFFER_TOO_SMALL       The buffer provided by the caller is too small.
 * \retval NFCSTATUS_RF_TIMEOUT             No data has been received within the TIMEOUT period.
 *
 * \note Please refer to HAL Transceive for a detailed description of the
 *       underlying function and the propagated parameters.
 *
 */

NFCSTATUS phFriNfc_OvrHal_Transceive(void                           *OvrHal,
                                     phFriNfc_CplRt_t               *CompletionInfo,
                                     phHal_sRemoteDevInformation_t  *RemoteDevInfo,
                                     phHal_uCmdList_t                Cmd,
                                     phHal_sDepAdditionalInfo_t     *DepAdditionalInfo,
                                     uint8_t                        *SendBuf,
                                     uint16_t                        SendLength,
                                     uint8_t                        *RecvBuf,
                                     uint16_t                       *RecvLength);

/**
 * \ingroup grp_fri_nfc_ovr_hal
 *
 * \brief TODO
 *
 */
NFCSTATUS phFriNfc_OvrHal_Receive(void                              *OvrHal,
                                  phFriNfc_CplRt_t                  *CompletionInfo,
                                  phHal_sRemoteDevInformation_t     *RemoteDevInfo,
                                  uint8_t                           *RecvBuf,
                                  uint16_t                          *RecvLength);

/**
 * \ingroup grp_fri_nfc_ovr_hal
 *
 * \brief TODO
 *
 */
NFCSTATUS phFriNfc_OvrHal_Send(void                             *OvrHal,
                               phFriNfc_CplRt_t                 *CompletionInfo,
                               phHal_sRemoteDevInformation_t    *RemoteDevInfo,
                               uint8_t                          *SendBuf,
                               uint16_t                         SendLength);


NFCSTATUS NFC_SendDEP(void *palI18092mPI,
					 uint8_t *command_buffer, 
					 uint16_t command_size, 
					 uint8_t **response_buffer, 
					 uint16_t * response_buffer_size);

#endif /* PHFRINFC_OVRHAL_H */
