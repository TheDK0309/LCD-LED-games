# LCD-LED-games
Using Renesas M16C62P develope kit to implement the following tasks:
1. LED game (program startup default mode): by pressing SW1, the ball will start moving in sequence of LED0-1-2-3 sequence, and by pressing SW2, the ball will bounce back in sequence of LED3-2-1-0. If the timing is not met to hit the ball, then game over by flashing all LEDs. SW3 can choose the ball speed from slow, median and fast.

2. LCD game: by long press SW3 for 3 seconds it enters this mode and another 3 seconds it toggles back to LED game. The ball is displayed as letter "o" on LCD. It always starts from left moving to the right, but it can randomly change to Line 1 or Line 2. SW1 and SW2 will act as the racket, displayed as "|" moving up and down to catch the ball. If the ball is hit back in predefined timing, the ball is moving back from right to left then left to right again. If the ball is missed then display flashing "GAMEOVER". SW3 can choose the ball speed from slow, median and fast.
