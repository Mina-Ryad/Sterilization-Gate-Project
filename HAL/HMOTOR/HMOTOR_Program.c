/*
 * HMOTOR_Program.c
 *
 *  Created on: Nov 16, 2021
 *      Author: Mina-Ryad
 */


#include "..\..\LIB\LSTD_TYPES.h"

#include "..\..\MCAL\MDIO\MDIO_Config.h"
#include "..\..\MCAL\MDIO\MDIO_Interface.h"
#include "HMOTOR_Config.h"

void HMOTOR_VidInit(void)
{
	MDIO_Error_State_SetPinDirection(RELAY_1_PIN,RELAY_1_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(RELAY_2_PIN,RELAY_2_PORT,PIN_OUTPUT);
}
void HMOTOR_VidForward(void)
{
	MDIO_Error_State_SetPinValue(RELAY_1_PIN,RELAY_1_PORT,PIN_HIGH);
	MDIO_Error_State_SetPinValue(RELAY_2_PIN,RELAY_2_PORT,PIN_LOW);
}

void HMOTOR_VidBackward(void)
{
	MDIO_Error_State_SetPinValue(RELAY_1_PIN,RELAY_1_PORT,PIN_LOW);
	MDIO_Error_State_SetPinValue(RELAY_2_PIN,RELAY_2_PORT,PIN_HIGH);
}

void HMOTOR_VidHold(void)
{
	MDIO_Error_State_SetPinValue(RELAY_1_PIN,RELAY_1_PORT,PIN_LOW);
	MDIO_Error_State_SetPinValue(RELAY_2_PIN,RELAY_2_PORT,PIN_LOW);
}


