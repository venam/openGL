#ifndef SPACE_SHIP_H_INCLUDED
#define SPACE_SHIP_H_INCLUDED

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void draw_Ship(bool is_flying);
void LoadGLTextures();
#endif // SPACE_SHIP_H_INCLUDED
