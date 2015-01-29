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
* Build System Definitions for Reader Library Framework.
* $Author: prabakaran.c $
* $Revision: 1.78.2.9 $
* $Date: Mon Dec  3 09:52:26 2012 $
*
* History:
*  MK: Generated 15. October 2009
*
*/

#ifndef PH_NXPBUILD_H
#define PH_NXPBUILD_H

/** \defgroup ph_NxpBuild NXP Build
* \brief Controls build behaviour of components.
* @{
*/

/* NXPBUILD_DELETE: included code lines should be always removed from code */

/* NXP Build defines                            */
/* use #define to include components            */
/* comment out #define to exclude components    */

/* DEBUG build mode */


/* BAL components */

#define NXPBUILD__PHBAL_REG_STUB                /**< Stub BAL definition */
#define NXPBUILD__PHBAL_REG_R_PI_SPI            /**< Raspberry Pi BAL definition */
//#define NXPBUILD__PHBAL_REG_SERIALWIN           /**< SerialWin BAL definition */
//#define NXPBUILD__PHBAL_REG_PCSCWIN             /**< PcscWin BAL definition */
//#define NXPBUILD__PHBAL_REG_RD70XUSBWIN         /**< Rd70X_UsbWin BAL definition */

#if defined (NXPBUILD__PHBAL_REG_STUB)          || \
    defined (NXPBUILD__PHBAL_REG_SERIALWIN)     || \
    defined (NXPBUILD__PHBAL_REG_PCSCWIN)       || \
    defined (NXPBUILD__PHBAL_REG_RD70XUSBWIN)
    #define NXPBUILD__PHBAL_REG                 /**< Generic BAL definition */
#endif

/* HAL components */

#define NXPBUILD__PHHAL_HW_RC523                /**< Rc523 HAL definition */
//#define NXPBUILD__PHHAL_HW_RD70X                /**< Rd70X HAL definition */
//#define NXPBUILD__PHHAL_HW_RC632                /**< Rc632 HAL definition */
//#define NXPBUILD__PHHAL_HW_CALLBACK             /**< Callback HAL definition */
//#define NXPBUILD__PHHAL_HW_RC663                /**< Rc663 HAL definition */
//#define NXPBUILD__PHHAL_HW_RD710                /**< Rd710 HAL definition */

#if defined (NXPBUILD__PHHAL_HW_RC523)        || \
    defined (NXPBUILD__PHHAL_HW_RD70X)        || \
    defined (NXPBUILD__PHHAL_HW_CALLBACK)     || \
    defined (NXPBUILD__PHHAL_HW_RC663)        || \
    defined (NXPBUILD__PHHAL_HW_RC632)        || \
    defined (NXPBUILD__PHHAL_HW_RD710)
    #define NXPBUILD__PHHAL_HW                  /**< Generic HAL definition */
#endif

/* PAL ISO 14443-3A components */

#define NXPBUILD__PHPAL_I14443P3A_SW            /**< Software PAL ISO 14443-3A definition */
//#define NXPBUILD__PHPAL_I14443P3A_RD70X         /**< Rd70X PAL ISO 14443-3A definition */
//#define NXPBUILD__PHPAL_I14443P3A_RD710         /**< Rd710 PAL ISO 14443-3A definition */

#if defined (NXPBUILD__PHPAL_I14443P3A_SW)          || \
    defined (NXPBUILD__PHPAL_I14443P3A_RD70X)       || \
    defined (NXPBUILD__PHPAL_I14443P3A_RD710)
    #define NXPBUILD__PHPAL_I14443P3A           /**< Generic PAL ISO 14443-3A definition */
#endif

/* PAL ISO 14443-3B components */

#define NXPBUILD__PHPAL_I14443P3B_SW            /**< Software PAL ISO 14443-3B definition */

#if defined (NXPBUILD__PHPAL_I14443P3B_SW)
    #define NXPBUILD__PHPAL_I14443P3B           /**< Generic PAL ISO 14443-3B definition */
#endif

/* PAL ISO 14443-4A components */

#define NXPBUILD__PHPAL_I14443P4A_SW            /**< Software PAL ISO 14443-4A definition */
//#define NXPBUILD__PHPAL_I14443P4A_RD710         /**< Rd710 PAL ISO 14443-4A definition */
        
#if defined (NXPBUILD__PHPAL_I14443P4A_SW)       || \
    defined (NXPBUILD__PHPAL_I14443P4A_RD710)
    #define NXPBUILD__PHPAL_I14443P4A           /**< Generic PAL ISO 14443-4A definition */
#endif

/* PAL ISO 14443-4 components */

#define NXPBUILD__PHPAL_I14443P4_SW             /**< Software PAL ISO 14443-4 definition */
//#define NXPBUILD__PHPAL_I14443P4_RD710          /**< Rd710 PAL ISO 14443-4 definition */

#if defined (NXPBUILD__PHPAL_I14443P4_SW)       || \
    defined (NXPBUILD__PHPAL_I14443P4_RD710)
    #define NXPBUILD__PHPAL_I14443P4            /**< Generic PAL ISO 14443-4 definition */
#endif

/* PAL MIFARE components */

//#define NXPBUILD__PHPAL_MIFARE_STUB             /**< Stub PAL MIFARE */
#define NXPBUILD__PHPAL_MIFARE_SW               /**< Software PAL MIFARE */
//#define NXPBUILD__PHPAL_MIFARE_RD710            /**< Rd710 PAL MIFARE */

#if defined (NXPBUILD__PHPAL_MIFARE_STUB)       || \
    defined (NXPBUILD__PHPAL_MIFARE_SW)         || \
    defined (NXPBUILD__PHPAL_MIFARE_RD710)
    #define NXPBUILD__PHPAL_MIFARE              /**< Generic PAL MIFARE definition */
#endif

/* PAL ISO15693 ICode SLI components */

//#define NXPBUILD__PHPAL_SLI15693_SW             /**< Software PAL Sli 15693 */

#if defined (NXPBUILD__PHPAL_SLI15693_SW)
    #define NXPBUILD__PHPAL_SLI15693            /**< Generic PAL Sli 15693 definition */
#endif 
/* PAL Felica components */

#define NXPBUILD__PHPAL_FELICA_SW               /**< Software PAL Felica */

#if defined (NXPBUILD__PHPAL_FELICA_SW)
    #define NXPBUILD__PHPAL_FELICA              /**< Generic PAL Felica definition */
#endif 

/* PAL ICode EPC/UID components */



/* PAL I18000p3m3 components */


/* PAL ISO 18092 components */

#define NXPBUILD__PHPAL_I18092MPI_SW            /**< Software PAL ISO 18092 definition */

#if defined (NXPBUILD__PHPAL_I18092MPI_SW)
    #define NXPBUILD__PHPAL_I18092MPI           /**< Generic PAL ISO 18092 definition */
#endif

/* AC dicover loop component */

#define NXPBUILD__PHAC_DISCLOOP_SW              /**< Discovery loop software componenet */

#if defined (NXPBUILD__PHAC_DISCLOOP_SW)
    #define NXPBUILD__PHAC_DISCLOOP             /**< Generic dicovery loop component */
#endif

#define NXPBUILD__PHAC_DISCLOOP_TYPEA_I3P3_TAGS  /**< Detect type A I3p3 cards */
#define NXPBUILD__PHAC_DISCLOOP_TYPEA_JEWEL_TAGS /**< Detect type A jewel cards */
#define NXPBUILD__PHAC_DISCLOOP_TYPEA_I3P4_TAGS  /**< Detect type A I3p4 cards */
#define NXPBUILD__PHAC_DISCLOOP_TYPEA_P2P_TAGS   /**< Detect type A P2P tags */

#if defined (NXPBUILD__PHAC_DISCLOOP_TYPEA_I3P3_TAGS) || \
    defined (NXPBUILD__PHAC_DISCLOOP_TYPEA_I3P4_TAGS) || \
    defined (NXPBUILD__PHAC_DISCLOOP_TYPEA_JEWEL_TAGS)
    #define NXPBUILD__PHAC_DISCLOOP_TYPEA_TAGS
#endif

#define NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS /**< Detect Type F tags */

#define NXPBUILD__PHAC_DISCLOOP_TYPEF_P2P_TAGS      /**< Detect Type F P2P tags */
#if defined (NXPBUILD__PHAC_DISCLOOP_TYPEF_P2P_TAGS)
   #define NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS
#endif

#define NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P3B_TAGS    /**< Detect TypeB, I3P3B tags */
#define NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P4B_TAGS    /**< Detect TypeB, I3P4B tags */
#define NXPBUILD__PHAC_DISCLOOP_TYPEB_BPRIME_TAGS   /**< Detect TypeB, B Prime tags */

#if defined (NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P3B_TAGS) || \
    defined (NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P4B_TAGS) || \
    defined (NXPBUILD__PHAC_DISCLOOP_TYPEB_BPRIME_TAGS)
    #define NXPBUILD__PHAC_DISCLOOP_TYPEB_TAGS          /**< Detect TypeB Tags */
#endif

/* OSAL components */
#define  NXPBUILD__PH_OSAL_LPC12XX                      /**< Software OSAL for LPC12xx */
#define  NXPBUILD__PH_OSAL_R_Pi                         /**< Software OSAL for Raspberry Pi */

#if defined (NXPBUILD__PH_OSAL_LPC12XX) || \
    defined (NXPBUILD__PH_OSAL_R_Pi)
    #define NXPBUILD__PH_OSAL                           /**< Generic OSAL definition */
#endif

/* AL Felica components */

/* AL MIFARE Classic components */

#define NXPBUILD__PHAL_MFC_SW                   /**< Software MIFARE Classic */

#if defined (NXPBUILD__PHAL_MFC_SW)
    #define NXPBUILD__PHAL_MFC                  /**< Generic AL MIFARE Classic definition */
#endif

/* AL MIFARE Plus components */


#define NXPBUILD__PHAL_MFDF_SW                  /**< Software MIFARE DESFire */

#if defined (NXPBUILD__PHAL_MFDF_SW)
    #define NXPBUILD__PHAL_MFDF                  /**< Generic AL MIFARE Desfire definition */
#endif

/* AL MIFARE Ultralight components */

#define NXPBUILD__PHAL_MFUL_SW                  /**< Software MIFARE Ultralight */

#if defined (NXPBUILD__PHAL_MFUL_SW)
    #define NXPBUILD__PHAL_MFUL                 /**< Generic AL MIFARE Ultralight definition */
#endif

/* AL Virtual Card Architecture components */


/* DL FPGA Box components */


/* DL Amplifier components */


/* DL Thermostream components */


/* DL Oscilloscope components */


/* DL Master Amplifier Oscilloscope components */


/* DL Stepper components */


/* AL I15693 components */


/* AL Sli components */


/* AL ISO 18000P3M3 components */


/* AL P40 PrivateCommands components */

/* AL P40 PublicCommand components */

/* CID Manager components */

#define NXPBUILD__PH_CIDMANAGER_SW              /**< Software CID Manager */
//#define NXPBUILD__PH_CIDMANAGER_RD710           /**< Rd710 CID Manager */

#if defined (NXPBUILD__PH_CIDMANAGER_SW)       || \
    defined (NXPBUILD__PH_CIDMANAGER_RD710)
    #define NXPBUILD__PH_CIDMANAGER             /**< Generic CID Manager definition */
#endif

/* Crypto components */


/* CryptoRng components */


/* KeyStore components */

//#define NXPBUILD__PH_KEYSTORE_SW                /**< Software KeyStore */
//#define NXPBUILD__PH_KEYSTORE_RC632             /**< RC632 KeyStore */
#define NXPBUILD__PH_KEYSTORE_RC663             /**< RC663 KeyStore */
//#define NXPBUILD__PH_KEYSTORE_RD710             /**< Rd710 KeyStore */

#if defined (NXPBUILD__PH_KEYSTORE_SW)      || \
    defined (NXPBUILD__PH_KEYSTORE_RC663)   || \
    defined (NXPBUILD__PH_KEYSTORE_RC632)   || \
    defined (NXPBUILD__PH_KEYSTORE_RD710)
    #define NXPBUILD__PH_KEYSTORE               /**< Generic KeyStore definition */
#endif

/* LN components */

#define NXPBUILD__PHLN_LLCP_FRI                /**< Software Link layer */

#if defined (NXPBUILD__PHLN_LLCP_FRI)
    #define NXPBUILD__PHLN_LLCP               /**< Generic Link layer definition */
#endif

/* Log component */

//#define NXPBUILD__PH_LOG

/** @}
* end of ph_NxpBuild
*/

#endif /* PH_NXPBUILD_H */
