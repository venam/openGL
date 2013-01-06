/*******
Space Game - Patrick Louis - 201202593
inspired by lylat wars - starfox
todo:
-move the todo n a wishlist file
-joystick
-ship moves more smoothly
-collision effect
-help menu
-pause the game
-better font (or 3d font for game over)
-gpl licensing
-level not increasing exponentianly
-make the window reshaping function
-other items maybe
-jump to a level
-make it modular
*******/



#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include "ModuleFont.h"
#include "space_ship.h"
#include "asteroid.h"
#include "fuel.h"
#include "gun.h"
#include "increase_bullet.h"
#include <cstdlib> /*random*/
#include <ctime>
#include <iostream>
#include <unistd.h> //for sleep()

using namespace std;

/*==================GLOBAL VARS======================*/

struct Ship
{
    float Fuel;
    bool  Life;
} space_ship;
struct ASTE
{
    GLfloat posX;
    GLfloat posY;
    bool    atEND;
};
struct gas
{
    GLfloat posX;
    GLfloat posY;
    bool    atEND;
};
struct bullet_ball
{
    GLfloat posX;
    GLfloat posY;
    bool    atEND;
};
struct gun_actions
{
    GLfloat gun_y;
    GLfloat gun_x;
    bool shouting;
    int nbbullets;
    bool wantstoshoot;
    bool have_shot;
};
struct Vector3
{
    float x;
    float y;
    float z;
};
struct BoundingBox
{
    Vector3 max;
    Vector3 min;
};
BoundingBox fuelBox;
BoundingBox gunBox;
BoundingBox the_bullet_box;
bullet_ball the_bullet;
int number_of_boxes = 8;
BoundingBox boxes[10]; //10 bounding boxes -- first one == space-ship
gun_actions gun_move;
gas thegas;
ASTE aste[7];
GLfloat level =0.0;
bool    warning          = 0;
bool    playing          = false;
int     ship_turning     = 1;
GLfloat move_around_text = 0.0F;
GLfloat ship_move_left   = 0.0f;
bool    ship_flying      = false;
bool    joystick_on_off  = false;
bool    pause_game       = false;
bool    in_how_to        = false;
/*==================GLOBAL VARS======================*/

/*==================FUNCTIONS PROTOTYPES==============*/
void reshape(int x,int y);
void keyboard(unsigned char key,int x,int y);
void joystick(unsigned int buttonMask,int x, int y, int z);
void Draw_Everything();
void Draw_text();
void ship();
bool check_warning(Ship space_ship);
bool check_life(Ship space_ship);
void Draw_Not_Playing();
void processSpecialKeys(int key, int xx, int yy);
void specialup(int key, int x, int y);
void asteroids();
bool Collision(BoundingBox *b, BoundingBox *b2);
bool CollisionTest(BoundingBox b2);
void drawbox(BoundingBox *b);
void fuel();
void gun();
void aste_return(int number);
void init_game(int during);
void ball_bullet();
void Draw_pause();
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

/*================MAIN=====FUNCTION==================*/
int main(int argc,char **argv)
{
    /* initialize the Ship Status */
    space_ship.Fuel = 100.0;
    space_ship.Life = true;
    srand(time(0));
    init_game(0);
    gun_move.gun_x        =-10.0;
    gun_move.gun_y        =-10.0;
    gun_move.shouting     =false;
    gun_move.nbbullets    = 100;
    gun_move.wantstoshoot =false;
    gun_move.have_shot    =false;

    /* initialisation of GLUT*/
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(400,50);
    glutInitWindowSize(500,700);
    glutCreateWindow("Space Game - Patrick Louis - venam");

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
    glutJoystickFunc(joystick,50);       //the joystick bindings

    //Related to the lighting effect
    glCullFace(GL_BACK);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
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
    glMaterialfv(GL_FRONT, GL_EMISSION , emission);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations

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

    if(!playing)
        {
            Draw_Not_Playing();
            init_game(0);
        }
    else
        {
        	if(pause_game==false)
			{
				init_game(1);

				//draw the boring text
				Draw_text();
				glLoadIdentity();

				//draw the fearsome asteroids
				asteroids();
				glLoadIdentity();

				//draw the magnificient ship
				ship();
				glLoadIdentity();

				//draw the add_bullet
				ball_bullet();
				glLoadIdentity();

				//draw the fuel
				fuel();
				glLoadIdentity();

				//draw the bullet it's shooting
				gun();
				glLoadIdentity();




				//test the collition of the ship with the asteroid (if true the life =1 which is death for the ship)
				space_ship.Life = !(CollisionTest(boxes[0]));

				//when hitting the fuel it goes down (so the init will reput it up) + it add 30/100 to the fuel
				if( Collision(&boxes[0],&fuelBox) )
					{
						space_ship.Fuel+=30.0;
						if(space_ship.Fuel>100)
							space_ship.Fuel=100.0;
						thegas.posY=-2.0;
					}

				//when hitting the ball of fuel it goes down (so the init will reput it up) + it add 1 to the bomb
				if( Collision(&boxes[0],&the_bullet_box ))
					{
						gun_move.nbbullets++;
						the_bullet.posY=-2.0;
					}

				//check if there's collision between a bullet and an asteroid
				for(int kk=1; kk<8; kk++)
					{
						if( Collision(&gunBox, &boxes[kk]) )
							{
								//if there's collision we put wantstoshoot to false (which determines if we draw the bullet or not)
								//shooting is also set to false because it can only be changed from the bullet drawing function
								gun_move.wantstoshoot=false;
								gun_move.shouting=false;
								//we move the hitted asteroid to the top ; maybe I should also add 1 to the score
								aste_return(kk-1);
								level+=0.0003;
							}
					}
				/**********************DRAW BOX FOR TESTING*******************/
				//you can uncomment here to see all the boxes
				/*
				for(int jj=0;jj<9;jj++)
					drawbox(&boxes[jj]);
				drawbox(&fuelBox);
				drawbox(&gunBox);
				drawbox(&the_bullet_box);
				*/

			}
			else
			{
				//draw the word pause in the middle of the screen
				Draw_pause();
				glLoadIdentity();

				//draw the boring text
				Draw_text();
				glLoadIdentity();
			}

        }

    //switch the buffers
    glutSwapBuffers();
}
/*==================END====DRAWING==================*/


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
    placeFontCursor(-0.9F,0.92F,0.0F);
    int my_fuel = space_ship.Fuel;
    glColor4f(52.0/255.0,
              101.0/255.0,
              164.0f/255.0,
              0.3
             );
    simpleBitmapOutput(REGULAR8x13,"Fuel : ");

    glColor3f(138.0/255.0,
              226.0/255.0,
              52.0f/255.0
             );
    if(warning)
        {
            glColor3f(239.0/255.0,
                      41.0/255.0,
                      41.0f/255.0
                     );
        }
    simpleBitmapOutput(REGULAR8x13,"    %6.0f ", space_ship.Fuel );

    glColor3f(52.0/255.0,
              101.0/255.0,
              164.0f/255.0
             );
    placeFontCursor( -0.33F,0.92F,0.0F);
    simpleBitmapOutput(REGULAR8x13,"Bombs:");
    glColor3f(138.0/255.0,
              226.0/255.0,
              52.0f/255.0
             );
    simpleBitmapOutput(REGULAR8x13,"   %5.0f", ((float)gun_move.nbbullets) );

    glColor3f(52.0/255.0,
              101.0/255.0,
              164.0f/255.0
             );
    placeFontCursor( 0.17F,0.92F,0.0F);
    simpleBitmapOutput(REGULAR8x13,"Level:");
    glColor3f(138.0/255.0,
              226.0/255.0,
              52.0f/255.0
             );
    simpleBitmapOutput(REGULAR8x13,"  %6.0f", level*1000 );



    placeFontCursor( 0.4F,0.92F,0.0F);
    glColor3f(173.0/255.0,
              127.0/255.0,
              168.0f/255.0
             );
    simpleBitmapOutput(REGULAR8x13,"    q => quit " );

    //square box
    glColor3f(74.0/255.0,
              87.0/255.0,
              90.0f/255.0
             );
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.98F,0.98F);
    glVertex2f(-0.98F,0.9F);
    glVertex2f(0.98F,0.9F);
    glVertex2f(0.98F,0.98F);
    glEnd();

}
/*=============END==STATUS_TEXT=====================*/

/*==================SHOW_PAUSE======================*/
void Draw_pause()
{
    placeFontCursor(-0.1F,0.0F,0.0F);
	glColor4f(52.0/255.0,
              101.0/255.0,
              164.0f/255.0,
              0.3
             );
    simpleBitmapOutput(REGULAR8x13,"Pause");
}
/*=============END==SHOW_PAUSE======================*/

/*=============NOT_PLAYING==========================*/
//the menu appearing if the player is not in the game
void Draw_Not_Playing()
{
    /* clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    if(in_how_to==false)
	{
		if(move_around_text<-1)
			move_around_text=1.0;

		move_around_text-=0.001;

		//for the startup screen
		placeFontCursor(move_around_text,0.0F,0.0F);
		int my_fuel = space_ship.Fuel;
		glColor3f(1.0/255.0,
				  0.0/255.0,
				  255.0f/255.0
				 );
		simpleBitmapOutput(REGULAR8x13,"Press 'p' to Start the Game!");

		placeFontCursor(0.3,0.3F,0.0F);

		glColor3f(52.0/255.0,
				  101.0/255.0,
				  164.0f/255.0
				 );
		placeFontCursor( 0.5F,0.92F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"Level:");
		glColor3f(138.0/255.0,
				  226.0/255.0,
				  52.0f/255.0
				 );
		simpleBitmapOutput(REGULAR8x13,"    %6.0f", level*1000 );

		glColor3f(52.0/255.0,
				  101.0/255.0,
				  164.0f/255.0
				 );
		placeFontCursor( -0.8F,0.92F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"Score:");
		glColor3f(138.0/255.0,
				  226.0/255.0,
				  52.0f/255.0
				 );
		simpleBitmapOutput(REGULAR8x13,"    %6.0f", level*10000 );

		///make a how to appear at the bottom right
		placeFontCursor( 0.5F,-0.96F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"h -> How To");

		if(level>0)
			{
				glColor3f(0.0/255.0,
						  0.0/255.0,
						  0.0f/255.0
						 );
				placeFontCursor( -0.23F,0.29F,0.0F);
				simpleBitmapOutput(REGULAR8x13,"GAME   OVER!");
				glColor3f(239.0/255.0,
						  41.0/255.0,
						  41.0f/255.0
						 );
				placeFontCursor( -0.25F,0.3F,0.0F);
				simpleBitmapOutput(REGULAR8x13,"GAME   OVER!");
			}
	}
	else
	{
		glColor3f(138.0/255.0,
				  226.0/255.0,
				  52.0f/255.0
				 );
		///make a how to appear at top
		placeFontCursor( -0.1F,0.96F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"How To");
		placeFontCursor( -0.1F,0.955F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"______");


		///make a return back to appear at the bottom right
		glColor3f(239.0/255.0,
				  41.0/255.0,
				  41.0f/255.0
				 );
		placeFontCursor( 0.5F,-0.95F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"h -> Return");

		glColor3f(52.0/255.0,
				  101.0/255.0,
				  164.0f/255.0
				 );
		placeFontCursor( -0.9F,0.80F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"Arrows[<- & ->] : Move left/right");

		placeFontCursor( -0.9F,0.70F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"Arrows [^] : Fly (consume more fuel)");

		placeFontCursor( -0.9F,0.60F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"SPACE BAR : Shoot a Bomb");

		placeFontCursor( -0.9F,0.50F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"j : Enable Joysitck Mode");

		placeFontCursor( -0.9F,0.40F,0.0F);
		simpleBitmapOutput(REGULAR8x13,"s : Pause the game");


	}

    //switch the buffers
    glutSwapBuffers();
}
/*========END==NOT_PLAYING==========================*/

/*======================SHIP========================*/
void ship()
{
    //move the ship left/right
    if(ship_move_left>1.0)
        ship_move_left=-1.0;
    else if(ship_move_left<-1.0)
        ship_move_left=1.0;

    glTranslatef(ship_move_left,0.0,0.0);
    glTranslatef(0.0,-0.8,0.0);
    glRotatef(20,1.0,0.0,0.0);
    glScalef(0.30,0.30,0.30);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    if(ship_turning==0)
        {
            glRotatef(24,0.0,1.0,0.0);
        }

    if(ship_turning==2)
        {
            glRotatef(-24,0.0,1.0,0.0);
        }

    if(ship_flying)
        {
            glTranslatef(0.0,0.0,-0.5);
            if(space_ship.Fuel>0.01) //0.01==DEAD
                space_ship.Fuel-=0.04;
            boxes[0].max.z=0.4;
            boxes[0].min.z=-0.4;
        }
    else
        {
            boxes[0].max.z=0.2;
            boxes[0].min.z=-0.2;
        }
    boxes[0].max.x=ship_move_left+0.040;
    boxes[0].max.y=-0.60;
    boxes[0].min.x=ship_move_left-0.040;
    boxes[0].min.y=-0.8;

    draw_Ship(ship_flying);
}
/*=================END==SHIP========================*/

/*====================ASTEROIDS=====================*/
void asteroids()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    for(int k=0; k<7; k++)
        {
            glPushMatrix();
            glScalef(0.091,0.091,0.091);
            glTranslatef(aste[k].posX,aste[k].posY,0.0);

            draw_asteroid();
            glPopMatrix();
        }

}
/*==============END===ASTEROIDS=====================*/

/*====================FUEL==========================*/
void fuel()
{
    thegas.posY-=0.002;
    glTranslatef(thegas.posX,thegas.posY,0.0);
    draw_Fuel();
}
/*================END=FUEL==========================*/

/*====================BULLET BALLS==================*/
void ball_bullet()
{
    //goes down slower then the fuel
    the_bullet.posY-=0.001;
    glTranslatef(the_bullet.posX,the_bullet.posY,0.0);
    draw_increase_bullet();

}
/*==============END===BULLET BALLS==================*/


/*====================BULLET=========================*/
void gun()
{
    //wantstoshoot becomes true only when we press space & we have bullets
    if(gun_move.wantstoshoot==true)
        {
            //if the bullet is outisde we reinitialize it
            if(gun_move.gun_y>=1.7)
                {
                    gun_move.gun_x        =0.0;
                    gun_move.gun_y        =0.0;
                    gun_move.shouting=false;
                    gun_move.wantstoshoot=false;
                }

            //first time we press space it's false so the bullet will start going up from where the ship was
            if(gun_move.shouting==false)
                {
                    gun_move.gun_y        =0.0;
                    gun_move.gun_x=ship_move_left;
                }

            //after the first time we set shouting to false so the bullet will not move with the ship
            gun_move.shouting=true;

            //move the bullet and update the boxes
            gun_move.gun_y+=0.003;
            glTranslatef(gun_move.gun_x,-0.6+gun_move.gun_y,0.0);
            draw_gun();
            gunBox.max.x = gun_move.gun_x+0.05;
            gunBox.min.x = gun_move.gun_x-0.05;
            gunBox.max.y = -0.6+gun_move.gun_y+0.025;
            gunBox.min.y = -0.6+gun_move.gun_y-0.05;
            gunBox.max.z = 0.2;
            gunBox.min.z = -0.2;
        }

    //no-bullets so just in case it enters the drawing we put is outside of the window
    else
        {
            gunBox.max.x = -10.05;
            gunBox.min.x = -10.05;
            gunBox.max.y = -10.05;
            gunBox.min.y = -10.05;
            gunBox.max.z = -10.05;
            gunBox.min.z = -10.05;
        }
}
/*===============END==BULLET=========================*/

/*====================INIT VALUES===================*/
//initialize some values depending on which part of the game the player is in
void init_game(int during)
{
    /**not in the game (menu)**/
    if(during==0)
        {
            //initialize the gun box+ gun
            gunBox.max.x = gun_move.gun_x+0.05;
            gunBox.min.x = gun_move.gun_x-0.05;
            gunBox.max.y = -0.6+gun_move.gun_y+0.025;
            gunBox.min.y = -0.6+gun_move.gun_y-0.05;
            gunBox.max.z = 0.2;
            gunBox.min.z = -0.2;
            gun_move.gun_x        =-10.0;
            gun_move.gun_y        =-10.0;
            gun_move.shouting     =false;
            gun_move.nbbullets    =100;
            gun_move.wantstoshoot =false;
            gun_move.have_shot    =false;

            //define multiple random values
            int random_99  = rand()%99;
            int random_num = rand()%10;
            int random_neg = rand()%2;
            int random_neg2 = rand()%2;
            int random_Y   = rand()%12;
            int random_18  = rand()%18;

            /* initialize the Ship Status */
            space_ship.Fuel = 100.0;
            space_ship.Life = true;
            warning          = 0;
            ship_turning     = 1;
            ship_move_left   = 0.0f;

            //initialize the gas
            if(random_neg2==0)
                thegas.posX=-((float)random_99/100);
            else
                thegas.posX=((float)random_99/100);
            thegas.posY=((float)random_18/10+0.9);
            fuelBox.max.x = thegas.posX+0.07;
            fuelBox.min.x = thegas.posX-0.07;
            fuelBox.max.y = thegas.posY+0.07;
            fuelBox.min.y = thegas.posY-0.07;
            fuelBox.max.z = 0.2;
            fuelBox.min.z = -0.2;

            //initialize the ball of bullet
            random_99  = rand()%99;
            random_neg2 = rand()%2;
            if(random_neg2==0)
                the_bullet.posX=-((float)random_99/100);
            else
                the_bullet.posX=((float)random_99/100);
            //goes down more rarely then the fuel
            the_bullet.posY=((float)random_18/10+2.0);
            the_bullet_box.max.x = the_bullet.posX+0.07;
            the_bullet_box.min.x = the_bullet.posX-0.07;
            the_bullet_box.max.y = the_bullet.posY+0.07;
            the_bullet_box.min.y = the_bullet.posY-0.07;
            the_bullet_box.max.z = 0.2;
            the_bullet_box.min.z = -0.2;



            //initialize the asteroids
            if(random_neg==0)
                aste[0].posX  = ( (float) random_num )/2;
            else
                aste[0].posX  = -( (float) random_num )/2;
            aste[0].posY = random_Y+11.0;
            aste_return(0);
            for(int k=0; k<7; k++)
                {
                    random_num =rand()%10;
                    random_neg = rand()%2;
                    random_Y   = rand()%12;
                    aste[k].posY  = random_Y+11.0;
                    if(random_neg==0)
                        aste[k].posX  = aste[k-1].posX + ( (float) random_num )/2;
                    else
                        aste[k].posX  = -(aste[k-1].posX + ( (float) random_num )/2);
                    aste[k].atEND = false;
                    boxes[k+1].max.x = aste[k].posX/10+0.09;
                    boxes[k+1].max.y = aste[k].posY/11+0.09;
                    boxes[k+1].max.z = 0.2;
                    boxes[k+1].min.x = aste[k].posX/10-0.09;
                    boxes[k+1].min.y = aste[k].posY/11-0.09;
                    boxes[k+1].min.z = -0.2;
                }
        }

    /**inside the game **/
    else if(during==1)
        {
            if(space_ship.Life==0)
                playing=false;

            /*check the ship gas status */
            warning         = check_warning(space_ship);

            if(space_ship.Fuel>0.01)
                space_ship.Fuel-=0.01;
            else if(space_ship.Fuel<=0.01)
                playing=false;

            //randomize the gas
            if(thegas.posY<-1.0)
                {
                    int random_99  = rand()%99;
                    int random_18  = rand()%18;
                    int random_neg2 = rand()%2;
                    if(random_neg2==0)
                        thegas.posX=-((float)random_99/100);
                    else
                        thegas.posX=((float)random_99/100);
                    thegas.posY=((float)random_18/10+0.9);
                }
            fuelBox.max.x = thegas.posX+0.07;
            fuelBox.min.x = thegas.posX-0.07;
            fuelBox.max.y = thegas.posY+0.07;
            fuelBox.min.y = thegas.posY-0.07;
            fuelBox.max.z = 0.2;
            fuelBox.min.z = -0.2;

            //randomize the ball of bullets
            if(the_bullet.posY<-1.0)
                {
                    int random_99  = rand()%99;
                    int random_18  = rand()%18;
                    int random_neg2 = rand()%2;
                    if(random_neg2==0)
                        the_bullet.posX=-((float)random_99/100);
                    else
                        the_bullet.posX=((float)random_99/100);
                    the_bullet.posY=((float)random_18/10+2.0);
                }
            the_bullet_box.max.x = the_bullet.posX+0.07;
            the_bullet_box.min.x = the_bullet.posX-0.07;
            the_bullet_box.max.y = the_bullet.posY+0.07;
            the_bullet_box.min.y = the_bullet.posY-0.07;
            the_bullet_box.max.z = 0.2;
            the_bullet_box.min.z = -0.2;

            //randomize the asteroids
            for(int k=0; k<7; k++)
                {
                    aste[k].posY-=(0.01+(level));
                    if(aste[k].posY<=-8.5)
                        {
                            aste[k].atEND=true;
                            level+=0.0001;

                        }
                    if(aste[k].atEND)
                        {
                            aste[k].atEND=false;
                            int random_num = rand()%10;
                            int random_neg = rand()%2;
                            int random_Y   = rand()%12;
                            aste[k].posY  = random_Y+11.0;
                            if(k>0)
                                {
                                    if(random_neg==0)
                                        {
                                            random_neg = rand()%2;
                                            if(random_neg==0)
                                                {
                                                    aste[k].posX  = aste[k-1].posX + ( (float) random_num )/2;
                                                }
                                            else
                                                {
                                                    aste[k].posX  = aste[k-1].posX - ( (float) random_num )/2;
                                                }
                                        }
                                    else
                                        {
                                            random_neg = rand()%2;
                                            if(random_neg==0)
                                                {
                                                    aste[k].posX  = -(aste[k-1].posX + ( (float) random_num )/2);
                                                }
                                            else
                                                {
                                                    aste[k].posX  = -(aste[k-1].posX - ( (float) random_num )/2);
                                                }
                                        }
                                }
                            else
                                {
                                    random_neg = rand()%2;
                                    if(random_neg==0)
                                        aste[k].posX  = ( (float) random_num )/2;
                                    else
                                        aste[k].posX  = -(( (float) random_num )/2);
                                }
                        }
                    boxes[k+1].max.x = aste[k].posX/10+0.09;
                    boxes[k+1].max.y = aste[k].posY/11+0.09;
                    boxes[k+1].max.z = 0.2;
                    boxes[k+1].min.x = aste[k].posX/10-0.09;
                    boxes[k+1].min.y = aste[k].posY/11-0.09;
                    boxes[k+1].min.z = -0.2;
                }
        }

}
/*==============END===INIT VALUES===================*/

/*==============RETURN A SINGLE ASTE UP=============*/
void aste_return(int number)
{
    int random_Y   = rand()%12;
    int random_num = rand()%10;
    int random_neg = rand()%2;
    //the asteroids
    if(random_neg==0)
        aste[number].posX  = ( (float) random_num )/2;
    else
        aste[number].posX  = -( (float) random_num )/2;
    aste[number].posY = random_Y+11.0;
}
/*=========END==RETURN A SINGLE ASTE UP=============*/

/*========================WARNING===================*/
bool check_warning(Ship space_ship)
{
    return(space_ship.Fuel<50);
}
/*==================END===WARNING===================*/

/*========================KEYBOARD==================*/
void keyboard(unsigned char key,int x,int y)
{
    switch (key)
        {
        case 'p' :
        case 'P' :
            //otherwise we can reset the level while in the game
            if(playing == false)
                {
                    playing = true;
                    level   = 0;
                }
            break;
        case 'Q':
        case 'q':
            /*'q' to quit/terminate the program */
            exit(0);
            break;
        case ' ':
            //space has a functionality only when the player still has bullets
            if(gun_move.nbbullets>0)
                {
                    //we turn wantstoshoot to true so the bullet we be drawn
                    gun_move.wantstoshoot=true;
                    //the function to draw the bullet turns shouting to false so we know that the bullet is sent
                    if(gun_move.shouting==false)
                        gun_move.nbbullets--;
                }
            break;
		case 'j':
			//j enable the joystick
			if(joystick_on_off==false)
				joystick_on_off=true;
			else
				joystick_on_off=false;
			break;
		case 's':
			if (pause_game==false)
				pause_game=true;
			else
				pause_game=false;
			break;
		case 'h':
		case 'H':
			if(in_how_to==false)
				in_how_to=true;
			else
				in_how_to=false;

        }
}
/*==================END===KEYBOARD==================*/

/*==========NOT PRESSING=KEYBOARD==================*/
/* return the moves to 0 */
//we want that because otherwise we will have to put a timer to return the ship to ship_turning =1
void specialup(int key, int x, int y)
{
    switch (key)
        {
        case GLUT_KEY_UP:
            ship_flying = false;
            break;
        case GLUT_KEY_LEFT:
            ship_turning = 1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            ship_turning = 1;
            glutPostRedisplay();
            break;
        }
}
/*======END=NOT PRESSING=KEYBOARD==================*/

/*============SPECIAL=KEYBOARD======================*/
//process the special events happening when a special key is pressed
void processSpecialKeys(int key, int xx, int yy)
{
    //those events only happens when we press 'p' [playing->true] in the keyboard() function
    if(playing)
        {
            if( key== GLUT_KEY_LEFT )
                {
                	glutPostRedisplay();
                    ship_move_left -= 0.06;
                    //before drawinf the ship we check if it's turning and to which side
                    glutPostRedisplay();
                    ship_turning    = 0;

                }
            else if ( key ==GLUT_KEY_RIGHT )
                {
                	glutPostRedisplay();
                    ship_move_left += 0.06;
                    glutPostRedisplay();
                    //before drawinf the ship we check if it's turning and to which side
                    ship_turning    = 2;
                    glutPostRedisplay();
                }
            else if ( key == GLUT_KEY_UP )
                {
                    ship_flying = true;
                    glutPostRedisplay();
                }
        }

}
/*=======END===SPECIAL=KEYBOARD====================*/

/*==============JOYSTICK=INPUTS====================*/
void joystick(unsigned int buttonMask,int x, int y, int z)
{
	if(joystick_on_off==true)
	{
		  ship_flying = false;
		  ship_turning = 1;
		  ///TRIANGLE
		  if(buttonMask==GLUT_JOYSTICK_BUTTON_A)
		  {
				exit(0);
				glutPostRedisplay();
		  }
		  ///CIRCLE
		  if(buttonMask==GLUT_JOYSTICK_BUTTON_B)
		  {
					  //otherwise we can reset the level while in the game
				if(playing == false)
					{
						playing = true;
						level   = 0;
					}
		  }
		  ///CROSS
		  if(buttonMask==GLUT_JOYSTICK_BUTTON_C)
		  {
				if(gun_move.nbbullets>0)
					{
						//we turn wantstoshoot to true so the bullet we be drawn
						gun_move.wantstoshoot=true;
						//the function to draw the bullet turns shouting to false so we know that the bullet is sent
						if(gun_move.shouting==false)
							gun_move.nbbullets--;
					}
		  }
		  ///SQUARE
		  if(buttonMask==GLUT_JOYSTICK_BUTTON_D)
		  {
				ship_flying = true;
				glutPostRedisplay();
		  }
		  if(buttonMask==512)
		  {
		  	if(pause_game==false)
			{
				pause_game=true;
				//sleep(1);
			}

			else
				pause_game=false;
		  }
		  if(x<0)
		  {
				if(playing)
				{
					  ship_move_left -= 0.045;
					  //before drawinf the ship we check if it's turning and to which side
					  ship_turning    = 0;
					  glutPostRedisplay();
				}
		  }
		  if(x>0)
		  {
				if(playing)
				{
						ship_move_left += 0.045;
						//before drawinf the ship we check if it's turning and to which side
						ship_turning    = 2;
						glutPostRedisplay();
				}
		  }
	}
}
/*==========END=JOYSTICK=INPUTS====================*/

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

/*==============CHECK IF COLLISION==================*/
//return true if collision between 2 bounding box
bool Collision(BoundingBox *b, BoundingBox *b2)
{
    return (
               b2->max.x <= b->max.x && b2->max.x >= b->min.x &&
               b2->max.y <= b->max.y && b2->max.y >= b->min.y &&
               b2->max.z <= b->max.z && b2->max.z >= b->min.z
           )||
           (
               b2->min.x <= b->max.x && b2->min.x >= b->min.x &&
               b2->min.y <= b->max.y && b2->min.y >= b->min.y &&
               b2->min.z <= b->max.z && b2->min.z >= b->min.z
           )||
           (
               b2->max.x-(b2->max.x-b2->min.x) <= b->max.x && b2->max.x-(b2->max.x-b2->min.x) >= b->min.x &&
               b2->max.y <= b->max.y && b2->max.y >= b->min.y &&
               b2->max.z <= b->max.z && b2->max.z >= b->min.z
           )||
           (
               b2->min.x+(b2->max.x-b2->min.x) <= b->max.x && b2->min.x+(b2->max.x-b2->min.x) >= b->min.x &&
               b2->min.y <= b->max.y && b2->min.y >= b->min.y &&
               b2->min.z <= b->max.z && b2->min.z >= b->min.z
           )||
           (
               b2->min.x+((b2->max.x-b2->min.x)/2) <= b->max.x && b2->min.x+((b2->max.x-b2->min.x)/2) >= b->min.x &&
               b2->min.y <= b->max.y && b2->min.y >= b->min.y &&
               b2->min.z <= b->max.z && b2->min.z >= b->min.z
           )
           ;
}
//test the collision between a bounding box and the asteroids
bool CollisionTest(BoundingBox b2)
{
    bool rez = false;
    for (int i=0; i<number_of_boxes; i++)
        rez = rez || Collision(&boxes[i+1],&b2);
    return rez;
}
//draw a bounding box
void drawbox(BoundingBox *b)
{
    glColor3f(1,1,1);
    glBegin (GL_LINE_LOOP);
    glVertex3f(b->max.x,b->max.y,b->min.z); // 0
    glVertex3f(b->min.x,b->max.y,b->min.z); // 1
    glVertex3f(b->min.x,b->min.y,b->min.z); // 2
    glVertex3f(b->max.x,b->min.y,b->min.z); // 3
    glEnd();

    glBegin (GL_LINE_LOOP);
    glVertex3f(b->max.x,b->min.y,b->max.z); // 4
    glVertex3f(b->max.x,b->max.y,b->max.z); // 5
    glVertex3f(b->min.x,b->max.y,b->max.z); // 6
    glVertex3f(b->min.x,b->min.y,b->max.z); // 7
    glEnd();

    glBegin (GL_LINE_LOOP);
    glVertex3f(b->max.x,b->max.y,b->min.z); // 0
    glVertex3f(b->max.x,b->max.y,b->max.z); // 5
    glVertex3f(b->min.x,b->max.y,b->max.z); // 6
    glVertex3f(b->min.x,b->max.y,b->min.z); // 1
    glEnd();

    glBegin (GL_LINE_LOOP);
    glVertex3f(b->max.x,b->min.y,b->max.z); // 4
    glVertex3f(b->min.x,b->min.y,b->max.z); // 7
    glVertex3f(b->min.x,b->min.y,b->min.z); // 2
    glVertex3f(b->max.x,b->min.y,b->min.z); // 3

    glEnd();
}
/*==========END=CHECK IF COLLISION==================*/
