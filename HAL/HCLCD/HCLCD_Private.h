#ifndef HCLCD_PRIVATE_H_
#define HCLCD_PRIVATE_H_

/**
	Function Set
	-------------------------------
	DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 0   0   1  DL   N   F   -   -
	------------------------------- 
	DL: Sets interface data length. Data is sent or received in 8-bit length (DB7 ~ DB0) when 
	DL = 1, and in 4-bit length (DB7 ~ DB4) when DL = 0. When the 4-bit length is
	selected, data must be sent or received twice.
	-----------------------------------------------------------------------------------------
	N: Sets the number of lines
	N = 0 : 1 line display (1/8 duty)
	N = 1 : 2 line display (1/16 duty)
	-----------------------------------------------------------------------------------------
	F: Sets character font.
	F = 0 : 5 x 7 dots
	F = 1 : 5 x 10 dots
**/
/*Function Set Modes----------------------001DNF00*/
#define FUNCTION_SET_8BITS_2LINES       0b00111000
#define FUNCTION_SET_8BITS_1LINES       0b00110100
#define FUNCTION_SET_4BITS_2LINES       0b00101000
#define FUNCTION_SET_4BITS_1LINES       0b00100100


/**
	Display ON/OFF Control
	-------------------------------
	DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 0   0   0   0   1   D   C   B
	-------------------------------
	D: The entire display is ON when D = 1 and OFF when D = 0. The display data remains in
	the DD RAM when display is OFF, it can be displayed immediately by setting D = 1.
	--------------------------------------------------------------------------------------
	C: The cursor displays when C = 1 and does not display when C = 0. The cursor is
	displayed on the 8th line when 5x7 dots character font has been selected.
	--------------------------------------------------------------------------------------
	B: The character indicated by the cursor blinks when B = 1. The blink is displayed by
	switching between all “High” data and display characters at 0.4 sec intervals.
	The cursor and the blink can be set to display simultaneously.
	When B = 0, the blink is off.
**/
/*Display ON/OFF Modes----------------------------00001DCB*/
#define DISPLAY_ON_CURSOR_ON_BLINKING_ON        0b00001111
#define DISPLAY_ON_CURSOR_ON_BLINKING_OFF       0b00001110
#define DISPLAY_ON_CURSOR_OFF                   0b00001100
#define DISPLAY_OFF                             0b00001000

/**
	Entry Mode Set
	-------------------------------
	DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 0   0   0   0   0   1  I/D SH
	-------------------------------
	I/D: Increases (I/D = 1) or decreases (ID = 0) the DD RAM address by 1 when a character
	code is written into or read from the DD RAM.
	The cursor or blink moves to the right when increased by 1 and to the left when
	decreased by 1. The same applies to writing and reading the CG RAM.
	-----------------------------------------------------------------------------------------
	S: Shifts the entire display when S = 1; shifts to the left when I/D = 1 and to the right
	when I/D = 0. Thus it looks as if the cursor stands still and only the display seems to
	move. The display does not shift when reading from DD RAM or writing/reading
	into/from CG RAM.
	When S = 0, the display does not shift.
**/
/*HCLCD Entry Mode Set Options----------------------000001IS*/
#define ENTRY_MODE_SET_INCREASE_WITH_SHIFT        0b00000111
#define ENTRY_MODE_SET_INCREASE                   0b00000110
#define ENTRY_MODE_SET_DECREASE_WITH_SHIFT        0b00000101
#define ENTRY_MODE_SET_DECREASE                   0b00000100

/**
	Set DDRAM Address
	DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 1  AC6 AC5 AC4 AC3 AC2 AC1 AC0
	Set DDRAM address in address Counter. Delay 39 s
**/
/* First Line = First Address (DB7 = 1 --> Decimel = 128) */
#define LINE1_OFFSET_ADDRESS    0b10000000
/* Secind Line = First Line + 64 (DB7 = 1 --> Decimel = 128 + 64 = 192)*/
#define LINE2_OFFSET_ADDRESS    0b11000000

#endif
