/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "../labirinto/matrice.h"
//#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int mode = 1;  //0=explore, 1=move
volatile int select0=0;
volatile int select1=0;
volatile int select2=0;
volatile int select3=0;
volatile int select4=0;

volatile int disable_joystick=0;

void RIT_IRQHandler (void)
{
if(disable_joystick==0){	
	int x,y;
	int d = controllo_ostacoli_vittoria();
	if(d<5){
		x=getObstacleX();
		y=getObstacleY();
		if(x!=-1 && y!=-1){  //se è un ostacolo e non un muro
			segnaOstacolo(x,y); //mi segno che l'ostacolo è stato trovato
			drawObstacle(y,x);
		}
	}
	if(d==200){
		clearPos(getY(),getX());
		drawExit(getY(),getX());
		GUI_Text(45,70,(uint8_t *) "GOOD GAME. YOU WON!", Red,White);
		disable_joystick=1;
	}

	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	 //SELECT
		select0++;
		switch(select0){
			case 1:
				if(mode==0){
					mode = 1;
					drawRobot(Black);
				}
				else{
					mode = 0;
					drawRobot(Red);
				}
				break;
			default:
				break;
		}
	}
	else if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	 //UP
		select0=0;
		select2=0;
		select3=0;
		select4=0;
		
		select1++;
		switch(select1){
			case 1:
				if(mode==0){
					if(getDir()!=3){
						cambiaDirezione(3); //NORD
						clearPos(getY(),getX());
						drawRobot(Red);
					}
				}
				
				break;
				
			case 20:
				select1=0;
				if(mode==1){
					if(getDir()!=3){
						cambiaDirezione(3);
						clearPos(getY(),getX());
						drawRobot(Black);
					}
					if(d!=0 && d!=200){
						clearPos(getY(),getX());
						muoviti();
						drawRobot(Black);
					}
				}
				break;
			default:
				break;
		}
	}
	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	 //RIGHT
		select0=0;
		select1=0;
		select3=0;
		select4=0;
		select2++;
		switch(select2){
			case 1:
				if(mode==0){
					if(getDir()!=0){
						cambiaDirezione(0); //EST
						clearPos(getY(),getX());
						drawRobot(Red);
					}
				}
				break;
				
			case 20:
				select2=0;
				if(mode==1){
					if(getDir()!=0){
						cambiaDirezione(0);
						clearPos(getY(),getX());
						drawRobot(Black);
					}
					if(d!=0 && d!=200){
						clearPos(getY(),getX());
						muoviti();
						drawRobot(Black);
					}
				}
				break;
			default:
				break;
		}
	}
	else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	 //DOWN
		select0=0;
		select1=0;
		select2=0;
		select4=0;
		select3++;
		switch(select3){
			case 1:
				if(mode==0){
					if(getDir()!=1){
						cambiaDirezione(1); //SUD
						clearPos(getY(),getX());
						drawRobot(Red);
					}
				}
				break;
				
			case 20:
				select3=0;
				if(mode==1){
					if(getDir()!=1){
						cambiaDirezione(1);
						clearPos(getY(),getX());
						drawRobot(Black);
					}
					if(d!=0 && d!=200){
						clearPos(getY(),getX());
						muoviti();
						drawRobot(Black);
					}
				}
				break;
			default:
				break;
		}
	}
	else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	 //LEFT
		select0=0;
		select1=0;
		select2=0;
		select3=0;
		select4++;
		switch(select4){
			case 1:
				if(mode==0){
					if(getDir()!=2){
						cambiaDirezione(2); //OVEST
						clearPos(getY(),getX());
						drawRobot(Red);
					}
				}
				break;
				
			case 20:
				select4=0;
				if(mode==1){
					if(getDir()!=2){
						cambiaDirezione(2);
						clearPos(getY(),getX());
						drawRobot(Black);
					}
					if(d!=0 && d!=200){
						clearPos(getY(),getX());
						muoviti();
						drawRobot(Black);
					}
				}
				break;
			default:
				break;
		}
	}
	else{
		select0=0;
		select1=0;
		select2=0;
		select3=0;
		select4=0;
	}
}
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
