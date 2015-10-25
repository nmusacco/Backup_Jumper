/*Nadia Salem*/
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "brandiD.h"

void drawPlatform(Game *game)
{
    glColor3ub(255,255,255);

    
    float w, h;
    for(int j = 0; j < 5; j++)
    {
        glPushMatrix();
        glTranslatef(s->center.x,s->center.y, 0);
        w=game->platform[i].width;
        h=game->platform[i].height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w,h);
        glVertex2i(w,h);
        glVertex2i(w,-h);
        glEnd();
        glPopMatrix();
    }
}

void makePlatform(int amt, Game *game, int centerX)
{
    
    for(int i = 0; i<amt; i++)
    {
        game->platform[i].width=50;
        game->platform[i].height=10;
        game->platform[i].pos.x=centerX;
        game->platform[i].pos.y=120+5*65-50*i;
    }
}
