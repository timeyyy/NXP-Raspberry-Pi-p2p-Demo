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
* Generic OSAL Component of Reader Library Framework.
* $Author: prabakaran.c $
* $Revision: 1.11 $
* $Date: Mon Dec  3 09:40:10 2012 $
*
* History:
*  PC: Generated 23. Aug 2012
*
*/


#include <ph_Status.h>
#include <ph_RefDefs.h>

#ifdef NXPBUILD__PH_OSAL
#include <phOsal.h>

#ifdef NXPBUILD__PH_OSAL_LPC12XX
#include "Lpc12xx/phOsal_Lpc12xx.h"
#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
#include "RaspberryPi/phOsal_R_Pi.h"
#endif /* NXPBUILD__PH_OSAL_R_Pi */

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Timer_Create(void *pDataParams, uint32_t *pTimerId)
{
    phStatus_t PH_MEMLOC_REM status = PH_ERR_SUCCESS;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phOsal_Timer_Create");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(pTimerId);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pTimerId);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_OSAL)
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return status;
    }
    
    /* Select the active layer to perform the action */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_OSAL_LPC12XX
    case PH_OSAL_LPC12XX_ID:
        status = phOsal_Lpc12xx_Timer_Create((phOsal_Lpc12xx_DataParams_t*)pDataParams, pTimerId);
        break;

#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
    case PH_OSAL_R_Pi_ID:
        status = phOsal_R_Pi_Timer_Create((phOsal_R_Pi_DataParams_t*)pDataParams, pTimerId);
        break;

#endif /* NXPBUILD__PH_OSAL_R_Pi */
    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);
    }

#ifdef NXPBUILD__PH_LOG
    if ((status & PH_ERR_MASK) == PH_ERR_SUCCESS)
	{
		PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, pTimerId_log, pTimerId);
    }
#endif
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Timer_Start(
    void * pDataParams,
    uint32_t dwTimerId,
    uint32_t dwRegTimeCnt, 
    ppCallBck_t pApplication_callback,
    void  * pContext
    )
{
    phStatus_t PH_MEMLOC_REM status = PH_ERR_SUCCESS;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phOsal_TImer_Start");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(dwTimerId);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(dwRegTimeCnt);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, dwTimerId_log, &dwTimerId);
    PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, dwRegTimeCnt_log, &dwRegTimeCnt);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
    PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_OSAL)
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return status;
    }

    /* Select the active layer to perform the action */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_OSAL_LPC12XX
    case PH_OSAL_LPC12XX_ID:
        status = phOsal_Lpc12xx_Timer_Start((phOsal_Lpc12xx_DataParams_t*)pDataParams, 
                                dwTimerId,
                                dwRegTimeCnt,
                                (ppCallBck_t)pApplication_callback,
                                pContext);
        break;
#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
    case PH_OSAL_R_Pi_ID:
        status = phOsal_R_Pi_Timer_Start((phOsal_R_Pi_DataParams_t*)pDataParams,
                                dwTimerId,
                                dwRegTimeCnt,
                                (ppCallBck_t)pApplication_callback,
                                pContext);
        break;
#endif /* NXPBUILD__PH_OSAL_R_Pi */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

    return status;
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Timer_Stop(void * pDataParams, uint32_t dwTimerId)
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phOsal_Timer_Stop");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(dwTimerId);
    PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, dwTimerId_log, &dwTimerId);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
    PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_OSAL)
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return status;
    }
    status = PH_ERR_SUCCESS;

    /* Select the active layer to perform the action */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_OSAL_LPC12XX
    case PH_OSAL_LPC12XX_ID:
        status = phOsal_Lpc12xx_Timer_Stop((phOsal_Lpc12xx_DataParams_t*)pDataParams, 
                                dwTimerId);
        break;
#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
    case PH_OSAL_R_Pi_ID:
        status = phOsal_R_Pi_Timer_Stop((phOsal_R_Pi_DataParams_t*)pDataParams,
                                dwTimerId);
        break;
#endif /* NXPBUILD__PH_OSAL_R_Pi */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    
    return status;
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Timer_Wait(
                             void * pDataParams, 
                             uint8_t bTimerDelayUnit, 
                             uint16_t wDelay
                             )
{
    phStatus_t PH_MEMLOC_REM status;

    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phOsal_Timer_Wait");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(bTimerDelayUnit);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(wDelay);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
    PH_LOG_HELPER_ADDPARAM_UINT8(PH_LOG_LOGTYPE_DEBUG, bTimerDelayUnit_log, &bTimerDelayUnit);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_DEBUG, wDelay_log, &wDelay);
    PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_OSAL)
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return status;
    }
    status = PH_ERR_SUCCESS;

    /* Select the active layer to perform the action */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_OSAL_LPC12XX
    case PH_OSAL_LPC12XX_ID:
        phOsal_Lpc12xx_Timer_Wait(
            (phOsal_Lpc12xx_DataParams_t*)pDataParams,
            bTimerDelayUnit,
            wDelay
            );
        break;
#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
    case PH_OSAL_R_Pi_ID:
        phOsal_R_Pi_Timer_Wait(
            (phOsal_R_Pi_DataParams_t*)pDataParams,
            bTimerDelayUnit,
            wDelay
            );
        break;
#endif /* NXPBUILD__PH_OSAL_R_Pi */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

    }
    return status;
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_Timer_Delete(void * pDataParams, uint32_t dwTimerId)
{
    phStatus_t PH_MEMLOC_REM status;
    
    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phOsal_Timer_Delete");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(dwTimerId);
    PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, dwTimerId_log, &dwTimerId);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
    PH_ASSERT_NULL (pDataParams);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_OSAL)
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return status;
    }
  
    /* Select the active layer to perform the action */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_OSAL_LPC12XX
    case PH_OSAL_LPC12XX_ID:
        status = phOsal_Lpc12xx_Timer_Delete((phOsal_Lpc12xx_DataParams_t*)pDataParams, 
                                dwTimerId);
        break;
#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
    case PH_OSAL_R_Pi_ID:
        status = phOsal_R_Pi_Timer_Delete((phOsal_R_Pi_DataParams_t*)pDataParams,
                                dwTimerId);
        break;
#endif /* NXPBUILD__PH_OSAL_R_Pi */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    
    return status;
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_GetMemory(
                        void * pDataParams, 
                        uint32_t dwLength,
                        void ** pMem
                        )
{
    phStatus_t PH_MEMLOC_REM status;
    
    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phOsal_GetMemory");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(dwLength);
    PH_LOG_HELPER_ADDPARAM_UINT32(PH_LOG_LOGTYPE_DEBUG, dwLength_log, &dwLength);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
    PH_ASSERT_NULL (pDataParams);
    
    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_OSAL)
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return status;
    }
  
    /* Select the active layer to perform the action */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_OSAL_LPC12XX
    case PH_OSAL_LPC12XX_ID:
        status = phOsal_Lpc12xx_GetMemory(
            (phOsal_Lpc12xx_DataParams_t*)pDataParams, 
            dwLength,
            pMem
            );
        break;
#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
    case PH_OSAL_R_Pi_ID:
        status = phOsal_R_Pi_GetMemory(
            (phOsal_R_Pi_DataParams_t*)pDataParams,
            dwLength,
            pMem
            );
        break;
#endif /* NXPBUILD__PH_OSAL_R_Pi */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    
    return status;
}

/*==============================================================================================
 *
 ---------------------------------------------------------------------------------------------*/
phStatus_t phOsal_FreeMemory(
                             void *pDataParams,
                             void *pMem
                             )
{
    phStatus_t PH_MEMLOC_REM status;
    
    PH_LOG_HELPER_ALLOCATE_TEXT(bFunctionName, "phOsal_FreeMemory");
    PH_LOG_HELPER_ALLOCATE_PARAMNAME(status);
    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_ENTER);
    PH_ASSERT_NULL (pDataParams);
    PH_ASSERT_NULL (pMem);

    /* Check data parameters */
    if (PH_GET_COMPCODE(pDataParams) != PH_COMP_OSAL)
    {
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);

        PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
        PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
        PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);

        return status;
    }
  
    /* Select the active layer to perform the action */
    switch (PH_GET_COMPID(pDataParams))
    {
#ifdef NXPBUILD__PH_OSAL_LPC12XX
    case PH_OSAL_LPC12XX_ID:
        status = phOsal_Lpc12xx_FreeMemory(
            (phOsal_Lpc12xx_DataParams_t*)pDataParams, 
            pMem
            );
        break;
#endif /* NXPBUILD__PH_OSAL_LPC12XX */

#ifdef NXPBUILD__PH_OSAL_R_Pi
    case PH_OSAL_R_Pi_ID:
        status = phOsal_R_Pi_FreeMemory(
            (phOsal_R_Pi_DataParams_t*)pDataParams,
            pMem
            );
        break;
#endif /* NXPBUILD__PH_OSAL_R_Pi */

    default:
        status = PH_ADD_COMPCODE(PH_ERR_INVALID_DATA_PARAMS, PH_COMP_OSAL);
    }

    PH_LOG_HELPER_ADDSTRING(PH_LOG_LOGTYPE_INFO, bFunctionName);
    PH_LOG_HELPER_ADDPARAM_UINT16(PH_LOG_LOGTYPE_INFO, status_log, &status);
    PH_LOG_HELPER_EXECUTE(PH_LOG_OPTION_CATEGORY_LEAVE);
    
    return status;
}

#endif  /* NXPBUILD__PH_OSAL */

