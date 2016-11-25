#ifndef SHIP_H
#define SHIP_H

#include <GL/glut.h>
#include "TextureManager.h"
#include "Proyectile.h"
#include "Bonus.h"
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
	int total_score;
	Proyectile shot;

	bool explode;

	bool upgrade_shot;

	/*Proyectile *shot;
	int numshots;
	int count;*/

	int iter;
	double x;
	double y;

	int timer;
	int timebase;
	int deltatime;
	int anim;
	float limit;

	Ship();

	Ship(GLfloat r, GLfloat xx, GLfloat yy, int lv)
	{
		sprite = TextureManager::Inst()->LoadTexture("image/ship2.png", GL_BGRA_EXT, GL_RGBA);
		lives=lv;
		radio=r;
		coordx=xx;
		coordy=yy;
		total_score=0;
		state=true;
		explode=false;

		shot.large=0.25f;
		shot.velocity=0.5f;

		iter=0;
		timer = 0;
		timebase = 0;
		deltatime=0;
		anim = 0;

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

		upgrade_shot=true;
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
		timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
		deltatime = timer -timebase;// delta time
		timebase = timer;
		anim += deltatime;

		if(!state)
			return;
		glPushMatrix();
		glTranslatef(coordx,0.0,coordy)	;
		glBegin(GL_QUADS);
		//vértices en 3d
		glColor3f(1,0,0);//rojo
		glVertex3d(-2,0,-2);//4
		glColor3f(1,1,0);//amarillo
		glVertex3d(-2,0,2);//3
		glColor3f(0,0,1);//azul
		glVertex3d(2,0,2);//2
		glColor3f(0,1,0);//verde
		glVertex3d(2,0,-2);//1
		glEnd();
			//------------------caras de la pirámide
			//para las caras triangulares
			//se usará GL_TRIANGLES
			//--------Cara 4  amarillo con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,2,0);
			glColor3f(1,1,0);
			glVertex3d(-2,0,-2);//1
			glVertex3d(2,0,-2);//4
			glEnd();

			//--------Cara 1 rojo con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,4,0);
			glColor3f(1,0,0);//rojo
			glVertex3d(4,0,-4);
			glVertex3d(4,0,4);
			glEnd();
			//--------Cara 3 verde con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,4,0);
			glColor3f(0,1,0);//verde
			glVertex3d(-4,0,4);
			glVertex3d(-4,0,-4);
			glEnd();
			//-------Cara 2 azul con blanco
			glBegin(GL_TRIANGLES);
			//vértices en 3d
			glColor3f(1,1,1);//blanco
			glVertex3d(0,4,0);
			glColor3f(0,0,1);//azul
			glVertex3d(4,0,4);
			glVertex3d(-4,0,4);
			glEnd();
		glPopMatrix();
		

		if (anim / 1000.0 > 0.15)
		{
			iter=(iter+1)%5;
			anim = 0;
		}
		shot.draw();

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

	bool bonus_collision(Bonus *b)
	{
		if( sqrt( pow(coordx - b->coordx, 2) + pow(coordy - b->coordy, 2) ) <= (radio + b->radio) && b->state && state)
		{
			b->state=false;
			if(b->type==0)
				explode=true;
			if(b->type==1)
				shot.upgrade();
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
	}*/
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
				
			e->state=false;
			sleep(1);
			if(lives==0){
				state=false;
			}	
				
			//explosion();
			lives--;
			return true;
		}
		return false;
	}

	//~Ship();
	
};

#endif
