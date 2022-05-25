#ifndef HKPD_INTERFACE_H_
#define HKPD_INTERFACE_H_

#define NOT_PRESSED 255

/*KPD INIT*/
void HKPD_VidInit(void);

/*KPD Get pressed*/
u8 HKPD_u8GetKeyPressed(void);

#endif

