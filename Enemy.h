#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <GL/glut.h>
#include "TextureManager.h"

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

	Enemy(GLfloat r)
	{
		imagen = TextureManager::Inst()->LoadTexture("image/rock.png", GL_BGRA_EXT, GL_RGBA);
		radio=r;
		coordx=rand()%20-10;
		coordy=rand()%5+5;
		state=true;
	}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw()
	{
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
	}

	void move()
	{

	}

};

#endif