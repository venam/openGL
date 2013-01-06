#include "gun.h"
#include <GL/glut.h>

int warning_bomb=0;
int clock       =30;

void draw_gun()
{
    if(warning_bomb==3)
        warning_bomb=0;
    if(warning_bomb==0)
    {
        glColor3f(52/255.0,
                101/255.0,
                164/255.0
        );
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glutSolidSphere(0.025,
                        10,10);

    }
    else if (warning_bomb==1)
    {
        glColor3f(114/255.0,
                159/255.0,
                207/255.0
        );
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glutSolidSphere(0.027,
                        30,30);
    }
    else if (warning_bomb==2)
    {
        glColor3f(117/255.0,
                80/255.0,
                123/255.0
        );
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glutSolidSphere(0.023,
                        30,30);
    }
    if(clock==0)
    {
        warning_bomb++;
        clock =30;
    }
    clock--;


}
