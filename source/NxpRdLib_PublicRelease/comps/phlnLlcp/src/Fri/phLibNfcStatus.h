/*
 *         Copyright (c), NXP Semiconductors
 *
 *                       (C)NXP Electronics N.V.2004
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

/**
 * \file  phLibNfcStatus.h
 * \brief NFC Status Values - Function Return Codes
 *
 * Project: NFC MW / HAL
 *
 * $Date: Wed Nov 28 16:37:26 2012 $
 * $Author: prabakaran.c $
 * $Revision: 1.2 $
 * $Aliases:  $
 *
 */
#ifndef PHLIBNFCSTATUS_H
#define PHLIBNFCSTATUS_H

#include <ph_Status.h>

#define LIB_NFC_VERSION_SET(v,major,minor,patch,build) ((v) = \
                           ( ((major) << 24) & 0xFF000000 ) | \
                           ( ((minor) << 16) & 0x00FF0000 ) | \
                           ( ((patch) << 8) & 0x0000FF00 ) | \
                           ( (build) & 0x000000FF ) )

#define NFCSTATUS_SHUTDOWN                  (0x0091)
#define NFCSTATUS_TARGET_LOST               (0x0092)
#define NFCSTATUS_REJECTED                  (0x0093)
#define NFCSTATUS_TARGET_NOT_CONNECTED      (0x0094) 
#define NFCSTATUS_INVALID_HANDLE            (0x0095)
#define NFCSTATUS_ABORTED                   (0x0096)
#define NFCSTATUS_COMMAND_NOT_SUPPORTED     (0x0097)
#define NFCSTATUS_NON_NDEF_COMPLIANT        (0x0098)
#define NFCSTATUS_OK                        (0x0000)

#ifndef NFCSTATUS_NOT_ENOUGH_MEMORY
#define NFCSTATUS_NOT_ENOUGH_MEMORY         (0x001F)
#endif

#endif /* PHNFCSTATUS_H */



