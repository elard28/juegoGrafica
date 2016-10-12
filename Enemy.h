#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"
using namespace std;
#define RANDOM ((float)rand()/RAND_MAX)

class Enemy
{
public:
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat imagen;
	bool state;
	int respawn;
	int score;
	int op;
	double x;
	double y;	

	Enemy(GLfloat r,int sc)
	{
		imagen = TextureManager::Inst()->LoadTexture("image/asteroide.png", GL_BGRA_EXT, GL_RGBA);
		radio=r;
		coordx=rand()%30-15;
		coordy=rand()%5+13;
		state=true;
		score=sc;
		x = 0.0625;
		y = 0.5;
		
	}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw(int i)
	{
		if(!state)
			return;
		glBindTexture(GL_TEXTURE_2D, imagen);
		glBegin(GL_QUADS);
		glTexCoord2f(x*i,y);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//dl
		glTexCoord2f(x*i,1.0f);
		glVertex3d(Left(), Up(), 0);//ul
		glTexCoord2f(x*(i+1.0), 1.0f);
		glVertex3d(Right(), Up(), 0);//ur
		glTexCoord2f(x*(i+1.0), y);
		glVertex3d(Right(), Down(), 0);//dr
		glEnd();
		
		if(coordy<-10){
			coordx=rand()%30-15;
			coordy=rand()%8+13;	
		}else{
			coordy-=0.05f;
		}		
		
			
		
	}

	bool destroy()
	{
		if (state)
		{
			state=false;
			return true;
		}
		return false;
	}

	void revive()
	{
		coordx=rand()%30-10;
		coordy=rand()%5+5;
		state=true;
	}

	/*bool collision(Ship *sh)
	{
		if( sqrt( pow(coordx - sh->coordx, 2) + pow(coordy - sh->coordy, 2) ) <= (radio + sh->radio) && sh->state)
		{
			sh->destroy();
			return true;
		}
		return false;
	}*/

};

#endif
