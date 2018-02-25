/***********************************************************************************
FILE NAME  	:	hwsetup.c
DESCRIPTION	:	Hardware Setup functions

Copyright   : 2005 Renesas Technology Europe Ltd.
Copyright   : 2005 Renesas Technology Corporation.
All Rights Reserved
***********************************************************************************/

/***********************************************************************************
Revision History
DD.MM.YYYY OSO-UID Description
14.01.2006 RTA-MGF First Release
***********************************************************************************/

/***********************************************************************************
System Includes
***********************************************************************************/

/***********************************************************************************
User Includes
***********************************************************************************/
/* sfr62P.h provides a structure to access all of the device registers. */
#include "sfr62p.h"
/* rskM16C62Pdef.h provides common defines for widely used items. */
#include "rskM16C62pdef.h"
#include "hwsetup.h"

/***********************************************************************************
User Program Code Prototypes
***********************************************************************************/
/* These functions are private so their prototypes are defined locally */
void ConfigureOperatingFrequency(void);
void EnablePeripheralModules(void);
void ConfigurePortPins(void);

/***********************************************************************************
User Program Code 
***********************************************************************************/

/***********************************************************************************
Function Name: 	HardwareSetup
Description:	Sets up hardware
Parameters: none
Return value: none
***********************************************************************************/
void HardwareSetup(void)
{    
	ConfigureOperatingFrequency();

	ConfigurePortPins();

	EnablePeripheralModules();

//	ConfigureInterrupts();
}
/***********************************************************************************
End of function HardwareSetup
***********************************************************************************/

/***********************************************************************************
Function Name: 	ConfigureOperatingFrequency
Description:	Sets up operating speed and start sub-clock
Parameters: none
Return value: none
***********************************************************************************/
void ConfigureOperatingFrequency(void)
{
	 unsigned short count = 10000;

	/* configure main clock */

	/* configure clock for divide by 1 mode */
	/* enable access to clock registers */
    prc0 = 1;

	/* set CM16,CM17 divide ratio to 1, main clock on in high drive no PLL*/
    cm1 = 0x20;

	/* set divide ratio to 1 */
	cm06 = 0;							
	
/* configure and switch main clock to PLL at 24MHz - comment this section
		out if PLL operation is not desired								*/

    /* allow writing to processor mode register */
	prc1 = 1;					

	/* set SFR access to 2 wait which is required for operation greater than 16 MHz */
	pm20 = 1;					

	/* protect processor mode register */
	prc1 = 0;					

	/* enable PLL in X4 mode then turn PLL on */
    plc0 = 0x12;

	/* enable PLL */
	plc07 = 1;					

	/* wait for PLL to stabilize (20mS maximum, 10,000 cycles @6Mhz) this decrement with no optimization 
	   is 12 cycles each, after delay switch clock to PLL */
    while(count > 0)
	{
		count--;
	}

	/* switch to PLL */
    cm11 = 1;

/* if not using PLL comment out to this line */

    /* protect clock control register */
	prc0 = 0;   				

	/* configure 32 kHz clock if not using 32 kHz clock comment this section out */

   	/* Unlock CM0 and CM1 */
	prc0 = 1;

	/* set XCin/XCout port pins to inputs*/
   	pd8_7 = 0;		
   	pd8_6 = 0;

 	/* Start the 32KHz crystal a delay must occur before a device uses this clock */
   	cm04 = 1; 		
}
/***********************************************************************************
End of function ConfigureOperatingFrequency
***********************************************************************************/

/***********************************************************************************
Function Name: 	EnablePeripheralModules
Description:	Enables Peripheral Modules before use also enables data flash
Parameters: none
Return value: none
***********************************************************************************/
void EnablePeripheralModules(void)
{
	/* enable data flash, all other modules are active on M16C */
	prc1 = 1;
	pm10 = 1;		
	prc1 = 0;
}
/***********************************************************************************
End of function EnablePeripheralModules
***********************************************************************************/

/***********************************************************************************
Function Name: 	ConfigurePortPins
Description:	Configures port pins 
Parameters: none
Return value: none
***********************************************************************************/
void ConfigurePortPins(void)
{
/* Port pins default to inputs. To ensure safe initialisation set the pin states
before changing the data direction registers. This will avoid any unintentional
state changes on the external ports.
Many peripheral modules will override the setting of the port registers. Ensure
that the state is safe for external devices if the internal peripheral module is
disabled or powered down. */

/* General device configuration */
	/* None required */   				

/* Switch Port configuration */
	/* All pins are inputs by default */

/* Configure unused pins as output low */
	p0=p1=p2=p3=p4=p5=p6=p7=p9=p10=0x0;       

	/* lower half of port 4 has the LEDs on it so keep the LEDs off */
	p4= 0x0f;

	/* configure direction registers as outputs*/
	pd0=pd1=pd2=pd3=pd4=pd5=pd7=pd10 = 0xff;
	
	/* to set port9 direction register must first unprotect register do not step or set breakpoints
	between unprotecting register and modifying the direction register */
	prc2=1;
	pd9=0xff;
	prc2 =0;

	/* port 6 is used by E8 do not modify upper half of port */
	pd6 |= 0x0f;

	/* port 8 has switches, NMI and sub-clock only modify p8_0 and p8_1 */
	p8_0 = p8_1 = 0;
	pd8_0 = pd8_1 = 1;		
}
/***********************************************************************************
End of function ConfigurePortPins
***********************************************************************************/
