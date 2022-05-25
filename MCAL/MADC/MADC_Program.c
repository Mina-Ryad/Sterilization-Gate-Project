/*
 * MADC_Program.c
 *
 *  Created on: Nov 22, 2021
 *      Author: Mina-Ryad
 */


#include "..\..\LIB\LSTD_TYPES.h"
#include "..\..\LIB\LBIT_MATH.h"

#include "MADC_Private.h"
#include "MADC_Config.h"
#include "..\MDIO\MDIO_Interface.h"

/*Pointer to Function Declaration (Call Back Function Pointer)*/
void (*MADC_CallBack)(void);

/*ISR ADC Interrupt Declaration */
void __vector_16(void) __attribute__((signal));



/*ADC Initialization*/
void MADC_VidInit(void)
{
	/*Select Vref*/
	/* REFS1 REFS0 Voltage Reference Selection
	 *   0     0   AREF, Internal Vref turned off
	 *   0     1   AVCC with external capacitor at AREF pin
	 *   1     0   Reserved
	 *   1     1   Internal 2.56V Voltage Reference with external capacitor at AREF pin
	*/
	#if MADC_SET_REFERANCE_VOLTAGE == MADC_AVCC_REFERENCE_VOLTAGE
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
	#elif MADC_SET_REFERANCE_VOLTAGE == MADC_2_56_REFERENCE_VOLTAGE
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	#else
		#error"ADC Reference Voltage Option is Not Valid...."
	#endif

	/*Set Prescaler*/
	/* ADC Prescaler Selections
	 * ADPS2 ADPS1 ADPS0 --- Division Factor
	 *   0     0     1          2
	 *   0     1     0          4
	 *   0     1     1          8
	 *   1     0     0          16
	 *   1     0     1          32
	 *   1     1     0          64
	 *   1     1     1          128
	*/
	ADCSRA &= MADC_BIT_MASKING_PRESCALER ;
	ADCSRA |= MADC_SET_PRESCALER ;

	/*ADLAR: ADC Left Adjust Result*/
	#if MADC_SET_ADJUST == MADC_LEFT_ADJUST
		SET_BIT(ADMUX,ADLAR);
	#elif MADC_SET_ADJUST == MADC_RIGHT_ADJUST
		CLR_BIT(ADMUX,ADLAR);
	#else
		#error "ADC Precaler is not Vaild...."
	#endif

	/* ADIE: ADC Interrupt Enable
	 * When this bit is written to one and the I-bit in SREG is set, the ADC Conversion Complete
	 * Interrupt is activated.
	 * */
	#if MADC_INTERRUPT == MADC_INTERRUPT_ENABLE
		SET_BIT(ADCSRA,ADIE);
	#elif MADC_INTERRUPT == MADC_INTERRUPT_DISABLE
		CLR_BIT(ADCSRA,ADIE);
	#else
		#error "ADC Precaler is not Vaild...."
	#endif

	/*ADC Auto Trigger Enable*/
	/*ADATE: ADC Auto Trigger Enable*/
	#if MADC_AUTO_TRIGGER == MADC_AUTO_TRIGGER_ENABLE
		SET_BIT(ADCSRA,ADATE);
	#elif MADC_AUTO_TRIGGER == MADC_AUTO_TRIGGER_DISABLE
		CLR_BIT(ADCSRA,ADATE);
	#else
		#error "ADC Precaler is not Vaild...."
	#endif

	/*ADC Auto Trigger Source Selections
	ADTS2 ADTS1 ADTS0 Trigger Source
	   0    0     0   Free Running mode
	   0    0     1   Analog Comparator
	   0    1     0   External Interrupt Request 0
	   0    1     1   Timer/Counter0 Compare Match
	   1    0     0   Timer/Counter0 Overflow
	   1    0     1   Timer/Counter Compare Match B
	   1    1     0   Timer/Counter1 Overflow
	   1    1     1   Timer/Counter1 Capture Event
	 */
	CLR_BIT(SFIOR,ADTS0);
	CLR_BIT(SFIOR,ADTS1);
	CLR_BIT(SFIOR,ADTS2);

	/*Enable to ADC*/
	/*ADEN: ADC Enable
	 * Writing this bit to one enables the ADC. By writing it to zero, the ADC is turned off. Turning
	 * the ADC off while a conversion is in progress, will terminate this conversion.
	*/
	SET_BIT(ADCSRA,ADEN);
}

/*ADC Start Conversion ---> Polling, Return ADC Value*/
u16 MADC_u16ADCStartConversion(u8 Copy_u8Channel)
{
	/*Select Channel*/
	Copy_u8Channel &= MADC_BIT_MASKING_CHANNEL ;
	ADMUX &= MADC_BIT_MASKING_REG_CHANNEL ;
	ADMUX |= Copy_u8Channel;
	/*ADC Start Conversion*/
	SET_BIT(ADCSRA,6);
	/*Wait on ADC Conversion Completed Flag is set to one*/
	while (GET_BIT (ADCSRA,4)==0);
	return ADC;
}

/**********************/
/*ADC Start Conversion*/
/**********************/
void MADC_u16ADCStartConversion_ISR(u8 Copy_u8Channel)
{
	/*Select Channel*/
	Copy_u8Channel &= ~MADC_BIT_MASKING_CHANNEL;
	ADMUX &= MADC_BIT_MASKING_REG_CHANNEL;
	ADMUX |= Copy_u8Channel;

	/*ADSC: ADC Start Conversion*/
	SET_BIT(ADCSRA,ADSC);
}

/**********************/
/** ADC Value Return **/
/**********************/
u16 MADC_VidADC_ReturnADC(void)
{
	return ADC;
}

/************************************************/
/** ADC passing address of Application Function**/
/************************************************/
void MADC_VidADC_SetCallBack(void(*Copy_VidCallBack)(void))
{
	MADC_CallBack = Copy_VidCallBack;
}

/*******************************/
/**ISR ADC Interrupt Function **/
/*******************************/
void __vector_16(void)
{
	MADC_CallBack();
}



