

#ifndef MODULEFONT
#define MODULEFONT


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
enum {
  CENTER = 0,
  RIGHT,
  LEFT } ;

enum {
  REGULAR8x13 = 1,
  REGULAR6x10,
  SYMBOL,
  DESSIN } ;

void lineOutput(int xi,int yi,int xf,int yf) ;
void simpleBitmapOutput(char *format,...) ;
void simpleBitmapOutput(int fonte,char *format,...) ;
void simpleBitmapOutput(int depth,int fonte,char *format,...) ;
void placeFontCursor(float x,float y,float z) ;
void deplacementCursor(float x,float y,float z) ;
void setFont(void *font,int alignement) ;
void setAlignement(int a);
void bitmapStringOutput(char *format,...) ;
void bitmapStringOutput(GLfloat x,GLfloat y,GLfloat z,char *format,...) ;
void bitmapOutput(void *font,char *format,...) ;
void bitmapOutput(GLfloat x,GLfloat y,GLfloat z,void *font,char *format,...) ;
void setBold(int b) ;
void setAntialiased(int a) ;
void setEcartementCaracteres(float e) ;
int getBold(void) ;
int getAntialiased(void) ;
float getEcartementCaracteres(void) ;
void strokeOutput(GLfloat x,GLfloat y,float fact,char *format,...) ;

#endif
