#ifndef RSKM16C62PDEF_H_INCLUDED
#define RSKM16C62PDEF_H_INCLUDED
/*********************************************************************************                                                                                   *
FILE NAME  	:	rskM16C62pdef.h
DESCRIPTION	:	Defines for M16C62P RSK
            
Copyright(C)2005, Renesas Technology Corp.                                      
All rights reserved.                                                            
**********************************************************************************/

/**********************************************************************************
Revision History
DD.MM.YYYY OSO-UID Description
21.01.2006 RTA-MGF First Release
**********************************************************************************/


/***********************************************************************************
Defines
***********************************************************************************/
/* Peripheral Clock Speed */
#define	f1_CLK_SPEED		24000000		
#define XIN_FREQ 			f1_CLK_SPEED

/* Switches */
#define	SW1 			p8_0 
#define SW2 			p8_1 
#define SW3 			p8_2 
#define SW1_DDR			pd8_0
#define SW2_DDR			pd8_1
#define SW3_DDR			pd8_2

/* LEDs */
#define	LED0			p4_0
#define	LED1			p4_1
#define	LED2			p4_2
#define	LED3			p4_3

#define	LED0_DDR		pd4_0
#define	LED1_DDR		pd4_1
#define	LED2_DDR		pd4_2
#define	LED3_DDR		pd4_3

#define LED_ON      	0
#define LED_OFF     	1

/* Common Defines */
#ifndef TRUE
#define TRUE    		1
#endif
#ifndef FALSE
#define FALSE   		0
#endif

#define ENABLE_IRQ   	{_asm(" FSET I");}
#define DISABLE_IRQ		{_asm(" FCLR I");}


#endif /* RSK62M16CPDEF_H_INCLUDED */
