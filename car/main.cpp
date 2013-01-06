/*******
car - Patrick Louis - 201202593
*******/



#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include "ModuleFont.h"
#include <iostream>
#include <cmath>
#include <cstdlib>                 //random
#include <ctime>                   //init random at time 0 - 1 Jan 1970
#include <unistd.h>                //for sleep()
#include <boost/thread/thread.hpp> //for the thread   -- multiplatform
#include <boost/bind.hpp>          //make it easier to pass arguments (pointer to a function)

using namespace std;

/*==================GLOBAL VARS======================*/
GLfloat car_move       = 0.0f;
GLfloat car_move_hor   = 0.0f;
bool red               = false;
bool yellow            = false;
bool brake             = 0;
bool finished_counting = false;
bool started_counting  = false;
float  points          = 0.0;
/*==================GLOBAL VARS======================*/

/*==================FUNCTIONS PROTOTYPES==============*/
void reshape(int x,int y);
void keyboard(unsigned char key,int x,int y);
void keyboardUP(unsigned char key,int x,int y);
void Draw_Everything();
void Draw_text();
void Draw_car();
void Draw_light();
void Draw_wall();
void processSpecialKeys(int key, int xx, int yy);
void specialup(int key, int x, int y);
/*=============END==FUNCTIONS PROTOTYPES==============*/

/*======================LIGHT=========================*/
const GLfloat light_ambient[]  = { 0.0f, 0.0/255.0, 30.0f/255.0, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 3.0f, -1.0f,1.0f };
const GLfloat mat_ambient[]    = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat mat_diffuse[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 20.0f };
const GLfloat emission []      = { 0.03, 0.03, 0.03, 1.0 };
/*================END==LIGHT=========================*/

/*======FUNCTION THAT COUNT TO A CERTAIN NUMBER======*/
void counting(int time)
{
	sleep(time);
	finished_counting=true;
}
/*==END=FUNCTION THAT COUNT TO A CERTAIN NUMBER======*/

/*======FUNCTION THAT RANDOMIZE THE LIGHT GREEN======*/
void count_random_time()
{
	srand(time(0));
	int random_5  = rand()%5;
	int random_3  = rand()%3;
	while(1)
	{
		//from green to red
		if(!started_counting)
		{
			random_5  = rand()%5;
			started_counting = true;
			boost::thread thrd2(boost::bind(&counting, random_5));
		}

		if(finished_counting)
		{
			yellow=true;
			random_3  = rand()%3;
			sleep(random_3+1);
			yellow=false;
			red = true;
			random_3  = rand()%4;
			sleep(random_3+1);
			red = false;
			finished_counting=false;
			started_counting=false;
		}


		sleep(1);
	}

}
/*==END=FUNCTION THAT RANDOMIZE THE LIGHT GREEN======*/


/*======GIVES A REAL EFFECT TO THE PUSH FORWARD======*/
void motor_effect(bool forward_left , bool neg )
{
	GLfloat push_effect = 0.02;
	if (forward_left==1)
	{
		if(neg==0)
			while(push_effect>0.001)
			{
				usleep(20000);
				car_move    += push_effect;
				push_effect -= 0.001;
			}
		else
		{
			while(push_effect>0.001)
			{
				usleep(20000);
				car_move    -= push_effect;
				push_effect -= 0.001;
			}
		}
	}
	else
	{
		while(push_effect>0.001)
		{
			if(neg==0)
			{
				usleep(20000);
				car_move_hor += push_effect;
				push_effect   -= 0.001;
			}
			else
			{
				usleep(20000);
				car_move_hor -= push_effect;
				push_effect   -= 0.001;
			}
		}
	}
}
/*==END=GIVES A REAL EFFECT TO THE PUSH FORWARD======*/


/*================MAIN=====FUNCTION==================*/
int main(int argc,char **argv)
{
	boost::thread thrd1(&count_random_time);

    /* initialisation of GLUT*/
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(400,50);
    glutInitWindowSize(500,700);
    glutCreateWindow("Car - Patrick Louis - venam");

    /* Initialisation of the window */
    glClearColor(21.0/255.0,
                 21.0/255.0,
                 21.0/255.0,
                 1.0); //clear the screen with black
    glPointSize(1.0);              //set the default size of the points

    /* functions to be used while redrawing the window */
    glutDisplayFunc(Draw_Everything);
    glutIdleFunc(Draw_Everything);
    glutSpecialUpFunc(specialup);        //what happens when not pressing
    glutSpecialFunc(processSpecialKeys); //what happens when special keys are clicked
    glutReshapeFunc(reshape);            //keep the aspect of what's inside the window when resizing
    glutKeyboardFunc(keyboard);          //the keyboard bindings (normal keys)
    glutKeyboardUpFunc(keyboardUP);

    //Related to the lighting & effect
    glClearDepth(1.0f);                                 // Depth Buffer Setup

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
    glCullFace(GL_BACK);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    /* Enter the main loop */
    glutMainLoop();
    return 0;
}
/*===========END==MAIN=====FUNCTION==================*/

/*=========================DRAWING==================*/
void Draw_Everything()
{
    /* clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    Draw_car();

    Draw_wall();
    Draw_text();
    Draw_light();

    //switch the buffers
    glutSwapBuffers();
}
/*==================END====DRAWING==================*/

/*=========================DRAW=CAR==================*/
void Draw_car()
{

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);


    glPushMatrix();
    glTranslatef(0.0,car_move,0.0);
    glTranslatef(car_move_hor,0.0,0.0);

    if(car_move>1.6)
    {
		points++;
		car_move=-0.91;
    }
	if(car_move<-1.0)
		car_move=1.5;
    if(car_move_hor>0.8)
		car_move_hor=0.8;
	if(car_move_hor<-0.8)
		car_move_hor=-0.8;

    glTranslatef(0.0,-0.7,0.0);
    glRotatef(10,1.0,0.0,0.0);
    glScalef(0.5,0.5,0.5);

    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
	glPushMatrix();
    glScalef(1.0,1.0,0.5);
	glutSolidCube(0.5);
	glTranslatef(0.0,0.2,0.0);
	glutSolidCube(0.4);
	glPopMatrix();


	glPushMatrix();
	glScalef(1.0,0.7,0.6);
	glColor3f(52.0/255.0,
            101.0/255.0,
            164.0f/255.0
    );
	glTranslatef(0.0,0.1,-0.2);
	glutSolidSphere(0.2,10,10);
	glPopMatrix();

	///WHEELS
	glScalef(1.0,1.0,0.8);
	glColor3f(40.0/255.0,
            40.0/255.0,
            40.0f/255.0
    );
	glPushMatrix();
	glTranslatef(0.3,0.1,0.15);
	glScalef(0.6,0.5,0.5);
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(90,0.0,1.0,0.0);
	glutSolidTorus(0.1,0.2,10,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3,0.1,0.15);
	glScalef(0.6,0.5,0.5);
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(90,0.0,1.0,0.0);
	glutSolidTorus(0.1,0.2,10,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3,-0.19,0.15);
	glScalef(0.6,0.5,0.5);
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(90,0.0,1.0,0.0);
	glutSolidTorus(0.1,0.2,10,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.3,-0.19,0.15);
	glScalef(0.6,0.5,0.5);
	glRotatef(90,1.0,0.0,0.0);
	glRotatef(90,0.0,1.0,0.0);
	glutSolidTorus(0.1,0.2,10,10);
	glPopMatrix();

	glPushMatrix();
	    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
	glTranslatef(0.0,-0.32,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    GLUquadricObj *quadobj;
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
                0.13,0.05,//up radius down radius
                0.1,//height
                10,10 //stack
    );
	glPopMatrix();

	///LIGHT
	glPushMatrix();
	glColor3f(255.0/255.0,
            0.0/255.0,
            0.0f/255.0
    );
    glTranslatef(0.1, 0.4,0.0);
    glScalef(0.5,0.5,1.0);
	glutSolidSphere(0.09,10,10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(255.0/255.0,
            0.0/255.0,
            0.0f/255.0
    );
    glTranslatef(-0.1, 0.4,0.0);
    glScalef(0.5,0.5,1.0);
	glutSolidSphere(0.09,10,10);
	glPopMatrix();

    glPopMatrix();
}

/*===============END=======DRAW=CAR==================*/

/*======================DRAW=WALL==================*/
void Draw_wall()
{
	glPushMatrix();
    glColor3f(0.0/255.0,
            2.0/255.0,
            17.0f/255.0
    );

	glPushMatrix();
    glTranslatef(-0.94,0.0,-0.0);
    glScalef(0.04,1.0,1.0);
    glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.94,0.0,-0.0);
    glScalef(0.04,1.0,1.0);
    glutSolidCube(2);
    glPopMatrix();


	glPopMatrix();
}
/*===============END=======DRAW=WALL==================*/

/*======================DRAW=LIGHT==================*/
void Draw_light()
{
	glPushMatrix();
	glColor3f(20.0/255.0,
			  255.0/255.0,
			  17.0f/255.0
		);
	if(red)
	{
		glColor3f(230.0/255.0,
				2.0/255.0,
				17.0f/255.0
		);
	}
	if(yellow)
	{
		glColor3f(255.0/255.0,
				242.0/255.0,
				0.0f/255.0
		);
	}
    glTranslatef(-0.4,0.94,-0.4);
    glutSolidSphere(0.06,20,20);

	glPopMatrix();
}
/*===============END=======DRAW=LIGHT==================*/

/*==================STATUS_TEXT=====================*/
//the top text
void Draw_text()
{
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    //for the status

    glColor4f(52.0/255.0,
              101.0/255.0,
              164.0f/255.0,
              0.3
             );

	 placeFontCursor(0.5F,0.92F,0.0F);
	 simpleBitmapOutput(REGULAR8x13,"Score:%3.0f", points );
	if(red)
	{
		placeFontCursor(-0.8F,0.92F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"STOP!!!");
	}
	else
	{
		placeFontCursor(-0.9F,0.92F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"Go for it!");
	}
	if(yellow)
	{
		placeFontCursor(-0.2F,0.92F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"WAIT");
	}




}
/*=============END==STATUS_TEXT=====================*/

/*==========NOT PRESSING=KEYBOARD==================*/
/* return the moves to 0 */
//we want that because otherwise we will have to put a timer to return the ship to ship_turning =1
void specialup(int key, int x, int y)
{
    switch (key)
        {
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_LEFT:
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            glutPostRedisplay();
            break;
        }
}
/*======END=NOT PRESSING=KEYBOARD==================*/

/*===============KEYBOARD=NOT PRESSSING=============*/
void keyboardUP(unsigned char key,int x,int y)
{
	switch (key)
	{
		case ' ':
		if(brake==0)
			brake = 1;
		else
			brake = 0;
		glutPostRedisplay();
		break;
	}
}
/*==========END==KEYBOARD=NOT PRESSSING===========*/

/*========================KEYBOARD==================*/
void keyboard(unsigned char key,int x,int y)
{
    switch (key)
        {
        case 'Q':
        case 'q':
            /*'q' to quit/terminate the program */
            exit(0);
            break;
		case ' ':
			if(brake==0)
				brake = 1;
			else
				brake = 0;
			glutPostRedisplay();
			break;
        }
}
/*==================END===KEYBOARD==================*/

/*============SPECIAL=KEYBOARD======================*/
//process the special events happening when a special key is pressed
void processSpecialKeys(int key, int xx, int yy)
{

	if( key== GLUT_KEY_LEFT )
		{
			if(brake==0)
			{
				//car_move_hor-=0.04;
				boost::thread thrd3(boost::bind(&motor_effect, 0,1));
				if(red)
					points --;
			}
			glutPostRedisplay();

		}
	else if ( key ==GLUT_KEY_RIGHT )
		{
			if(brake==0)
			{
				boost::thread thrd3(boost::bind(&motor_effect, 0,0));
				if(red)
					points --;
			}
			glutPostRedisplay();

		}
	else if ( key == GLUT_KEY_UP )
		{
			if(brake==0)
			{
				boost::thread thrd3(boost::bind(&motor_effect, 1,0));
				if(red)
					points --;
			}
			glutPostRedisplay();
		}
	else if ( key == GLUT_KEY_DOWN )
		{
			if(brake==0)
			{
				boost::thread thrd3(boost::bind(&motor_effect, 1,1));
				if(red)
					points --;
			}
			glutPostRedisplay();
		}

}
/*=======END===SPECIAL=KEYBOARD====================*/


/*===============WINDOWS RESHAPING==================*/
void reshape(int x,int y)
{
    /*BIG PROBLEM HERE WITH THE RESHAPE
    if (x<y)
        glViewport(0,(y-x)/2,x,x);
    else
        glViewport((x-y)/2,0,y,y);
    */
}
/*===========END=WINDOWS RESHAPING==================*/
