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
* LPC12xx OSAL Component of Reader Library Framework.
* $Author: prabakaran.c $
* $Revision: 1.2 $
* $Date: Mon Nov 26 05:17:09 2012 $
*
* History:
*  PC: Generated 23. Aug 2012
*
*/


#include <ph_Status.h>
#include <ph_RefDefs.h>
#include <phOsal.h>

#ifdef NXPBUILD__PH_OSAL_LPC12XX

#include "phOsal.h"
#include "phOsal_Lpc12xx.h"
#include "timer32.h"



/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_Timer_Init(phOsal_Lpc12xx_DataParams_t * pDataParams)
{
    

    pDataParams->wId = PH_COMP_OSAL | PH_OSAL_LPC12XX_ID;
    
    /* Lets be ready with the timer */
    Timer_Init();

    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_OSAL);
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_Timer_Create(
    phOsal_Lpc12xx_DataParams_t *pDataParams,
    uint32_t * pTimerId
    )
{
    Timer_Create(pTimerId);
    
    if (*pTimerId == -1)
    {
        /* No timer found, need to return error */
        return PH_ADD_COMPCODE(PH_OSAL_ERR_NO_FREE_TIMER,  PH_COMP_OSAL);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_OSAL);
    }
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_Timer_Wait(
    phOsal_Lpc12xx_DataParams_t * pDataParams,
    uint8_t bTimerDelayUnit,
    uint16_t wDelay
    )
{
    /* We will always use timer 1 for delaying purpose */
    enable_timer32(1);

    if (bTimerDelayUnit == PH_OSAL_TIMER_UNIT_MS)
    {
        /* Delay in terms of Milli seconds */
        delay32Ms(1, wDelay);
    }
    else
    {
        /* Delay in terms of Micro seconds */
        delay32Us(1, wDelay);
    }
    return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_OSAL);
}


/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_Timer_Start(
    phOsal_Lpc12xx_DataParams_t * pDataParams,
    uint32_t     dwTimerId,       
    uint32_t     dwRegTimeCnt,    
    ppCallBck_t  pApplicationCallback,
    void         *pContext            
    )
{
    phStatus_t status;
    
    status = Timer_Register(dwTimerId, dwRegTimeCnt, pApplicationCallback, pContext);
    if (status == PH_ERR_SUCCESS)
    {
       return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_OSAL);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_OSAL_ERR_INVALID_TIMER, PH_COMP_OSAL);   
    }
}
    
/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_Timer_Stop(
    phOsal_Lpc12xx_DataParams_t * pDataParams,  
    uint32_t dwTimerId                          
    )
{
    phStatus_t status;
    status = Timer_Stop(dwTimerId);
    if (status == PH_ERR_SUCCESS)
    {
       return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_OSAL);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_OSAL_ERR_INVALID_TIMER, PH_COMP_OSAL);   
    }
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_Timer_Delete(
    phOsal_Lpc12xx_DataParams_t * pDataParams,     
    uint32_t dwTimerId                             
    )
{
    phStatus_t status;

    status = Timer_Delete(dwTimerId);
    if (status == PH_ERR_INTERNAL_ERROR)
    {
        return PH_ADD_COMPCODE(PH_OSAL_ERR_INVALID_TIMER, PH_COMP_OSAL);
    }
    else
    {
        return PH_ADD_COMPCODE(PH_ERR_SUCCESS, PH_COMP_OSAL);
    }
   
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_GetMemory(
                                phOsal_Lpc12xx_DataParams_t *pDataParams, 
                                uint32_t dwLength,
                                void ** pMem
                                )
{
    phStatus_t status = PH_ERR_SUCCESS;

    PHOSAL_UNUSED_VARIABLE(pDataParams);
    pMem = (void *) malloc(dwLength);

    if (pMem == NULL)
        status = PH_ERR_RESOURCE_ERROR;

    return status;
}


/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Lpc12xx_FreeMemory(
                                phOsal_Lpc12xx_DataParams_t *pDataParams,
                                void * ptr                             
                                )
{
    phStatus_t status = PH_ERR_SUCCESS;

    PHOSAL_UNUSED_VARIABLE(pDataParams);
    if(NULL !=  ptr)
        free(ptr);

    return status;
}
    

    
#endif /* NXPBUILD__PH_OSAL_LPC12XX */
