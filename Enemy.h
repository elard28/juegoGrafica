#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"

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

	Enemy(GLfloat r,int sc)
	{
		imagen = TextureManager::Inst()->LoadTexture("image/rock.png", GL_BGRA_EXT, GL_RGBA);
		radio=r;
		coordx=rand()%20-10;
		coordy=rand()%5+5;
		state=true;
		score=sc;
	}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw()
	{
		if(!state)
			return;
		glBindTexture(GL_TEXTURE_2D, imagen);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//dl
		glTexCoord2f(0.0,1.0);
		glVertex3d(Left(), Up(), 0);//ul
		glTexCoord2f(1.0,1.0);
		glVertex3d(Right(), Up(), 0);//ur
		glTexCoord2f(1.0,0.0);
		glVertex3d(Right(), Down(), 0);//dr
		glEnd();

		coordy-=0.01f;
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
		coordx=rand()%20-10;
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