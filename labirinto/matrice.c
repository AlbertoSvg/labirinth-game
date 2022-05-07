#include "lpc17xx.h"
#include "matrice.h"
#include "../GLCD/GLCD.h"


typedef struct{
	int x;
	int y;
	int direction;   //0 -> E, 1 -> S, 2 -> W, 3 -> N
	
}posizione;

unsigned int const r = 13;
unsigned int const c = 15;
unsigned char matrice[r][c];
posizione pos;
volatile unsigned char obstacles[r][c];


void matrix_init(void){
	 int i,j;
	 for(i=0;i<r;i++){
		 for(j=0;j<c;j++){
			 matrice[i][j]=0;
		 }
	 }
	 matrice[0][0]=2;
	 matrice[0][14]=2;
	 matrice[12][0]=2;
	 matrice[12][14]=2;
	 
	 matrice[1][2]=1;
	 matrice[1][3]=1;
	 matrice[1][4]=1;
	 matrice[1][5]=1;
	 
	 matrice[2][7]=1;
	 matrice[3][7]=1;
	 matrice[4][7]=1;
	 matrice[5][7]=1;
	 
	 matrice[5][0]=1;
	 matrice[5][1]=1;
	 matrice[5][2]=1;
	 matrice[5][3]=1;
	 matrice[5][4]=1;
	 
	 matrice[5][9]=1;
	 
	 matrice[5][13]=1;
	 matrice[6][13]=1;
	 matrice[7][13]=1;
	 matrice[8][13]=1;
	 
	 matrice[7][0]=1;
	 matrice[8][0]=1;
	 matrice[9][0]=1;
	 matrice[10][0]=1;
	 matrice[11][0]=1;
	 
	 matrice[9][2]=1;
	 matrice[10][2]=1;
	 matrice[11][2]=1;
	 matrice[12][2]=1;
	 
	 for(i=0;i<r;i++){
		 for(j=0;j<c;j++){
			 obstacles[i][j]=0;
		 }
	 }
}	

void init_position(void){
	pos.x=7;
	pos.y=7;
	pos.direction=0;
}


int controllo_ostacoli_vittoria(void){
	int i;
	if(matrice[pos.x][pos.y]==2)
		return 200;   //vittoria
	
		switch(pos.direction){
		case 0: 
			for(i=pos.y+1;i<c;i++){
				if(matrice[pos.x][i]==1)
					return i - pos.y -1; // check ostacolo
			}
			return c-pos.y-1; // ritorno distanza dal muro
			
		case 1:
			for(i=pos.x+1;i<r;i++){
				if(matrice[i][pos.y]==1)
					return i - pos.x -1;
			}
			return r-pos.x-1;
			
		case 2:
			for(i=pos.y-1;i>=0;i--){
				if(matrice[pos.x][i]==1)
					return  pos.y - i -1;
			}
			return pos.y;
			
		case 3:
			for(i=pos.x-1;i>=0;i--){
				if(matrice[i][pos.y]==1)
					return  pos.x - i -1;
			}
			return pos.x;
	}
	return -1;
}


void muoviti(void){
	if(pos.direction ==0){		
			
			pos.y+=1;
	}
	if(pos.direction==1){
			
			pos.x+=1;
	}
	if(pos.direction==2){
		
			pos.y-=1;
	}
	if(pos.direction==3){
		
			pos.x-=1;
	}
	return;
}

void cambiaDirezione(int dir){
	pos.direction=dir;
}

int getX(){
	return pos.x;
}

int getY(){
	return pos.y;
}

int getObstacleX(){
	int i;
	switch(pos.direction){
		case 0: 
			for(i=pos.y+1;i<c;i++){
				if(matrice[pos.x][i]==1){
					return pos.x;
				}
			}
			break;
		case 1:
			for(i=pos.x+1;i<r;i++){
				if(matrice[i][pos.y]==1){
					return i;
				}
			}
			break;
		case 2:
			for(i=pos.y-1;i>=0;i--){
				if(matrice[pos.x][i]==1){
					return pos.x;
				}
			}
			break;
		case 3:
			for(i=pos.x-1;i>=0;i--){
				if(matrice[i][pos.y]==1){
					return i;
				}
			}
			break;
	}
	return -1;
}

int getObstacleY(){
	int i;
	switch(pos.direction){
		case 0: 
			for(i=pos.y+1;i<c;i++){
				if(matrice[pos.x][i]==1)
					return i; // check ostacolo
			}
			break;
		case 1:
			for(i=pos.x+1;i<r;i++){
				if(matrice[i][pos.y]==1)
					return pos.y;
			}
			break;
		case 2:
			for(i=pos.y-1;i>=0;i--){
				if(matrice[pos.x][i]==1)
					return i;
			}
			break;
		case 3:
			for(i=pos.x-1;i>=0;i--){
				if(matrice[i][pos.y]==1)
					return pos.y;
			}
			break;
	}
	return -1;
}

int getDir(){
	return pos.direction;
}

void segnaOstacolo(int x, int y){
	
	obstacles[x][y]=1;
}

void clearObstacles(){
	int i,j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			if(obstacles[i][j]==1){
				obstacles[i][j]=0; // setto di nuovo l'ostacolo
				clearPos(j,i);
			}
		}
	}
}
