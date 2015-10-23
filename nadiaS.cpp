/*Nadia Salem*/
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "brandiD.h"

void drawPlatform(Game *game)
{
    glColor3ub(255,255,255);

    Shape *s;
    float w, h;
    for(int j = 0; j < 5; j++)
    {
        s = game->platform[j];
        glPushMatrix();
        glTranslatef(s->center.x,s->center.y, 0);
        w=s->width;
        h=s->height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w,h);
        glVertex2i(w,h);
        glVertex2i(w,-h);
        glEnd();
        glPopMatrix();
    }
}

void makePlatform(int amt, Game *game)
{
    
    for(int i = 0; i<amt; i++)
    {
        game->platform[i].platform.width=50;
        game->platform[i].platform.height=10;
        game->platform[i].platform.center.x=120+5*65-50*i;
        game->platform[i].platform.center.y=120+5*65-50*i;
    }
}
