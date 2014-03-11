#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <GLUT/vvector.h>

#include "Matrix.h"
#include "Matrix.cpp"
#include "Vector.h"
#include "Vector.cpp"

#define USE_MATH_DEFINES
#define DEBUG 1

float sealevel;
float polysize;

float pitch;
float roll;

float speed  = 0.0005;

float lookatVector[3];
float rVector[3];
float upVector[3];

float eye[3];

const int fps = 30;

using namespace std;


int seed(float x, float y) {
    static int a = 1588635695, b = 1117695901;
	int xi = *(int *)&x;
	int yi = *(int *)&y;
    return ((xi * a) % b) - ((yi * b) % a);
}



void mountain(float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float s)
{
	float x01,y01,z01,x12,y12,z12,x20,y20,z20;
    
	if (s < polysize) {
		x01 = x1 - x0;
		y01 = y1 - y0;
		z01 = z1 - z0;
        
		x12 = x2 - x1;
		y12 = y2 - y1;
		z12 = z2 - z1;
        
		x20 = x0 - x2;
		y20 = y0 - y2;
		z20 = z0 - z2;
        
		float nx = y01*(-z20) - (-y20)*z01;
		float ny = z01*(-x20) - (-z20)*x01;
		float nz = x01*(-y20) - (-x20)*y01;
        
		float den = sqrt(nx*nx + ny*ny + nz*nz);
        
		if (den > 0.0) {
			nx /= den;
			ny /= den;
			nz /= den;
		}
        
		glNormal3f(nx,ny,nz);
		glBegin(GL_TRIANGLES);
        glVertex3f(x0,y0,z0);
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
		glEnd();
        
		return;
	}
    
	x01 = 0.5*(x0 + x1);
	y01 = 0.5*(y0 + y1);
	z01 = 0.5*(z0 + z1);
    
	x12 = 0.5*(x1 + x2);
	y12 = 0.5*(y1 + y2);
	z12 = 0.5*(z1 + z2);
    
	x20 = 0.5*(x2 + x0);
	y20 = 0.5*(y2 + y0);
	z20 = 0.5*(z2 + z0);
    
	s *= 0.5;
    
	srand(seed(x01,y01));
	z01 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
	srand(seed(x12,y12));
	z12 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
	srand(seed(x20,y20));
	z20 += 0.3*s*(2.0*((float)rand()/(float)RAND_MAX) - 1.0);
    
	mountain(x0,y0,z0,x01,y01,z01,x20,y20,z20,s);
	mountain(x1,y1,z1,x12,y12,z12,x01,y01,z01,s);
	mountain(x2,y2,z2,x20,y20,z20,x12,y12,z12,s);
	mountain(x01,y01,z01,x12,y12,z12,x20,y20,z20,s);
}

void init(void)
{
	GLfloat white[] = {1.0,1.0,1.0,1.0};
	GLfloat lpos[] = {0.0,1.0,0.0,0.0};
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
	glClearColor (0.5, 0.5, 1.0, 0.0);
	/* glShadeModel (GL_FLAT); */
	glEnable(GL_DEPTH_TEST);
    
	sealevel = 0.0;
	polysize = 0.01;
    
    lookatVector[0] = -0.5;
    lookatVector[1] =  0.5;
    lookatVector[2] = 0;
    
    eye[0] = 0.5; eye[1] = 0.0; eye[2] = 0.25;
    
    upVector[0] = 0.0; upVector [1] = 0.0; upVector[2] = 1.0;
    
    
    gluLookAt (eye[0], eye[1], eye[2],
               eye[0] + lookatVector[0], eye[1] + lookatVector[1], eye[2] + lookatVector[2],
               upVector[0], upVector[1], upVector[2]);
    

    //VEC_CROSS_PRODUCT(rVector, lookatVector, upVector);
    
    
}

void display(void)
{
	
    
    GLfloat pipelineStore[16];
	GLfloat tanamb[] = {0.2,0.15,0.1,1.0};
	GLfloat tandiff[] = {0.4,0.3,0.2,1.0};
    
	GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
	GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
	GLfloat seaspec[] = {0.5,0.5,1.0,1.0};
    
    
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	//glLoadIdentity ();             /* clear the matrix */
    
    
    
    /* viewing transformation  */
	   
    
    
	//glRotatef(angle, 0.0, 0.0, 1.0);
	//glTranslatef (-0.5, -0.5, 0.0);      /* modeling transformation */
    
	//	glutSolidTeapot(1.0);
    
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tandiff);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
	mountain(0.0,0.0,0.0, 1.0,0.0,0.0, 0.0,1.0,0.0, 1.0);
	mountain(1.0,1.0,0.0, 0.0,1.0,0.0, 1.0,0.0,0.0, 1.0);
    
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
	glNormal3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
    glVertex3f(0.0,0.0,sealevel);
    glVertex3f(1.0,0.0,sealevel);
    glVertex3f(1.0,1.0,sealevel);
    glVertex3f(0.0,1.0,sealevel);
	glEnd();
    
	glutSwapBuffers();
	glFlush ();
    
    // Add matrix to pipeline to modify based on inputs
    
    //if set to pitch up
    if(pitch == -1.0){
        glGetFloatv(GL_MODELVIEW_MATRIX, pipelineStore); // store pipeline
        glLoadIdentity(); // clear pipeline
        glRotatef(2.0,1.0, 0.0, 0.0); // put rotate at bottom of matrix stack
        glMultMatrixf(pipelineStore); // drop pipeline back on top
        
        
    }
    if(pitch ==  1.0){
        glGetFloatv(GL_MODELVIEW_MATRIX, pipelineStore);
        glLoadIdentity();
        glRotatef(-2.0,1.0, 0.0, 0.0);
        glMultMatrixf(pipelineStore);
        
    }
    if(roll == 1.0){
        glGetFloatv(GL_MODELVIEW_MATRIX, pipelineStore);
        glLoadIdentity();
        glRotatef(2.0,0.0, 0.0, 1.0);
        glMultMatrixf(pipelineStore);
        
    }
    if(roll == -1.0){
        glGetFloatv(GL_MODELVIEW_MATRIX, pipelineStore);
        glLoadIdentity();
        glRotatef(-2.0,0.0, 0.0, 1.0);
        glMultMatrixf(pipelineStore);
        
    }
    
    
    //The translation that makes my view move forward at a speed

    glGetFloatv(GL_MODELVIEW_MATRIX, pipelineStore);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, speed);
    glMultMatrixf(pipelineStore);
    
    
	
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(90.0,1.0,0.01,10.0);
	glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
		case '-':
			sealevel -= 0.01;
			break;
		case '+':
		case '=':
			sealevel += 0.01;
			break;
		case 'f':
			polysize *= 0.5;
			break;
		case 'c':
			polysize *= 2.0;
			break;
        case 'w':
            pitch = -1.0;
            break;
        case 'a':
            roll = -1.0;
            break;
        case 's':
            pitch = 1.0;
            break;
        case 'd':
            roll = 1.0;
            break;
        case 'q':
            speed += 0.001;
            break;
        case 'e':
            speed -= 0.001;
            break;
		case 27:
			exit(0);
			break;
    }
}

void keyboardPress(int key, int x, int y)
{
    if (key==GLUT_KEY_UP)
        pitch = -1.0;
    if (key==GLUT_KEY_DOWN)
        pitch = 1.0;
    if(key==GLUT_KEY_RIGHT)
        roll = 1.0;
    if(key==GLUT_KEY_LEFT)
        roll = -1.0;
    
}

void keyboardRelease(int key, int x, int y)
{
    if (key==GLUT_KEY_UP)
        pitch = 0.0;
    if (key==GLUT_KEY_DOWN)
        pitch = 0.0;
    if(key==GLUT_KEY_RIGHT)
        roll = 0.0;
    if(key==GLUT_KEY_LEFT)
        roll = 0.0;
    
}

void myClock(int in)
{
    glutPostRedisplay();
    glutTimerFunc(1000/fps,myClock,in);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardPress);
    glutSpecialUpFunc(keyboardRelease);
    glutTimerFunc(1000/fps, myClock, 0);
    glutMainLoop();
    return 0;
}