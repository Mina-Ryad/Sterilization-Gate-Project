/*
 * MTIMER_Private.h
 *
 *  Created on: Nov 18, 2021
 *      Author: Mina-Ryad
 */

#ifndef _TIMER0_PRIVATE_H_
#define _TIMER0_PRIVATE_H_

/*-----------------------------------------------------------------------------------*/
/*-------------------------------------- TIMER 0 ------------------------------------*/
/*-----------------------------------------------------------------------------------*/

/** Timer/Counter Control Register **/
/** ------------------------------ **/
#define TCCR0 *((volatile u8*)0x53)
#define WGM00 BIT6
#define WGM01 BIT3
#define COM00 BIT4
#define COM01 BIT5

/* Timer/Counter Interrupt Mask Register
 * -------------------------------------
 * • Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
 * When the OCIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
 * Timer/Counter0 Compare Match interrupt is enabled. The corresponding interrupt is
 * executed if a compare match in Timer/Counter0 occurs, i.e., when the OCF0 bit is set in
 * the Timer/Counter Interrupt Flag Register – TIFR.
 * ----------------------------------------------------------------------------------------------
 * • Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable
 * When the TOIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
 * Timer/Counter0 Overflow interrupt is enabled. The corresponding interrupt is executed if
 * an overflow in Timer/Counter0 occurs, i.e., when the TOV0 bit is set in the
 * Timer/Counter Interrupt Flag Register – TIFR.
 * */
#define TIMSK *((volatile u8*)0x59)
#define TOIE0 BIT0
#define OCIE0 BIT1

/* Timer/Counter Register
 * ----------------------
 * The Timer/Counter Register gives direct access, both for read and write operations, to
 * the Timer/Counter unit 8-bit counter. Writing to the TCNT0 Register blocks (removes)
 * the compare match on the following timer clock. Modifying the counter (TCNT0) while
 * the counter is running, introduces a risk of missing a compare match between TCNT0
 * and the OCR0 Register.
 * */
#define TCNT0 *((volatile u8*)0x52)

/* Output Compare Register
 * -----------------------
 * The Output Compare Register contains an 8-bit value that is continuously compared
 * with the counter value (TCNT0). A match can be used to generate an output compare
 * interrupt, or to generate a waveform output on the OC0 pin.
 * */
#define OCR0  *((volatile u8*)0x5C)

/*	Clock Select
 *  Bit 2:0 – CS02:0:
 *  The three Clock Select bits select the clock source to be used by the Timer/Counter.
 *  Table 42. Clock Select Bit Description
 *  CS02 CS01 CS00 Description
 *    0    0    0         No clock source (Timer/Counter stopped).
 *    0    0    1         clkI/O/(No prescaling)
 *    0    1    0         clkI/O/8 (From prescaler)
 *    0    1    1         clkI/O/64 (From prescaler)
 *    1    0    0         clkI/O/256 (From prescaler)
 *    1    0    1         clkI/O/1024 (From prescaler)
 *    1    1    0         External clock source on T0 pin. Clock on falling edge.
 *    1    1    1         External clock source on T0 pin. Clock on rising edge.
*/
#define TIMER_STOPPED       	 0b000
#define TIMER_NO_PRESCALER  	 0b001
#define TIMER_8_PRESCALER   	 0b010
#define TIMER_64_PRESCALER  	 0b011
#define TIMER_256_PRESCALER 	 0b100
#define TIMER_1024_PRESCALER 	 0b101
#define TIMER_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE  0b110
#define TIMER_EXTERNAL_CLOCK_SOURCE_RISING_EDGE   0b111
#define TIMER_CLOCK_SELECT_MASK  0b11111000

/* Timer 0 Modes Selection*/
#define TIMER0_NORMAL_MODE				0
#define TIMER0_PWM_PAHSE_CORRECT_MODE	1
#define TIMER0_CTC_MODE					2
#define TIMER0_FAST_PWM_MODE			3

/*Timer 0 CTC 0C0 Pin Selection*/
#define TIMER0_OC0_PIN_DISCONNECTED		0
#define TIMER0_OC0_PIN_TOGGLE			1
#define TIMER0_OC0_PIN_SET				2
#define TIMER0_OC0_PIN_CLR				3

/*Timer 0 CTC Interrupt Selection*/
#define TIMER0_SET_CTC_INTERRUPT_ENABELED	0
#define TIMER0_SET_CTC_INTERRUPT_DISABLED	1

/*Timer 0 OverFlow Interrupt Selection*/
#define  TIMER0_SET_OVERFLOW_INTERRUPT_ENABELED 0
#define  TIMER0_SET_OVERFLOW_INTERRUPT_DISABLED 1

#endif /* MCAL_MTIMER_MTIMER_PRIVATE_H_ */
