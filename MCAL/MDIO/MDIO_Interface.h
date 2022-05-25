#ifndef _MDIO_INTERFACE_H_
#define _MDIO_INTERFACE_H_

#define MDIO_PORTA 0
#define MDIO_PORTB 1
#define MDIO_PORTC 2
#define MDIO_PORTD 3

#define PIN_OUTPUT 1
#define PIN_INPUT 0

#define PORT_OUTPUT 0xFF
#define PORT_INPUT 0

#define PIN_HIGH 1
#define PIN_LOW 0

#define PORT_HIGH 1
#define PORT_LOW 0

#define MOST_NIBBLE_OUTPUT 0b11110000
#define MOST_NIBBLE_INPUT 0b00001111

#define LEAST_NIBBLE_OUTPUT 0b00001111
#define LEAST_NIBBLE_INPUT 0b11110000

#define MOST_NIBBLE_HIGH 0b11110000
#define MOST_NIBBLE_LOW 0b00001111

#define LEAST_NIBBLE_HIGH 0b00001111
#define LEAST_NIBBLE_LOW 0b11110000

typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7	
}E_Pin_t;

/*Set Pin Direction Function*/
Error_State MDIO_Error_State_SetPinDirection(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8PinDirection);

/*Set Port Direction Function*/
Error_State MDIO_Error_State_SetPortDirection(u8 Copy_u8PortNumber, u8 Copy_u8PortDirection);

/*Set Pin Value Function*/
Error_State MDIO_Error_State_SetPinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8 Copy_u8PinValue);

/*Toggle Pin Value Function*/
Error_State MDIO_Error_State_TogglePinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber);

/*Set Port Value Function*/
Error_State MDIO_Error_State_SetPortValue(u8 Copy_u8PortNumber, u8 Copy_u8PortValue);

/*Get Pin Value Function*/
Error_State MDIO_Error_State_GetPinValue(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber, u8* P_u8PinValue);

/*Active Pull-Up Resistor Function*/
void MDIO_Vid_PullUpResistor(u8 Copy_u8PinNumber, u8 Copy_u8PortNumber);

/*Set Nibble Direction Function*/
Error_State MDIO_Error_State_SetNibbleDirection(u8 Copy_u8PortNumber, u8 Copy_u8NibbleDirection);

/*Set Most Significant Nibble Values Function*/
void MDIO_Error_State_SetMostSignificantNibbleValues(u8 Copy_u8PortNumber, u8 Copy_u8NibbleValues);

/*Set Least Significant Nibble Values Function*/
void MDIO_Error_State_SetLeastSignificantNibbleValues(u8 Copy_u8PortNumber, u8 Copy_u8NibbleValues);

Error_State MDIO_Error_State_SetNibbleValue(u8 copy_u8PinStart, u8 Copy_u8PortNumber, u8 Copy_u8NibbleValues);


#endif
