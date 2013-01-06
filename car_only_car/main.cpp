/*******
Buldozer - Patrick Louis - 201202593

inspired by lylat wars
*******/

#include <stdio.h>
#include <GL/glut.h>


GLuint texture[4];          //stores texture objects  ----------------------TESTING TEXTURES HERE

/*==================GLOBAL VARS======================*/
char presse;
int anglex,angley,x,y,xold,yold;
/*==================GLOBAL VARS======================*/


/*==================FUNCTIONS PROTOTYPES==============*/
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void draw_Ship();
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
    glutCreateWindow("Space_Ship - Patrick Louis - venam");

    /* Initialisation of the window */
    //glClearColor(62.0/255,124.0/255,102.0/255,0.5);
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);

    /* Message for the user (on the console) */
    printf("q to QUIT the program\n");


    /* functions to be used while redrawing the window */
    glutDisplayFunc(affichage);

    glutKeyboardFunc(clavier);           //keyboard
    glutReshapeFunc(reshape);            //keep the aspect of the cube when resizing the window
    glutMouseFunc(mouse);                //what will happens on mouse events
    glutMotionFunc(mousemotion);         //what happens when you move the cube

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
void affichage()
{
    /* clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();



    //The moves related functions
    glRotatef(-angley,1.0,0.0,0.0);
    glRotatef(-anglex,0.0,1.0,0.0);

    glColor3f(1, 1, 1);
    glDisable(GL_TEXTURE_2D);

    draw_Ship();



    //switch the buffers
    glutSwapBuffers();
}
/*==================END====DRAWING==================*/

/*=======================SHIP=======================*/
void draw_Ship()
{
    /********************start SIHP********************/
    //glMatrixMode(GL_MODELVIEW);
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texture[0]);   /* choose the texture to use.*/


    //cocpit
    glColor3f(230.0/255.0,
            225.0/255.0,
            173.0f/255.0
    );
    glPushMatrix();

	glPushMatrix();
    glScalef(1.0,1.0,0.5);
	glutSolidCube(0.5);
	glTranslatef(0.0,0.2,0.0);
	glutSolidCube(0.4);
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0,1.0,0.6);
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
/*==================END==SHIP=======================*/


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

