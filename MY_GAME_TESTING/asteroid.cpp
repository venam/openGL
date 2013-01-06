#include "asteroid.h"
#include <GL/glut.h>
#include <cstdlib> /*random*/
#include <ctime>
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
GLfloat rotation_over_itself = 0.0;


void draw_asteroid()
{
        int random__ = rand()%255;
        int random__1 = rand()%255;
        int random__2 = rand()%255;
        glColor4f(random__/255.0,
                random__1/255.0,
                random__2/255.0,
                0.2
        );
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

        rotation_over_itself+=0.2;
        glRotatef(rotation_over_itself,1.0,1.0,0.0);
        glBegin(GL_TRIANGLES);
        for (i = 0; i < 20; i++) {
        /* color information here */
        glVertex3fv(&vdata[tindices[i][0]][0]);
        glVertex3fv(&vdata[tindices[i][1]][0]);
        glVertex3fv(&vdata[tindices[i][2]][0]);
        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}
