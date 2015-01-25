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
 * \file  phFriNfc_LlcpMacNfcip.h
 * \brief NFC LLCP MAC Mapping for NFCIP.
 *
 * Project: NFC-FRI
 *
 */

#ifndef PHFRINFC_LLCPMACNFCIP_H
#define PHFRINFC_LLCPMACNFCIP_H


/*include files*/
#include "phNfcTypes.h"
#include "phNfcLlcpTypes.h"
#include <ph_Status.h>
#include "phFriNfc.h"
 
/** 
 * \name MAC Mapping for NFCIP
 *
 * File: \ref phFriNfc_LlcpMacNfcip.h
 *
 */


/** \defgroup grp_fri_nfc_llcp_macnfcip NFCIP MAC Mapping
 *
 *  TODO
 *
 */
NFCSTATUS phFriNfc_LlcpMac_Nfcip_Register (phFriNfc_LlcpMac_t *LlcpMac);

#endif /* PHFRINFC_LLCPMACNFCIP_H */
