/*
 * MTIMER_Program.c
 *
 *  Created on: Nov 18, 2021
 *      Author: Mina-Ryad
 */


#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBIT_MATH.h"
#include "TIMER0_Config.h"
#include "TIMER0_Private.h"
#include "TIMER0_Interface.h"

/*-----------------------------------------------------------------------------------*/
/*-------------------------------------- TIMER 0 ------------------------------------*/
/*-----------------------------------------------------------------------------------*/

/*Pointer to Function Declaration (Call Back Function Pointer)*/
void (*TIMER0_CallBack)(void);

/*ISR CTC Interrupt Declaration */
void __vector_10(void) __attribute__((signal));

/*ISR OverFlow Interrupt Declaration */
void __vector_11(void) __attribute__((signal));

/*******************************/
/*** Timer 0 Initialization ****/
/*******************************/
void TIMER0_VidInit(void)
{
	/*Select Prescaling */
	TCCR0 &= TIMER_CLOCK_SELECT_MASK;
	TCCR0 |= TIMER0_SET_PRESCALER;

/* Waveform Generation Mode Bit Description
 * -------------------------------------------------------------------------------------------------
 * WGM01  WGM00 Timer/Counter Mode of Operation--TOP-----Update of OCR0--TOV0 Flag Set-on
 * -------------------------------------------------------------------------------------------------
 *   0       0        Normal                     0xFF     Immediate           MAX
 *   0       1        PWM, Phase Correct         0xFF     TOP                BOTTOM
 *   1       0        CTC                        OCR0     Immediate           MAX
 *   1       1        Fast PWM                   0xFF     TOP                 MAX
*/

#if TIMER0_SET_MODE == TIMER0_NORMAL_MODE
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
#elif TIMER0_SET_MODE == TIMER0_PWM_PAHSE_CORRECT_MODE
	SET_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
#elif TIMER0_SET_MODE == TIMER0_CTC_MODE
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
#elif TIMER0_SET_MODE == TIMER0_FAST_PWM_MODE
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
#else
	#error "Timer0 Mode is Not Valid..."
#endif

/* Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable
 * When the TOIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
 * Timer/Counter0 Overflow interrupt is enabled. The corresponding interrupt is executed if
 * an overflow in Timer/Counter0 occurs, i.e., when the TOV0 bit is set in the
 * Timer/Counter Interrupt Flag Register – TIFR.
* */
#if TIMER0_SET_OVERFLOW_INTERRUPT == TIMER0_SET_OVERFLOW_INTERRUPT_ENABELED
	SET_BIT(TIMSK,TOIE0);
#elif TIMER0_SET_OVERFLOW_INTERRUPT == TIMER0_SET_OVERFLOW_INTERRUPT_DISABLED
	CLR_BIT(TIMSK,TOIE0);
#else
	#error "Timer0 Set OverFlow Interrupt is Not Valid..."
#endif

/*	Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
 * --------------------------------------------------------------------
 * When the OCIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
 * Timer/Counter0 Compare Match interrupt is enabled. The corresponding interrupt is
 * executed if a compare match in Timer/Counter0 occurs,
 */
#if TIMER0_SET_CTC_INTERRUPT == TIMER0_SET_CTC_INTERRUPT_ENABELED
	SET_BIT(TIMSK,OCIE0);
#elif TIMER0_SET_CTC_INTERRUPT == TIMER0_SET_CTC_INTERRUPT_DISABLED
	CLR_BIT(TIMSK,OCIE0);
#else
	#error "Timer0 Set CTC Interrupt is Not Valid..."
#endif

/* Compare Output Mode, non-PWM Mode
	COM01 COM00 Description
	  0     0       Normal port operation, OC0 disconnected.
	  0     1       Toggle OC0 on compare match
	  1     0       Clear OC0 on compare match
	  1     1       Set OC0 on compare match
*/
#if TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_DISCONNECTED
	CLR_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_TOGGLE
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_SET
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_CLR
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
#else
	#error "TIMER0 CTC OC0 Mode is not valid..."
#endif
}

/*******************************/
/*** Set Preload Function ******/
/*******************************/
void TIMER0_VidSetPreload(u8 Copy_u8Preload)
{
	TCNT0 = Copy_u8Preload;
}

/*********************************/
/*** Set CTC Value Function ******/
/*********************************/
void TIMER0_VidSetCTCValue(u8 Copy_u8SetCTCValue)
{
	OCR0 = Copy_u8SetCTCValue;
}

/***************************************************/
/**CTC ISR passing address of Application Function**/
/***************************************************/
void TIMER0_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack = Copy_VidCallBack;
}

/********************************************************/
/**OverFlow ISR passing address of Application Function**/
/********************************************************/
void TIMER0_VidOverFlow_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack = Copy_VidCallBack;
}

/*******************************/
/**ISR CTC Interrupt Function **/
/*******************************/
void __vector_10(void)
{
	TIMER0_CallBack();
}

/************************************/
/**ISR OverFlow Interrupt Function **/
/************************************/
void __vector_11(void)
{
	TIMER0_CallBack();
}

