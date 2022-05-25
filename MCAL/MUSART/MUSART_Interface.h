/*
 * MUSART_Interface.h
 *
 *  Created on: Nov 25, 2021
 *      Author: gerges
 */

#ifndef MCAL_MUSART_MUSART_INTERFACE_H_
#define MCAL_MUSART_MUSART_INTERFACE_H_

/*USART Initialization*/
void MUSART_VidInit(void);
/*USART Send Data*/
void MUSART_VidSendChar(u8 Copy_u8Data);
/*USART Receive Data*/
u8 MUSART_u8ReceiveData(void);
void MUSART_VidSendString(u8 *Copy_u8Data);
void MUSART_VidReceiveString(u8 *Copy_u8Data);
void MUSART_VidSetCallBack(void (*Copy_pFun)(void));
void MUSART_VidUSART_Receive_Interrupt_Enable(void);

#endif /* MCAL_MUSART_MUSART_INTERFACE_H_ */
