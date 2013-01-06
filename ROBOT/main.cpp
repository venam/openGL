/*******
Buldozer - Patrick Louis - 201202593

inspired by this picture: http://blog.rockanddirt.com/wp-content/uploads/2012/09/caterpillar-bulldozer-10.jpeg
*******/

#include <stdio.h>
#include <GL/glut.h>
#include "ModuleFont.h"

/*==================GLOBAL VARS======================*/
//for the boulder
#define X .525731112119133606
#define Z .850650808352039932
static GLfloat vdata[12][3] = {
{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
static GLuint tindices[20][3] = {
{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };
int i;
//
char presse;
int anglex,angley,x,y,xold,yold;
GLfloat move_tank = 0.0F;
GLfloat rotate_tank = 0.0F;
GLfloat hands_transltar_angle = 0.0F;
GLfloat angle_arms_down = 0.0F;
bool lifting_it = false;
/*==================GLOBAL VARS======================*/


/*==================FUNCTIONS PROTOTYPES==============*/
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void processSpecialKeys(int key, int xx, int yy) ;
void draw_dirt();
void draw_tank();
void Draw_text();
/*=============END==FUNCTIONS PROTOTYPES==============*/

/*======================LIGHT=========================*/
const GLfloat light_ambient[]  = { 0.0f, 0.0/255.0, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 10.0f, 0.0f,1.0f };
const GLfloat mat_ambient[]    = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat mat_diffuse[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 10.0f };
/*================END==LIGHT=========================*/

/*================MAIN=====FUNCTION==================*/
int main(int argc,char **argv)
{
    /* initialisation of GLUT*/
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bulldozer - Patrick Louis - venam");

    /* Initialisation of the window */
    //glClearColor(62.0/255,124.0/255,102.0/255,0.5);
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);

    /* Message for the user (on the console) */
    printf("UP/DOWN arrows to move forward/backward\n");
    printf("SHIFT+UP/DOWN arrows to move the ARMS\n");
    printf("LEFT/RIGHT arrows to move the Lower part of the ARMS\n");
    printf("q to QUIT the program\n");


    /* functions to be used while redrawing the window */
    glutDisplayFunc(affichage);

    glutKeyboardFunc(clavier);           //keyboard
    glutSpecialFunc(processSpecialKeys); //what happens when special keys are clicked
    glutReshapeFunc(reshape);            //keep the aspect of the cube when resizing the window
    glutMouseFunc(mouse);                //what will happens on mouse events
    glutMotionFunc(mousemotion);         //what happens when you move the cube

    //Related to the lighting effect
    glCullFace(GL_BACK);

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    //static float white[] = { 1.0F,1.0F,1.0F,1.0F };
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,white);

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
void affichage()
{
    int i,j;
    /* clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    Draw_text();


    //The moves related functions
    glRotatef(-angley,1.0,0.0,0.0);
    glRotatef(-anglex,0.0,1.0,0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    //draw block and floor
    glPushMatrix();
    draw_dirt();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


    glRotatef(rotate_tank,0.0,1.0,0.0);
    glTranslatef(move_tank,0.0,0.0);
    draw_tank();


    glFlush();
    //switch the buffers
    glutSwapBuffers();
}
/*==================END====DRAWING==================*/

/*==================STATUS==========================*/
void Draw_text()
{
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );

    //for the status
    placeFontCursor(0.3F,0.92F,-0.9F);
    simpleBitmapOutput(REGULAR8x13,"  %6.1f Angle2 ", angle_arms_down);
        glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
    placeFontCursor(-0.35F,0.92F,-0.9F);
    simpleBitmapOutput(REGULAR8x13,"%6.1f Angle1  |", hands_transltar_angle);
    placeFontCursor(-0.95F,0.92F,-0.9F);
    simpleBitmapOutput(REGULAR8x13,"%6.1f Move   |", move_tank);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.95F,0.98F);
    glVertex2f(-0.95F,0.9F);
    glVertex2f(0.95F,0.9F);
    glVertex2f(0.95F,0.98F);
    glEnd();

}
/*=============END==STATUS==========================*/

/*=======================TANK=======================*/
void draw_tank()
{
    /********************start buldozer********************/

    /**********************base********************/
    glColor3f(
        254.0/255.0,
        226.0/255.0,
        67.0/255.0
    );
    glPushMatrix();
    glScalef(1.0,0.5,1.0);

    glutSolidCube(0.5);

    glLineStipple(0.5, 0x3F07);
    glEnable(GL_LINE_STIPPLE);

    glutSolidCube(0.45);

    glTranslatef(0.20,0.3,0.0);
    glLineStipple(0.2, 0x3F02);

    glutSolidCube(0.12);

    glDisable(GL_LINE_STIPPLE);
    glTranslatef(-0.20,-0.3,0.0);
    glTranslatef(0.0,0.3,0.0);
    glScalef(1.0,1/0.5,1.0);
    glScalef(1.0,0.5,1.0);

    /***********************Cocpit********************/
    glutSolidCube(0.15);

    glScalef(1.0,1/0.5,1.0);
    glScalef(0.3,1.0,1.0);
    glColor3f(
        66.0/255.0,
        141.0/255.0,
        173.0/255.0
    );
    glTranslatef(-0.27,0.0,0.0);

    glutSolidSphere(0.04,
                    10,10);

    glColor3f(
        254.0/255.0,
        226.0/255.0,
        67.0/255.0
    );

    /**********************Wheels********************/
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glLoadIdentity();
    glPopMatrix(); //regive the position before flush
    glPushMatrix();
    glTranslatef(0.22,-0.16,-0.35);

    //rotate the wheels
    glRotatef(-move_tank*3,0.0,0.0,1.0);

    //1
    GLUquadricObj *quadobj;
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
                0.04,0.04,//up radius down radius
                0.20,//height
                10,10 //stack
    );

    glColor3f(
        106.0/255.0,
        105.0/255.0,
        101.0/255.0
    );

    glutSolidTorus(0.05,0.1,
                    20,10);

    glScalef(0.62,0.28,1.0);
    glTranslatef(-0.3,0.0,0.0);


    glutSolidTorus(0.05,0.55,
                    20,30);

    glScalef(1/0.62,1/
             0.28,1.0);
    glTranslatef(0.3,0.0,0.0);

    glColor3f(
        254.0/255.0,
        226.0/255.0,
        67.0/255.0
    );
    glTranslatef(0.0,0.0,0.67);
    glRotatef(180,1.0,0.0,0.0);
    glTranslatef(-0.11,0.0, 0.0);

    //2
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
        0.04,0.04,//up radius down radius
        0.20,//height
        10,10 //stack
    );

    glColor3f(
        106.0/255.0,
        105.0/255.0,
        101.0/255.0
    );
    glRotatef(-180,1.0,0.0,0.0);

    glutSolidTorus(0.05,0.1,
                    20,10);

    glTranslatef(0.11,0.0,-0.0);
    glColor3f(
        254.0/255.0,
        226.0/255.0,
        67.0/255.0
    );

    //front wheel
    glTranslatef(0.0,0.0,-0.66);
    glTranslatef(-0.22,0.16,-0.35);
    glTranslatef(-0.22,-0.16,0.35);


    //3
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
                0.04,0.04,//up radius down radius
                0.20,//height
                10,10 //stack
    );

    glColor3f(
        106.0/255.0,
        105.0/255.0,
        101.0/255.0
    );

    glutSolidTorus(0.05,0.1,
                    20,10);

    glColor3f(
            254.0/255.0,
            226.0/255.0,
            67.0/255.0
    );
    glTranslatef(0.0,0.0,0.67);
    glRotatef(180,1.0,0.0,0.0);

    //4
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
            0.04,0.04,//up radius down radius
            0.20,//height
            10,10 //stack
    );

    glColor3f(
        106.0/255.0,
        105.0/255.0,
        101.0/255.0
    );
    glRotatef(-180,1.0,0.0,0.0);

    glutSolidTorus(0.05,0.1,
                    20,10);

    glScalef(0.62,0.28,1.0);
    glTranslatef(0.21,0.0,0.0);

    glutSolidTorus(0.05,0.55,
                    20,30);

    glScalef(1/0.62,1/
             0.28,1.0);
    glTranslatef(-0.21,0.0,0.0);

    glColor3f(
        254.0/255.0,
        226.0/255.0,
        67.0/255.0
    );


    /***********************ARMS********************/
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glLoadIdentity();
    glPopMatrix(); //regive the position before flush
    glPushMatrix();
    glTranslatef(-0.2,0.1,0.2);
    glRotatef(-90,0.0,1.0,0.0);
    glRotatef(hands_transltar_angle,1.0,0.0,0.0);

    quadobj = gluNewQuadric();

    gluCylinder(quadobj,
                0.04,0.04,//up radius down radius
                0.30,//height
                10,10 //stack
    );

    /********************Upper part********************/
    glRotatef(90,0.0,1.0,0.0);
    glTranslatef(0.2,-0.0,-0.2);
    glTranslatef(-0.5,-0.055, 0.0);

    //some special stuff going on here!
    glTranslatef( 0.0, 0.1, 0.0);
    glRotatef(angle_arms_down,0.0,0.0,1.0);
    glTranslatef( 0.0, -0.1, 0.0);
    glScalef(0.1,0.5,1.0);
    glColor3f(
        106.0/255.0,
        105.0/255.0,
        101.0/255.0
    );

    glutSolidCube(0.5);

    glutSolidCube(0.45);

    glScalef(1/0.1,1/0.5,1.0);
    glRotatef(-90,1.0,0.0,0.0);
    glScalef(0.5,1.0,0.1);
    glTranslatef( -0.17, 0.0, -1.0);

    glutSolidCube(0.5);

    glutSolidCube(0.45);

    glScalef(1/0.5,1.0,1/0.1);
    glTranslatef( -0.10, -0.22, 0.03);

    glutSolidCube(0.05);
    for(int kk=0; kk<4;kk++)
    {
        glTranslatef( 0.0, 0.1, 0.00);
        glutSolidCube(0.05);
    }


    glColor3f(
        254.0/255.0,
        226.0/255.0,
        67.0/255.0
    );
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glLoadIdentity();
    glPopMatrix(); //regive the position before flush
    glTranslatef(-0.2,0.1,-0.2);
    glRotatef(-90,0.0,1.0,0.0);
    glRotatef(hands_transltar_angle,1.0,0.0,0.0);

    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
        0.04,0.04,//up radius down radius
        0.30,//height
        10,10 //stack
    );
}
/*==================END==TANK=======================*/

/*=========================GROUND==================*/
void draw_dirt()
{
    // Draw ground
	glColor3f(87.0/255.0,
            47.0/255.0,
            23.0f/255.0
    );

	glTranslatef(0.0,-0.33,0.0);
	glScalef(1.0,0.01,1.0);
	glutSolidCube(4);
	glScalef(1.0,1/0.01,1.0);
	glTranslatef(0.0,0.33,0.0);

	glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );

    if (hands_transltar_angle>=36.6 && hands_transltar_angle<=45.0 && angle_arms_down<=-40 && angle_arms_down>=-50 && move_tank<=-0.35 && move_tank>=-0.5)
    {
        lifting_it = true;
    }
    if( !lifting_it )
    {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glTranslatef(-1.0,-0.13,0.0);
        //glutSolidCube(0.20);
        //glutSolidCube(0.1);
        glScalef(0.2,0.2,0.2);
        glBegin(GL_TRIANGLES);
        for (i = 0; i < 20; i++) {
        /* color information here */
        glVertex3fv(&vdata[tindices[i][0]][0]);
        glVertex3fv(&vdata[tindices[i][1]][0]);
        glVertex3fv(&vdata[tindices[i][2]][0]);
        }
        glEnd();
        glShadeModel(GL_SMOOTH);
    }
    else
    {


        glTranslatef(0.0,0.0, 0.0);


        glTranslatef(0.0,0.30,0.0);
        //some special stuff going on here!
        glTranslatef(0.0,-hands_transltar_angle/150,0.0);


        glRotatef(rotate_tank,0.0,1.0,0.0);
        glTranslatef(-0.6+move_tank,-0.13,0.0);

        glScalef(0.2,0.2,0.2);
        glBegin(GL_TRIANGLES);
        for (i = 0; i < 20; i++) {
        /* color information here */
        glVertex3fv(&vdata[tindices[i][0]][0]);
        glVertex3fv(&vdata[tindices[i][1]][0]);
        glVertex3fv(&vdata[tindices[i][2]][0]);
        }
        glEnd();
    }


}
/*====================END==GROUND==================*/

/*========================KEYBOARD==================*/
void clavier(unsigned char touche,int x,int y)
{
    switch (touche)
    {
        case 'q' : /*la touche 'q' permet de quitter le programme */
        exit(0);
    }
}
/*==================END===KEYBOARD==================*/

/*===============WINDOWS RESHAPING==================*/
void reshape(int x,int y)
{
    if (x<y)
        glViewport(0,(y-x)/2,x,x);
    else
        glViewport((x-y)/2,0,y,y);
}
/*===========END=WINDOWS RESHAPING==================*/

/*===============MOUSE ACTIONS======================*/
void mouse(int button, int state,int x,int y)
{
    /* si on appuie sur le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        presse = 1; /* le booleen presse passe a 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold=y;
    }
    /* si on relache le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        presse=0; /* le booleen presse passe a 0 (faux) */
}
/*==========END==MOUSE ACTIONS======================*/

/*===============MOUSE EVENTS=======================*/
void mousemotion(int x,int y)
{
    if (presse) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
        en fonction de la position actuelle de la souris et de la derniere
        position sauvegardee */
        anglex=anglex+(x-xold);
        angley=angley+(y-yold);
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
}
/*========END====MOUSE EVENTS=======================*/

/*============SPECIAL=KEYBOARD======================*/
void processSpecialKeys(int key, int xx, int yy)
{

    if( key== GLUT_KEY_LEFT )
    {
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_SHIFT)
        {
            rotate_tank += 10.;
            glutPostRedisplay();
        }
        else
        {
            angle_arms_down -= 10.;
            glutPostRedisplay();
        }
    }
    else if ( key ==GLUT_KEY_RIGHT )
    {
        int mod = glutGetModifiers();
        if(mod == GLUT_ACTIVE_SHIFT)
        {
            rotate_tank -= 10.;
            glutPostRedisplay();
        }
        else
        {
            angle_arms_down += 10.;
            glutPostRedisplay();
        }
    }
    else if (key== GLUT_KEY_UP )
    {

        int mod = glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT)
        {
            if(hands_transltar_angle<75.)
            {
                hands_transltar_angle+=0.3;
                glutPostRedisplay();
            }
        }
        else
        {
        move_tank -= 0.1;
        glutPostRedisplay();
        }
     }

    else if ( key==  GLUT_KEY_DOWN )
    {

        int mod = glutGetModifiers();
        if (mod==GLUT_ACTIVE_SHIFT)
        {
            if(hands_transltar_angle>-40.)
            {
                hands_transltar_angle-=0.3;
                glutPostRedisplay();
            }
        }
        else
        {
            move_tank += 0.1;
            glutPostRedisplay();
        }
    }


}
/*=======END===SPECIAL=KEYBOARD====================*/
