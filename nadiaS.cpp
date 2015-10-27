/*Nadia Salem*/
int random(int x, int y)
{
     srand(time(NULL));
    int num;
    if(x < 0 && y < 0)
    {
            num = rand()%((y-x))+y;
    }
    else if (x > 0 && y > 0)
    {
        if(x < y)
        {
            num = rand() % (x-y)+ x;
        }
        else
        num = rand() % (x-y) + y;
    }
    else
    {
        if(x < y)
           num = rand() % ((-1*x)+y) +x;
        else
        num = rand() % ((-1*y)+x)+y;
    }
return num;
}
void drawPlatform(Game *game, int amt)
{
    glColor3ub(255,255,255);

    
    float w, h;
    for(int j = 0; j < amt; j++)
    {
        glPushMatrix();
        glTranslatef(game->platform[j].pos.x,game->platform[j].pos.x, 0);
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

void makePlatform(int amt, Game *game, int startCenterX)
{
    
    for(int i = 0; i<amt; i++)
    {
        game->platform[i].width=50;
        game->platform[i].height=10;
        game->platform[i].pos.x=startCenterX +random(-100,100) +30*i;
        game->platform[i].pos.y=120+5*65-50*i;
    }
}
