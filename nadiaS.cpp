/*Nadia Salem*/

void drawPlatform(Game *game, int amt)
{
    glColor3ub(255,255,255);

    
    float w, h;
    for(int j = 0; j <2; j++)
    {
        glPushMatrix();
        glTranslatef(game->platform[j].pos.x,game->platform[j].pos.y, 0);
        w=game->platform[j].width;
        h=game->platform[j].height;
        glBegin(GL_QUADS);
        glVertex2i(-w,-h);
        glVertex2i(-w,h);
        glVertex2i(w,h);
        glVertex2i(w,-h);
        glEnd();
        glPopMatrix();
    }
}


// Pedro Gonzalez: "this will cause issue if amt is greater than 5!!!"
//Nadia Salem: I fixed Drawplatforms so it won't happen

void makePlatform(int amt, Game *game)
{
    srand(time(NULL));
    for(int i = 0; i<2; i++)
    {
        game->platform[i].width=50;
        game->platform[i].height=10;
        game->platform[i].pos.x=window_width/(2);
        game->platform[i].pos.y=(window_height+i+1)/4*20;
    }
}
