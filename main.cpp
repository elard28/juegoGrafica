#define GLUT_DISABLE_ATEXIT_HACK	
//#include <windows.h>
#include <math.h>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include "glut.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include <GL/glut.h>
#include "TextureManager.h"
#include "Ship.h"
//#include "Rock.h"

#define KEY_ESC 27

using namespace std;

Ship *nave;
Enemy *enemigo;


GLfloat sprites;
GLfloat texture;
GLfloat shoot;
GLfloat rock;

int timer = 0;
int timebase = 0;
int anim = 0;
int i = 0;
double x = 0.2;
double y = 0.666;


void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//funcion de transparencia
	glEnable(GL_BLEND);//utilizar transparencia
	timer = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
	int dt = timer -timebase;// delta time
	timebase = timer;
	anim += dt;//duracion de la animacion entre dos cambios de Sprite
	


	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);//coordenadas de textura
	glVertex3d(-16, -12, 0); //dl
	glTexCoord2f(0.0, 1.0f); //ul
	glVertex3d(-16, 12, 0);
	glTexCoord2f(1.0, 1.0f); //ur
	glVertex3d(16, 12, 0);
	glTexCoord2f(1.0, 0.0); //dr
	glVertex3d(16, -12, 0);
	glEnd();

	//glDisable(GL_BLEND);

	if (anim / 1000.0 > 0.15)// si el tiempo de animacion dura mas 0.15s cambiamos de sprite
	{
		i++;
		anim = 0.0;
	}

	if (i == 5) i = 0;

	glBindTexture(GL_TEXTURE_2D, sprites);
	glBegin(GL_QUADS);
	glTexCoord2f(x*i, y);//coordenadas de textura
	glVertex3d(nave->coordx-nave->radio, nave->coordy-nave->radio, 0);//abajo izquierda
	glTexCoord2f(x*i, 1.0f);
	glVertex3d(nave->coordx-nave->radio, nave->coordy+nave->radio, 0);//arriba izquierda
	glTexCoord2f(x*(i+1.0), 1.0f);
	glVertex3d(nave->coordx+nave->radio, nave->coordy+nave->radio, 0);//arriba derecha
	glTexCoord2f(x*(i+1.0), y);
	glVertex3d(nave->coordx+nave->radio, nave->coordy-nave->radio, 0);//abajo derecha
	glEnd();
	//nave->draw(i);

	if(nave->shot.state)
	{
		nave->shot.draw();
		nave->shot.move();
	}

	if(enemigo->state)
		enemigo->draw();

	if(nave->shot.collision(enemigo))
		enemigo->state=false;

	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.4f, 0.4f, 0.4f, 0.2f); //(R, G, B, transparencia) en este caso un fondo negro
	glEnable(GL_TEXTURE_2D);
	//modo projeccion 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Get a handle for our "myTextureSampler" uniform
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width / 50.0f, width / 50.0f, -height / 50.0f, height / 50.0f, -1.0f, 1.0f);

	// todas la informaciones previas se aplican al la matrice del ModelView
	glMatrixMode(GL_MODELVIEW);
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	case 'a':
		nave->shoot();
		break;

	default:
		break;
	}

}

GLvoid window_arrow(int key, int x, int y)
{
	switch (key) 
	{
	case GLUT_KEY_RIGHT: //d
		if(nave->Right()<16)
			nave->go_right();
		cout<<"mueve derecha"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_LEFT: //f
		if(nave->Left()>-16)
			nave->go_left();
		cout<<"mueve izquiera"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_UP: //e
		if(nave->Up()<0)
			nave->go_up();
		cout<<"mueve arriba"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	case GLUT_KEY_DOWN: //g
		if(nave->Down()>-12)
			nave->go_down();
		cout<<"mueve abajo"<<"\tx: "<<nave->coordx<<"\ty: "<<nave->coordy<<endl;
		break;

	default:
		break;
	}

}

//function called on each frame
GLvoid window_idle()
{
	glutPostRedisplay();
}

int main(int argc, char** argv) 
{
	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("Textura: Animacion"); //titulo de la ventana

	init_GL();


	texture = TextureManager::Inst()->LoadTexture("image/space1.jpg", GL_BGR_EXT, GL_RGB);
	sprites = TextureManager::Inst()->LoadTexture("image/nave.png", GL_BGRA_EXT, GL_RGBA);

	nave=new Ship(2.5f,0,-5);
	//Rock roca(2);
	enemigo=new Enemy(2.0f);
	
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	glutKeyboardFunc(&window_key);
	glutSpecialFunc(&window_arrow);
	glutIdleFunc(&window_idle);
	glutMainLoop(); //bucle de rendering

	return 0;
}

//g++ main.cpp -lGL -lGLU -lglut -lfreeimage