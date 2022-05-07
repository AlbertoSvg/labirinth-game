/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../labirinto/matrice.h"

extern int disable_joystick;

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
	static int clear = 0;

	
  getDisplayPoint(&display, Read_Ads7846(), &matrix );
	
	// RESTART
	
	if(display.x <= 110 && display.x >= 30){
		if(display.y <= 300 && display.y >=240){
			clear = 1;
			disable_joystick=1; //stop game
			GUI_Text(70,100,(uint8_t *) "Touch to start", Blue,White);
			GUI_Text(80,120,(uint8_t *) "a new game", Blue,White);
		}
	}
	
	// CLEAR
	
	if(display.x <= 210 && display.x >= 130){
		if(display.y <= 300 && display.y >=240){
			clearObstacles();
		}
	}
	
	if(clear==1){
		if(display.x <= 210 && display.x >= 30){
			if(display.y <= 220 && display.y >=64){
				clear = 0;
				disable_joystick=0; //stop game
				newGame();
			}
		}
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
