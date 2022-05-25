#include "..\..\LIB\LSTD_TYPES.h"
#include "..\..\MCAL\MDIO\MDIO_Interface.h"

#include "HCLCD_Private.h"
#include "HCLCD_Config.h"
#include "HCLCD_Interface.h"

#include "util/delay.h"

/**************************************/
/** Initialize CLCD with 8-Bits Mode **/
/**************************************/
void HCLCD_Vid8Bits_Init(void)
{
	/*LCD Data and Control Port Init*/
	MDIO_Error_State_SetPortDirection(DATA_PORT,PORT_OUTPUT);
	MDIO_Error_State_SetPinDirection(RS,CONTROL_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(RW,CONTROL_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(EN,CONTROL_PORT,PIN_OUTPUT);
	/*wait 30ms*/
	_delay_ms(30);

	/*Send function send command*/
	HCLCD_VidWriteCommand_8Bits(HCLCD_FUNCTION_SET);
	_delay_ms(2);

	/*send Display ON/OFF Command*/
	HCLCD_VidWriteCommand_8Bits(HCLCD_Display_On_Off);
	_delay_ms(2);

	/* Send Clear Display Command*/
	HCLCD_VidWriteCommand_8Bits(DISPLAY_CLEAR);
	_delay_ms(2);

	/*Entry Mode Set Command*/
	HCLCD_VidWriteCommand_8Bits(HCLCD_ENTRY_MODE_SET);
	_delay_ms(2);
}	

/**************************************/
/******* Send Char in 8-Bits Mode *****/
/**************************************/
/** 
	Write data to CG or DD RAM
	--------------------------------------
	RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 1  0 	D7  D6  D5  D4  D3  D2  D1  D0
	--------------------------------------
	Write data into internal RAM (DDRAM/CGRAM). Delay 43us
 **/
void HCLCD_VidWriteChar_8Bits(u8 Copy_u8Data)
{
	/*Select Command Register --> Write one on RS pin */
	MDIO_Error_State_SetPinValue(RS,CONTROL_PORT,PIN_HIGH);

	/*Select write mode --> write zero on RW pin*/
	MDIO_Error_State_SetPinValue(RW,CONTROL_PORT,PIN_LOW);

	/* Send data on port data */
	MDIO_Error_State_SetPortValue(DATA_PORT, Copy_u8Data);

	/* Set Enable High --> Low --> High */
	MDIO_Error_State_SetPinValue(EN,CONTROL_PORT,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN,CONTROL_PORT,PIN_LOW);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN,CONTROL_PORT,PIN_HIGH);
	_delay_ms(2);
}

/**************************************/
/**** Send Command in 8-Bits Mode *****/
/**************************************/
/** Write data to CG or DD RAM
	--------------------------------------
	RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 0  0 	D7  D6 	D5  D4  D3  D2  D1  D0
	--------------------------------------
	Send Command**/
void HCLCD_VidWriteCommand_8Bits(u8 Copy_u8Command)
{
	/*Select Command Register --> Write zero on RS pin */
	MDIO_Error_State_SetPinValue(RS,CONTROL_PORT,PIN_LOW);

	/*select write mode --> write zero on RW pin*/
	MDIO_Error_State_SetPinValue(RW,CONTROL_PORT,PIN_LOW);

	/* Send command on port data */
	MDIO_Error_State_SetPortValue(DATA_PORT, Copy_u8Command);

	/* Set Enable High --> Low --> High */
	MDIO_Error_State_SetPinValue(EN,CONTROL_PORT,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN,CONTROL_PORT,PIN_LOW);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN,CONTROL_PORT,PIN_HIGH);
	_delay_ms(2);
}

/**********************************************/
/** Write Multiple Characters in 8-Bits Mode **/
/**********************************************/
void HCLCD_VidWriteString_8Bits(u8* PCopy_u8String)
{
	u8 LOC_u8StringCounter = 0;
	/* Loop to print until reaching NULL Character*/
	while (PCopy_u8String[LOC_u8StringCounter] != NULL)
	{
		HCLCD_VidWriteChar_8Bits(PCopy_u8String[LOC_u8StringCounter]);
		LOC_u8StringCounter++;
	}
}

/*************************************************/
/** Write Multiple Number on LCD in 8-Bits Mode **/
/*************************************************/
void HCLCD_VidWriteNumber_8Bits(u32 Copy_u32Number)
{
	/* Maximum Digits in u32 is 10 digits */
	u8 LOC_u8ArrayReversedNumber[10];
	u8 LOC_u8NumberCounter=0;
	s8 LOC_s8SendCharLoopCounter;
	/* Check if Number > 0*/
	if(Copy_u32Number>0)
	{
		/* Loop to reverse Number */
		while(Copy_u32Number!=0)
		{
			LOC_u8ArrayReversedNumber[LOC_u8NumberCounter] = (Copy_u32Number%10) ;
			Copy_u32Number/=10;
			LOC_u8NumberCounter++;
		}
		/* Loop to Write Digit by Digit on the CLCD*/
		for(LOC_s8SendCharLoopCounter = LOC_u8NumberCounter - 1 ; LOC_s8SendCharLoopCounter >= 0 ; LOC_s8SendCharLoopCounter--)
		{
			HCLCD_VidWriteChar_8Bits(LOC_u8ArrayReversedNumber[LOC_s8SendCharLoopCounter]+'0');
		}
	}
	/* Check if Number = 0 */
	else
	{
		HCLCD_VidWriteChar_8Bits('0');
	}
}

/****************************/
/** Set Position of Cursor **/
/****************************/
/**
	Set DDRAM Address
	DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 1  AC6 AC5 AC4 AC3 AC2 AC1 AC0
	Set DDRAM address in address Counter. Delay 39 s
 **/
void HCLCD_VidSetPosition_8Bits(u8 Copy_u8LineNumber, u8 Copy_u8PositionNumber)
{
	/* Check if first Line and in range of 16*/
	if((Copy_u8LineNumber==HCLCD_LINE1)&&((Copy_u8PositionNumber>=0)&&(Copy_u8PositionNumber<16)))
	{
		HCLCD_VidWriteCommand_8Bits((LINE1_OFFSET_ADDRESS+Copy_u8PositionNumber));
	}
	/* Check if Second Line and in range of 16*/
	else if((Copy_u8LineNumber==HCLCD_LINE2)&&((Copy_u8PositionNumber>=0)&&(Copy_u8PositionNumber<16)))
	{
		HCLCD_VidWriteCommand_8Bits((LINE2_OFFSET_ADDRESS+Copy_u8PositionNumber));
	}
	else
	{
		/*Do Nothing*/
	}
}

/******************************************************************************************************************************************************/
/******************************************************************************************************************************************************/
/******************************************************************************************************************************************************/



/**************************************/
/** Initialize CLCD with 4-Bits Mode **/
/**************************************/
void HCLCD_vid4Bits_Init(void)
{
	/*Set Data pins as Output*/
	MDIO_Error_State_SetPinDirection(HCLCD_DATA_PIN0, DATA_CONTROL_PORT_4BITS, PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(HCLCD_DATA_PIN1, DATA_CONTROL_PORT_4BITS, PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(HCLCD_DATA_PIN2, DATA_CONTROL_PORT_4BITS, PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(HCLCD_DATA_PIN3, DATA_CONTROL_PORT_4BITS, PIN_OUTPUT);
	/*Set RS as output*/
	MDIO_Error_State_SetPinDirection(RS_4Bits, DATA_CONTROL_PORT_4BITS, PIN_OUTPUT);
	/*Set enable pin as output*/
	MDIO_Error_State_SetPinDirection(EN_4Bits, DATA_CONTROL_PORT_4BITS, PIN_OUTPUT);
	/*wait 30ms*/
	_delay_ms(30);
	MDIO_Error_State_SetPinValue(RS_4Bits , DATA_CONTROL_PORT_4BITS , PIN_LOW);
	MDIO_Error_State_SetNibbleValue( HCLCD_DATA_PIN0, DATA_CONTROL_PORT_4BITS, ( FUNCTION_SET_4BITS_2LINES & 0xF0 ) >> ( 7-HCLCD_DATA_PIN3 ) );
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_LOW);
	_delay_ms(2);
	/*Send function set command*/
	HCLCD_VidWriteCommand_4Bits(FUNCTION_SET_4BITS_2LINES);
	_delay_ms(2);
	/*send Display ON/OFF Command*/
	HCLCD_VidWriteCommand_4Bits(HCLCD_Display_On_Off);
	_delay_ms(2);
	/* Send Clear Display Command*/
	HCLCD_VidWriteCommand_4Bits(DISPLAY_CLEAR);
	_delay_ms(2);
	/*Entry Mode Set Command*/
	HCLCD_VidWriteCommand_4Bits(HCLCD_ENTRY_MODE_SET);
	_delay_ms(2);
}	

/******************************/
/** 4-Bits Mode Send Command **/
/******************************/
void HCLCD_VidWriteCommand_4Bits(u8 Copy_u8Command)
{
	/*Select Command Register --> Write zero on RS pin */
	MDIO_Error_State_SetPinValue(RS_4Bits , DATA_CONTROL_PORT_4BITS , PIN_LOW);
	/* Send Most Significant Nibble command on port data */
	MDIO_Error_State_SetNibbleValue(HCLCD_DATA_PIN0, DATA_CONTROL_PORT_4BITS, (Copy_u8Command & 0xF0)>>(7-HCLCD_DATA_PIN3));
	/* Enable **/
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_LOW);
	_delay_ms(2);
	//MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	//_delay_ms(2);

	MDIO_Error_State_SetPinValue(RS_4Bits , DATA_CONTROL_PORT_4BITS , PIN_LOW);

	/* Send Least Significant Nibble command on port data */
	MDIO_Error_State_SetNibbleValue(HCLCD_DATA_PIN0, DATA_CONTROL_PORT_4BITS, (Copy_u8Command & 0x0F)<<(HCLCD_DATA_PIN0));
	/* Set Enable High --> Low --> High */
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_LOW);
	_delay_ms(2);
	//MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	//_delay_ms(2);
}

/******************************/
/**** 4-Bits Mode Send Data ***/
/******************************/
void HCLCD_VidWriteChar_4Bits(u8 Copy_u8Data)
{
	/*Select Command Register --> Write zero on RS pin */
	MDIO_Error_State_SetPinValue(RS_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	/* Send Most Significant Nibble command on port data */
	MDIO_Error_State_SetNibbleValue( HCLCD_DATA_PIN0, DATA_CONTROL_PORT_4BITS, ( Copy_u8Data&0xF0 ) >> ( 7-HCLCD_DATA_PIN3 ) );
	/* Enable **/
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_LOW);
	_delay_ms(2);
	//MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	//_delay_ms(2);
	MDIO_Error_State_SetPinValue(RS_4Bits , DATA_CONTROL_PORT_4BITS , PIN_HIGH);
	/* Send Least Significant Nibble command on port data */
	MDIO_Error_State_SetNibbleValue(HCLCD_DATA_PIN0, DATA_CONTROL_PORT_4BITS, ( Copy_u8Data&0x0F ) << ( HCLCD_DATA_PIN0 ));
	/* Set Enable High --> Low --> High */
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_LOW);
	_delay_ms(2);
	//MDIO_Error_State_SetPinValue(EN_4Bits,DATA_CONTROL_PORT_4BITS,PIN_HIGH);
	//_delay_ms(2);
}

/**********************************************/
/** Write Multiple Characters in 4-Bits Mode **/
/**********************************************/
void HCLCD_VidWriteString4Bits(u8* PCopy_u8String)
{
	u8 LOC_u8StringCounter = 0;
	/* Loop to print until reaching NULL Character*/
	while (PCopy_u8String[LOC_u8StringCounter] != NULL)
	{
		HCLCD_VidWriteChar_4Bits(PCopy_u8String[LOC_u8StringCounter]);
		LOC_u8StringCounter++;
	}
}

/*************************************************/
/** Write Multiple Number on LCD in 4-Bits Mode **/
/*************************************************/
void HCLCD_VidWriteNumber_4Bits(u32 Copy_u32Number)
{
	/* Maximum Digits in u32 is 10 digits */
	u8 LOC_u8ArrayReversedNumber[10];
	u8 LOC_u8NumberCounter=0;
	s8 LOC_s8SendCharLoopCounter;
	/* Check if Number > 0*/
	if(Copy_u32Number>0)
	{
		/* Loop to reverse Number */
		while(Copy_u32Number!=0)
		{
			LOC_u8ArrayReversedNumber[LOC_u8NumberCounter] = (Copy_u32Number%10) ;
			Copy_u32Number/=10;
			LOC_u8NumberCounter++;
		}
		/* Loop to Write Digit by Digit on the CLCD*/
		for(LOC_s8SendCharLoopCounter = LOC_u8NumberCounter - 1 ; LOC_s8SendCharLoopCounter >= 0 ; LOC_s8SendCharLoopCounter--)
		{
			HCLCD_VidWriteChar_4Bits(LOC_u8ArrayReversedNumber[LOC_s8SendCharLoopCounter]+'0');
		}
	}
	/* Check if Number = 0 */
	else
	{
		HCLCD_VidWriteChar_4Bits('0');
	}
}
