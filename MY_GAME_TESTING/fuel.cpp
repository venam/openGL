#include <GL/glut.h>

#include "fuel.h"
#include "ModuleFont.h"

void draw_Fuel()
{
    GLfloat spec[]={1.0, 1.0 ,1.0 ,1.0};      //sets specular highlight of balls
    GLfloat posl[]={ 2.0f, 3.0f, -1.0f,1.0f };//position of ligth source
    GLfloat amb[]={0.2f, 0.2f, 0.2f ,1.0f};   //global ambient
    GLfloat amb2[]={0.3f, 0.3f, 0.3f ,1.0f};  //ambient of lightsource
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
	glLightfv(GL_LIGHT0,GL_POSITION,posl);
	glLightfv(GL_LIGHT0,GL_AMBIENT,amb2);
    glColor3f(252.0/255.0,
            233.0/255.0,
            79.0f/255.0
    );
    glutSolidSphere(0.07,
                    30,30);
     glColor3f(27.0/255.0,
            27.0/255.0,
            48.0f/255.0
    );
    glutSolidSphere(0.070,
                    3,2);

    placeFontCursor(-0.01F,-0.017,-0.4F);
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
    simpleBitmapOutput(REGULAR8x13,"F");

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
}

