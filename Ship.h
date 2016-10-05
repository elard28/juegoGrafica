#ifndef SHIP_H
#define SHIP_H

#include <GL/glut.h>
#include "TextureManager.h"
#include "Proyectile.h"

class Ship
{
public:
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	bool state;
	GLfloat sprite;
	Proyectile shot;
	double x;
	double y;

	Ship();

	Ship(GLfloat r, GLfloat x, GLfloat y)
	{
		sprite = TextureManager::Inst()->LoadTexture("image/nave.png", GL_BGRA_EXT, GL_RGBA);
		radio=r;
		coordx=x;
		coordy=y;
		shot.large=1.0f;
		shot.velocity=0.5f;

		x = 0.2;
		y = 0.666;
	}

	void go_right(){coordx++;}
	void go_left(){coordx--;}
	void go_up(){coordy++;}
	void go_down(){coordy--;}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw(int i)
	{
		glBindTexture(GL_TEXTURE_2D, sprite);
		glBegin(GL_QUADS);
		glTexCoord2f(x*i, y);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//abajo izquierda
		glTexCoord2f(x*i, 1.0f);
		glVertex3d(Left(), Up(), 0);//arriba izquierda
		glTexCoord2f(x*(i+1.0), 1.0f);
		glVertex3d(Right(), Up(), 0);//arriba derecha
		glTexCoord2f(x*(i+1.0), y);
		glVertex3d(Right(), Down(), 0);//abajo derecha
		glEnd();


	}

	void shoot()
	{
		shot.state=true;
		shot.coordx=coordx;
		shot.coordy=coordy+radio+shot.large;
	}

	//~Ship();
	
};

#endif