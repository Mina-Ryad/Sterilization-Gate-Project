/*
 * MADC_Private.h
 *
 *  Created on: Nov 22, 2021
 *      Author: Mina-Ryad
 */

#ifndef MCAL_MADC_MADC_PRIVATE_H_
#define MCAL_MADC_MADC_PRIVATE_H_

#define ADMUX *((volatile u8*)0x27)
#define MUX0	PIN0
#define MUX1	PIN1
#define MUX2	PIN2
#define MUX3	PIN3
#define MUX4	PIN4
#define ADLAR	PIN5
#define REFS0	PIN6
#define REFS1	PIN7

#define ADCSRA *((volatile u8*)0x26)
#define ADPS0	PIN0
#define ADPS1	PIN1
#define ADPS2	PIN2
#define ADIE	PIN3
#define ADIF	PIN4
#define ADATE	PIN5
#define ADSC	PIN6
#define ADEN	PIN7

#define ADC *((volatile u16*)0x24)

#define SFIOR *((volatile u8*)0x50)
#define ADTS0	PIN5
#define ADTS1	PIN6
#define ADTS2	PIN7

#define MADC_AVCC_REFERENCE_VOLTAGE		0
#define MADC_2_56_REFERENCE_VOLTAGE		1

#define MADC_BIT_MASKING_PRESCALER 0b11111000
#define MADC_BIT_MASKING_REG_CHANNEL 0b11100000
#define MADC_BIT_MASKING_CHANNEL 0b11111000


#define MADC_LEFT_ADJUST	0
#define MADC_RIGHT_ADJUST	1

#define MADC_2_PRESCALER	0b001
#define MADC_4_PRESCALER	0b010
#define MADC_8_PRESCALER	0b011
#define MADC_16_PRESCALER	0b100
#define MADC_32_PRESCALER	0b101
#define MADC_64_PRESCALER	0b110
#define MADC_128_PRESCALER	0b111

#define MADC_INTERRUPT_DISABLE		0
#define MADC_INTERRUPT_ENABLE		1

#define FREE_RUNNUNG_MODE			0
#define ANALOG_COMPARATOR			1
#define EXTERNAL_INTERRUPT_0		2
#define TIMER_0_CTC					3
#define TIMER_0_OVERFLOW			4
#define TIMER_1_CTC_B				5
#define TIMER_1_OVERFLOW			6
#define TIMER_1_ICU					7

#define MADC_AUTO_TRIGGER_DISABLE 	0
#define MADC_AUTO_TRIGGER_ENABLE	1

#endif /* MCAL_MADC_MADC_PRIVATE_H_ */
