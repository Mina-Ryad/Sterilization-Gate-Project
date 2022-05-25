#ifndef HCLCD_INTERFACE_H_
#define HCLCD_INTERFACE_H_

/** 
	Clear Display
	-------------------------------
	DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	 0   0   0   0   0   0   0   1
	-------------------------------
	Clears entire display and sets DDRAM address to 00H. Dealy 1.53ms 
**/
/* Clear Display */
#define DISPLAY_CLEAR		0b00000001

/* Select lines on Display */
#define HCLCD_LINE1    1
#define HCLCD_LINE2    2

/*Initialize 4-Bits or 8-Bits Modes */
void HCLCD_Vid8Bits_Init(void);
void HCLCD_vid4Bits_Init(void);

/* 8-Bits Mode Send Char and Command */
void HCLCD_VidWriteChar_8Bits(u8 Copy_u8Data);
void HCLCD_VidWriteCommand_8Bits(u8 Copy_u8Command);

/* 4-Bits Mode Send Char and Command */
void HCLCD_VidWriteChar_4Bits(u8 Copy_u8Data);
void HCLCD_VidWriteCommand_4Bits(u8 Copy_u8Command);

/* Write Multiple Characters */
void HCLCD_VidWriteString4Bits(u8* PCopy_u8String);
void HCLCD_VidWriteString_8Bits(u8* PCopy_u8String);

/* Set Position of DDRAM AC */
void HCLCD_VidSetPosition_4Bits(u8 Copy_u8LineNumber, u8 Copy_u8PositionNumber);
void HCLCD_VidSetPosition_8Bits(u8 Copy_u8LineNumber, u8 Copy_u8PositionNumber);

/* Write Multiple Number on LCD */
void HCLCD_VidWriteNumber_4Bits(u32 Copy_u8Number);
void HCLCD_VidWriteNumber_8Bits(u32 Copy_u8Number);


#endif
