/*
 * MADC_Interface.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Mina-Ryad
 */

#ifndef MCAL_MADC_MADC_INTERFACE_H_
#define MCAL_MADC_MADC_INTERFACE_H_

/*ADC Initialization*/
void MADC_VidInit(void);

/*ADC Start Conversion ---> Polling, Return ADC Value*/
u16 MADC_u16ADCStartConversion(u8 Copy_u8Channel);

/**/
void MADC_VidADC_SetCallBack(void(*Copy_VidCallBack)(void));

u16 MADC_VidADC_ReturnADC(void);

void MADC_u16ADCStartConversion_ISR(u8 Copy_u8Channel);

#endif /* MCAL_MADC_MADC_INTERFACE_H_ */
