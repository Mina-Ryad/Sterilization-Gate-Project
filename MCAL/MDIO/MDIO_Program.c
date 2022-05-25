#include "..\..\LIB\LSTD_TYPES.h"
#include "..\..\LIB\LBIT_MATH.h"

#include "MDIO_Interface.h"
#include "MDIO_Private.h"

/*****************************/
/**Set Pin Direction Function*/
/*****************************/

Error_State MDIO_Error_State_SetPinDirection(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8PinDirection)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PinNumber>=0)&&(Copy_u8PinNumber<8))
	{
		switch(Copy_u8PortNumber)
		{
			case MDIO_PORTA:
				if(Copy_u8PinDirection==PIN_OUTPUT)
				{
					SET_BIT(DDRA,Copy_u8PinNumber);
				}
				else if(Copy_u8PinDirection==PIN_INPUT)
				{
					CLR_BIT(DDRA,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTB:
				if(Copy_u8PinDirection==PIN_OUTPUT)
				{
					SET_BIT(DDRB,Copy_u8PinNumber);
				}
				else if(Copy_u8PinDirection==PIN_INPUT)
				{
					CLR_BIT(DDRB,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTC:
				if(Copy_u8PinDirection==PIN_OUTPUT)
				{
					SET_BIT(DDRC,Copy_u8PinNumber);
				}
				else if(Copy_u8PinDirection==PIN_INPUT)
				{
					CLR_BIT(DDRC,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTD:
				if(Copy_u8PinDirection==PIN_OUTPUT)
				{
					SET_BIT(DDRD,Copy_u8PinNumber);
				}
				else if(Copy_u8PinDirection==PIN_INPUT)
				{
					CLR_BIT(DDRD,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			default:
				LOC_Error_State_ReturnState=NOK;
				break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	
	return LOC_Error_State_ReturnState;
}

/******************************/
/**Set Port Direction Function*/
/******************************/

Error_State MDIO_Error_State_SetPortDirection(u8 Copy_u8PortNumber,u8 Copy_u8PortDirection)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PortDirection==PORT_OUTPUT)||(Copy_u8PortDirection==PORT_INPUT))
	{
		switch(Copy_u8PortNumber)
		{
			case MDIO_PORTA:
				DDRA=Copy_u8PortDirection;
				break;
			case MDIO_PORTB:
				DDRB=Copy_u8PortDirection;
				break;
			case MDIO_PORTC:
				DDRC=Copy_u8PortDirection;
				break;	
			case MDIO_PORTD:
				DDRD=Copy_u8PortDirection;
				break;	
			default:
				LOC_Error_State_ReturnState=NOK;
				break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	return LOC_Error_State_ReturnState;
}

/*****************************/
/*** Set Pin Value Function***/
/*****************************/

Error_State MDIO_Error_State_SetPinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8PinValue)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PinNumber>=0)&&(Copy_u8PinNumber<8))
	{
		switch(Copy_u8PortNumber)
		{
			case MDIO_PORTA:
				if(Copy_u8PinValue==PIN_HIGH)
				{
					SET_BIT(PORTA,Copy_u8PinNumber);
				}
				else if(Copy_u8PinValue==PIN_LOW)
				{
					CLR_BIT(PORTA,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTB:
				if(Copy_u8PinValue==PIN_HIGH)
				{
					SET_BIT(PORTB,Copy_u8PinNumber);
				}
				else if(Copy_u8PinValue==PIN_LOW)
				{
					CLR_BIT(PORTB,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTC:
				if(Copy_u8PinValue==PIN_HIGH)
				{
					SET_BIT(PORTC,Copy_u8PinNumber);
				}
				else if(Copy_u8PinValue==PIN_LOW)
				{
					CLR_BIT(PORTC,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTD:
				if(Copy_u8PinValue==PIN_HIGH)
				{
					SET_BIT(PORTD,Copy_u8PinNumber);
				}
				else if(Copy_u8PinValue==PIN_LOW)
				{
					CLR_BIT(PORTD,Copy_u8PinNumber);
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			default:
				LOC_Error_State_ReturnState=NOK;
				break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	
	return LOC_Error_State_ReturnState;
}

/**********************************/
/***** Set Port Value Function ****/
/**********************************/

Error_State MDIO_Error_State_SetPortValue(u8 Copy_u8PortNumber, u8 Copy_u8PortValue)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PortValue>=0)&&(Copy_u8PortValue<=255))
	{
		switch(Copy_u8PortNumber)
		{
			case MDIO_PORTA:
					PORTA=Copy_u8PortValue;
				break;
			case MDIO_PORTB:
					PORTB=Copy_u8PortValue;
				break;
			case MDIO_PORTC:
					PORTC=Copy_u8PortValue;
				break;
			case MDIO_PORTD:
					PORTD=Copy_u8PortValue;
				break;
			
			default:
				LOC_Error_State_ReturnState=NOK;
				break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	
	return LOC_Error_State_ReturnState;
}

/**********************************/
/****** Get Pin Value Function ****/
/**********************************/
Error_State MDIO_Error_State_GetPinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8* P_u8PinValue)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PinNumber>=0)&&(Copy_u8PinNumber<8))
	{	
		switch(Copy_u8PortNumber)
		{

			case MDIO_PORTA:
				* P_u8PinValue=GET_BIT(PINA,Copy_u8PinNumber);
				break;
			case MDIO_PORTB:
				* P_u8PinValue=GET_BIT(PINB,Copy_u8PinNumber);
				break;
			case MDIO_PORTC:
				* P_u8PinValue=GET_BIT(PINC,Copy_u8PinNumber);
				break;
			case MDIO_PORTD:
				* P_u8PinValue=GET_BIT(PIND,Copy_u8PinNumber);
				break;
			default:
				LOC_Error_State_ReturnState=NOK;
				break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	return LOC_Error_State_ReturnState;
}

/**********************************/
/**** Toggle Pin Value Function ***/
/**********************************/
Error_State MDIO_Error_State_TogglePinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PinNumber>=0)&&(Copy_u8PinNumber<8))
	{	
		switch(Copy_u8PortNumber)
		{
			case MDIO_PORTA:
				TOGGLE_BIT(PORTA, Copy_u8PinNumber);
				break;
			case MDIO_PORTB:
				TOGGLE_BIT(PORTD, Copy_u8PinNumber);
				break;
			case MDIO_PORTC:
				TOGGLE_BIT(PORTC, Copy_u8PinNumber);
				break;
			case MDIO_PORTD:
				TOGGLE_BIT(PORTD, Copy_u8PinNumber);
				break;
			default:
				LOC_Error_State_ReturnState=NOK;
				break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	return LOC_Error_State_ReturnState;	
}

/*************************************/
/**Activate Pull-Up Resistor Function*/
/*************************************/

void MDIO_Vid_PullUpResistor(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber)
{
	MDIO_Error_State_SetPinDirection(Copy_u8PinNumber,Copy_u8PortNumber,PIN_INPUT);
	MDIO_Error_State_SetPinValue(Copy_u8PinNumber,Copy_u8PortNumber,PIN_HIGH);
}

/**********************************/
/***Set NIBBLE Direction Function**/
/**********************************/
Error_State MDIO_Error_State_SetNibbleDirection(u8 Copy_u8PortNumber, u8 Copy_u8NibbleDirection)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8NibbleDirection==MOST_NIBBLE_OUTPUT)||(Copy_u8NibbleDirection==LEAST_NIBBLE_OUTPUT)||(Copy_u8NibbleDirection==MOST_NIBBLE_INPUT)||(Copy_u8NibbleDirection==LEAST_NIBBLE_HIGH))
	{
		switch(Copy_u8PortNumber)
		{
			case MDIO_PORTA:
				if(Copy_u8NibbleDirection==MOST_NIBBLE_OUTPUT)
				{
					DDRA |= MOST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_OUTPUT)
				{
					DDRA |= LEAST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==MOST_NIBBLE_INPUT)
				{
					DDRA &= MOST_NIBBLE_INPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_HIGH)
				{
					DDRA &= LEAST_NIBBLE_HIGH;
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTB:
				if(Copy_u8NibbleDirection==MOST_NIBBLE_OUTPUT)
				{
					DDRB |= MOST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_OUTPUT)
				{
					DDRB |= LEAST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==MOST_NIBBLE_INPUT)
				{
					DDRB &= MOST_NIBBLE_INPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_HIGH)
				{
					DDRB &= LEAST_NIBBLE_HIGH;
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTC:
				if(Copy_u8NibbleDirection==MOST_NIBBLE_OUTPUT)
				{
					DDRC |= MOST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_OUTPUT)
				{
					DDRC |= LEAST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==MOST_NIBBLE_INPUT)
				{
					DDRC &= MOST_NIBBLE_INPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_HIGH)
				{
					DDRC &= LEAST_NIBBLE_HIGH;
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;
			case MDIO_PORTD:
				if(Copy_u8NibbleDirection==MOST_NIBBLE_OUTPUT)
				{
					DDRD |= MOST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_OUTPUT)
				{
					DDRD |= LEAST_NIBBLE_OUTPUT;
				}
				else if(Copy_u8NibbleDirection==MOST_NIBBLE_INPUT)
				{
					DDRD &= MOST_NIBBLE_INPUT;
				}
				else if(Copy_u8NibbleDirection==LEAST_NIBBLE_HIGH)
				{
					DDRD &= LEAST_NIBBLE_HIGH;
				}
				else
				{
					LOC_Error_State_ReturnState=NOK;
				}
				break;	
			default:
				LOC_Error_State_ReturnState=NOK;
				break;
		}	
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	return LOC_Error_State_ReturnState;	
}

/*****************************************************/
/**** Set Most Segnificant Nibble Values Function ***/
/***************************************************/
void MDIO_Error_State_SetMostSignificantNibbleValues(u8 Copy_u8PortNumber, u8 Copy_u8NibbleValues)
{
	switch(Copy_u8PortNumber)
	{
		case MDIO_PORTA:
			PORTA = (PORTA & MOST_NIBBLE_LOW) | (Copy_u8NibbleValues & (MOST_NIBBLE_HIGH));
			break;
		case MDIO_PORTB:
			PORTB = (PORTB & MOST_NIBBLE_LOW) | (Copy_u8NibbleValues & (MOST_NIBBLE_HIGH));
			break;
		case MDIO_PORTC:
			PORTC = (PORTC & MOST_NIBBLE_LOW) | (Copy_u8NibbleValues & (MOST_NIBBLE_HIGH));
			break;
		case MDIO_PORTD:
			PORTD = (PORTD & MOST_NIBBLE_LOW) | (Copy_u8NibbleValues & (MOST_NIBBLE_HIGH));
			break;	
		default:
			break;
	}	
}

/*****************************************************/
/**** Set Least Significant Nibble Values Function ***/
/*****************************************************/
void MDIO_Error_State_SetLeastSignificantNibbleValues(u8 Copy_u8PortNumber, u8 Copy_u8NibbleValues)
{
	switch(Copy_u8PortNumber)
	{
		case MDIO_PORTA:
			PORTA = (PORTA & LEAST_NIBBLE_LOW) | (Copy_u8NibbleValues & (LEAST_NIBBLE_HIGH));
			break;
		case MDIO_PORTB:
			PORTB = (PORTB & LEAST_NIBBLE_LOW) | (Copy_u8NibbleValues & (LEAST_NIBBLE_HIGH));
			break;
		case MDIO_PORTC:
			PORTC = (PORTC & LEAST_NIBBLE_LOW) | (Copy_u8NibbleValues & (LEAST_NIBBLE_HIGH));
			break;
		case MDIO_PORTD:
			PORTD = (PORTD & LEAST_NIBBLE_LOW) | (Copy_u8NibbleValues & (LEAST_NIBBLE_HIGH));
			break;	
		default:
			break;
	}	
}

/*****************************************************/
/****** Set Any Nibble Values Function ************/
/*****************************************************/
Error_State MDIO_Error_State_SetNibbleValue(u8 copy_u8PinStart, u8 Copy_u8PortNumber, u8 Copy_u8NibbleValues)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if(copy_u8PinStart<=4)
	{
		switch(Copy_u8PortNumber)
		{
			case MDIO_PORTA:
				PORTA &= ~(LEAST_NIBBLE_HIGH<<copy_u8PinStart);
				PORTA |= Copy_u8NibbleValues;
				break;
			case MDIO_PORTB:
				PORTB &= ~(LEAST_NIBBLE_HIGH<<copy_u8PinStart);
				PORTB |= Copy_u8NibbleValues;
				break;
			case MDIO_PORTC:
				PORTC &= ~(LEAST_NIBBLE_HIGH<<copy_u8PinStart);
				PORTC |= Copy_u8NibbleValues;
				break;
			case MDIO_PORTD:
				PORTD &= ~(LEAST_NIBBLE_HIGH<<copy_u8PinStart);
				PORTD|= Copy_u8NibbleValues;
				break;	
			default:
				break;
		}	
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	return LOC_Error_State_ReturnState;
}
