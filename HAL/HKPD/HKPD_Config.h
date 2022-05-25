#ifndef HKPD_CONFIG_H_
#define HKPD_CONFIG_H_

/*Row Port Options
 * 1- MDIO_PORTA
 * 2- MDIO_PORTB
 * 3- MDIO_PORTC
 * 4- MDIO_PORTD*/
#define ROW_PORT     MDIO_PORTB
/*Row Pins Options: From PIN0 To PIN7*/
#define ROW_PIN0   PIN0
#define ROW_PIN1   PIN1
#define ROW_PIN2   PIN2
#define ROW_PIN3   PIN3
#define ROW_NIBBLE_INPUT 	LEAST_NIBBLE_INPUT

/*Column Port Options
 * 1- MDIO_PORTA
 * 2- MDIO_PORTB
 * 3- MDIO_PORTC
 * 4- MDIO_PORTD*/
#define COL_PORT    MDIO_PORTB
/*Row Pins Options: From PIN0 To PIN7*/
#define COL_PIN0    PIN4
#define COL_PIN1    PIN5
#define COL_PIN2    PIN6
#define COL_PIN3    PIN7
#define COL_NIBBLE_OUTPUT 	MOST_NIBBLE_OUTPUT

/*Column INIT is Start Col pin and COL End is last col pin +1  */
#define COL_INIT     4
#define COL_END      8

/*row INIT is Start row pin and row end is last row pin +1  */
#define ROW_INIT     0
#define ROW_END      4

#endif
