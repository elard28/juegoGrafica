#define GLUT_DISABLE_ATEXIT_HACK	
//#include <windows.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
//#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"
#include "Bonus.h"
#include "EnemyShip.h"
//#include "Rock.h"

using namespace std;

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define ECHAP 27

Ship *nave;
Enemy **enemigo;

int num_enemigos=20;

//variables para el gizmo
float delta_x = 0.0; 
float delta_y = 0.0;
float mouse_x, mouse_y;
float var_x = 0.0;
float var_z = -30.0;
float step = 0; //0.0 Posicion inicial. 1.0 Traslacion. 2.0 Primera Rotacion(en y). 3.0 Segunda Rotacion (en x) 4.0 Ultima Rotacion (en z)

void print()
{
	cout<<"var_x: "<<var_x<<endl;
	cout<<"var_z: "<<var_z<<endl;
	cout<<"delta_x: "<<delta_x<<endl;
	cout<<"delta_y: "<<delta_y<<endl;
	cout<<endl;
}

GLvoid initGL()
{

	glEnable(GL_DEPTH_TEST);


	glClearColor(RED, GREEN, BLUE, ALPHA);
}


void Gizmo3D(){


	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 3.0f);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	return;

}



GLvoid window_display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(45.0f, 1.0f, 0.01f, 100.0f);


	/*glTranslatef(var_x, 0.0, var_z);
	glRotatef(delta_x, 0.0, 1.0, 0.0);
	glRotatef(delta_y, 1.0, 0.0, 0.0);*/

	glTranslatef(0.0, 0.0, -30.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);
	glRotatef(-30.0, 1.0, 0.0, 0.0);



	nave->draw();

	//for (int i = 0; i < num_enemigos; ++i)
	//	enemigo[i]->draw();

	for (int i = 0; i < num_enemigos; ++i)
	{
		enemigo[i]->draw();

		if(nave->shot.collision(enemigo[i]))
		{
			enemigo[i]->destroy();
			cout<<"Enemigo "<<i<<" destruido"<<endl;
			nave->win(enemigo[i]->score);
			cout<<"Puntaje: "<<nave->total_score<<endl;
		}

		cout<<"nave->collision(enemigo[i]): "<<nave->collision(enemigo[i])<<endl;
		if(nave->collision(enemigo[i]))
		{
			nave->destroy();
			cout<<"should be destroyed"<<endl;
		}
	}
	

	glutSwapBuffers();

	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
}



void init_scene()
{

}



GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case ECHAP:
		exit(0);
		break;

	case 'a':
		nave->shoot();
		cout<<"Disparo"<<endl;
		break;
	case 'd':
		if(!nave -> explode)
			break;
		for (int i = 0; i < num_enemigos; ++i)
		{
			if(enemigo[i]->destroy())
				nave->win(enemigo[i]->score);
		}
		nave -> explode=false;
		cout<<"Explosion"<<endl;
		cout<<"Puntaje: "<<nave->total_score<<endl;
		break;

	default:
		printf("La touche %d non active.\n", key);
		break;
	}

}

//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

///////////////////////////////////////////////////////////////////////////////
//(1)
///////////////////////////////////////////////////////////////////////////////
/*GLvoid callback_special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		var_z += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		var_z -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		var_x += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		var_x -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_PAGE_UP:
		step++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_PAGE_DOWN:
		step--;
		glutPostRedisplay();
		break;


	}
}*/

GLvoid callback_special(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_RIGHT: //d
		if(nave->Right()<15)
			nave->go_right();
		//cout<<"mueve derecha"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_LEFT: //f
		if(nave->Left()>-15)
			nave->go_left();
		//cout<<"mueve izquiera"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_UP: //e
		if(nave->Up()<0)
			nave->go_up();
		//cout<<"mueve arriba"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_DOWN: //g
		if(nave->Down()>-10)
			nave->go_down();
		//cout<<"mueve abajo"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	default:
		break;
	}

}



///////////////////////////////////////////////////////////////////////////////
//(2)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}

	if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
		print();
}

///////////////////////////////////////////////////////////////////////////////
//(3)
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	
	delta_x += x - mouse_x;
	delta_y += y - mouse_y;
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);


	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Milky Way");


	initGL();

	nave=new Ship(2.0f,0.0f,-5.0f,3);

	enemigo=new Enemy*[num_enemigos];
	for (int i = 0; i < num_enemigos; ++i)
		enemigo[i]=new Enemy(1.0f,50);

	init_scene();

	
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	
	
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	glutKeyboardFunc(&window_key);
	//glutKeyboardUpFunc(&window_key_up); //key release events
	glutSpecialFunc(&callback_special);
	//glutSpecialUpFunc(&callback_special_up); //key release events
	
	//function called on each frame
	glutIdleFunc(&window_idle);

	glutMainLoop();

	return 1;
}




