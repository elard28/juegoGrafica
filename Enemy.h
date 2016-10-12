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

	int iter;
	GLfloat x;
	GLfloat y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	Enemy(GLfloat r,int sc)
	{
		//imagen = TextureManager::Inst()->LoadTexture("image/rock.png", GL_BGRA_EXT, GL_RGBA);
		imagen = TextureManager::Inst()->LoadTexture("image/asteroide.png", GL_BGRA_EXT, GL_RGBA);
		iter=0;
		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;
		limit=(rand()%65+5)/100.0;

		x=0.0625f;
		y=0.5f;

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

	/*void draw()
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
	}*/

	void draw()
	{
		/*timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer -timebase;// delta time
		timebase = timer;
		anim += deltatime;

		if(!state)
			return;
		glBindTexture(GL_TEXTURE_2D, imagen);
		glBegin(GL_QUADS);
		glTexCoord2f(x*iter, y);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//abajo izquierda
		glTexCoord2f(x*iter, 1.0f);
		glVertex3d(Left(), Up(), 0);//arriba izquierda
		glTexCoord2f(x*(iter+1.0), 1.0f);
		glVertex3d(Right(), Up(), 0);//arriba derecha
		glTexCoord2f(x*(iter+1.0), y);
		glVertex3d(Right(), Down(), 0);//abajo derecha
		glEnd();

		coordy-=0.01f;
		if (anim / 1000.0 > limit)// si el tiempo de animacion dura mas 0.30s cambiamos de sprite
		{
			iter=(iter+1)%16;
			anim = 0;
		}*/
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