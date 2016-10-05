#ifndef PROYECTILE_H
#define PROYECTILE_H

#include <math.h>
#include "Enemy.h"

class Proyectile
{
public:
	GLfloat large;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat velocity;
	bool state;
	GLfloat sprite;

	double x;
	double y;

	Proyectile()
	{
		sprite = TextureManager::Inst()->LoadTexture("image/laser_blue.png", GL_BGRA_EXT, GL_RGBA);
		state=false;
	}

	void move()
	{
		coordy+=velocity;
	}

	GLfloat Right(){return coordx+large/4;}
	GLfloat Left(){return coordx-large/4;}
	GLfloat Up(){return coordy+large;}
	GLfloat Down(){return coordy-large;}

	void draw()
	{
		glBindTexture(GL_TEXTURE_2D, sprite);
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

	bool collision(Enemy *e)
	{
		if( sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) ) <= (large + e->radio) && e->state)
		{
			e->state=false;
			state=false;
			return true;
		}
		return false;
	}
	
};

#endif