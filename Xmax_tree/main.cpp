/*******
Xmax Scene - Patrick Louis - 201202593
*******/

#include <stdio.h>
#include <GL/glut.h>
#include <ctime>
#include <iostream>

/*==================GLOBAL VARS======================*/
char presse;
int anglex,angley,x,y,xold,yold;
bool color_red_green       = false;
float alpha                = 1.0;
int counter                = 60;
GLfloat tree2_parts_rotate = 0.0;
GLfloat tree2_parts_rotate2 = 0.0;
GLfloat tree2_parts_rotate3 = 0.0;
int     tree2_counter      = 5;
/*==================GLOBAL VARS======================*/


/*==================FUNCTIONS PROTOTYPES==============*/
void draw_everything();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void processSpecialKeys(int key, int xx, int yy) ;
void ground();
void tree();
void tree2();
void clocker();
void lights();
void snow_man();
/*=============END==FUNCTIONS PROTOTYPES==============*/

/*======================LIGHT=========================*/
const GLfloat light_ambient[]  = { 20.0/255.0, 0.0/255.0, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 5.0f, 0.0f,1.0f };
const GLfloat mat_ambient[]    = { 0.5f, 0.5f, 0.5f, 0.5f };
const GLfloat mat_diffuse[]    = { 0.5f, 0.5f, 0.5, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 2.0f };
/*================END==LIGHT=========================*/

/*================MAIN=====FUNCTION==================*/
int main(int argc,char **argv)
{
    /* initialisation of GLUT*/
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(500,500);
    glutCreateWindow("Xmax Scene - Patrick Louis - venam");

    /* Initialisation of the window */
    glClearColor(16.0/255,12.0/255,27.0/255,1);
    glPointSize(2.0);

    /* Message for the user (on the console) */
    printf("q to QUIT the program\n");


    /* functions to be used while redrawing the window */
    glutDisplayFunc(draw_everything);
    glutIdleFunc(draw_everything);

    glutKeyboardFunc(clavier);           //keyboard
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

    ///important for the transparency
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	///

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
void draw_everything()
{
    int i,j;
    /* clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    //The moves related functions
    glRotatef(-angley,1.0,0.0,0.0);
    glRotatef(-anglex,0.0,1.0,0.0);

    ground();
    tree();

    glPushMatrix();
    glTranslatef(0.5,0.0,0.7);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5,-0.05, 0.1);
    glScalef(0.7,0.9,0.7);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9,-0.15,-0.2);
    glScalef(0.5,0.5,0.5);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9,-0.15,0.2);
    glScalef(0.6,0.5,0.6);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6,-0.12,0.2);
    glScalef(0.7,0.7,0.7);
    tree2();
    glPopMatrix();


    clocker();
    lights();

    glPushMatrix();
    glTranslatef(0.0,-0.06,0.3);
    glScalef(0.7,0.7,0.7);
    snow_man();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3,-0.14,-0.6);
    glRotatef(-40,0.0,1.0,0.0);
    glScalef(0.5,0.5,0.5);
    snow_man();
    glPopMatrix();

    //switch the buffers
    glutSwapBuffers();
}
/*==================END====DRAWING==================*/

/*====================CLOCK=========================*/
void clocker()
{
	glPushMatrix();

	//glass
	glPushMatrix();
	glColor4f(204.0/255.0,
              223.0/255.0,
              216.0f/255.0,
              0.6
    );
	glTranslatef(0.0,0.48,0.0);
	glScalef(1.0,1.0,0.2);
	glutSolidSphere(0.1,
					10,10);
	glPopMatrix();

	//protection
	glPushMatrix();
	glColor4f(44.0/255.0,
              44.0/255.0,
              44.0f/255.0,
              1.0
    );
    glTranslatef(0.0,0.48,0.0);
    glutSolidTorus(0.01,0.1,
				   20,20);
	glScalef(0.1,0.1,1.0);
	glColor4f(255.0/255.0,
              48.0/255.0,
              0.0f/255.0,
              0.5
    );
	glutSolidSphere(0.05,
					10,10);
	glPopMatrix();

	//pins
	time_t curr;
	tm local;
	time(&curr); // get current time_t value
	local=*(localtime(&curr)); // dereference and assign
	int minutes = local.tm_min;
	int hours   = local.tm_hour;
	int seconds = local.tm_sec;

	//360 = 60
	//360 = 12

	//BIG
	glPushMatrix();
	glColor4f(0.0/255.0,
              0.0/255.0,
              0.0f/255.0,
              1.0
    );
    glTranslatef(0.0,0.52,0.0);
    //set the rotation
    glTranslatef(0.0,-0.045,0.0);
    glRotatef(-(minutes*6),0.0,0.0,1.0);
    glTranslatef(0.0,0.045,0.0);

    glScalef(0.1,0.9,0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	//SMALL
	glPushMatrix();
	glColor4f(0.0/255.0,
              0.0/255.0,
              0.0f/255.0,
              1.0
    );
    glTranslatef(0.0,0.50,0.0);

    glTranslatef(0.0,-0.025,0.0);
    glRotatef(-(hours*30),0.0,0.0,1.0);
    glTranslatef(0.0,0.025,0.0);

    glScalef(0.1,0.5,0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	//SECONDS
	glPushMatrix();
	glColor4f(0.0/255.0,
              0.0/255.0,
              0.0f/255.0,
              1.0
    );
    glTranslatef(0.0,0.52,0.0);
    //set the rotation
    glTranslatef(0.0,-0.045,0.0);
    glRotatef(-(seconds*6),0.0,0.0,1.0);
    glTranslatef(0.0,0.045,0.0);

    glScalef(0.1,0.9,0.5);
	glutSolidCube(0.1);
	glPopMatrix();

	glPopMatrix();
}
/*================END=CLOCK=========================*/

/*====================LIGHTS=========================*/
void lights()
{
	glPushMatrix();
	alpha-=0.01;
	counter --;
	glColor4f(61.0/255.0,
              197.0/255.0,
              0.0f/255.0,
              alpha
    );
    if(counter<0)
	{
		counter = 60;
		if(color_red_green==true)
			color_red_green=false;
		else
			color_red_green=true;
		alpha=1.0;
	}

    if(color_red_green==true)
	{
		glColor4f(166.0/255.0,
				  31.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}

    for(int i=0;i<360;i+=40)
	{
		glPushMatrix();
		glRotatef(i,0.0,1.0,0.0);
		glTranslatef(0.2,-0.01,0.0);

		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
    for(int i=0;i<360;i+=40)
	{
		glPushMatrix();
		glRotatef(i,0.0,1.0,0.0);
		glTranslatef(0.3,-0.06,0.04);

		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
	glTranslatef(0.0,0.1,0.0);
    for(int i=0;i<360;i+=40)
	{
		glPushMatrix();
		glRotatef(i-20,0.0,1.0,0.0);
		glTranslatef(0.15,-0.01,0.0);

		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
	glTranslatef(0.0,0.1,0.0);
    for(int i=0;i<360;i+=40)
	{
		glPushMatrix();
		glRotatef(i+30,0.0,1.0,0.0);
		glTranslatef(0.1,-0.01,0.0);

		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
	glTranslatef(0.0,0.1,0.0);
    for(int i=0;i<360;i+=100)
	{
		glPushMatrix();
		glRotatef(i+70,0.0,1.0,0.0);
		glTranslatef(0.1,-0.01,0.0);

		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}

	glPopMatrix();
}
/*===============END==LIGHTS=========================*/

/*====================SNOW MAN=======================*/
void snow_man()
{
	glPushMatrix();

	glTranslatef(-0.6,-0.12,0.5);
	glColor3f(255.0/255.0,
              255.0/255.0,
              255.0f/255.0
              );
	glutSolidSphere(0.25,
					10,10);
	glTranslatef(0.0, 0.3,0.0);
	glutSolidSphere(0.15,
					10,10);

	glColor3f(0.0/255.0,
              0.0/255.0,
              0.0f/255.0
              );
	glTranslatef(-0.05, 0.05,-0.12);
	glutSolidSphere(0.017,
					10,10);
	glTranslatef(0.1, 0.00,0.0);
	glutSolidSphere(0.017,
					10,10);

	glColor3f(242.0/255.0,
              139.0/255.0,
              0.0f/255.0
              );
	glTranslatef(-0.05, -0.03,-0.03);
	glRotatef(180,1.0,0.0,0.0);
	glutSolidCone(0.025,0.07,
				  10,10);

	glPopMatrix();

}
/*================END=SNOW MAN=======================*/

/*===================TREE===========================*/
void tree()
{
	glPushMatrix();

	//base
	glPushMatrix();
	glColor3f(90.0/255.0,
              56.0/255.0,
              22.0f/255.0
    );
	glTranslatef(0.0,-0.057,0.0);
	glRotatef(90,1.0,0.0,0.0);
    GLUquadricObj *quadobj;
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
                0.1,0.1,//up radius down radius
                0.25,//height
                10,10 //stack
    );
    glPopMatrix();

    //leaves
	glColor3f(65.0/255.0,
              107.0/255.0,
              14.0f/255.0
    );
    glTranslatef(0.0,0.007,0.0);
    for(int i=0;i<360;i+=40)
	{
		glPushMatrix();
		glRotatef(i,0.0,1.0,0.0);
		glRotatef(20,1.0,0.0,0.0);
		glScalef(1.0,0.6,1.0);
		glutSolidCone( 0.1, 0.5,
						10,  10);
		glPopMatrix();
	}
    glTranslatef(0.0,0.1,0.0);
    for(int i=0;i<360;i+=40)
	{
		glPushMatrix();
		glRotatef(i+20,0.0,1.0,0.0);
		glRotatef(20,1.0,0.0,0.0);
		glScalef(1.0,0.6,1.0);
		glutSolidCone( 0.1, 0.4,
						10,  10);
		glPopMatrix();
	}
    glTranslatef(0.0,0.07,0.0);
    for(int i=0;i<360;i+=40)
	{
		glPushMatrix();
		glRotatef(i+60,0.0,1.0,0.0);
		glRotatef(20,1.0,0.0,0.0);
		glScalef(1.0,0.6,1.0);
		glutSolidCone( 0.1, 0.25,
						10,  10);
		glPopMatrix();
	}
    glTranslatef(0.0,0.07,0.0);
    for(int i=0;i<360;i+=60)
	{
		glPushMatrix();
		glRotatef(i+60,0.0,1.0,0.0);
		glRotatef(20,1.0,0.0,0.0);
		glScalef(1.0,0.6,1.0);
		glutSolidCone( 0.1, 0.2,
						10,  10);
		glPopMatrix();
	}
    glTranslatef(0.0,0.01,0.0);
    glRotatef(-90,1.0,0.0,0.0);
	glutSolidCone( 0.08, 0.13,
					10,  10);


	glPopMatrix();
}
/*==============END==TREE===========================*/

/*=================TREE2============================*/
void tree2()
{
	glPushMatrix();

	//make it with a counter every 10 redraw
	tree2_counter--;
	if(tree2_counter<0)
	{
		tree2_parts_rotate++;
		tree2_parts_rotate2-=1;
		tree2_parts_rotate3+=3;

		tree2_counter=5;
	}

	//PART 1 - BASE
	glPushMatrix();
	glColor3f(90.0/255.0,
              56.0/255.0,
              22.0f/255.0
    );
	glTranslatef(0.0,-0.075,0.0);
	glRotatef(90,1.0,0.0,0.0);
    GLUquadricObj *quadobj;
    quadobj = gluNewQuadric();
    gluCylinder(quadobj,
                0.05,0.1,//up radius down radius
                0.2,//height
                10,10 //stack
    );
	glPopMatrix();

	//PART 2
	glPushMatrix();
	glColor3f(65.0/255.0,
              107.0/255.0,
              14.0f/255.0
    );
	glTranslatef(0.0,-0.09,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glRotatef(tree2_parts_rotate2,0.0,0.0,1.0);
	glutSolidCone(0.25,0.2,
				 30,20);

    if(color_red_green==true)
	{
		glColor4f(166.0/255.0,
				  31.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	else
	{
		glColor4f(61.0/255.0,
				  197.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	for(int i=0;i<=360;i+=40)
	{
		glPushMatrix();
		glRotatef(i,0.0,0.0,1.0);
		glTranslatef(-0.2,0.1,0.04);
		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
	glPopMatrix();

	//PART 3
	glPushMatrix();
	glColor3f(65.0/255.0,
              107.0/255.0,
              14.0f/255.0
    );
	glTranslatef(0.0, -0.01,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glRotatef(tree2_parts_rotate-10,0.0,0.0,1.0);
	glutSolidCone(0.2,0.2,
				 30,20);
    if(color_red_green==false)
	{
		glColor4f(166.0/255.0,
				  31.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	else
	{
		glColor4f(61.0/255.0,
				  197.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	for(int i=0;i<=360;i+=40)
	{
		glPushMatrix();
		glRotatef(i,0.0,0.0,1.0);
		glTranslatef(-0.13,0.1,0.04);
		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
	glPopMatrix();

	//PART 3
	glPushMatrix();
	glColor3f(65.0/255.0,
              107.0/255.0,
              14.0f/255.0
    );
	glTranslatef(0.0, 0.06,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glRotatef(tree2_parts_rotate3,0.0,0.0,1.0);
	glutSolidCone(0.15,0.15,
				 30,20);
    if(color_red_green==true)
	{
		glColor4f(166.0/255.0,
				  31.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	else
	{
		glColor4f(61.0/255.0,
				  197.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	for(int i=0;i<=360;i+=80)
	{
		glPushMatrix();
		glRotatef(i,0.0,0.0,1.0);
		glTranslatef(-0.10,0.1,0.04);
		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
	glPopMatrix();

	//PART 4
	glPushMatrix();
	glColor3f(65.0/255.0,
              107.0/255.0,
              14.0f/255.0
    );
	glTranslatef(0.0, 0.12,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glRotatef(tree2_parts_rotate2-90,0.0,0.0,1.0);
	glutSolidCone(0.13,0.16,
				 30,20);
    if(color_red_green==false)
	{
		glColor4f(166.0/255.0,
				  31.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	else
	{
		glColor4f(61.0/255.0,
				  197.0/255.0,
				  0.0f/255.0,
				  alpha
		);
	}
	for(int i=0;i<=360;i+=120)
	{
		glPushMatrix();
		glRotatef(i,0.0,0.0,1.0);
		glTranslatef(-0.06,0.1,0.04);
		glutSolidSphere(0.02,
						10,10);
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
}
/*=============END=TREE2============================*/

/*=========================GROUND==================*/
void ground()
{
	glPushMatrix();
    // Draw ground
	glColor3f(230.0/255.0,
              225.0/255.0,
              173.0f/255.0
    );
    glRotatef(-1,1.0,0.0,0.0);

	glTranslatef(0.0,-0.33,0.0);
	glScalef(1.0,0.02,1.0);
	glutSolidCube(4);
	glPopMatrix();

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
