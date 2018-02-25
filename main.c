/***********************************************************************************
FILE NAME  	:	main.c
DESCRIPTION :	Empty project set up for RSKM16C62P					


Copyright   : 2005 Renesas Technology Europe Ltd.
Copyright   : 2005 Renesas Technology Corporation.
All Rights Reserved

***********************************************************************************/

/***********************************************************************************
Revision History
DD.MM.YYYY OSO-UID Description
21.01.2006 RTA-MGF First Release
***********************************************************************************/

/**********************************************************************************
System Includes
***********************************************************************************/

/**********************************************************************************
User Includes
***********************************************************************************/
#include "sfr62p.h"
/* rskM16C62p_def.h defines some common definitions */
#include "rskM16C62Pdef.h"	
#include "main.h"
#include "lcd.h"
#include "stdlib.h"
//mode of each game : OFF=LED game,ON=LCD game
#define ON 255
#define OFF 0
#pragma	INTERRUPT timer_a0
#pragma	INTERRUPT timer_a1
#pragma INTERRUPT sw1
#pragma INTERRUPT sw2
#pragma INTERRUPT sw3

//Global variables
//***********************************************************************************/
//LED game variables
int toggle_led=5; //toggle_LED==5 let the game not start, until the players change it to 1,for LED game
int toggle = 5; //toggle==5 let the game not start, until the players change it to 1,for LCD game
long int delay_val = 200000; 

//LCD game variables
int i;
int ball_pos = 1; //position of the ball in upper or lower row
int count = 1;
int direction = 0; // 0 - to right; 1 - to left
int sw1_pos = 0; // right player:0 - up using switch 1; 1 - down
int sw2_pos = 0; //left player using switch 2 0 - up ; 1 - down
int ball_line; //upper or lower row
char str_line1[8], str_line2[8];
char ball = 'o';
int speed = 50;

//timer a1 variables
char mode=OFF;
int count_mode=0;
 

//User Program Code
//***********************************************************************************/

void update_display(void)
{
	//Left player's stick moving
	if(sw2_pos == 0) 
	{
		str_line1[0] = '|'; //stick on the upper row
		str_line2[0] = ' ';
	} else if(sw2_pos == 1) 
	{
		str_line1[0] = ' ';
		str_line2[0] = '|'; //stick on lower row
	}
	
	//moving the ball
	for(i = 1; i < 7; i++) //each row has 8 characters maximum,
		{
			if( ball_line == 0) //ball in upper row
			{
				if(i == ball_pos) str_line1[i] = ball; //the position same as the ball_pos's value is filled with 'o'
				else str_line1[i] = ' '; //other positions(except 1st and last) are empty
		
				str_line2[i] = ' '; //lower row is empty
			} else
			{
				if(i == ball_pos) str_line2[i] = ball; //the position same as the ball_pos's value is filled with 'o'
				else str_line2[i] = ' '; //other positions(except 1st and last) are empty
		
				str_line1[i] = ' ';	//upper row is empty
			}
			
		}
	
	
	//Right player's stick moving
	if(sw1_pos == 0) 
	{
		str_line1[7] = '|'; //stick on the upper row
		str_line2[7] = ' ';
	} else if(sw1_pos == 1)
	{
		str_line1[7] = ' ';
		str_line2[7] = '|'; //stick on lower row
	}

	DisplayString(LCD_LINE1, str_line1);
	DisplayString(LCD_LINE2, str_line2);
}


void timer_a0(void) 
{
	if(toggle == 1) //start the game
	{
		update_display();
	
		if(++count == speed)
		{
			count = 1;
			ball_line = rand() % 2; //ball moves random between 2 row
			if(direction == 0) //ball moving to right
			{
				ball_pos++;//ball moving to right
				if(ball_pos == 6) //when it reach the check point, check if player catch the ball , forming "o|" at position 6 and 7 of either rows
				{
					update_display();
					if((ball_line == 0 && str_line1[ball_pos+1] == '|') || (ball_line == 1 && str_line2[ball_pos+1] == '|')) direction = 1; //if the player catch the ball in the allowed time, the ball will bounce to opposite side
					else //if player can not catch the ball
					{
						DisplayString(LCD_LINE1, "GAMEOVER");
						toggle = 5; //stop the game
					}
				}
			}
			else 
			{
				ball_pos--; //ball moves to the left
				if(ball_pos == 1)  //when it reach the check point, check if player catch the ball , forming "|o" at position 0 and 1 of either rows
				{
					update_display();
					if((ball_line == 0 && str_line1[ball_pos-1] == '|') || (ball_line == 1 && str_line2[ball_pos-1] == '|')) direction = 0;//if the player catch the ball in the allowed time, the ball will bounce to opposite side
					else //if player can not catch the ball
					{
						DisplayString(LCD_LINE1, "GAMEOVER");
						toggle = 5; //stop the game
					}
				}
			}
		}
	}
}

void timer_a1(void){
	
	if(p8_4==0) //if the 3rd switch is pressed
	{
		if(++count_mode == 300) { //if the 3rd switch is held for 3s
			mode =~ mode; //change the game moe
			count_mode=0; //reset count
			if(mode==ON) ta0s = 1; //if mode is "ON", active timer a0 for LCD game
			else ta0s=0; //if mode is "OFF" , timer a0 is not working
				
		}
		
	}
	else count_mode=0; //if the time the switch was held did not reach 3s, reset it to 0
}


void delay(void) { //creating time to move between each LEDs
	long int j;
	for(j = 0; j < delay_val; j++) {}
}

void delay_to_bounce(void) { //creating 1s delay
	long int j;
	for(j = 0; j < 200000; j++) {}
}

void rotate_left(void) //LED turn on in sequence from left to right
{
	int i;
	for( i = 0; i < 4; ++i) 
	{
		if (toggle_led == 0) toggle_led = 1; //not allow to change direction when the LEDs are moving, until it reach the last position
		
		p4 |= 0x0F; //all LEDs off at start
		p4 &= ~( 1 << i ); //turn on LEDs in order from left to right
		delay(); //each LEDs turn on for the time allowed (default 1s, decreased by pressing sw3)
	}
	
	
	delay_to_bounce(); //after 1s
	if (toggle_led == 1) //if the direction of the LED not changed(the player did not "catch" the ball in time
	{
		//turn on all LEDs
		p4_0 = 0;
		p4_1 = 0;
		p4_2 = 0;
		p4_3 = 0;
		toggle_led = 5; //stop the game
	}
}

void rotate_right(void) //LED turn on in sequence from right to left
{

	for(i = 3; i >= 0; --i)
	{
		if (toggle_led == 1) toggle_led = 0; //not allow to change direction when the LEDs are moving, until it reach the last position
		p4 |= 0x0F;//all LEDs off at start

		p4 &= ~( 1 << i );  //turn on LEDs in order from right to left
		delay();
	}
	delay_to_bounce();
	if (toggle_led == 0) //if the direction of the LED not changed(the player did not "catch" the ball in time
	{
		//turn on all LEDs
		p4_0 = 0;
		p4_1 = 0;
		p4_2 = 0;
		p4_3 = 0;
		toggle_led = 5; //stop the game
	}
}

void sw1(void)
{
	if(mode == OFF){ //if in LED game mode
		toggle_led=1; //LEDs turn on from right to left
	}
	else if(mode==ON){ //if in LCD game mode
		if(toggle == 5) //if game did not start
		{
			toggle = 1; //start the game
			ball_pos = 6; //start the game with the ball from the right
			direction= 1; //moving to left
		}
		if(++sw1_pos == 2) sw1_pos = 0; //reset the sw1_pos if it exceed 1
	}
}


void sw2(void)
{	
	if(mode==OFF){ //if in LED game mode
		toggle_led=0; //LEDs turn on from left to right
	}
	else if(mode==ON){ //if in LCD game mode
		if(toggle == 5) //if game did not start
		{
			toggle = 1; //start the game
			ball_pos = 1; //start the game with the ball from the left
			direction= 0; //moving to right
		}
		if(++sw2_pos == 2) sw2_pos = 0; //reset the sw1_pos if it exceed 1
	}
}


void sw3(void) 
{
	ta1s = 1; //start timer a1
	if(mode==OFF){ //in LED game mode, change the time between each LEDs to turn on, decreased by half a second each time the sw is pressed
		delay_val -= 10000;
		if (delay_val <= 0) delay_val = 200000; //reset the value to default if it goes below 0
	}
	
	
	else if(mode==ON){ //in LCD game mode, change the speed of the ball moving, default is 1/2s,decreased by 10 ms each time the sw is pressed
		speed -= 10;
		if(speed < 10) speed = 50; //reset the value to default if it goes below 0
	}
	
}

void part1(void) {
	if (toggle_led == 5) return; //if toggle==5, the game is not running
	
	if (toggle_led) //if toogle LED=1
		rotate_left();
	else  //if toogle LED=0
		rotate_right();
}

void part2(void) {
	InitialiseDisplay();
	
	asm ( "FSET I" ); 		/* enable interrupts */
	ta0mr = 0b01000000;		/* f8 = 3MHz */
	ta0   = 29999; 			/* 10 * 10^(-3) * 3 * 10^(6) -1 meaning 10ms @3MHz */

	
	ta1ic=0x01;
	ta1mr = 0b01000000;		/* f8 = 3MHz */
	ta1   = 29999; 			/* 10 * 10^(-3) * 3 * 10^(6) -1 meaning 10ms @3MHz */
	
	
	DISABLE_IRQ
	ta0ic = 0x01;			/* interrupt priority level 1 (first non-zero lowest lvl) */
	ta1ic=0x01;
	int0ic = 0x01;
	int1ic = 0x01;
	int2ic = 0x05;
	ENABLE_IRQ
}

void main(void)				
{

	part2();
	
	while(1) {
		if(mode==OFF) part1(); //run part1( LED game) if mode is "OFF"
	}
}         
