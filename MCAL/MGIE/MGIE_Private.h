/*
 * MGIE_Private.h
 *
 *  Created on: Nov 15, 2021
 *      Author: Mina-Ryad
 */

#ifndef MCAL_MGIE_MGIE_PRIVATE_H_
#define MCAL_MGIE_MGIE_PRIVATE_H_


/*Status Register*/
#define SREG  *((volatile u8*)0x5F)

/*I: Global Interrupt Enable*/
#define I_SREG  PIN7

#endif /* MCAL_MGIE_MGIE_PRIVATE_H_ */
