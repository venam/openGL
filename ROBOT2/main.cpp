/********************************************************/
/*                     mecha robots                     */
/********************************************************/
/*       DISPLAY A FREAKING AWESOME ROBOT               */
/********************************************************/
/* Coded  by Patrick Louis                              */
/* date:         Thu Nov 15 14:52:06 EET 2012           */
/********************************************************/

#include <stdio.h>
#include <GL/glut.h>
//#include <unistd.h> //for sleep()


/*==================GLOBAL VAR=======================*/
char presse;
int anglex,angley,x,y,xold,yold;
GLfloat my_arm_moves      = 0.0;
GLfloat my_arm_moves_side = 0.0;
GLfloat my_arm_moves_shift=0.0;
/*===========END===GLOBAL VAR=======================*/


/*==================PROTOTYPES=======================*/
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void processSpecialKeys(int key, int xx, int yy);
void robot_dancing_idle();
/*============END==PROTOTYPES=======================*/


/*======================LIGHT=========================*/
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.5f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 0.5f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 0.5f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 0.5f };
const GLfloat high_shininess[] = { 100.0f };
/*================END==LIGHT=========================*/


/*======================MAIN==========================*/
int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(350,350);
  glutCreateWindow("Freaking MECHA - Patrick Louis - venam");

  /* Initialisation d'OpenGL */
  glClearColor(0.12,0.12,0.12,1.0);
  glPointSize(3.0); //size of the points
  glEnable(GL_DEPTH_TEST);

  /* affichage du menu sur l'invite de commande */
  printf("p pour affichage en mode carre plein\n");
  printf("s pour affichage en mode sommets seuls\n");
  printf("f pour affichage en mode fil de fer\n");
  printf("q pour quitter le programme\n");
  printf("d pour Enable Depth Test\n");
  printf("D pour Disable Depth Test\n");



  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage); //THIS IS WHAT WE WILL DRAW!!!
  //glutIdleFunc(robot_dancing_idle);

  glutKeyboardFunc(clavier);           //keyboard
  glutSpecialFunc(processSpecialKeys); //what happens when special keys are clicked
  glutReshapeFunc(reshape);            //keep the aspect of the cube when resizing the window
  glutMouseFunc(mouse);                //what will happens on mouse events
  glutMotionFunc(mousemotion);         //what happens when you move the cube


    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

  /* enters main glut loop */
  glutMainLoop();
  return 0;
}
/*=================END=MAIN==========================*/


/*==================DRAW ROBOT=======================*/
void affichage()
{
  int i,j;
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();          //reset eveything related to the state machine


  glRotatef(-angley,1.0,0.0,0.0); //angle , x , y, z
  glRotatef(-anglex,0.0,1.0,0.0);

  /*gluLookAt(	0.0f, 0.0f,  3.0f,
				0.0f, 5.0f,  0.0f,
				0.0f, 0.0f,  0.0f);*/



  /* Body */
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );
  glPushMatrix();
  glScalef(1.0F,1.0F,0.7F);

  glutWireSphere(0.3,
                30,30);
  glutWireSphere(0.25,
                30,30);
  glScalef(1.0F,1.0F,0.6F);
  glTranslatef(0.0, 0.0, -0.5);
    glColor3f(
            69.0/255.0,
            67.0/255.0,
            149.0/255.0);
  glTranslatef(0.0,  0.1, 0.9);
  glutSolidCube(0.2);
  glutWireCube(0.17);
  glutWireCube(0.15);
  glTranslatef(0.0, -0.1, -0.9);

  glutSolidSphere( 0.08,
                  10, 10);
  glTranslatef(0.1, 0.0, 0.0);
  glutSolidSphere( 0.04,
                  10, 10);
  glTranslatef(-0.2, 0.0, 0.0);
  glutSolidSphere( 0.04,
                  10, 10);
  glTranslatef(0.1, 0.1, 0.0);
  glutSolidSphere( 0.04,
                  10, 10);
  glTranslatef(0.0, -0.2, 0.0);
  glutSolidSphere( 0.04,
                  10, 10);
    glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );


  /* head */
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLoadIdentity();
  glPopMatrix(); //regive the position before flush
  glPushMatrix();
  glScalef(1.0F,1.0F,0.7F);
  glTranslatef(-0.0, 0.24, 0.1);
  glutWireSphere(0.23,
                10,10);

  glScalef(1.0F,1.0F,1.4F);
  glTranslatef(0.0, 0.082, -0.13);
  glColor3f(
        221.0/255.0,
        226.0/255.0,
        65.0/255.0);
  glLineStipple(0.5, 0x3F07);
  glEnable(GL_LINE_STIPPLE);

  glutSolidCube(0.13);
  glutSolidCube(0.12);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glDisable(GL_LINE_STIPPLE);
  glutSolidCube(0.09);

  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  //eyes
  glColor3f(
            69.0/255.0,
            67.0/255.0,
            149.0/255.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glTranslatef(-0.025, 0.0, -0.072);
  glScalef(1.0F,1.0F,0.2F);
    glutSolidSphere( 0.02,
                  20, 20);
    glTranslatef(0.05, 0.0, 0.0);
    glutSolidSphere( 0.02,
                  20, 20);



  //return normal color and line mode
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );

  //Feet
  glLoadIdentity();
  glPopMatrix(); //regive the position before flush
  glPushMatrix();

  glPushMatrix();

  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  glTranslatef(0.0, -0.4, 0.0);
  glRotatef(280.,1.0,0.0,0.0);
    glColor3f(
            128.0/255.0,
            130.0/255.0,
            148.0/255.0);

     /*the really magic cylinder*/
  //------------------------------------

  //check this one latter

  GLUquadricObj *quadobj;
  quadobj = gluNewQuadric();
  gluCylinder(quadobj,
              0.05,0.05,//up radius down radius
              0.15,//height
              20,20 //stack
              );
 //-------------------------------------
    glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );
 glRotatef(-15.,1.0,0.0,0.0);

  glutSolidSphere( 0.055,
                  20, 20);

  glTranslatef(0.05, -0.0, 0.0);
  glutSolidSphere( 0.04,
                  10, 10);
  glTranslatef(-0.1, -0.0, 0.0);
  glutSolidSphere( 0.04,
                  10, 10);
    glColor3f(
            128.0/255.0,
            130.0/255.0,
            148.0/255.0);
  glTranslatef(0.26, 0.017, -0.34);
  glRotatef(45.,0.0,1.0,0.0);
  glRotatef(290.,0.0,1.0,0.0);
     /*the really magic cylinder*/
  //------------------------------------

  //check this one latter
  quadobj = gluNewQuadric();
  gluCylinder(quadobj,
              0.035,0.02,//up radius down radius
              0.355,//height
              20,20 //stack
              );
 //-------------------------------------
 glRotatef(-45.,0.0,1.0,0.0);
 glRotatef(-290.,0.0,1.0,0.0);
 glTranslatef(0.0, -0.0, -0.16);
     /*the really magic cylinder*/
  //------------------------------------
    glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );
  //check this one latter
  quadobj = gluNewQuadric();
  gluCylinder(quadobj,
              0.2,0.09,//up radius down radius
              0.2,//height
              20,20 //stack
              );
  gluCylinder(quadobj,
              0.16,0.086,//up radius down radius
              0.2,//height
              50,50 //stack
              );
 //-------------------------------------


//=================OTHER FOOT==================
    glColor3f(
            128.0/255.0,
            130.0/255.0,
            148.0/255.0);
  glLoadIdentity();
  glPopMatrix(); //regive the position before flush
  glPushMatrix();

  glPushMatrix();
  glTranslatef(0.0, -0.4, 0.0);
  glRotatef(280.,1.0,0.0,0.0);

glRotatef(-15.,1.0,0.0,0.0);

  glTranslatef(-0.18, 0.017, -0.34);
  glRotatef(90.,0.0,1.0,0.0);
  glRotatef(290.,0.0,1.0,0.0);
     /*the really magic cylinder*/
  //------------------------------------

  //check this one latter
  quadobj = gluNewQuadric();
  gluCylinder(quadobj,
              0.035,0.02,//up radius down radius
              0.355,//height
              20,20 //stack
              );
 //-------------------------------------
 glRotatef(-90.,0.0,1.0,0.0);
 glRotatef(-290.,0.0,1.0,0.0);
 glTranslatef(0.0, -0.0, -0.16);
     /*the really magic cylinder*/
  //------------------------------------
    glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );
  //check this one latter
  quadobj = gluNewQuadric();
  gluCylinder(quadobj,
              0.2,0.09,//up radius down radius
              0.2,//height
              20,20 //stack
              );
  gluCylinder(quadobj,
              0.16,0.086,//up radius down radius
              0.2,//height
              50,50 //stack
              );
 //-------------------------------------







  //Arms
  glLoadIdentity();
  glPopMatrix(); //regive the position before flush
  glPushMatrix();
  glTranslatef(-0.3, 0.1, 0.0);

  glRotatef(my_arm_moves,1.0, 0.0, 0.0);
  glRotatef(-my_arm_moves_side,0.0, 1.0, 0.0);
  glutSolidSphere( 0.1,
                  20, 20);
  glutSolidSphere( 0.07,
                  20, 20);
  glTranslatef(0.0,0.0,-0.1);

  glTranslatef(0.0,0.0,-0.2);
      glColor3f(
            128.0/255.0,
            130.0/255.0,
            148.0/255.0);
    gluCylinder(quadobj,
              0.03,0.03,//up radius down radius
              0.2,//height
              20,20 //stack
              );
        glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );
  glRotatef(40.,0.0,0.0,1.0);
  glTranslatef(-0.00,0.0,-0.07);
  glScalef(1.0F,0.5F,1.0F);
  //rotate here

  glRotatef(my_arm_moves_shift,1.0, 0.0, 0.0);
    glutSolidSphere( 0.1,
                  10, 10);
    glutSolidSphere( 0.08,
                  20, 20);
  glScalef(1.0F,1/0.5F,1.0F);
  //glRotatef(40.,0.0,0.0,1.0);
  glRotatef(-90.,1.0,0.0,0.0);
  glScalef(1.0F,3.0F,1.0F);
  glTranslatef(-0.05, 0.03, -0.03);
  glutSolidSphere( 0.02,
                  6, 6);
  glTranslatef(0.04,0.0,0.0);
  glutSolidSphere( 0.02,
                  6, 6);
  glTranslatef(0.04,0.0,0.0);
  glutSolidSphere( 0.02,
                  6, 6);



  //right arm
  glLoadIdentity();
  glPopMatrix();
  glTranslatef(0.3, 0.1, 0.0);
  glRotatef(my_arm_moves,1.0, 0.0, 0.0);
  glRotatef(my_arm_moves_side,0.0, 1.0, 0.0);

  glutSolidSphere( 0.1,
                  20, 20);
  glutSolidSphere( 0.07,
                  20, 20);

  glTranslatef(0.0,0.0,-0.1);

  glTranslatef(0.0,0.0,-0.2);
      glColor3f(
            128.0/255.0,
            130.0/255.0,
            148.0/255.0);
    gluCylinder(quadobj,
              0.03,0.03,//up radius down radius
              0.2,//height
              20,20 //stack
              );
    glColor3f(
            124.0/255.0,
            120.0/255.0,
            210.0/255.0
           );
  glRotatef(-40.,0.0,0.0,1.0);
  glTranslatef(-0.00,0.0,-0.07);
  glScalef(1.0F,0.5F,1.0F);
  //rotate here
  glRotatef(my_arm_moves_shift,1.0, 0.0, 0.0);
    glutSolidSphere( 0.1,
                  10, 10);
    glutSolidSphere( 0.08,
                  20, 20);

  glScalef(1.0F,1/0.5F,1.0F);
  //glRotatef(40.,0.0,0.0,1.0);
  glRotatef(-90.,1.0,0.0,0.0);

  glScalef(1.0F,3.0F,1.0F);

  glTranslatef(-0.05, 0.03, -0.03);
      glutSolidSphere( 0.02,
                  6, 6);
  glTranslatef(0.04,0.0,0.0);
  glutSolidSphere( 0.02,
                  6, 6);
  glTranslatef(0.04,0.0,0.0);
  glutSolidSphere( 0.02,
                  6, 6);

  glutSwapBuffers();
}
/*===========END===DRAW ROBOT=======================*/


/*================DRAW ROBOT=DANCING=================*/
void robot_dancing_idle()
{
    /*
    GLfloat my_arm_moves      = 0.0;
    GLfloat my_arm_moves_side = 0.0;
    GLfloat my_arm_moves_shift=0.0;
    */

    if (my_arm_moves<60)
    {
        my_arm_moves+=10.;
        affichage();

    }
    else
    {
        my_arm_moves-=70.;
        affichage();
    }

}
/*==========END==DRAW ROBOT=DANCING=================*/


/*==================KEYBOARD =======================*/
void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}
/*==========END====KEYBOARD =======================*/


/*==============RESHAPE WINDOW APSECT==============*/
void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}
/*==========END=RESHAPE WINDOW APSECT==============*/


/*==================MOUSE ACTIONS=================*/
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
/*=============END=MOUSE ACTIONS=================*/


/*==================MOUSE EVENTS=================*/
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
/*==============END=MOUSE EVENTS=================*/


/*============SPECIAL=KEYBOARD==================*/
void processSpecialKeys(int key, int xx, int yy) {

        if( key== GLUT_KEY_LEFT )
        {
                my_arm_moves_side -= 10.;
                glutPostRedisplay();
        }
        else if ( key ==GLUT_KEY_RIGHT )
        {

                my_arm_moves_side += 10.;
                glutPostRedisplay();
        }
        else if (key== GLUT_KEY_UP )
        {

                int mod = glutGetModifiers();
                if (mod==GLUT_ACTIVE_SHIFT)
                {
                    if(my_arm_moves_shift<75.)
                    {
                        my_arm_moves_shift+=30.;
                        glutPostRedisplay();
                    }
                }
                else
                {
                my_arm_moves += 10.;
                glutPostRedisplay();
                }
         }

          else if ( key==  GLUT_KEY_DOWN )
          {

                int mod = glutGetModifiers();
                if (mod==GLUT_ACTIVE_SHIFT)
                {
                    if(my_arm_moves_shift>-40.)
                    {
                        my_arm_moves_shift-=30.;
                        glutPostRedisplay();
                    }
                }
                else
                {
                my_arm_moves -= 10.;
                glutPostRedisplay();
                }
          }


	}
/*=======END===SPECIAL=KEYBOARD================*/
