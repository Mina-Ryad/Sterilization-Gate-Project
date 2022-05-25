/*
 * MUSART_Program.c
 *
 *  Created on: Nov 25, 2021
 *      Author: gerges
 */

#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\LIB\LBIT_MATH.h"

#include"MUSART_Private.h"
#include"MUSART_Config.h"

void (*MUSART_CallBack)(void);

/*USART Initialization*/
void MUSART_VidInit(void)
{
	u8 LOC_u8Copy_UCSRC=0;
	/*Select USART Mode*/
#if USART_SET_MODE==USART_ASYNCHRONOUS_MODE
	CLR_BIT(LOC_u8Copy_UCSRC,6);
#elif USART_SET_MODE==USART_SYNCHRONOUS_MODE
	SET_BIT(LOC_u8Copy_UCSRC,6);
#else
#error"USART Mode Is not valid..."
#endif
	/*Parity Mode*/
#if USART_SET_PARITY_MODE==USART_DISABLED_PARITY
	CLR_BIT(LOC_u8Copy_UCSRC,5);
	CLR_BIT(LOC_u8Copy_UCSRC,4);
#elif USART_SET_PARITY_MODE==USART_EVEN_PARITY
	SET_BIT(LOC_u8Copy_UCSRC,5);
	CLR_BIT(LOC_u8Copy_UCSRC,4);
#elif USART_SET_PARITY_MODE==USART_ODD_PARITY
	SET_BIT(LOC_u8Copy_UCSRC,5);
	SET_BIT(LOC_u8Copy_UCSRC,4);
#else
#error"USART Parity Mode Is not valid..."
#endif
	/*Select Stop Bit*/
#if USART_SET_STOP_BIT==USART_STOP_ONE_BIT
	CLR_BIT(LOC_u8Copy_UCSRC,3);
#elif USART_SET_STOP_BIT==USART_STOP_TWO_BIT
	SET_BIT(LOC_u8Copy_UCSRC,3);
#else
#error "USART Stop Bit Number Is not valid..."
#endif
	/*Select Char Size */
#if USART_SET_CHR_SIZE==USART_CHR_SIZE_5
	CLR_BIT(LOC_u8Copy_UCSRC,2);
	CLR_BIT(LOC_u8Copy_UCSRC,1);
	CLR_BIT(UCSRB,2);
#elif USART_SET_CHR_SIZE==USART_CHR_SIZE_6
	CLR_BIT(LOC_u8Copy_UCSRC,2);
	SET_BIT(LOC_u8Copy_UCSRC,1);
	CLR_BIT(UCSRB,2);
#elif USART_SET_CHR_SIZE==USART_CHR_SIZE_7
	SET_BIT(LOC_u8Copy_UCSRC,2);
	CLR_BIT(LOC_u8Copy_UCSRC,1);
	CLR_BIT(UCSRB,2);
#elif USART_SET_CHR_SIZE==USART_CHR_SIZE_8
	SET_BIT(LOC_u8Copy_UCSRC,2);
	SET_BIT(LOC_u8Copy_UCSRC,1);
	CLR_BIT(UCSRB,2);
#elif USART_SET_CHR_SIZE==USART_CHR_SIZE_9
	SET_BIT(LOC_u8Copy_UCSRC,2);
	SET_BIT(LOC_u8Copy_UCSRC,1);
	SET_BIT(UCSRB,2);
#else
#error"USART CHR SIZE Is not valid..."
#endif
	/*Set LOC_u8Copy_UCSRC Value in UCSRC Register and select UCSRC Register*/
	SET_BIT(LOC_u8Copy_UCSRC,7);
	UCSRC=LOC_u8Copy_UCSRC;
	/*Set BuadRate -->9600*/
	UBRRL=51;
	/*Enable To TX and RX*/
	SET_BIT(UCSRB,4);
	SET_BIT(UCSRB,3);
}
/*USART Send Data*/
void MUSART_VidSendChar(u8 Copy_u8Data)
{
	/*Wait until Register Empty Flag is set*/
	while(GET_BIT(UCSRA,5)==0);
	UDR=Copy_u8Data;
}
/*USART Receive Data*/
u8 MUSART_u8ReceiveData(void)
{
	/*Wait until Receive Complete Flag is set*/
	//while(GET_BIT(UCSRA,7)==0);
	return UDR;
}
void MUSART_VidSendString(u8 *Copy_u8Data)
{
	u8 LOC_CharCount=0;
	while(Copy_u8Data[LOC_CharCount]!=NULL)
	{
		MUSART_VidSendChar(Copy_u8Data[LOC_CharCount]);
		LOC_CharCount++;
	}
}
void MUSART_VidReceiveString(u8 *Copy_u8Data)
{
	u8 LOC_CharCount=0;
	while(1)
	{
		Copy_u8Data[LOC_CharCount]=MUSART_u8ReceiveData();
		if(Copy_u8Data[LOC_CharCount]=='\t')
		{
			break;
		}
		LOC_CharCount++;
	}

}
void MUSART_VidUSART_Receive_Interrupt_Enable(void)
{
	SET_BIT(UCSRB,7);
}
void MUSART_VidSetCallBack(void (*Copy_pFun)(void))
{
	MUSART_CallBack=Copy_pFun;
}
void __vector_13(void)
{
	MUSART_CallBack();
}
