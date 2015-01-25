/*
*         Copyright (c), NXP Semiconductors Bangalore / India
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
* Generic Discovery Loop Activities Component of Reader Library Framework.
* $Author: prabakaran.c $
* $Revision: 1.19 $
* $Date: Mon Dec  3 12:36:03 2012 $
*
* History:
*  PC: Generated 23. Aug 2012
*
*/

#ifndef PHACDICLOOP_H
#define PHACDICLOOP_H

#include <ph_Status.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */ 




/** \defgroup phac Activity layer
*  \brief This component implements the discovery loop functionality 
* @{
*/


/* General utility macros */
#define PHAC_DISCLOOP_CHECK_ANDMASK(value, mask) \
                                               ((value & mask) != 0)             /**< Logically ands value and mask, if the corresponding bit is set, then non zero value is returned else zero is returned */


#define PHAC_DISCLOOP_SET_POLL_MODE                           0x01U              /**< Configures the loop to look/poll for tags */
#define PHAC_DISCLOOP_SET_LISTEN_MODE                         0x02U              /**< Configures the loop to listen for reader activity */
#define PHAC_DISCLOOP_SET_PAUSE_MODE                          0x04U              /**< Enables pause mode in the loop */

#define PHAC_DISCLOOP_POLL_MIN_LOOPTIME                       0x1U               /**< The minimum number of times the polling loop should run */
#define PHAC_DISCLOOP_POLL_MAX_LOOPTIME                       0x20U              /**< The maximum number of times the polling loop is allowed to run */

#define PHAC_DISCLOOP_TYPEA_DEFAULT_DEVICE_LIMIT                03U              /**< The default value loaded for device limit for Type A tags */ 
#define PHAC_DISCLOOP_TYPEA_DEFAULT_POLL_LIMIT                  20U              /**< Default value for polling loop count for Type A tags */
#define PHAC_DISCLOOP_TYPEB_DEFAULT_SLOT_NUM                  0x00U              /**< Default value for slot numbers for Type B tags */
#define PHAC_DISCLOOP_TYPEB_DEFAULT_DEVICE_LIMIT                03U              /**< Default value for maximum number of TypeB tags that can be detected*/
#define PHAC_DISCLOOP_TYPEB_DEFAULT_POLL_LIMIT                  20U              /**< Default value for polling loop count for Type B tags */
#define PHAC_DISCLOOP_TYPEF_DEFAULT_DEVICE_LIMIT                03U              /**< Default value for maximum number of TypeF tags that can be detected*/
#define PHAC_DISCLOOP_TYPEF_DEFAULT_POLL_LIMIT                  20U              /**< Default value for polling loop counter for Type F tags */
#define PHAC_DISCLOOP_TYPEF_DEFAULT_TIME_SLOT                 0x00U              /**< Default value for time slot parameter for detecting Felica tags */

#define PHAC_DISCLOOP_TYPEA_DEFAULT_GT                        5100U              /**< Default guard time for Type A technology in Micro seconds */
#define PHAC_DISCLOOP_TYPEB_DEFAULT_GT                        5100U              /**< Default guard time for Type B technology in Micro seconds */
#define PHAC_DISCLOOP_TYPEF_DEFAULT_GT                       20400U              /**< Default guard time for Type F technology in Micro seconds */
#define PHAC_DISCLOOP_TYPEB_TOF_DEFAULT_GT                   15300U              /**< Default guard time for NFC-F device detection precedded by NFC-B type */ 

#define PHAC_DISCLOOP_DEFAULT_PAUSE_TIME                       500U              /**< Default guard time in milli seconds */

#define PHAC_DISCLOOP_I3P3A_MAX_ATQA_LENGTH                   0x02U              /**< ATQA length for 13P3A card type */
#define PHAC_DISCLOOP_I3P3A_MAX_UID_LENGTH                    0x0AU              /**< Maximum UID length for 14443 Type A compliant tags */
#define PHAC_DISCLOOP_I3P4A_MAX_ATS_LENGTH                     255U              /**< I3P4A ATS maximum length */ 
#define PHAC_DISCLOOP_JEWEL_HR_LENGTH                         0x02U              /**< Jewel tag HR length */
#define PHAC_DISCLOOP_JEWEL_UID_LENGTH                        0x04U              /**< Jewel tag UID length */
#define PHAC_DISCLOOP_I3P3A_MAX_SAK_LENGTH                    0x02U              /**< SAK length */ 

#define PHAC_DISCLOOP_FELICA_IDM_LENGTH                       0x08U              /**< IDM Length for Felica */  
#define PHAC_DISCLOOP_FELICA_PMM_LENGTH                       0x08U              /**< PMm length for felica */


#define PHAC_DISCLOOP_TYPEA_I3P3_NR                           0x03U              /**< Number of type A 13P3 cards */

#define PHAC_DISCLOOP_TYPEF_NR                                0x03U              /**< Number of Type F cards that can be accommodated */


#define PHAC_DISCLOOP_NO_TAGS_FOUND                         0x0000U               /**< Indicates that no card was found */
#define PHAC_DISCLOOP_TYPEA_DETECTED_TAG_TYPE1              0x0001U               /**< Detected Type 1 card */
#define PHAC_DISCLOOP_TYPEA_DETECTED_TAG_TYPE2              0x0002U               /**< Detected Type 2 card */
#define PHAC_DISCLOOP_TYPEA_DETECTED_TAG_TYPE4A             0x0004U               /**< Detected Type 4A card */
#define PHAC_DISCLOOP_TYPEA_DETECTED_TAG_NFC_DEP_TYPE4A     0x0010U               /**< Detected tag type 4A configured for NFC DEP protocol */
#define PHAC_DISCLOOP_TYPEF_DETECTED_TAG_P2P                0x0020U               /**< Detected Type F tag which is p2p capaable */
#define PHAC_DISCLOOP_TYPEA_DETECTED_TAG_P2P                0x0040U               /**< Detected Type A tag which is p2p capaable */
#define PHAC_DISCLOOP_TYPEA_DETECTED                        0x0080U               /**< Mask indicating that Type A tag was detected */
#define PHAC_DISCLOOP_TYPEB_DETECTED                        0x0100U               /**< Mask indicating that Type B tag was detected */
#define PHAC_DISCLOOP_TYPEF_DETECTED                        0x0200U               /**< Mask indicating that Type F tag was detected */

#define PHAC_DISCLOOP_TYPEA_ACTIVATE                          0x00U               /**< Activate Type A tag */
#define PHAC_DISCLOOP_TYPEB_ACTIVATE                          0x01U               /**< Activate Type B tag */



/* Configuration parameters for technology detection */
#define PHAC_DISCLOOP_CON_POLL_A                              0x01U               /**< Single bit flag that indicates whether to poll for Type A tags or not */
#define PHAC_DISCLOOP_CON_POLL_B                              0x02U               /**< Flag indicating whether to poll for type B tags in detection phase */
#define PHAC_DISCLOOP_CON_POLL_F                              0x04U               /**< Indicates polling loop in detect phase whether to look for type cards or not */

/* Configuration for turning off anti collsion */
#define PHAC_DISCLOOP_CON_ANTICOLL_A                          0x01U               /**< When set, will disable Anti collision for Type A tags */
#define PHAC_DISCLOOP_CON_ANTICOLL_B                          0x02U               /**< When set, will disable Anti collision for Type A tags */
 
#define PHAC_DISCLOOP_TYPEA_POLL_LIMIT                          50U               /**< Maximum number of times the polling loop can be run while polling for Type A tags */
#define PHAC_DISCLOOP_TYPEB_POLL_LIMIT                          50U               /**< Maximum number of times the polling loop can be run while polling for Type B tags */
#define PHAC_DISCLOOP_TYPEF_POLL_LIMIT                          50U               /**< Maximum number of times the polling loop can be run while polling for Type F tags */

#define PHAC_DISCLOOP_CON_BITR_212                            0x02U               /**< 212 Kbps bit rate for Type F tags */
#define PHAC_DISCLOOP_CON_BITR_424                            0x03U               /**< 424 Kbps bit rate for Type F tags */

/* Bail out parameters */
#define PHAC_DISCLOOP_CON_BAIL_OUT_A                          0x01U               /**< Bit mask used in case if one wants to bail out after detecting Type A card(s) */
#define PHAC_DISCLOOP_CON_BAIL_OUT_B                          0x02U               /**< Bit mask used in case if one wants to bail out after detecting Type B card(s) */


#define PHAC_DISCLOOP_STATE_UNKNOWN                           0x00U               /**< Indicates generic unknown state */
#define PHAC_DISCLOOP_STATE_IDLE                              0x10U               /**< Indicates that the loop is idle */
#define PHAC_DISCLOOP_STATE_DETECTING                         0x20U               /**< The discovery loop is in detection phase */
#define PHAC_DISCLOOP_STATE_DETECTED                          0x30U               /**< Indicates that the discovery loop has completed detection phase */
#define PHAC_DISCLOOP_STATE_ACTIVATING                        0x40U               /**< Indicates that the loop is in activation phase */
#define PHAC_DISCLOOP_STATE_ACTIVATED                         0x50U               /**< Indicates that the loop has finished activation phase */
#define PHAC_DISCLOOP_STATE_TAG_TYPEA                         0x01U               /**< Bit mask used to indicate that the detection/activation phase is being performed on Type A tags */
#define PHAC_DISCLOOP_STATE_TAG_TYPEB                         0x02U               /**< Bit mask used to indicate that the detection/activation phase is being roomed on Type B tags */
#define PHAC_DISCLOOP_STATE_TAG_TYPEF                         0x03U               /**< Bit mask used to indicate that the detection/activation phase is being primmed on Type F tags */

#define PHAC_DISCLOOP_TYPEA_STATE_READY                       0x04U               /**< Declares that the particular Type A tag is in Raddy state */
#define PHAC_DISCLOOP_TYPEA_STATE_ACTIVATED                   0x05U               /**< Indicates that the Type A tag is activated */
#define PHAC_DISCLOOP_TYPEB_STATE_SLEEP_B                     0x04U               /**< Indicates that the Type B tag is in sleep state */ 

/* Options for get/set configs */
#define PHAC_DISCLOOP_CONFIG_GTA_VALUE_US                     0x00U               /** This option sets the guard time for Type A tech detection */
#define PHAC_DISCLOOP_CONFIG_GTB_VALUE_US                     0x01U               /** This option sets the guard time for Type B tech detection */
#define PHAC_DISCLOOP_CONFIG_GTF_VALUE_US                     0x02U               /** This option sets the guard time for Type F tech detection */
#define PHAC_DISCLOOP_CONFIG_GTA_VALUE_MS                     0x03U               /** This option sets the guard time for Type A tech detection */
#define PHAC_DISCLOOP_CONFIG_GTB_VALUE_MS                     0x04U               /** This option sets the guard time for Type B tech detection */
#define PHAC_DISCLOOP_CONFIG_GTF_VALUE_MS                     0x05U               /** This option sets the guard time for Type F tech detection */
#define PHAC_DISCLOOP_CONFIG_MODE                             0x06U               /**< Sets the polling mode options, the user has to supply the desired mode of operation by performing 'or' operations on the defined constants for enabling poll, listen and pause modes. */
#define PHAC_DISCLOOP_CONFIG_NUM_POLL_LOOPS                   0x07U               /**< Sets number of times the discover loop loops */
#define PHAC_DISCLOOP_CONFIG_TYPEA_POLL_LIMIT                 0x08U               /**< Sets the limit for loop that polls for Type A tags */
#define PHAC_DISCLOOP_CONFIG_TYPEA_DEVICE_LIMIT               0x09U               /**< Sets the number of Type A tags that can be detected */
#define PHAC_DISCLOOP_CONFIG_TYPEB_DEVICE_LIMIT               0x0AU               /**< Sets the number of Type B tags that can be detected */
#define PHAC_DISCLOOP_CONFIG_TYPEF_DEVICE_LIMIT               0x0BU               /**< Sets the number of Type F tags that can be detected */
#define PHAC_DISCLOOP_CONFIG_TYPEB_NCODING_SLOT               0x0CU               /**< Sets the coding slot number for Type B tags */
#define PHAC_DISCLOOP_CONFIG_TYPEB_POLL_LIMIT                 0x0DU               /**< This option sets poll limit for detection of Type B tags */  
#define PHAC_DISCLOOP_CONFIG_TYPEB_AFI_REQ                    0x0EU               /**< This option is to be used to set AFI to be used during reqb, set AFI to zero if it is required that all the cards should respond regardless of AFI */
#define PHAC_DISCLOOP_CONFIG_TYPEB_EXTATQB                    0x0FU               /**< This option enables or disables extended ATQB option */
#define PHAC_DISCLOOP_CONFIG_TYPEB_FSDI                       0x10U               /**< Sets the FSDI for the Type B tags */
#define PHAC_DISCLOOP_CONFIG_TYPEB_CID                        0x11U               /**< Sets the CID for Type B tags */
#define PHAC_DISCLOOP_CONFIG_TYPEB_DRI                        0x12U               /**< Sets the DRI for Type B tags */
#define PHAC_DISCLOOP_CONFIG_TYPEB_DSI                        0x13U               /**< Sets the DSI for Type B tags */
#define PHAC_DISCLOOP_CONFIG_TYPEF_SYSTEM_CODE                0x14U               /**< Sets the system code for the selection of Felica tags */
#define PHAC_DISCLOOP_CONFIG_TYPEF_TIME_SLOT                  0x15U               /**< Sets the time slot for detecting Type F tags */
#define PHAC_DISCLOOP_CONFIG_TYPEF_POLL_LIMIT                 0x16U               /**< Sets/gets the number of times the polling loop loops while looking for Type B tags */
#define PHAC_DISCLOOP_CONFIG_TAGS_DETECTED                    0x17U               /**< Returns the tags that were detected up until the call to get config was made */
#define PHAC_DISCLOOP_CONFIG_GTA_VALUE                        0x18U               /**< When used with get config, returns the unit used for GTA */
#define PHAC_DISCLOOP_CONFIG_GTB_VALUE                        0x19U               /**< When used with get config, returns the unit used for GTB */
#define PHAC_DISCLOOP_CONFIG_GTF_VALUE                        0x1AU               /**< When used with get config, returns the unit used for GTF */
#define PHAC_DISCLOOP_CONFIG_LOOP_STATE                       0x1BU               /**< Returns the state Gd the polling loop */
#define PHAC_DISCLOOP_CONFIG_BAIL_OUT                         0x1CU               /**< Sets/gets the bail out parameter */
#define PHAC_DISCLOOP_CONFIG_TYPEA_NR_TAGS_FOUND              0x1DU               /**< Returns the number of Type A tags found */
#define PHAC_DISCLOOP_CONFIG_TYPEA_NR_TAGS_ACTIVATED          0x1EU               /**< Configuration that returns number of Type A tags that are activated */ 
#define PHAC_DISCLOOP_CONFIG_TYPEB_NR_TAGS_FOUND              0x1FU               /**< Returns the number of Type B tags found */
#define PHAC_DISCLOOP_CONFIG_TYPEB_NR_TAGS_ACTIVATED          0x20U               /**< Configuration that returns number of Type B tags that are activated */ 
#define PHAC_DISCLOOP_CONFIG_TYPEF_NR_TAGS_FOUND              0x21U               /**< Returns the number of Type F tags found */
#define PHAC_DISCLOOP_CONFIG_TYPEF_NR_TAGS_ACTIVATED          0x22U               /**< Configuration that returns number of Type F tags that are activated */ 

/* Type A Layer 4 configs */

#define PHAC_DISCLOOP_CONFIG_TYPEA_I3P4_FSDI                  0x23U               /**< Sets the Fsdi for the 14443-4A communication */
#define PHAC_DISCLOOP_CONFIG_TYPEA_I3P4_CID                   0x24U               /**< Sets the CID for the 14443-4A communication */
#define PHAC_DISCLOOP_CONFIG_TYPEA_I3P4_DRI                   0x25U               /**< Sets the Dri for the 14443-4A communication */
#define PHAC_DISCLOOP_CONFIG_TYPEA_I3P4_DSI                   0x26U               /**< Sets the Dsi for the 14443-4A communication */

/* Type A P2P configs */

#define PHAC_DISCLOOP_CONFIG_TYPEA_P2P_DID                    0x27U               /**< Sets DID for Type A P2P tags */
#define PHAC_DISCLOOP_CONFIG_TYPEA_P2P_LRI                    0x28U               /**< Sets LRi for Type A P2P tags */ 
#define PHAC_DISCLOOP_CONFIG_TYPEA_P2P_NAD_ENABLE             0x29U               /**< Enables NAD if wValue = 1 else disables NAD */
#define PHAC_DISCLOOP_CONFIG_TYPEA_P2P_NAD                    0x2AU               /**< Sets the NAD */
#define PHAC_DISCLOOP_CONFIG_TYPEA_P2P_GI_LEN                 0x2BU               /**< Sets the length of the general bytes */
#define PHAC_DISCLOOP_CONFIG_TYPEA_P2P_ATR_RES_LEN            0x2CU               /**< Returns the Attribute response length */


/* Type F P2P configs */

#define PHAC_DISCLOOP_CONFIG_TYPEF_P2P_DID                    0x2DU               /**< Sets DID for Type F P2P tags */
#define PHAC_DISCLOOP_CONFIG_TYPEF_P2P_LRI                    0x2EU               /**< Sets LRi for Type F P2P tags */ 
#define PHAC_DISCLOOP_CONFIG_TYPEF_P2P_NAD_ENABLE             0x2FU               /**< Enables NAD if wValue = 1 else disables NAD */
#define PHAC_DISCLOOP_CONFIG_TYPEF_P2P_NAD                    0x30U               /**< Sets the NAD */
#define PHAC_DISCLOOP_CONFIG_TYPEF_P2P_GI_LEN                 0x31U               /**< Sets the length of the general bytes */
#define PHAC_DISCLOOP_CONFIG_TYPEF_P2P_ATR_RES_LEN            0x32U               /**< Returns the Attribute response length */

/* Pause mode configs */
#define PHAC_DISCLOOP_CONFIG_PAUSE_PERIOD                     0x33U               /**< Configures the period for pause mode */
#define PHAC_DISCLOOP_CONFIG_PAUSE_PERIOD_MS                  0x34U               /**< Configures the unit for delay on pause mode in Milli seconds */

#define PHAC_DISCLOOP_CONFIG_DETECT_TAGS                      0x36U               /**< Specifies the types of tags to be detected */
#define PHAC_DISCLOOP_CONFIG_STOP                             0x37U               /**< Option used to stop the discovery loop */

#define PHAC_DISCLOOP_CONFIG_GTBF_VALUE_US                    0x38U               /**< Option used to configure GTBF in micorseconds */
#define PHAC_DISCLOOP_CONFIG_GTBF_VALUE_MS                    0x39U               /**< Option used to configure GTBF in Milli seconds */
#define PHAC_DISCLOOP_CONFIG_GTBF_VALUE                       0x40U               /**< Option used to get the GTBF time value */                   
#define PHAC_DISCLOOP_CONFIG_ANTI_COLL                        0x41U               /**< Option to set anti collsion flag */


/* Config for setting the pointer */
#define PHAC_DISCLOOP_CONFIG_SETPTR_I14443PA                  0x01U               /**< Set pointer for PAL I14443A component */
#define PHAC_DISCLOOP_CONFIG_SETPTR_I14443P4A                 0x02U               /**< Set pointer for PAL I14443-4A component */
#define PHAC_DISCLOOP_CONFIG_SETPTR_I14443P3B                 0x03U               /**< Set pointer for PAL I14443-3B component */
#define PHAC_DISCLOOP_CONFIG_SETPTR_FELICA                    0x04U               /**< Set pointer for PAL Felica component */
#define PHAC_DISCLOOP_CONFIG_SETPTR_18092_MPI                 0x05U               /**< Set pointer for PAL 18092 component */

#define PHAC_DISCLOOP_TYPEB_I3P3B_NR                          0x03U               /**< Maximum Type B I13P3B that can be accommodated */
#define PHAC_DISCLOOP_TYPEB_BPRIME_NR                         0x03U               /**< Number of Type B B Prime cards that can be stored in memory at a time */
#define PHAC_DISCLOOP_TYPEB_BPRIME_DIV_LENGTH                 0x04U               /**< Serial number length for BPrime tag (4-byte) */
#define PHAC_DISCLOOP_TYPEB_MAX_HIS_LEN                         15U               /**< Maximum historical bytes length */


/** \name phalDiscLoop Custom Error Codes
*/
/** @{ */

#define PHAC_DISCLOOP_ERR_TYPEA_NO_TAG_FOUND                 (PH_ERR_CUSTOM_BEGIN + 0)   /**< Discover Loop error - No Type A tag found in field */   
#define PHAC_DISCLOOP_ERR_TYPEB_NO_TAG_FOUND                 (PH_ERR_CUSTOM_BEGIN + 1)   /**< Discover Loop error - No Type B tag found in field */
#define PHAC_DISCLOOP_ERR_TYPEF_NO_TAG_FOUND                 (PH_ERR_CUSTOM_BEGIN + 2)   /**< Discover Loop error - No Type F tag found in field */
/** @} */
                                                                                
/**
 * Definition of target for type A card 
 */
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEA_TAGS
typedef struct phacDiscLoop_TypeA_Tags
{
    uint8_t  bTotalTagsFound_A;                                                 /**< Number of type A tags found */ 
    uint8_t  bActivatedTagNumber_A;                                             /**< Number of activated tags */
    uint8_t  bDeviceLimit_A;                                                    /**< Maximum number of Type A tags that can be detected */
    uint8_t  bLoopLimit_A;                                                      /**< Number of times the polling loop loops */     

    
#ifdef  NXPBUILD__PHAC_DISCLOOP_TYPEA_I3P3_TAGS
    struct phacDiscLoop_TypeA_I3P3
    {
        uint8_t aAtqa[PHAC_DISCLOOP_I3P3A_MAX_ATQA_LENGTH];                      /**< ATQA received from IS014443A compliant device */
        uint8_t aUid[PHAC_DISCLOOP_I3P3A_MAX_UID_LENGTH];                        /**< Contains known UID bytes for the given cascade level */
        uint8_t bUidSize;                                                        /**< Size of the UID that was received from the PICC */
        uint8_t aSak[PHAC_DISCLOOP_I3P3A_MAX_SAK_LENGTH];                        /**< Select acknowledge from the IS01443A type A card */
        uint8_t bTagState;                                                       /**< State of this tag */
        
    }aTypeA_I3P3[PHAC_DISCLOOP_TYPEA_I3P3_NR];
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEA_13P3_TAGS */
    
#ifdef  NXPBUILD__PHAC_DISCLOOP_TYPEA_I3P4_TAGS
    struct phascDiscLoop_TypeA_I3P4
    {
        uint8_t bFsdi;                                                          /**< Frame size integer */          
        uint8_t bCid;                                                           /**< Card identifier */
        uint8_t bDri;                                                           /**< Divisor receive */
        uint8_t bDsi;                                                           /**< Divisor send */
        uint8_t aAts[PHAC_DISCLOOP_I3P4A_MAX_ATS_LENGTH];                       /**< Holds the answer to select response */
        uint8_t bTagState;                                                      /**< State of the tag */
    }sTypeA_I3P4;
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEA_13P4_TAGS */
    
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEA_JEWEL_TAGS
    struct phacDiscLoop_Type_Jewel
    {
        uint8_t aAtqa[PHAC_DISCLOOP_I3P3A_MAX_ATQA_LENGTH];                      /**< Atqa returned by Jewel Tags */
        uint8_t abHr[PHAC_DISCLOOP_JEWEL_HR_LENGTH];                             /**< Header Rom mask */
        uint8_t aUid[PHAC_DISCLOOP_JEWEL_UID_LENGTH];                            /**< Contains the UID for the tag */
        uint8_t bTagState;                                                       /**< State of the tag */
    }sType_Jewel;
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEA_JEWEL_TAGS */
 
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEA_P2P_TAGS   
    struct phacDiscLoop_Type_P2P_TAGS
    {
        uint8_t bDid;                                                               /**< Did for 18092 MPI ATR command */
        uint8_t bLri;                                                               /**< Length reduction for initiator */
        uint8_t bNadEnable;                                                         /**< Indicates whether NAD is enabled or not */
        uint8_t bNad;                                                               /**< Node address, ignored if \a bNadEnabled is zero */
        uint8_t *pGi;                                                               /**< General bytes information, the user should populate with appropriate address if \a bGiLength in non zero */
        uint8_t bGiLength;                                                          /**< Length of the general bytes should be zero if general bytes are not used */
        uint8_t *pAtrRes;                                                           /**< Attribute response; uint8_t[64] */
        uint8_t bAtrResLength;                                                      /**< Length of the ATR response */
    }sTypeA_P2P;

#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEA_P2P_TAGS */

} phacDiscLoop_TypeA_Tags_t;
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEA_TAGS */

#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEB_TAGS
typedef struct phacDiscLoop_TypeB_Tags
{
    uint8_t bTotalTagsFound_B;                                                   /**< Number of Type B tags detected  */
    uint8_t bDeviceLimit_B;                                                      /**< Fix the limit of number of tags to be discovered during activation  */
    uint8_t bActivatedTagNumber_B;                                               /**< Number of Type B tags activated */
    uint8_t bNCodingSlotNumber;
    uint8_t bLoopLimit_B;                                                        /**< Limit for number of times polling loop has to run for detecting Type B tags */
    uint8_t bCollPend;                                                           /**< Flag that indicates whether anti-collision is pending or not */
    
    /**< N = [0..4] (Number of slots is 2 exp N to adjust the probability that a PICC answers in an unique slot) */
    /**< Number of used Time Slot i.e. number of slots where we found targets with or without collision */

    uint8_t bAfiReq;
    uint8_t bExtendedAtqBbit;  /**< For coding b5 of PARAM of REQB:  b5=1 extended ATQB supported */
    uint8_t bAdvFeaturesBit;   /**< For coding b6 of PARAM of REQB:  b6=1 advanced features supported (NFC Forum) */
    uint8_t bFsdi;             /**< Frame size integer. Valid values: 0-8 */
    uint8_t bCid;              /**< Card identifier. Valid values 0-14 */
    uint8_t bDri;              /**< Divisor receive (PC to PICC) integer. Valid values: 0-3 */
    uint8_t bDsi;              /**< Divisor send (PICC to PCD) integer. Valid values: 0-3 */
    
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P3B_TAGS
    struct phacDiscLoop_TypeB_I3P3B 
    {
        uint8_t aPupi[4];                               /**< ISO14443-3B PUPI. */
        uint8_t bAtqBLength;                            /**< Length of the ATQB response */
        uint8_t bTagState;                              /**< Holds state of this particular tag */
        struct phacDiscLoop_TypeB_I3P3B_AppData
        {
            uint8_t bAfiAtqB;          /**< Application data 1st byte (AFI). */
            uint8_t aAID[2];           /**< Application data 2nd-3rd byte (AID). */
            uint8_t bNbAppli;          /**< Application data 4th byte (Number of Applications). */
        } sAppData;
        
        struct phacDiscLoop_TypeB_I3P3B_ProtInfo_struct
        {
            uint8_t bDataRateMaxT;     /**< Protocol info 1st byte : bit rate capability of PICC. \n
                                          Bit 0 - 2 ... bit rate capability of the PICC for the direction from PCD to PICC. \n
                                          Bit 3 is 0 RFU. \n
                                          Bit 4 - 6 ... bit rate capability of the PICC for the direction from PICC to PCD. \n
                                          Bit 7 if 1 is same bit rate in both direction. */
            uint8_t bFsciType;         /**< Protocol info 2nd byte \n
                                          Bit 4 - 7 ... Fsci: Max frame size supported by the target. \n
                                          code       0  1  2  3  4  5  6  7   8   9-F \n
                                          frame size 16 24 32 40 48 64 96 128 256 256 \n
                                          Bit 1 - 3 are 0
                                          Bit 0 ... Type: Protocol Type compliance (1 yes / 0 no). */
            uint8_t bFwiFo;            /**< Protocol info 3rd byte \n
                                          Bit 4 - 7 ... FWI: Frame Waiting time Integer. \n
                                          Bit 0 - 1 ... FO: Frame Option supported by the PICC (CID/NAD). */
            uint8_t bSfgi;             /**< Protocol info 4th byte (Extended ATQB: optional byte) \n
                                          Bit 0 - 3 ... Sfgi shifted from (7 - 4) >> 4 on LSB*/
        } sProtInfo;
        
    } aI3P3B[PHAC_DISCLOOP_TYPEB_I3P3B_NR];
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P3B_TAGS */
    
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P4B_TAGS
    struct phacDiscLoop_TypeB_I3P4B_Tag_struct 
    {
        uint8_t bMbli;         /**< MBLI is available on bits [3:0] >*/
        
        uint8_t bParam1;  /**< Param1 for type B Attrib:
                             Bit 2 ... SOF 
                             Bit 3 ... EOF 
                             Bit 4-5 ... Minimum TR1 
                             Bit 6-7 ... Minimum TR0 
                          */
    } sI3P4B;
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEB_I3P4B_TAGS */
    
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEB_BPRIME_TAGS
    struct TypeB_Bprime_Tag_struct 
    {
        uint8_t bTVAd; /**< [Out] Tag & Validator address:
                          This parameter is managed only by the I_BPrime RF module. The Host must not change
                          its value and shall use it in any Raw frames to be sent to a BPrime tag.
                          b7~b4 for Tag Address, may be 1 to 15 and never 0,
                          b3~b0 for Validator address, may be 0 to 15.
                       */
        uint8_t aDIV[PHAC_DISCLOOP_TYPEB_BPRIME_DIV_LENGTH]; /**< [Out] 4 LSBytes of the card's serial number */
        uint8_t bHisLen; /**< [Out] Received historical bytes length, 0 means no historical bytes */
        uint8_t bHisBytes[PHAC_DISCLOOP_TYPEB_MAX_HIS_LEN]; /**< [Out] Received historical bytes picked up from ATR Bytes */
    } aBprime[PHAC_DISCLOOP_TYPEB_BPRIME_NR];
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEB_BPRIME_TAGS */

}phacDiscLoop_TypeB_Tags_t;
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEB_TAGS */
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS
typedef struct phacDiscLoop_TypeF_Tags
   {
    uint8_t   bDeviceLimit_F;          /**< Maximum number of Felica card that can be detected */
    uint8_t   bTotalTagsFound_F;       /**< Holds the number of tags that were detected */
    uint8_t   bActivatedTagNumber_F;   /**< Number of cards that were activated */
    uint8_t   bLoopLimit_F;            /**< Number of times the polling loop loops */
    uint8_t   aSystemCode[2];          /**< System code */
    uint8_t   bTimeSlot;               /**< Maximum time slot */

    struct  phacDiscLoop_TypeF
       {
        uint8_t aIDmPMm[PHAC_DISCLOOP_FELICA_IDM_LENGTH + PHAC_DISCLOOP_FELICA_PMM_LENGTH]; /**< Manufacture ID + PMm */
        uint8_t aRD[2];                                                                     /**< Request Data to be sent by Tag to PCD in case RC is set in polling request. */
       }aTypeF[PHAC_DISCLOOP_TYPEF_NR];

#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEF_P2P_TAGS
    struct phacDiscLoop_TypeF_P2P
       {
        uint8_t bDid;          /**< device identifier. Disabled if set to 0 else should have a value between 1-14 */
        uint8_t bLri;          /**< Length reduction of Initiator. Should be a value in range 0-3 */
        uint8_t bNadEnable;    /**< Enable usage of node address. If set to zero nad is disabled */
        uint8_t bNad;          /**< Nod address */
        uint8_t *pGi;          /**< Optional general bytes */
        uint8_t bGiLength;     /**< Length of the optional bytes */
        uint8_t *pAtrRes;      /**< Pointer to the Attribute response */
        uint8_t bAtrResLength; /**< Attribute response length */
       }sTypeF_P2P;
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEF_P2P_TAGS */
   } phacDiscLoop_TypeF_Tags_t;
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS */



/**
 * Starts the dicovery loop
 */
phStatus_t phacDiscLoop_Start(
    void * pDataParams                                                          /**<[In] Pointer to this layer's parameter structure */ 
    );

/** Typedef for the error handling call back function */
typedef void(*pErrHandlerCallback)(phStatus_t);

/**
 * \brief   Set the configuration value 
 *
 * \return  Error code
 *
 * \retval #PH_ERR_SUCCESS            operation successful
 * \retval #PH_ERR_INVALID_PARAMETER  Invalid option/response received 
 * \retval other                      Other errors depending on underlaying component
 *
 */

phStatus_t phacDiscLoop_SetConfig(
    void * pDataParams,                                                        /**< [In] Pointer to this layer's parameter structure */
    uint16_t wConfig,                                                          /**< [In] Configuration identifier */
    uint16_t wValue                                                            /**< [In] Configuration value */
    );

/**
 * \brief   Get the configuration value 
 *
 * \return  Error code
 *
 * \retval #PH_ERR_SUCCESS             operation successful
 * \retval #PH_ERR_INVAID_PARAMETER    Invalid option/response received 
 * \retval other                       Other errors depending on underlaying component
 *
 */

phStatus_t phacDiscLoop_GetConfig(
    void * pDataParams,                                                        /**< [In] Pointer to this layer's parameter structure */
    uint16_t wConfig,                                                          /**< [In] Configuration identifier */
    uint16_t *pValue                                                           /**< [Out] Configuration value */
    );


/**
 * \brief    Activates the given tag type with given index 
 *
 * \return   Error code
 * \retval   #PH_ERR_SUCCESS      On success
 * \retval   #PH_ERR_INVALID_ARG  If inavlid index or card type was given
 *
 */

phStatus_t phacDiscLoop_ActivateCard(
    void * pDataParams,                                                        /**< [In] Pointer to this layer's parameter structure */
    uint8_t bTagType,                                                          /**< [In] Tag type could be Type A,B or F */
    uint8_t bTagIndex                                                          /**< [In] The tag which has to be activated */
    );

#ifdef __DEBUG
/* This API would be available only for debugging purpose and test bench */
/**
 * \brief   Assigns the component data paramter to one of the filed in 
 *          discover loop parameter based on the option
 *
 * \return  Error code
 * \retval  #PH_ERR_INVALID_PARAMTER  If invalid option was passed
 * \retval  #PH_ERR_SUCCESS           on success
 *
 */
phStatus_t phacDiscLoop_SetPtr(
    void * pDataParams,									/**< [In] Pointer to this layer's paramter structure */
    void * pI14443p3a,									/**< [In] Pointer to 14443a paramter structure */
    void * pI14443p4a,									/**< [In] Pointer to 14443a layer 4 paramter structure */
    void * pI14443p3b,									/**< [In] Pointer to 14443b layer paramter structure */
    void * pFeilca,										/**< [In] Pointer to pal felica paramter structure */
    void * pI18092mPI									/**< [In] Pointer to pal mpI paramter structure */
    );
#endif /* __DEBUG */
/** @} */


#ifdef NXPBUILD__PHAC_DISCLOOP_SW
/** \defgroup phacdiscloop_Sw Component : Software
* @{
*/

#define PHAC_DISCLOOP_SW_ID   0x01                                              /**< ID for Software Discover loop component */


/**
 * \brief Private parameter structure
 */
typedef struct phacDiscLoop_Sw_DataParams
{
    uint16_t                  wId;                       /**< ID for this component, not to be modified */
    uint8_t                   bDetectionConfiguration;   /**< configuration for detection of various technologies */
    uint16_t                  wGTa;                      /**< Guard time for A type in ms */
    uint16_t                  wGTb;                      /**< Guard time for B type in ms */
    uint16_t                  wGTf;                      /**< Guard time for F type in ms */
    uint16_t                  wGTbf;                     /**< Guard timr for switching from Tech Type B detection to Tech Type F */
    uint8_t                   bGTaUnit;                  /**< Time out unit for guard time for Type A could be MS or US */
    uint8_t                   bGTbUnit;                  /**< Time out unit for guard time for Type B could be MS or US */
    uint8_t                   bGTfUnit;                  /**< Time out unit for guard time for Type F could be MS or US */
    uint8_t                   bGTbfUnit;                 /**< Time out unit for guard time while siwtching from B to A MS or US */
    uint8_t                   bNumPollLoops;             /**< Number of times the discovery loop should loop looking for cards before discovery loop gives up */
    uint8_t                   bState;                    /**< Indicates the current state */
    uint16_t                  wTagsFound;                /**< Sets bit masks indicating tags that were found */
    uint8_t                   bBailOut;                  /**< The bail out parameter after detecting a card type */
    uint8_t                   bLoopMode;                 /**< Holds the combination of poll, listen and pause mode for discover loop */
    pErrHandlerCallback       pErrHandler;               /**< Pointer to the user error handler function */
    uint16_t                  wPausePeriod;              /**< The delay to be used in pause mode */
    uint8_t                   bPausePeriodUnit;          /**< The time unit used for delaying in pause mode */
    uint8_t                   bStopFlag;                 /**< This flag indicates that the discovery loop should exit */
    uint8_t                   bConColl;                  /**< Holds the information whether collision resolution is required or not */
    void                    * pHalDataParams;            /**< Pointer to the HAL layer component */
    void                    * pPal1443p3aDataParams;     /**< Pointer to the 14443P3A layer PAL data params */
    void                    * pPal1443p4aDataParams;     /**< Pointer to the 14443P4A layer PAL data params */
    void                    * pPalFelicaDataParams;      /**< Pointer to the Felica PAL data params */
    void                    * pPal1443p3bDataParams;     /**< Pointer to the Type B 14443-B PAL data params */
    void                    * pPal18092mPIDataParams;    /**< Pointer to 18092 MPI PAL data Params */
    void                    * pOsal;                     /**< Pointer to the OS layer component */

#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEA_TAGS
    phacDiscLoop_TypeA_Tags_t sTypeATargetInfo;          /**< information gathered from TYPE A tags */
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEA_TAGS */
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS
    phacDiscLoop_TypeF_Tags_t sTypeFTargetInfo;          /**< Information gathered from TYPE F tags */
#endif  /* NXPBUILD__PHAC_DISCLOOP_TYPEF_TAGS */
#ifdef NXPBUILD__PHAC_DISCLOOP_TYPEB_TAGS
    phacDiscLoop_TypeB_Tags_t sTypeBTargetInfo;          /**< Information gathered from TYPE B tags */
#endif /* NXPBUILD__PHAC_DISCLOOP_TYPEB_TAGS */
    
} phacDiscLoop_Sw_DataParams_t;
  
/**
 * \brief  Initializes the discovery loop software component.
 * \return Status code
 * \retval #PH_ERR_SUCCESS if operation was successful.
 * \note   All the layer components that are passed should be initialized
 *         before the call is made to start the discover loop
 */

phStatus_t phacDiscLoop_Sw_Init(
    phacDiscLoop_Sw_DataParams_t * pDataParams,                                 /**< [In] pointer to this layer's parameter structure */
    uint16_t wSizeOfDataParams,                                                 /**< [In] size of data params */
    void * pHalDataParams,                                                      /**< [In] The HAL component that is used for data exchange */
    void * pOsal                                                                /**< [In] Reference to the OS AL data parameters */
    );



/*@}*/


#endif   /* NXPBUILD__PHAC_DISCLOOP_SW */

#endif
