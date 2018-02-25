***********************************************************************************
DESCRIPTION		Renesas Starter Kit Project Readme File
***********************************************************************************

/***********************************************************************************
Revision History
DD.MM.YYYY OSO-UID Description
27.11.2006 RTE-DDE Corrected ring connector pin-out
***********************************************************************************/

This project can be debugged with HEW and an E8.
The Quick Start Guide supplied with the RSK can be referred to for help in connecting to the target.
This code has been designed so that the E8 Firmware Program can be located at address h'FF000 and the E8 Firmware RAM at 2B80h'.

Details of the sample project can be found at the top of the C file which contains the projects main() function.

Support
Online technical support and information is available at: www.renesas.com/rsk

Technical Contact Details:

America: techsupport.rta@renesas.com 
Europe:  tools.support.eu@renesas.com 
Japan:   csc@renesas.com 

RSKM16C62P MCU Port - Board Connector Cross-Reference/*
Device = M30620FCPFP

***********************************************************************************
PORT	 	PIN NAME/				RING 		COMMON BUS	
NUMBER		FUNCTION				BUS PIN		PIN	Hardware
***********************************************************************************			
			Vcc - 5V							JA1-1
			VCC - 3V							JA1-3
			AVcc					J1-18		JA1-5	
			Gnd						J1-11		JA2-4,JA1-2
			AVss					J1-15		JA1-6
			Vref					J1-17		JA1-7
			CNVss					J1-6
			Reset					J1-9	

P0_0		AN0_0 /  D0				J4-8 		JA3-17
P0_1		AN0_1 /  D1				J4-7		JA3-18
P0_2		AN0_2 /  D2				J4-6		JA3-19
P0_3		AN0_3 /  D3				J4-5		JA3-20
P0_4		AN0_4 /  D4				J4-4		JA3-21
P0_5		AN0_5 /  D5				J4-3		JA3-22
P0_6		AN0_6 /  D6				J4-2		JA3-23
P0_7		AN0_7 /  D7				J4-1		JA3-24
			
P1_0		D8						J3-30		JA3-29		
P1_1		D9						J3-29		JA3-30
P1_2		D10						J3-28		JA3-31
P1_3		D11						J3-27		JA3-32
P1_4		D12						J3-26		JA3-33
P1_5		D13 / INT3n				J3-25		JA3-34
P1_6		D14 / INT4n				J3-24		JA3-35
P1_7		D15 / INT5n				J3-23		JA3-36	
			
P2_0		AN2_0 /  A0				J3-22		JA3-1
P2_1		AN2_1 /  A1				J3-21		JA3-2
P2_2		AN2_2 /  A2				J3-20		JA3-3
P2_3		AN2_3 /  A3				J3-19		JA3-4
P2_4		AN2_4 /  A4				J3-18		JA3-5
P2_5		AN2_5 /  A5				J3-17		JA3-6
P2_6		AN2_6 /  A6				J3-16		JA3-7
P2_7		AN2_7 /  A7				J3-15		JA3-8	

P3_0		A8						J3-13		JA3-9
P3_1		A9						J3-11		JA3-10
P3_2		A10						J3-10		JA3-11
P3_3		A11						J3-9		JA3-12
P3_4		A12						J3-8		JA3-13
P3_5		A13						J3-7		JA3-14
P3_6		A14						J3-6		JA3-15
P3_7		A15						J3-5		JA3-16	

P4_0		A16						J3-4		JA3-37		LED0
P4_1		A17						J3-3		JA3-38		LED1
P4_2		A18						J3-2		JA3-39		LED2	
P4_3		A19						J3-1		JA3-40		LED3
P4_4		CS3n					J2-17		JA3-27
P4_5		CS2n					J2-18		JA3-28
P4_6		CS1n					J2-19		JA3-45
P4_7		CS0n					J2-20		JA3-21		

P5_0		WRLn/WRn				J2-16		JA3-48
P5_1		WRHn/BHEn				J2-15		JA3-47
P5_2		RDn						J2-14		JA3-25
P5_3		BCLK					J2-13		JA2-24
P5_4		HLDA					J2-12		JA2-11
P5_5		HOLDn					J2-11		------
P5_6		ALE						J2-10		JA3-48
P5_7		RDYn/CLKOUT				J2-9		JA3-21	

P6_0		CTS0/RTS0				J2-8		JA2-12
P6_1		CLK0					J2-7		JA3-10
P6_2		RXD0/SCLO				J2-6		JA3-8
P6_3		TXD0/SDA0				J2-5		JA2-6
P6_4		CTS1n/RTS1n/CTS0n/CLKS1	J2-4		------		E8 BUSY
P6_5		CLK1					J2-3		------		E8 CLK
P6_6		RxD1/SCL1				J2-2		------		E8 RX DATA
P6_7		TxD1/SDA1				J2-1		------		E8 TX DATA

P7_0		TxD2/SDA2/TA0ut			J1-30		JA1-25
P7_1		RxD2/SCL2/TA0in/TB5in	J1-29		JA1-26
P7_2		CLK2/TA1out/V			J1-28		
P7_3		CTS2/RTS2/TA1in/Vn		J1-27		JA2-16
P7_4		TA2out/W				J1-26		JA2-17		
P7_5		TA2in/Wn				J1-25		JA2-18		
P7_6		TA3out					J1-24		JA5-5		
P7_7		TA3in					J1-23		JA5-6

P8_0		TA4Ot/U					J1-22		JA1-13
P8_1		TA4in/Un				J1-21		JA1-14
P8_2		INTOn					J1-20		JA2-7		SW1
P8_3		INT1n					J1-19		JA2-9		SW2
P8_4		INT2n/ZP				J1-18		JA2-13		SW3
P8_5		NMI						J1-17		JA2-3		
P8_6		XCOUT					J1-10		
P8_7		XCIN					J1-11				


P9_0		TB0IN/CLK3				J1-7		JA6-11
P9_1		TB1in/SOUT3				----		JA6-9
P9_2		TB2in/SIN3				----		JA6-12
P9_3		TB3in/DA0				J1-4		JA2-16
P9_4		TB4in/DA1				J1-3		JA2-17		
P9_5		ANEX0/CLK4				J1-2		JA2-18		
P9_6		ANEX1/SOUT4				J1-1		JA5-5		
P9_7		ADTRG/SIN4				J4-20		JA5-6		

P10_0		ANO						J4-17		JA1-9		AD Pot
P10_1		AN1						J4-15		JA1-10
P10_2		AN2						J4-14		JA1-11
P10_3		AN3						J4-13		JA1-11
P10_4		AN4/KI0					J4-12		JA5-1		
P10_5		AN5/KI1					J4-11		JA5-2		
P10_6		AN6/KI2					J4-10		JA5-3		
P10_7		AN7/KI3					J4-9		JA5-4		
