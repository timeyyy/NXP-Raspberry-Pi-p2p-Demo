/*
*         Copyright (c), NXP Semiconductors Gratkorn / Austria
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

/** \file
* Status Code definitions for Reader Library Framework.
* $Author: prabakaran.c $
* $Revision: 1.93.2.4 $
* $Date: Wed Nov 28 16:28:56 2012 $
*
* History:
*  CHu: Generated 19. May 2009
*
*/

#ifndef PH_STATUS_H
#define PH_STATUS_H

#ifndef NXPBUILD_DELETE
#include <ph_NxpBuild.h>
#endif /* NXPBUILD_DELETE */

#include <ph_TypeDefs.h>

#ifdef _WIN32
#pragma warning(push)           /* PRQA S 3116 */
#pragma warning(disable:4001)   /* PRQA S 3116 */
#include <string.h>
#pragma warning(pop)            /* PRQA S 3116 */
#else
#include <string.h>
#endif

#ifdef NXPBUILD__PH_LOG
#include <phLog.h>
#endif

/** \defgroup ph_Error Error Code Collection
* \brief Common Error Codes
* @{
*/

/** \name Success Codes
*/
/*@{*/
#define PH_ERR_SUCCESS                  0x0000U /**< Returned in case of no error. */
#define PH_ERR_SUCCESS_CHAINING         0x0071U /**< Rx chaining is not complete, further action needed. */
#define PH_ERR_SUCCESS_INCOMPLETE_BYTE  0x0072U /**< An incomplete byte was received. */
/*@}*/

/** \name Communication Errors
*/
/*@{*/
#define PH_ERR_IO_TIMEOUT               0x0001U /**< No reply received, e.g. PICC removal. */
#define PH_ERR_INTEGRITY_ERROR          0x0002U /**< Wrong CRC or parity detected. */
#define PH_ERR_COLLISION_ERROR          0x0003U /**< A collision occured. */
#define PH_ERR_BUFFER_OVERFLOW          0x0004U /**< Attempt to write beyond buffer size. */
#define PH_ERR_FRAMING_ERROR            0x0005U /**< Invalid frame format. */
#define PH_ERR_PROTOCOL_ERROR           0x0006U /**< Received response violates protocol. */
#define PH_ERR_AUTH_ERROR               0x0007U /**< Authentication error. */
#define PH_ERR_READ_WRITE_ERROR         0x0008U /**< A Read or Write error occured in RAM/ROM or Flash. */
#define PH_ERR_TEMPERATURE_ERROR        0x0009U /**< The RC sensors signal overheating. */
#define PH_ERR_RF_ERROR                 0x000AU /**< Error on RF-Interface. */
#define PH_ERR_INTERFACE_ERROR          0x000BU /**< An error occured in RC communication. */
#define PH_ERR_LENGTH_ERROR             0x000CU /**< A length error occured. */
#define PH_ERR_INTERNAL_ERROR           0x007FU /**< An internal error occured. */
#define PH_ERR_RESOURCE_ERROR           0x000DU /**< An resource error. */
/*@}*/

/** \name Parameter & Command Errors
*/
/*@{*/
#define PH_ERR_INVALID_DATA_PARAMS      0x0020U /**< Invalid data parameters supplied (layer id check failed). */
#define PH_ERR_INVALID_PARAMETER        0x0021U /**< Invalid parameter supplied. */
#define PH_ERR_PARAMETER_OVERFLOW       0x0022U /**< Reading/Writing a parameter would produce an overflow. */
#define PH_ERR_UNSUPPORTED_PARAMETER    0x0023U /**< Parameter not supported. */
#define PH_ERR_UNSUPPORTED_COMMAND      0x0024U /**< Command not supported. */
#define PH_ERR_USE_CONDITION            0x0025U /**< Condition of use not satisfied. */
#define PH_ERR_KEY                      0x0026U /**< A key error occured. */
/*@}*/

/** @} */

/** \defgroup ph_Status Generic Definitions
* \brief Contains definitions which are generic throughout the library
* @{
*/

/**
* \name Boolean Values
*/
/*@{*/
#define PH_ON                           0x0001U /**< Enabled. */
#define PH_OFF                          0x0000U /**< Disabled. */
#define PH_SUPPORTED                    0x0001U /**< Supported. */
#define PH_UNSUPPORTED                  0x0000U /**< Not Supported. */
/*@}*/

/**
* \name Configuration
*/
/*@{*/
#define PH_CONFIG_CUSTOM_BEGIN          0xE000U /**< Starting number of custom configs. */
/*@}*/

/**
* \name Component identifiers
*/
/*@{*/
#define PH_COMP_MASK                    0xFF00U /**< Component Mask for status code and component ID. */
#define PH_COMPID_MASK                  0x00FFU /**< ID Mask for component ID. */
#define PH_ERR_MASK                     0x00FFU /**< Error Mask for status code. */
#define PH_ERR_CUSTOM_BEGIN             0x0080U /**< Starting number of custom error codes. */
#define PH_COMP_GENERIC                 0x0000U /**< Generic Component Code. */
#define PH_COMP_BAL                     0x0100U /**< BAL Component Code. */
#define PH_COMP_HAL                     0x0200U /**< HAL Component Code. */
#define PH_COMP_PAL_ISO14443P3A         0x0300U /**< ISO14443-3A PAL-Component Code. */
#define PH_COMP_PAL_ISO14443P3B         0x0400U /**< ISO14443-3B PAL-Component Code. */
#define PH_COMP_PAL_ISO14443P4A         0x0500U /**< ISO14443-4A PAL-Component Code. */
#define PH_COMP_PAL_ISO14443P4          0x0600U /**< ISO14443-4 PAL-Component Code. */
#define PH_COMP_PAL_MIFARE              0x0700U /**< MIFARE(R) PAL-Component Code. */
#define PH_COMP_PAL_FELICA              0x0800U /**< Open FeliCa PAL-Component Code. */
#define PH_COMP_PAL_EPCUID              0x0900U /**< ICode EPC/UID PAL-Component Code. */
#define PH_COMP_PAL_SLI15693            0x0A00U /**< ICode SLI/ISO15693 PAL-Component Code. */
#define PH_COMP_PAL_I18000P3M3          0x0B00U /**< ISO18000-3 Mode3 PAL-Component Code. */
#define PH_COMP_PAL_I18092MPI           0x0C00U /**< ISO18092 passive initiator mode PAL-Component Code. */
#define PH_COMP_PAL_I18092MT            0x0D00U /**< ISO18092 target mode PAL-Component Code. */
#define PH_COMP_PAL_I14443P4AC          0x0E00U /**< ISO 144434A Card mode protocol. */
#define PH_COMP_PAL_I14443P4C           0x0F00U /**< ISO 14443-4 Card mode protocol. */
#define PH_COMP_AL_MFC                  0x1000U /**< MIFARE(R) Classic AL-Component Code. */
#define PH_COMP_AL_MFUL                 0x1100U /**< MIFARE(R) Ultralight AL-Component Code. */
#define PH_COMP_AL_MFP                  0x1200U /**< MIFARE(R) Plus AL-Component Code. */
#define PH_COMP_AL_VCA                  0x1300U /**< Virtual Card Architecture AL-Component Code. */
#define PH_COMP_AL_FELICA               0x1400U /**< Open FeliCa AL-Component Code. */
#define PH_COMP_AL_I15693               0x1500U /**< ISO15693 AL-Component Code. */
#define PH_COMP_AL_SLI                  0x1600U /**< ICode SLI AL-Component Code. */
#define PH_COMP_AL_I18000P3M3           0x1800U /**< ISO18000-3 Mode3 AL-Component Code. */
#define PH_COMP_AL_MFDF                 0x1900U /**< MIFARE DESFIRE EV1 AL Component Code. */
#define PH_COMP_AL_MFDFEV2              0x2000U /**< MIFARE DESFIRE EV2 AL Component Code. */
#define PH_COMP_AL_P40CMDPRIV           0x1A00U /**< P40 command libraryAL-Component Code. */
#define PH_COMP_AL_P40CMDPUB			0x1B00U /**< P40 command libraryAL-Component Code. */
#define PH_COMP_DL_AMP					0x3000U /**< Amplifier DL-Component Code. */
#define PH_COMP_DL_THSTRM				0x3100U /**< Thermostream DL-Component Code. */
#define PH_COMP_DL_OSCI					0x3200U /**< Oscilloscope DL-Component Code. */
#define PH_COMP_DL_RDFPGA				0x3300U	/**< Reader FPGA Box DL-Component Code. */
#define PH_COMP_DL_MSTAMPOSC			0x3400U /**< Master Amplifier Oscilloscope DL-Component Code. */
#define PH_COMP_DL_STEPPER				0x3500U /**< Stepper DL-Component Code. */
#define PH_COMP_AC_DISCLOOP             0x4000U /**< Discovery Loop. */
#define PH_COMP_CE_T4T                  0x5000U /**< Card Emulation T4T. */
#define PH_COMP_LN_LLCP                 0x6000U /**< LLCP code. */
#define PH_COMP_NP_SNEP                 0x7000U /**< SNEP Code. */
#define PH_COMP_CIDMANAGER              0xE000U /**< Cid Manager Component Code. */
#define PH_COMP_CRYPTOSYM               0xE100U /**< CryptoSym Component Code. */
#define PH_COMP_KEYSTORE                0xE200U /**< KeyStore Component Code. */
#define PH_COMP_TOOLS                   0xE300U /**< Tools Component Code. */
#define PH_COMP_CRYPTORNG               0xE400U /**< CryptoRng Component Code. */
#define PH_COMP_LOG                     0xEF00U /**< Log Component Code. */
#define PH_COMP_OSAL                    0xF000U /**< OS AL component code */
/*@}*/

/** 
* Macro for error handling of underlaying layer and exit.
*/
#define PH_CHECK_SUCCESS(status)         {if ((status) != PH_ERR_SUCCESS) {return (status);}}
#define PH_CHECK_SUCCESS_FCT(status,fct) {(status) = (fct); PH_CHECK_SUCCESS(status);}

/**
*  Macro for component-error-code adding of current layer.
*/
#define PH_ADD_COMPCODE(stat, code)     ((phStatus_t)(((stat) == PH_ERR_SUCCESS) || ((stat) & PH_COMP_MASK) ? (stat) : (((stat) & PH_ERR_MASK) | ((code) & PH_COMP_MASK))))

/**
*  Macro to get the component code or id using a pointer to a memory.
*/
#define PH_GET_COMPCODE(pId)            ( (*((uint16_t*)(pId))) & PH_COMP_MASK )
#define PH_GET_COMPID(pId)              ( (uint8_t)(*((uint16_t*)(pId))) )

/** \name Exchange Options
*/
/*@{*/
/**
Default exchange mode.
Combine with #PH_EXCHANGE_BUFFERED_BIT and
#PH_EXCHANGE_LEAVE_BUFFER_BIT to perform buffering.
\c ISO14443-4 specific:
Performs Tx/Rx chaining with the card.
Returns #PH_ERR_SUCCESS_CHAINING when RxBuffer is full and
does not ACK the last received block.
*/
#define PH_EXCHANGE_DEFAULT             0x0000U

/**
\c ISO14443-4 specific:
Chains given data to card.
Combine with #PH_EXCHANGE_BUFFERED_BIT and
#PH_EXCHANGE_LEAVE_BUFFER_BIT to perform buffering.
Does not receive any data.
*/
#define PH_EXCHANGE_TXCHAINING          0x0001U

/**
\c ISO14443-4 specific:
Starts transmission with and R(ACK) block and
performs Rx chaining with the card.
Returns #PH_ERR_SUCCESS_CHAINING when RxBuffer is full and
does not ACK the last received block.
*/
#define PH_EXCHANGE_RXCHAINING          0x0002U

/**
\c ISO14443-4 specific:
Starts transmission with and R(ACK) block and
performs Rx chaining with the card.
Completes Rx chaining with the card if RxBuffer is full.
*/
#define PH_EXCHANGE_RXCHAINING_BUFSIZE  0x0003U

/** Mask for the above modes. All other bits are reserved. */
#define PH_EXCHANGE_MODE_MASK           0x000FU

/** Mask for custom exchange bits. These 4 bits can be used for custom exchange behaviour. */
#define PH_EXCHANGE_CUSTOM_BITS_MASK    0x00F0U

/**
Does not clear the internal buffer before operation.
If this bit is set and data is transmitted,
the contents of the internal buffer are sent first.
*/
#define PH_EXCHANGE_LEAVE_BUFFER_BIT    0x4000U

/**
Buffers Tx-Data into internal buffer
instead of transmitting it.
*/
#define PH_EXCHANGE_BUFFERED_BIT        0x8000U

/**
The given data is the first part of a stream.
(Helper definition for buffering).
*/
#define PH_EXCHANGE_BUFFER_FIRST   (PH_EXCHANGE_DEFAULT | PH_EXCHANGE_BUFFERED_BIT)

/**
The given data is a subsequent part of a stream.
(Helper definition for buffering).
*/
#define PH_EXCHANGE_BUFFER_CONT    (PH_EXCHANGE_DEFAULT | PH_EXCHANGE_BUFFERED_BIT | PH_EXCHANGE_LEAVE_BUFFER_BIT)

/**
The given data is the last part of a stream.
(Helper definition for buffering).
*/
#define PH_EXCHANGE_BUFFER_LAST    (PH_EXCHANGE_DEFAULT | PH_EXCHANGE_LEAVE_BUFFER_BIT)
/*@}*/

/** \name Log Interface
*/
/*@{*/
#ifdef NXPBUILD__PH_LOG

#define PH_LOG_HELPER_ALLOCATE_PARAMNAME(pParam) PH_LOG_ALLOCATE_PARAMNAME(pParam)
#define PH_LOG_HELPER_ALLOCATE_TEXT(pIdent, pText) PH_LOG_ALLOCATE_TEXT(pIdent, pText)
#define PH_LOG_HELPER_ADDSTRING(bLogType,pString) phLog_AddString(pDataParams, (bLogType), (pString))
#define PH_LOG_HELPER_ADDPARAM_UINT8(bLogType,pName,pParam) phLog_AddParam_Uint8(pDataParams, (bLogType), (pName), (pParam))
#define PH_LOG_HELPER_ADDPARAM_UINT16(bLogType,pName,pParam) phLog_AddParam_Uint16(pDataParams, (bLogType), (pName), (pParam))
#define PH_LOG_HELPER_ADDPARAM_UINT32(bLogType,pName,pParam) phLog_AddParam_Uint32(pDataParams, (bLogType), (pName), (pParam))
#define PH_LOG_HELPER_ADDPARAM_BUFFER(bLogType,pName,pParam,wLength) phLog_AddParam_Buffer(pDataParams, (bLogType),(pName),(pParam),(wLength))
#define PH_LOG_HELPER_EXECUTE(bOption) phLog_Execute(pDataParams, (bOption))

#else

#define PH_LOG_HELPER_ALLOCATE_PARAMNAME(pParam)
#define PH_LOG_HELPER_ALLOCATE_TEXT(pIdent, pText)
#define PH_LOG_HELPER_ADDSTRING(bLogType,pString)
#define PH_LOG_HELPER_ADDPARAM_UINT8(bLogType,pName,pParam)
#define PH_LOG_HELPER_ADDPARAM_UINT16(bLogType,pName,pParam)
#define PH_LOG_HELPER_ADDPARAM_UINT32(bLogType,pName,pParam)
#define PH_LOG_HELPER_ADDPARAM_BUFFER(bLogType,pName,pParam,wLength)
#define PH_LOG_HELPER_EXECUTE(bOption)

#endif
/*@}*/

/** @}
* end of ph_Status group
*/

/** \name Debug Definitions
*/
/*@{*/
#ifdef NXPBUILD__PH_DEBUG
#define PH_ASSERT_NULL(a) while((a) == NULL);
#else
#define PH_ASSERT_NULL(a)
#endif
/*@}*/
#ifdef NXPBUILD__PHLN_LLCP_FRI
#define CID_FRI_NFC_LLCP                0x61    /**< \ingroup grp_comp_id LLCP Core. */
#define CID_FRI_NFC_LLCP_MAC            0x62    /**< \ingroup grp_comp_id LLCP Mac Mappings. */
#define CID_FRI_NFC_LLCP_TRANSPORT      0x63    /**< \ingroup grp_comp_id LLCP Transport. */
#define CID_FRI_NFC_OVR_HAL             0x64    /**< \ingroup grp_comp_id NFC-Device, HAL-based. */

/* Internally required by \ref PHNFCSTVAL. */
#define PHNFCSTSHL8                          (8U)
/* Required by \ref PHNFCSTVAL. */
#define PHNFCSTBLOWER                        ((NFCSTATUS)(0x00FFU))

/**
 *  \name NFC Status Composition Macro
 *
 *  This is the macro which must be used to compose status values.
 *
 *  \param[in] phNfcCompID Component ID, as defined in \ref phNfcCompId.h .
 *  \param[in] phNfcStatus Status values, as defined in \ref phNfcStatus.h .
 *
 *  \note The macro is not required for the \ref NFCSTATUS_SUCCESS value. This is the only
 *        return value to be used directly.
 *        For all other values it shall be used in assigment and conditional statements e.g.:
 *        - NFCSTATUS status = PHNFCSTVAL(phNfcCompID, phNfcStatus); ...
 *        - if (status == PHNFCSTVAL(phNfcCompID, phNfcStatus)) ...
 *
 */
#define PHNFCSTVAL(phNfcCompID, phNfcStatus)                                \
            ( ((phNfcStatus) == (NFCSTATUS_SUCCESS)) ? (NFCSTATUS_SUCCESS) :  \
                ( (((NFCSTATUS)(phNfcStatus)) & (PHNFCSTBLOWER)) |          \
                    (((uint16_t)(phNfcCompID)) << (PHNFCSTSHL8)) ) )     /**< \ingroup grp_retval
                                                                              Use this macro for return value composition. */
#define PHNFCSTATUS(phNfcStatus)  ((phNfcStatus) & 0x00FFU)
#define PHNFCCID(phNfcStatus)  (((phNfcStatus) & 0xFF00U)>>8)

/**
 *  \name Status Codes
 *
 *  Generic Status codes for the NFC components. Combined with the Component ID
 *  they build the value (status) returned by each
 *  function. Some Specific E.g.:\n
 *  <UL>
 *      <LI> \ref grp_comp_id "Component ID" -  e.g. 0x10, plus                 </LI>
 *      <LI> status code as listed in this file - e.g. 0x03                     </LI>
 *  </UL>
 *  result in a status value of 0x0003.
 *
 *  \note The \ref grp_comp_id "Component ID" used for return codes
     must not be \ref CID_NFC_NONE
 *        except for the value \ref NFCSTATUS_SUCCESS.
 */
/*@{*/

/** \ingroup grp_retval
    The function indicates successful completion. */
#define NFCSTATUS_SUCCESS                                       (0x0000)

/** \ingroup grp_retval
    At least one paramter could not be properly interpreted. */
#define NFCSTATUS_INVALID_PARAMETER                             (0x0001)

/** \ingroup grp_retval
    The buffer provided by the caller is too small. */
#define NFCSTATUS_BUFFER_TOO_SMALL                              (0x0003)

/** \ingroup grp_retval
    Device specifier/handle value is invalid for the operation. */
#define NFCSTATUS_INVALID_DEVICE                                (0x0006)

/** \ingroup grp_retval
    The function executed successfully but could have returned
    more information than space provided by the caller. */
#define NFCSTATUS_MORE_INFORMATION                              (0x0008)

/** \ingroup grp_retval
    No response from the remote device received: Time-out.*/
#define NFCSTATUS_RF_TIMEOUT                                    (0x0009)

/** \ingroup grp_retval
    RF Error during data transaction with the remote device.*/
#define NFCSTATUS_RF_ERROR                                      (0x000A)

/** \ingroup grp_retval
    Not enough resources (e.g. allocation failed.). */
#define NFCSTATUS_INSUFFICIENT_RESOURCES                        (0x000C)

/** \ingroup grp_retval
    A non-blocking function returns this immediately to indicate
    that an internal operation is in progress. */
#define NFCSTATUS_PENDING                                       (0x000D)

/** \ingroup grp_retval
    A board communication error occurred
    (e.g. configuration went wrong). */
#define NFCSTATUS_BOARD_COMMUNICATION_ERROR                     (0x000F)

/** \ingroup grp_retval
    Invalid State of the particular state machine
 */
#define NFCSTATUS_INVALID_STATE									(0x0011)


/** \ingroup grp_retval
    This Layer is Not initialised, hence initialisation required.
 */
#define NFCSTATUS_NOT_INITIALISED								(0x0031)


/** \ingroup grp_retval
    The Layer is already initialised, hence initialisation repeated.
 */
#define NFCSTATUS_ALREADY_INITIALISED							(0x0032)


/** \ingroup grp_retval
    Feature not supported . */
#define NFCSTATUS_FEATURE_NOT_SUPPORTED                         (0x0033)

/** \ingroup grp_retval
    The Unregistration command has failed because the user wants to unregister on
    an element for which he was not registered*/
#define NFCSTATUS_NOT_REGISTERED								(0x0034)


/** \ingroup grp_retval
    The Registration command has failed because the user wants to register on
    an element for which he is already registered*/
#define NFCSTATUS_ALREADY_REGISTERED							(0x0035)

/** \ingroup grp_retval
    Single Tag with Multiple
	Protocol support detected. */
#define NFCSTATUS_MULTIPLE_PROTOCOLS	 	                    (0x0036)

/** \ingroup grp_retval
    Feature not supported . */
#define NFCSTATUS_MULTIPLE_TAGS	 	                            (0x0037)

/** \ingroup grp_retval
    A DESELECT event has occurred. */
#define NFCSTATUS_DESELECTED                                    (0x0038)

/** \ingroup grp_retval
    A RELEASE event has occurred. */
#define NFCSTATUS_RELEASED                                      (0x0039)

/** \ingroup grp_retval
    The operation is currently not possible or not allowed */
#define NFCSTATUS_NOT_ALLOWED                                   (0x003A)

/** \ingroup grp_retval
     The sytem is busy with the previous operation.    
*/
#define NFCSTATUS_BUSY											(0x006F)


/* NDEF Mapping error codes */

/** \ingroup grp_retval
    The remote device (type) is not valid for this request. */
#define NFCSTATUS_INVALID_REMOTE_DEVICE                         (0x001D)

/** \ingroup grp_retval
    Smart tag functionality not supported */
#define NFCSTATUS_SMART_TAG_FUNC_NOT_SUPPORTED                  (0x0013)

/** \ingroup grp_retval
    Read operation failed */
#define NFCSTATUS_READ_FAILED                                   (0x0014)

/** \ingroup grp_retval
    Write operation failed */
#define NFCSTATUS_WRITE_FAILED                                  (0x0015)

/** \ingroup grp_retval
    Non Ndef Compliant */
#define NFCSTATUS_NO_NDEF_SUPPORT                               (0x0016)

/** \ingroup grp_retval
    Could not proceed further with the write operation: reached card EOF*/
#define NFCSTATUS_EOF_NDEF_CONTAINER_REACHED                    (0x001A)

/** \ingroup grp_retval
    Incorrect number of bytes received from the card*/
#define NFCSTATUS_INVALID_RECEIVE_LENGTH                        (0x001B)

/** \ingroup grp_retval
    The data format/composition is not understood/correct. */
#define NFCSTATUS_INVALID_FORMAT                                (0x001C)


/** \ingroup grp_retval
    There is not sufficient storage available. */
#define NFCSTATUS_INSUFFICIENT_STORAGE                          (0x001F)

/** \ingroup grp_retval
    The Ndef Format procedure has failed. */
#define NFCSTATUS_FORMAT_ERROR                                  (0x0023)

/** \ingroup grp_retval
    Max number of Status Codes*/
#define NFCSTATUS_FAILED										(0x00FF)
/*@}*/
#endif /* NXPBUILD__PHLN_LLCP_FRI */
#endif /* PH_STATUS_H */
