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
* Generic LLCP Link layer Component of Reader Library Framework.
* $Author: prabakaran.c $
* $Revision: 1.6 $
* $Date: Fri Nov 30 11:46:48 2012 $
*
* History:
*  PC: Generated 23. Aug 2012
*
*/
#ifndef PHLNLLCP_H
#define PHLNLLCP_H

#include <ph_Status.h>

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef NXPBUILD__PHLN_LLCP_FRI

#include "../comps/phlnLlcp/src/Fri/phFriNfc_Llcp.h"
#include "../comps/phlnLlcp/src/Fri/phNfcLlcpTypes.h"
#include "../comps/phlnLlcp/src/Fri/phNfcHalTypes.h"
#include "../comps/phlnLlcp/src/Fri/phFriNfc_LlcpTransport.h"

/** \defgroup phlnLlcp_Fri Component : FRI
* \brief FRI implementation of LLCP
*
* @{
*/
#define PHLN_LLCP_FRI_ID               0x01    /**< ID for LLCP FRI component */

   /**
	* \brief FRI LLCP parameter structure
	*/
	typedef struct
	{
		uint16_t wId;                                       /**< Layer ID for this component, NEVER MODIFY! */
        phlnLlcp_t                      * pLlcp;            /**< Pointer to the Llcp layer */
        phlnLlcp_sLinkParameters_t      * pLinkParams;      /**< Pointer to the Link parameters */
        phlnLlcp_Transport_t            * pLlcpSocketTable; /**< Pointer to the Socket table */
        void                            * pTxBuffer;        /**< Pointer to the Tx buffer */
        uint16_t                          wTxBufferLength;  /**< Length of the Tx buffer */
        void                            * pRxBuffer;        /**< Length of the Rx buffer */
        uint16_t                          wRxBufferLength;  /**< Pointer to FRI llcp elements */
        phHal_sRemoteDevInformation_t   * pRemoteDevInfo;   /**< Pointer to the Remote device information */
        void                            * pLowerDevice;     /**< Pointer to the Lower device */
	} phlnLlcp_Fri_DataParams_t;

   /**
	* \brief Initialise the LLCP FRI component.
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
   	phStatus_t phlnLlcp_Fri_Init(
		phlnLlcp_Fri_DataParams_t * pDataParams,            /**< [In] Pointer to this layer's parameter structure. */
		uint16_t wSizeOfDataParams,                         /**< [In] Size of the Dataparams */
        phlnLlcp_t * pLlcp,                                 /**< [In] Pointer to the Llcp layer */
        phlnLlcp_sLinkParameters_t * pLinkParams,           /**< [In] Pointer to the Link parameters */
        phlnLlcp_Transport_t * pLlcpSocketTable,            /**< [In] Pointer to the Socket table */
        phHal_sRemoteDevInformation_t * pRemoteDevInfo,     /**< [In] Pointer to the Remote device information */
        void * pTxBuffer,                                   /**< [In] Pointer to the Tx buffer */
        uint16_t wTxBufferLength,                           /**< [In] Length of the Tx buffer */
        void * pRxBuffer,                                   /**< [In] Pointer to the Rx buffer */
        uint16_t wRxBufferLength,                           /**< [In] Length of the Rx buffer */
        void * pLowerDevice                                 /**< [In] Pointer to the Lower device */
        );

/** @} */
#endif /* NXPBUILD__PHLN_LLCP_FRI */

#ifdef NXPBUILD__PHLN_LLCP

/** \defgroup phln Link Abstraction Layer
* \brief These are the Components which are used to abstract the functionality of the physical reader device to a generic interface.
* @{
*/

   /**
	* \brief Reset the LLCP layer
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Reset(  
        void * pDataParams,                     /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_LinkStatus_CB_t pfLink_CB,     /**< [In] Pointer to the callback function. */
        void * pContext                         /**< [In] Pointer to the Reset context */
        );

   /**
	* \brief Check the LLCP layer link
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_ChkLlcp(
        void * pDataParams,                 /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Check_CB_t pfCheck_CB,     /**< [In] Pointer to the callback function. */
        void * pContext                     /**< [In] Pointer to the Reset context */
        );

   /**
	* \brief Activate the LLCP layer link
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Activate(
        void * pDataParams        /**< [In] Pointer to this layer's parameter structure. */
        );

   /**
	* \brief Deactivate the LLCP layer link
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Deactivate(
        void * pDataParams        /**< [In] Pointer to this layer's parameter structure. */
        );

   /**
	* \brief Get the local node information 
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_GetLocalInfo(
        void * pDataParams        /**< [In] Pointer to this layer's parameter structure. */
        );

   /**
	* \brief Get the Remote node information 
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_GetRemoteInfo(
        void * pDataParams        /**< [In] Pointer to this layer's parameter structure. */
        );

   /**
	* \brief API to send the data over LLCP
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
   	phStatus_t phlnLlcp_Send(
		void * pDataParams,                         /**< [In] Pointer to this layer's parameter structure. */
		phlnLlcp_sPacketHeader_t * pHeader,         /**< [In] Pointer to the header */
        phlnLlcp_sPacketSequence_t * pSequence,     /**< [In] Pointer to the Packet sequence */
        phNfc_sData_t * pInfo,                      /**< [In] Pointer to the Data */
        phlnLlcp_Send_CB_t pfSend_CB,               /**< [In] Pointer to the callback function */
        void * pContext                             /**< [In] Pointer to the context */
        );

   /**
	* \brief API to receive the data over LLCP
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
   	phStatus_t phlnLlcp_Recv(
		void * pDataParams,                 /**< [In] Pointer to this layer's parameter structure. */
		phlnLlcp_Recv_CB_t pfRecv_CB,       /**< [In] Pointer to the callback function */
        void * pContext                     /**< [In] Pointer to the context */
        );
   /**
	* \brief Reset API for Transport layer
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Reset(
        void * pDataParams              /**< [In] Pointer to this layer's parameter structure. */
        );
   
   /**
	* \brief Close all the sockets
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_CloseAll(
        void * pDataParams              /**< [In] Pointer to this layer's parameter structure. */
        );

   /**
	* \brief Get the local node information 
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_SocketGetLocalOptions(
        void * pDataParams,                                     /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t  *pLlcpSocket,              /**< [In] Pointer to socket */
        phlnLlcp_Transport_sSocketOptions_t   *pLocalOptions    /**< [Out] Pointer to local socket options */
        );

   /**
	* \brief Get the local node information 
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_SocketGetRemoteOptions(
        void * pDataParams,                                     /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t  *pLlcpSocket,              /**< [In] Pointer to socket */
        phlnLlcp_Transport_sSocketOptions_t  *psRemoteOptions   /**< [Out] Pointer to remote socket options */
        );

   /**
	* \brief Create a socket on a LLCP-connected device
    *
    * This function creates a socket for a given LLCP link. Sockets can be of two types : 
    * connection-oriented and connectionless. If the socket is connection-oriented, the caller
    * must provide a working buffer to the socket in order to handle incoming data. This buffer
    * must be large enough to fit the receive window (RW * MIU), the remaining space being
    * used as a linear buffer to store incoming data as a stream. Data will be readable later
    * using the phLibNfc_LlcpTransport_Recv function.
    * The options and working buffer are not required if the socket is used as a listening socket,
    * since it cannot be directly used for communication.
    *
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Socket(
        void * pDataParams,                                 /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_eSocketType_t eType,             /**< [In] The socket type. */
        phlnLlcp_Transport_sSocketOptions_t * pOptions,     /**< [In] The options to be used with the socket. */
        phNfc_sData_t * pWorkingBuffer,                     /**< [In] A working buffer to be used by the library. */
        phlnLlcp_Transport_Socket_t ** pLlcpSocket,         /**< [Out] A pointer on the socket to be filled with a socket found on the socket table. */
        phlnLlcp_TransportSocketErrCb_t pErr_Cb,            /**< [In] The callback to be called each time the socket is in error. */
        void * pContext                                     /**< [In] Upper layer context to be returned in the callback */
        );

   /**
	* \brief Close the socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Close(
        void * pDataParams,                             /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket   /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        );

   /**
	* \brief Bind a socket to a local SAP
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Bind(
        void * pDataParams,                             /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,      /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        uint8_t nSap,                                   /**< [In] A port number for a specific socket */
        phNfc_sData_t *psServiceName                    /**< [In] Service name */
        );

   /**
	* \brief Listen for incoming connection requests on a socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Listen(
        void * pDataParams,                                 /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,          /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phlnLlcp_TransportSocketListenCb_t pListen_Cb,      /**< [In] The callback to be called each time the socket receive a connection request. */
        void * pContext                                     /**< [In] Upper layer context to be returned in the callback. */
        );

   /**
	* \brief Accept an incoming connection request for a socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Accept(
        void * pDataParams,                                     /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,              /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phlnLlcp_Transport_sSocketOptions_t * pOptions,         /**< [In] The options to be used with the socket. */
        phNfc_sData_t * psWorkingBuffer,                        /**< [In] A working buffer to be used by the library. */
        phlnLlcp_TransportSocketErrCb_t pErr_Cb,                /**< [In] The callback to be called each time the accepted socket is in error. */
        phlnLlcp_TransportSocketAcceptCb_t pAccept_RspCb,       /**< [In] The callback to be called each time the socket is accepted. */
        void * pContext                                         /**< [In] Upper layer context to be returned in the callback. */    
        );

   /**
	* \brief Reject an incoming connection request for a socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Reject(
        void * pDataParams,                                     /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,              /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phlnLlcp_TransportSocketRejectCb_t pReject_RspCb,       /**< [In] The callback to be call when the Reject operation is completed */
        void * pContext                                         /**< [In] Upper layer context to be returned in the callback. */    
        );

   /**
	* \brief Try to establish connection with a socket on a remote SAP
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Connect(
        void * pDataParams,                                         /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,                  /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        uint8_t nSap,                                               /**< [In] The destination SAP to connect to. */
        phlnLlcp_TransportSocketConnectCb_t   pConnect_RspCb,       /**< [In] The callback to be call when the connection operation is completed */
        void * pContext                                             /**< [In] Upper layer context to be returned in the callback. */    
        );

   /**
	* \brief Try to establish connection with a socket on a remote service, given its URI
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_ConnectByUri(
        void * pDataParams,                                         /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,                  /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phNfc_sData_t * psUri,                                      /**< [In] The URI corresponding to the destination SAP to connect to. */
        phlnLlcp_TransportSocketConnectCb_t   pConnect_RspCb,       /**< [In] The callback to be call when the connection operation is completed */
        void * pContext                                             /**< [In] Upper layer context to be returned in the callback. */    
        );

   /**
	* \brief Disconnect a currently connected socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Disconnect(
        void * pDataParams,                                 /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,          /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phlnLlcp_SocketDisconnectCb_t pDisconnect_RspCb,    /**< [In] The callback to be call when the disconnection operation is completed */
        void * pContext                                     /**< [In] Upper layer context to be returned in the callback. */    
        );

   /**
	* \brief Send data on a socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Send(
        void * pDataParams,                             /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,      /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phNfc_sData_t * pBuffer,                        /**< [In] The buffer containing the data to send. */
        phlnLlcp_TransportSocketSendCb_t pSend_RspCb,   /**< [In] The callback to be call when the send operation is completed */
        void * pContext                                 /**< [In] Upper layer context to be returned in the callback. */    
        );
   
   /**
	* \brief Read data on a socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_Recv(
        void * pDataParams,                             /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,      /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phNfc_sData_t * pBuffer,                        /**< [In] The buffer receiving the data. */
        phlnLlcp_TransportSocketRecvCb_t pRecv_RspCb,   /**< [In] The callback to be call when the receive operation is completed */
        void * pContext                                 /**< [In] Upper layer context to be returned in the callback. */    
        );

    /*****************************************/
    /*           ConnectionLess              */
    /*****************************************/

   /**
	* \brief Send data on a socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_SendTo(
        void * pDataParams,                             /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,      /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        uint8_t nSap,                                   /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phNfc_sData_t * pBuffer,                        /**< [In] The buffer containing the data to send. */
        phlnLlcp_TransportSocketSendCb_t pSend_RspCb,   /**< [In] The callback to be call when the send operation is completed */
        void * pContext                                 /**< [In] Upper layer context to be returned in the callback. */    
        );

   /**
	* \brief Read data on a socket
	* \return Status code
	* \retval #PH_ERR_SUCCESS Operation successful.
	* \retval Other Depending on implementation and underlaying component.
	*/
    phStatus_t phlnLlcp_Transport_RecvFrom(
        void * pDataParams,                             /**< [In] Pointer to this layer's parameter structure. */
        phlnLlcp_Transport_Socket_t * pLlcpSocket,      /**< [In] A pointer to a phlnLlcp_Transport_Socket_t. */
        phNfc_sData_t * pBuffer,                        /**< [In] The buffer receiving the data. */
        phlnLlcp_TransportSocketRecvFromCb_t pRecv_Cb,  /**< [In] The callback to be call when the receive operation is completed */
        void * pContext                                 /**< [In] Upper layer context to be returned in the callback. */    
        );

/** @} */
#endif /* NXPBUILD__PHLN_LLCP */

#ifdef __cplusplus
} /* Extern C */
#endif /* Extern C */

#endif /* PHLNLLCP_H*/