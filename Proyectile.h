#ifndef PROYECTILE_H
#define PROYECTILE_H

#include <math.h>
#include "Enemy.h"
#include "EnemyShip.h"

class Proyectile
{
public:
	GLfloat large;
	GLfloat coordx;
	GLfloat coordy;
	GLfloat coordz;
	GLfloat velocity;
	bool state;
	GLfloat sprite;
	bool upgraded;

	double x;
	double y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	Proyectile()
	{
		sprite = TextureManager::Inst()->LoadTexture("image/laser_blue.png", GL_BGRA_EXT, GL_RGBA);
		state=false;

		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;
	}


	GLfloat Right(){return coordx+large;}
	GLfloat Left(){return coordx-large;}
	GLfloat Up(){return coordy+large*4;}
	GLfloat Down(){return coordy-large*4;}

	void draw()
	{
		if(!state)
			return;

		/*if(upgraded)
		{
			timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
			deltatime = timer -timebase;// delta time
			timebase = timer;
			anim += deltatime;
			if (anim / 1000.0 > 10.0)
			{
				downgrade();
				//anim = 0;
			}
		}
		
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

		coordy+=velocity;*/

		glPushMatrix();
		glTranslatef(coordx, coordy, coordz);
		glRotatef(90, 1.0, 0.0, 0.0);
		GLUquadricObj *obj = gluNewQuadric();
	    gluCylinder(obj, 0.1f, 0.4f, 5, 30, 30);
	    glPopMatrix();

	    coordy+=velocity;
	}

	bool collision(Enemy *e)
	{
		if( sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) ) <= (large + e->radio) && e->state && state)
		{
			e->state=false;
			state=false;
			return true;
		}
		return false;
	}

	bool collisionShip(EnemyShip *es)
	{
		if( sqrt( pow(coordx - es->coordx, 2) + pow(coordy - es->coordy, 2) ) <= (large + es->radio) && es->state && state)
		{
			es->state=false;
			state=false;
			return true;
		}
		return false;
	}

	void upgrade()
	{
		if(upgraded)
			return;
		sprite = TextureManager::Inst()->LoadTexture("image/laser_super.png", GL_BGRA_EXT, GL_RGBA);
		large=large*3.0f;
		upgraded=true;
		anim=0;
	}

	void downgrade()
	{
		if(!upgraded)
			return;
		sprite = TextureManager::Inst()->LoadTexture("image/laser_blue.png", GL_BGRA_EXT, GL_RGBA);
		large=large/3.0f;
		upgraded=false;
	}
	
};

#endif