#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "image.h"
#include "space_ship.h"
#include "stdio.h"

GLuint texture[4];          //stores texture objects  ----------------------TESTING TEXTURES HERE



/*=======================SHIP=======================*/
void draw_Ship(bool is_flying)
{
    /********************start SIHP********************/
    glMatrixMode(GL_MODELVIEW);

    //cocpit
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
    glPushMatrix();
    glTranslatef(0.0,0.3,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    /* That's how we do textures :)*/
    glutSolidCone( 0.1, 0.4,
                    10,  10);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,-0.03,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    GLUquadricObj *quadobj;
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
                0.1,0.1,//up radius down radius
                0.35,//height
                10,10 //stack
    );

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,0.06,-0.08);
    glScalef(1.0,0.9,0.6);
    glutSolidCube(0.16);
    glColor3f(52.0/255.0,
            101.0/255.0,
            164.0f/255.0
    );
    glTranslatef(0.0,0.09,0.0);
    glScalef(1.0,0.2,1.0);
    glutSolidCube(0.16);
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );

    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0,-0.02,0.0);
    glScalef(1.0,0.1,1.0);
    glutSolidSphere(0.10,
                    10, 10);

    //GAS
    glPopMatrix();
    glPushMatrix();
    glColor3f(239.0/255.0,
            41.0/255.0,
            41.0f/255.0
    );
    glTranslatef(0.0,-0.041,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    gluCylinder(quadobj,
                0.05,0.05,//up radius down radius
                0.01,//height
                5,5 //stack
    );
    gluCylinder(quadobj,
                0.04,0.04,//up radius down radius
                0.01,//height
                5,5 //stack
    );
    if(!is_flying)
    {
        glColor3f(196.0/255.0,
                160.0/255.0,
                0.0f/255.0
        );
        gluCylinder(quadobj,
                    0.02,0.02,//up radius down radius
                    0.01,//height
                    5,5 //stack
        );
    }
    else
    {
        glColor3f(0.0/255.0,
                  0.0/255.0,
                  255.0f/255.0
        );
        glTranslatef(0.0,-0.03,0.0);
        gluCylinder(quadobj,
                    0.04,0.04,//up radius down radius
                    0.03,//height
                    10,10 //stack
        );
        glTranslatef(0.0,0.03,0.0);

    }
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );


    //wings base
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.0, 0.13,0.06);
    glScalef(0.8,0.4,0.06);
    glutSolidCube(0.5);


    //wing defence right
    glColor3f(52.0/255.0,
            101.0/255.0,
            164.0f/255.0
    );
    glPopMatrix();
    glPushMatrix();
    glScalef(0.3,1.0,1.0);
    glTranslatef(0.32,0.13,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    glutSolidCone( 0.08, 0.3,
                    5,  5);
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
    glPopMatrix();
    glPushMatrix();
    glScalef(0.3,1.0,1.0);
    glTranslatef(0.32,0.13,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    glutSolidCube( 0.08);


    //wing defence left
    glColor3f(52.0/255.0,
            101.0/255.0,
            164.0f/255.0
    );
    glPopMatrix();
    glPushMatrix();
    glScalef(0.3,1.0,1.0);
    glTranslatef(-0.32,0.13,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    glutSolidCone( 0.08, 0.3,
                    5,  5);
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
    glPopMatrix();
    glPushMatrix();
    glScalef(0.3,1.0,1.0);
    glTranslatef(-0.32,0.13,0.0);
    glRotatef(-90,1.0,0.0,0.0);
    glutSolidCube( 0.08);
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );

    //wings stabilizer left
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.20,0.1,0.1);
    glRotatef(-45,0.0,1.0,0.0);
    glScalef(0.3,1.0,0.3);
    glutSolidCube( 0.2);


    //wings stabilizer right
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.20,0.1,0.1);
    glRotatef(-45,0.0,1.0,0.0);
    glScalef(0.3,1.0,0.3);
    glutSolidCube( 0.2);


    //long wings part left
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.20,0.1,0.11);
    glRotatef(-55,0.0,1.0,0.0);
    glRotatef(-10,0.0,0.0,1.0);
    glRotatef( 35,1.0,0.0,0.0);
    glScalef(0.3,1.0,0.3);
    glutSolidCone( 0.09, 2.5,
                    5,  5);

    //long wings part right
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.20,0.1,0.11);
    glRotatef(55,0.0,1.0,0.0);
    glRotatef(-10,0.0,0.0,1.0);
    glRotatef( 35,1.0,0.0,0.0);
    glScalef(0.3,1.0,0.3);
    glutSolidCone( 0.09, 2.5,
                    5,  5);

    glPopMatrix();

    glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);


}
/*==================END==SHIP=======================*/


