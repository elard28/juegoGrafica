#ifndef SHIP_H
#define SHIP_H

#include <GL/glut.h>
#include "TextureManager.h"
#include "Proyectile.h"
#include <iostream>
#include <unistd.h>

using namespace std;

class Ship
{
public:
	int lives;
	GLfloat radio;
	GLfloat coordx;
	GLfloat coordy;
	bool state;
	GLfloat sprite;
	GLfloat spriteExplosion;
	int total_score;
	Proyectile shot;
	int timer; // recupera el tiempo ,que paso desde el incio de programa
	int deltatime;// delta time
	int timebase;
	int anim;//duracion de la animacion entre dos cambios de Sprite
	int iter;
	int iter_exp;
	int num_limit;


	/*Proyectile *shot;
	int numshots;
	int count;*/

	double x;
	double y;
	double x_explosion;
	double y_explosion;

	Ship();

	Ship(GLfloat r, GLfloat xx, GLfloat yy, int lv)
	{
		timer = 0;
		deltatime = 0;
		timebase = 0;
		anim = 0;
		iter = 0;
		num_limit = 5;
		iter_exp = 0;


		sprite = TextureManager::Inst()->LoadTexture("image/ship2.png", GL_BGRA_EXT, GL_RGBA);
		spriteExplosion = TextureManager::Inst()->LoadTexture("image/explosion.png", GL_BGRA_EXT, GL_RGBA);
		lives = lv;
		radio = r;
		coordx = xx;
		coordy = yy;
		total_score = 0;
		state = true;

		shot.large = 0.25f;
		shot.velocity = 0.5f;

		/*numshots=ns;
		shot=new Proyectile[ns];
		for (int i = 0; i < count; ++i)
		{
			shot[i].large=1.0f;
			shot[i].velocity=0.5f;
		}
		count=0;*/

		x = 0.25;
		y = 0.666;
		x_explosion = 0.20;
		y_explosion = 0.25;
	}

	void go_right(){coordx++;}
	void go_left(){coordx--;}
	void go_up(){coordy++;}
	void go_down(){coordy--;}

	GLfloat Right(){return coordx+radio;}
	GLfloat Left(){return coordx-radio;}
	GLfloat Up(){return coordy+radio;}
	GLfloat Down(){return coordy-radio;}

	void draw()
	{
		if(!state)
			return;

		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer - timebase;// delta time
		timebase = timer;
		anim += deltatime;//duracion de la animacion entre dos cambios de Sprite
		
		glBindTexture(GL_TEXTURE_2D, sprite);
		glBegin(GL_QUADS);
		glTexCoord2f(x * iter, y);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//abajo izquierda
		glTexCoord2f(x * iter, 1.0f);
		glVertex3d(Left(), Up(), 0);//arriba izquierda
		glTexCoord2f(x * (iter + 1.0), 1.0f);
		glVertex3d(Right(), Up(), 0);//arriba derecha
		glTexCoord2f(x * (iter + 1.0), y);
		glVertex3d(Right(), Down(), 0);//abajo derecha
		glEnd();

		if (anim / 1000.0 > 0.15)
		{
			iter = (iter + 1) % num_limit;
			anim = 0.0;
		}
	}

	void drawExplotion()
	{
		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer - timebase;// delta time
		timebase = timer;
		anim += deltatime;//duracion de la animacion entre dos cambios de Sprite
		
		glBindTexture(GL_TEXTURE_2D, spriteExplosion);
		glBegin(GL_QUADS);
		glTexCoord2f(x_explosion * iter_exp, y_explosion);//coordenadas de textura
		glVertex3d(Left(), Down(), 0);//abajo izquierda
		glTexCoord2f(x_explosion * iter_exp, 1.0f);
		glVertex3d(Left(), Up(), 0);//arriba izquierda
		glTexCoord2f(x_explosion * (iter_exp + 1.0), 1.0f);
		glVertex3d(Right(), Up(), 0);//arriba derecha
		glTexCoord2f(x_explosion * (iter_exp + 1.0), y_explosion);
		glVertex3d(Right(), Down(), 0);//abajo derecha
		glEnd();

		if (anim / 1000.0 > 0.15)
		{
			iter_exp = (iter_exp + 1) % num_limit;
			anim = 0.0;
		}
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

	void explosion()
	{
		for(int i = 0; i<20; i++){
			drawExplotion();
		}
	}

	/*void shoot()
	{
		shot[count].state=true;
		shot[count].coordx=coordx;
		shot[count].coordy=coordy+radio+shot[count].large;
		count=(count+1)%numshots;
	}
	*/
	bool collision(Enemy *e)
	{
		/*for (int i = 0; i < numshots; ++i)
		{
			if (shot[i].collision(e))
				return true;
		}
		return false;*/

		/*cout<<"distancia: "<<sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) )<<endl;*/
		if( sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) ) <= (e->radio && (e->state && state)) )
		{
			cout<<"distancia: "<<sqrt( pow(coordx - e->coordx, 2) + pow(coordy - e->coordy, 2) )<<endl;
			usleep(10000);
			e->state=false;
			state=false;
			explosion();
			return true;
		}
		return false;
	}

	//~Ship();
	
};

#endif