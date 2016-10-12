#ifndef SHIP_H
#define SHIP_H

#include <GL/glut.h>
#include "TextureManager.h"
#include "Proyectile.h"

class Ship
{
public:
	int lives;
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	bool state;
	GLfloat sprite;
	int total_score;
	Proyectile shot;

	/*Proyectile *shot;
	int numshots;
	int count;*/

	double x;
	double y;

	Ship();

	Ship(GLfloat r, GLfloat xx, GLfloat yy, int lv)
	{
		sprite = TextureManager::Inst()->LoadTexture("image/nave.png", GL_BGRA_EXT, GL_RGBA);
		lives=lv;
		radio=r;
		coordx=xx;
		coordy=yy;
		total_score=0;
		state=true;

		shot.large=0.25f;
		shot.velocity=0.5f;

		/*numshots=ns;
		shot=new Proyectile[ns];
		for (int i = 0; i < count; ++i)
		{
			shot[i].large=1.0f;
			shot[i].velocity=0.5f;
		}
		count=0;*/

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
		if(!state)
			return;
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

	void win(int sc)
	{
		total_score+=sc;
	}

	void shoot()
	{
		shot.state=true;
		shot.coordx=coordx;
		shot.coordy=coordy+radio+shot.large;
	}

	bool ifShot()
	{
		return shot.state;
	}

	bool destroy()
	{
		if (state)
		{
			state=false;
			lives--;
			return true;
		}
		return false;
	}

	/*void shoot()
	{
		shot[count].state=true;
		shot[count].coordx=coordx;
		shot[count].coordy=coordy+radio+shot[count].large;
		count=(count+1)%numshots;
	}
	bool collision(Enemy *e)
	{
		for (int i = 0; i < numshots; ++i)
		{
			if (shot[i].collision(e))
				return true;
		}
		return false;
	}*/

	//~Ship();
	
};

#endif