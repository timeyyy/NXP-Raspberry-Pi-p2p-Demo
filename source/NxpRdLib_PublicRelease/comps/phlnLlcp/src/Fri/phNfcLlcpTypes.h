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
 * \file  phNfcLlcpTypes.h
 * \brief NFC LLCP public types
 *
 * Project: NFC-FRI
 *
 */


#ifndef PHNFCLLCPTYPES_H /* */
#define PHNFCLLCPTYPES_H /* */

#include "phNfcTypes.h"
#include "phLibNfcStatus.h"

/*=========== CONSTANTS ===========*/

/**
 *  \name LLCP default parameters.
 *
 *  Definitions for use when wanting to use default LLCP parameter values.
 *
 */
 /*@{*/
#define PHFRINFC_LLCP_MIU_DEFAULT         128  /**< Default MIU value (in bytes).*/
#define PHFRINFC_LLCP_WKS_DEFAULT         1    /**< Default WKS value (bitfield).*/
#define PHFRINFC_LLCP_LTO_DEFAULT         10   /**< Default LTO value (in step of 10ms).*/
#define PHFRINFC_LLCP_RW_DEFAULT          1    /**< Default RW value (in frames).*/
#define PHFRINFC_LLCP_OPTION_DEFAULT      0    /**< Default OPTION value (in frames).*/
#define PHFRINFC_LLCP_MIUX_DEFAULT        0    /**< Default MIUX value (in bytes) */
#define PHFRINFC_LLCP_MIUX_MAX            0x7FF    /**< Max MIUX value (in bytes) */
#define PHFRINFC_LLCP_PDU_HEADER_MAX      3    /**< Max size of PDU header (in bytes) */
#define PHFRINFC_LLCP_SN_MAX_LENGTH       255  /**< Max length value for the Service Name */
#define PHFRINFC_LLCP_RW_MAX              15   /**< Max RW value (in frames).*/
/*@}*/

/**
 *  \name LLCP config parameters.
 *
 *  Definitions used for internal LLCP configuration.
 *
 */
 /*@{*/
#define PHFRINFC_LLCP_NB_SOCKET_MAX          5   /**< Max.number of simultaneous sockets */
#define PHFRINFC_LLCP_SNL_RESPONSE_MAX       256 /**< Max.number of simultaneous discovery requests */
/*@}*/

/**
 * \internal 
 * \name Fixed value for ERROR op code.
 *
 */
/*@{*/
#define PHFRINFC_LLCP_ERR_DISCONNECTED               0x00
#define PHFRINFC_LLCP_ERR_FRAME_REJECTED             0x01
#define PHFRINFC_LLCP_ERR_BUSY_CONDITION             0x02
#define PHFRINFC_LLCP_ERR_NOT_BUSY_CONDITION         0x03

/**
 * \internal 
 * \name Fixed value for DM op code.
 *
 */
/*@{*/
#define PHFRINFC_LLCP_DM_OPCODE_DISCONNECTED               0x00
#define PHFRINFC_LLCP_DM_OPCODE_SAP_NOT_ACTIVE             0x01
#define PHFRINFC_LLCP_DM_OPCODE_SAP_NOT_FOUND              0x02
#define PHFRINFC_LLCP_DM_OPCODE_CONNECT_REJECTED           0x03
#define PHFRINFC_LLCP_DM_OPCODE_CONNECT_NOT_ACCEPTED       0x20
#define PHFRINFC_LLCP_DM_OPCODE_SOCKET_NOT_AVAILABLE       0x21


/*========== ENUMERATES ===========*/

/* Enum reperesents the different LLCP Link status*/
typedef enum phFriNfc_LlcpMac_eLinkStatus
{
   phFriNfc_LlcpMac_eLinkDefault,
   phFriNfc_LlcpMac_eLinkActivated,
   phFriNfc_LlcpMac_eLinkDeactivated
}phFriNfc_LlcpMac_eLinkStatus_t;

/* Enum represents the different Socket types  */
typedef enum phFriNfc_LlcpTransport_eSocketType
{
   phFriNfc_LlcpTransport_eDefaultType,
   phFriNfc_LlcpTransport_eConnectionLess,
   phFriNfc_LlcpTransport_eConnectionOriented
}phFriNfc_LlcpTransport_eSocketType_t;


/*========== STRUCTURES ===========*/

typedef struct phFriNfc_LlcpTransport_sSocketOptions
{
    /** The remote Maximum Information Unit Extension (NOTE: this is MIUX, not MIU !)*/
    uint16_t miu;

   /** The Receive Window size (4 bits)*/
   uint8_t rw;

}phFriNfc_LlcpTransport_sSocketOptions_t;

typedef struct phFriNfc_Llcp_sLinkParameters
{
    /** The remote Maximum Information Unit (NOTE: this is MIU, not MIUX !)*/
    uint16_t   miu;

    /** The remote Well-Known Services*/
    uint16_t   wks;

    /** The remote Link TimeOut (in 1/100s)*/
    uint8_t    lto;

    /** The remote options*/
    uint8_t    option;

} phFriNfc_Llcp_sLinkParameters_t, phlnLlcp_sLinkParameters_t;

#endif

/* EOF */
