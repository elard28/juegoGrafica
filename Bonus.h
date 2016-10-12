#ifndef BONUS_H
#define BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#include "TextureManager.h"

class Bonus
{
public:
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat imagen;
	bool state;
	int respawn;
	int score;
	int type;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	Bonus(GLfloat r, int sc, int tp)
	{
		radio=r;
		score=sc;
		state=true;
		type=tp;
		switch(type)
		{
			case 0:
				imagen = TextureManager::Inst()->LoadTexture("image/grenade.png", GL_BGRA_EXT, GL_RGBA);
				break;
			case 1:
				imagen = TextureManager::Inst()->LoadTexture("image/ray.png", GL_BGRA_EXT, GL_RGBA);
				break;
			default:
				break;
		}
		coordx=rand()%20-10;
		coordy=rand()%5+5;

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;
	}

	void setType(int tp)
	{
		type=tp;
		switch(type)
		{
			case 0:
				imagen = TextureManager::Inst()->LoadTexture("image/grenade.png", GL_BGRA_EXT, GL_RGBA);
				break;
			case 1:
				imagen = TextureManager::Inst()->LoadTexture("image/ray.png", GL_BGRA_EXT, GL_RGBA);
				break;
			default:
				break;
		}
	}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw()
	{
		if(!state)
		{
			revive(20.0);
			return;
		}
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

		coordy-=0.05f;
		if(Down()<-12)
			state=false;
	}

	void revive(float rv)
	{
		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer -timebase;// delta time
		timebase = timer;
		anim += deltatime;

		if (anim / 1000.0 > rv)
		{
			state=true;
			coordx=rand()%20-10;
			coordy=rand()%5+5;
			int rn=rand()%2;
			setType(rn);
			anim=0;
		}
	}

	//~Bonus();
	
};

#endif