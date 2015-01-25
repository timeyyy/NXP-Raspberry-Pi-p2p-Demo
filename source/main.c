/*==============================================================================================
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

/*==============================================================================================
 **
 * Header for this file
 */
#include <stdio.h>
#include <ph_Status.h>

/*==============================================================================================
 **
 * Reader Library Headers
 */
#include <phpalI14443p3a.h>
#include <phpalI14443p4.h>
#include <phpalI14443p3b.h>
#include <phpalI14443p4a.h>
#include <phpalFelica.h>

#include "SnepClient.h"
#include <phhalHw.h>
/*==============================================================================================
 **
 * Defines and Local Variables
 */
uint8_t bHalBufferTx[64];                          /**< HAL TX buffer */
uint8_t bHalBufferRx[64];                          /**< HAL RX buffer */
uint8_t bAtr_Res[30];                              /**< ATR response holder */
uint8_t bAtr_ResLength;                            /**< ATR response length */
uint8_t bGtLen;                                    /**< Gt length */
void  *pHal;                                       /**< HAL pointer */
void  *balReader;                                  /**< BAL pointer */

phbalReg_Stub_DataParams_t       balReaderStub;    /**< BAL component holder */
phhalHw_Rc523_DataParams_t       halReader523;     /**< HAL component holder */
phpalI14443p3a_Sw_DataParams_t   palI14443p3a;     /**< PAL I14443-A component */
phpalI14443p4a_Sw_DataParams_t   palI14443p4a;     /**< PAL I14443-4A component */
phpalI14443p3b_Sw_DataParams_t   palI14443p3b;     /**< PAL I14443-B component */
phpalI14443p4_Sw_DataParams_t    palI14443p4;      /**< PAL I14443-4 component */
phpalFelica_Sw_DataParams_t      palFelica;        /**< PAL Felica component */

/*==================================================
 ** GI information */
const uint8_t GI[] = {
      0x46,0x66,0x6D,      /* LLCP magic numbers */
      0x01,0x01,0x10,      /*VERSION*/
      0x03,0x02,0x00,0x01, /*WKS*/
      0x04,0x01,0xF1       /*LTO*/
};

/*==============================================================================================
 **
 *  \brief   Resets the RF field 
 ---------------------------------------------------------------------------------------------*/
void NFC_Reset(void)
    {
    phStatus_t status;

    status = phhalHw_FieldOff(pHal);
    status = phhalHw_FieldOn(pHal);

    return;
    }

/*==============================================================================================
 * \brief     Prints the UID.
 *
 * \param     uid     Array of UID data to be printed in hex
 * \param     uidLen  Length of the UID array
 *
 ---------------------------------------------------------------------------------------------*/
void printUid(uint8_t * uid, uint8_t uidLen)
    {
    int i;

    for (i=0; i<uidLen; i++)
        {
        printf ("%02X", uid[i]);
        }
    printf (" ");
    }

/*==============================================================================================
 * \brief      Initializes the discover loop component
 *     phacDiscLoop_Sw_DataParams_t * pDataParams   <[In]  DataParams representing the discovery loop
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t DiscLoopInit( phacDiscLoop_Sw_DataParams_t * pDataParams )
    {
    phStatus_t status;

    /* Set for poll and listen mode */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_MODE,
            PHAC_DISCLOOP_SET_POLL_MODE | PHAC_DISCLOOP_SET_PAUSE_MODE);
    CHECK_SUCCESS(status);

    /* Set for detection of TypeA, TypeB and Type F tags */
    status = phacDiscLoop_SetConfig(
            pDataParams,
            PHAC_DISCLOOP_CONFIG_DETECT_TAGS,
            PHAC_DISCLOOP_CON_POLL_A/* | PHAC_DISCLOOP_CON_POLL_B */| PHAC_DISCLOOP_CON_POLL_F
    );
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_PAUSE_PERIOD_MS, 1000);
    CHECK_SUCCESS(status);

    /* Set number of polling loops to 5 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_NUM_POLL_LOOPS, 5);
    CHECK_SUCCESS(status);

    /* Configure felica discovery */
    /* Set the system code to 0xffff */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_SYSTEM_CODE, 0xffff);
    CHECK_SUCCESS(status);
    /* Set the maximum number of Type F tags to be detected to 3 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_DEVICE_LIMIT, 3);
    CHECK_SUCCESS(status);
    /* Set the polling limit for Type F tags to 5 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_POLL_LIMIT, 5);
    CHECK_SUCCESS(status);
    /* Set the slot number to 3 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_TIME_SLOT, 3);
    CHECK_SUCCESS(status);
    /* Set LRI to 3 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_P2P_LRI, 3);
    CHECK_SUCCESS(status);
    /* Set DID to 3 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_P2P_DID, 0);
    CHECK_SUCCESS(status);
    /* Disable NAD */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_P2P_NAD_ENABLE, PH_OFF);
    CHECK_SUCCESS(status);
    /* Clear NAD info */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_P2P_NAD, 0);
    CHECK_SUCCESS(status);
    /* Assign the GI */
    discLoop.sTypeFTargetInfo.sTypeF_P2P.pGi = (uint8_t *)GI;
    /* Set the length of GI */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_P2P_GI_LEN, sizeof(GI));
    CHECK_SUCCESS(status);
    /* Assign ATR response */
    discLoop.sTypeFTargetInfo.sTypeF_P2P.pAtrRes = bAtr_Res;
    /* Set ATR response length */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_P2P_ATR_RES_LEN, bAtr_ResLength);

    /* Configure Type B tag discovery */
    /* Set slot coding number to 0 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEB_NCODING_SLOT, 0);
    CHECK_SUCCESS(status);
    /* Set AFI to 0, Let all TypeB tags in field respond */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEB_AFI_REQ, 0);
    CHECK_SUCCESS(status);
    /* Disable extended ATQB response */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEB_EXTATQB, 0);
    CHECK_SUCCESS(status);
    /* Set poll limit for Type B tags to 5 */
    status = phacDiscLoop_SetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEB_POLL_LIMIT, 5);
    CHECK_SUCCESS(status);

    return PH_ERR_SUCCESS;
    }

/*==============================================================================================
 * This function demonstrates the usage of discovery loop
 * It detects and displays the type of card and UID
 * In case of P2P device, it enables LLCP and transmits the message
 *
 * \param   pDataParams      The discovery loop data parameters
 *
 * \note   This function will never return
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t DiscLoopDemo(phacDiscLoop_Sw_DataParams_t * pDataParams)
    {
    phStatus_t status;
    uint16_t   wTagsDetected;
    int        loop = 0;
    uint16_t   wNumberOfTags;

    while(1)
        {
        status = phacDiscLoop_Start(pDataParams);
        if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
            {
            /* Get the tag types detected info */
            status = phacDiscLoop_GetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TAGS_DETECTED, &wTagsDetected);
            if (((status & PH_ERR_MASK) != PH_ERR_SUCCESS) || wTagsDetected == PHAC_DISCLOOP_NO_TAGS_FOUND)
                {
                phhalHw_FieldReset(pHal);
                continue;
                }

            if (PHAC_DISCLOOP_CHECK_ANDMASK(wTagsDetected, PHAC_DISCLOOP_TYPEF_DETECTED))
                {
#ifdef PRETTY_PRINTING
                printf("Detected Type F tag(s) ");
#else
                printf ("\n[Type F] , wTagsDetected = 0x%x\n",wTagsDetected);
#endif

                /* Get the number of Type F tags detected */
                status = phacDiscLoop_GetConfig(pDataParams, PHAC_DISCLOOP_CONFIG_TYPEF_NR_TAGS_FOUND, &wNumberOfTags);

                /* Loop through all the type F tags and print the IDm */
                for (loop = 0; loop < wNumberOfTags; loop++)
                    {
#ifdef PRETTY_PRINTING
                    printf ("IDm: ");
                    printf ("Card %d: ",loop + 1);
#endif
               printUid(
                       pDataParams->sTypeFTargetInfo.aTypeF[loop].aIDmPMm,
                       PHAC_DISCLOOP_FELICA_IDM_LENGTH);
               printf ("\n");
                    }

                if (wTagsDetected & PHAC_DISCLOOP_TYPEF_DETECTED_TAG_P2P)
                    {
                    /* If Type F tag with P2P capability was discovered, do and P2P exchange */
//                   printf("Type F P2P compatibility device has been detected \n");
                    bGtLen = bAtr_ResLength - 17;
                    /* push the data to the LLCP protocol data structure */
                    RemoteInfo.SessionOpened = 1;
                    RemoteInfo.RemDevType = phNfc_eNfcIP1_Target;
                    RemoteInfo.RemoteDevInfo.NfcIP_Info.ATRInfo_Length = (discLoop.sTypeFTargetInfo.sTypeF_P2P.bAtrResLength - 17);
                    memcpy(RemoteInfo.RemoteDevInfo.NfcIP_Info.ATRInfo, &discLoop.sTypeFTargetInfo.sTypeF_P2P.pAtrRes[17], (discLoop.sTypeFTargetInfo.sTypeF_P2P.bAtrResLength - 17));

                    /* =======================================================
                     * SNEP Client Demo
                  -------------------------------------------------------*/

                    status = SNEPClientDemo();

                    if (status != PH_ERR_SUCCESS)
                       {
                       NFC_LlcpClose();
                       }
                    }
                }
                else
                {
                   printf("Card detected.\n");
                }
            }

			status = phOsal_Timer_Wait(&osal, 1, 0x3ff);  // 1023ms
			CHECK_SUCCESS(status);

			printf("phhalHw_FieldReset %0x\n",status);
			CHECK_SUCCESS(status);
        }
    }

/*=============================
 *    M A I N
 *============================*/
/*==============================================================================================
 *
 *   Main Function
 *
 ---------------------------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
    phbalReg_R_Pi_spi_DataParams_t spi_balReader;

    //void *halReader;
    phStatus_t status;
    uint8_t volatile card_or_tag_detected;

    uint8_t bHalBufferReader[0x40];
    uint8_t bValue;

    /* Initialize the Reader BAL (Bus Abstraction Layer) component */
    status = phbalReg_R_Pi_spi_Init(&spi_balReader, sizeof(phbalReg_R_Pi_spi_DataParams_t));
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to initialize SPI\n");
        return 1;
    }
	else
	{
    printf("OK: phbalReg_R_Pi_spi_Init\n");
    printf("wId: %0x\n",spi_balReader.wId);
    printf("spiFD: %0x\n",spi_balReader.spiFD);
    printf("spiMode: %0x\n",spi_balReader.spiMode);
    printf("spiBPW: %0x\n",spi_balReader.spiBPW);
    printf("spiDelay: %0x\n",spi_balReader.spiDelay);
    printf("spiSpeed: %0x %d\n",spi_balReader.spiSpeed,spi_balReader.spiSpeed);
	}
    balReader = (void *)&spi_balReader;

    status = phbalReg_OpenPort((void*)balReader);
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to open bal\n");
        return 2;
    }

    /* we have a board with PN512,
     * but on the software point of view,
     * it's compatible to the RC523 */
    status = phhalHw_Rc523_Init(&halReader523,
                                sizeof(phhalHw_Rc523_DataParams_t),
                                balReader,
                                0,
                                bHalBufferReader,
                                sizeof(bHalBufferReader),
                                bHalBufferReader,
                                sizeof(bHalBufferReader));
    pHal = &halReader523;
    
    /* Set the parameter to use the SPI interface */
    halReader523.bBalConnectionType = PHHAL_HW_BAL_CONNECTION_SPI;

    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to initialize the HAL\n");
        return 3;
    }

    /* Set the HAL configuration to SPI */
    status = phhalHw_SetConfig(pHal, PHHAL_HW_CONFIG_BAL_CONNECTION,
                               PHHAL_HW_BAL_CONNECTION_SPI);
    if (PH_ERR_SUCCESS != status)
    {
        printf("Failed to set hal connection SPI\n");
        return 4;
    }

    phhalHw_ReadRegister(pHal, PHHAL_HW_RC523_REG_VERSION, &bValue);
    printf("Chip version: %0x\n",bValue);


    /* Initialize the I14443-A PAL layer */
    printf("phpalI14443p3a_Sw_Init\n");
    status = phpalI14443p3a_Sw_Init(&palI14443p3a, sizeof(phpalI14443p3a_Sw_DataParams_t), pHal);
    CHECK_SUCCESS(status);

    /* Initialize the I14443-A PAL component */
    printf("phpalI14443p4a_Sw_Init\n");
    status = phpalI14443p4a_Sw_Init(&palI14443p4a, sizeof(phpalI14443p4a_Sw_DataParams_t), pHal);
    CHECK_SUCCESS(status);

    /* Initialize the I14443-B PAL  component */
    printf("phpalI14443p3b_Sw_Init\n");
    status = phpalI14443p3b_Sw_Init(&palI14443p3b, sizeof(palI14443p3b), pHal);
    CHECK_SUCCESS(status);

    /* Initialize PAL Felica PAL component */
    printf("phpalFelica_Sw_Init\n");
    status = phpalFelica_Sw_Init(&palFelica, sizeof(phpalFelica_Sw_DataParams_t), pHal);
    CHECK_SUCCESS(status);

    /* Init 18092 PAL component */
    printf("phpalI18092mPI_Sw_Init\n",bValue);
    status = phpalI18092mPI_Sw_Init(&palI18092mPI, sizeof(phpalI18092mPI_Sw_DataParams_t), pHal);
    CHECK_SUCCESS(status);

    /* Initialize the timer component */
    status = phOsal_R_Pi_Timer_Init(&osal);
    CHECK_SUCCESS(status);

    /* Initialize the discover component */
    printf("phacDiscLoop_Sw_Init\n");
    status = phacDiscLoop_Sw_Init(&discLoop, sizeof(phacDiscLoop_Sw_DataParams_t), pHal, &osal);
    CHECK_SUCCESS(status);

    discLoop.pPal1443p3aDataParams = &palI14443p3a;
    discLoop.pPal1443p3bDataParams = &palI14443p3b;
    discLoop.pPal1443p4aDataParams = &palI14443p4a;
    discLoop.pPal18092mPIDataParams = &palI18092mPI;
    discLoop.pPalFelicaDataParams = &palFelica;
    discLoop.pHalDataParams = pHal;
    discLoop.pOsal = &osal;

    /* reset the IC  */
    printf("phhalHw_FieldReset\n");
    status = phhalHw_FieldReset(pHal);
    CHECK_SUCCESS(status);

    printf("DiscLoopInit\n");
    DiscLoopInit(&discLoop);

    printf("DiscLoopDemo\n");
    DiscLoopDemo(&discLoop);

    return 0;
    }

/*==============================================================================================
 *   End of File
 ---------------------------------------------------------------------------------------------*/

