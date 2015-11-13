// ----------------------------------------------
// 
// -----------------------------------------
// collisions!

#define rnd() (float)rand() / (float)RAND_MAX
#include <cmath>

const double oobillion = 1.0 / 1e9;
double timeDiff2(struct timespec *start, struct timespec *end) {
    return (double)(end->tv_sec - start->tv_sec ) +
	(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}


bool Game::checkBottomScreen()
{
    // bottom of screen, allow double jump
    if(player.position.y - player.height <= 0) // WORKS!!!
    {
	setPosY(player.height);
	setAccel(velX(),0);
	if_jump = true;
	return true;
    }
    return false;
}

bool Game::checkLeftScreenHit()
{
    // left side of screen
    if(player.position.x - player.width <= 0)
    {
	setPosX(player.width);
	setAccel(0,velY());
	return true;
    }
    return false;
}

bool Game::checkRightScreenHit()
{
    // right side of screen
    if(player.position.x + player.width >= window_width)
    {
	setPosX(window_width - player.width);
	setAccel(0,velY());
	return true;
    }	
    return false;
}

// checks PLATFORM collisions
bool Game::checkCollision()
{
    for(int i =0; i <5; i++)
    {
	Platform *p = &platform[i];
	// check y axis
	if(posY() - player.height >= p->pos.y  && posY() - player.height <= p->pos.y + p->height)
	    // checks x axis
	    if(posX() <= (p->pos.x + p->width) && posX() >= (p->pos.x - p->width))
		// makes him land first before setting it as a collision
		if(velY() <= 0)
		{ 
		    setPosY(player.height + (p->pos.y + p->height) - 0.04 * player.height);
		    setAccel(velX(),0);
		    if_jump = true;  
		    return true;
		}
    }
    return false;
}

// needs work
bool Game::checkMissileHit()
{
    if(!setMissiles)
	return false;
    int x = posX();
    int y = posY();
    int mx = missiles.position.x;
    int my = missiles.position.y;

    float distance = sqrt(pow(x-mx,2) + pow(y-my,2));
    if(distance <= missiles.height/3 || distance <= player.width)
	return true;
    return false;
}

void Game::removeMissiles()
{
    timespec cTime;
    clock_gettime(CLOCK_REALTIME, &cTime);
    double timeDiffer = timeDiff2(&missiles.MissilesStart, &cTime);
    if(timeDiffer >= 4)
    {
	setMissiles = false;
	//cout << "Test Missile" << endl;
    }
}

void Game::makeMissilesExp()
{
    if(setMissiles)
	return;
    float vely = 2;
    missiles.numExp = 200;

    int x = missiles.position.x;
    int y = missiles.position.y;

    //Particles &p = par;
    for(int i = 0; i < missiles.numExp; ++i)
    {
	missiles.exp[i].s.center.x = x;
	missiles.exp[i].s.center.y = y;
	missiles.exp[i].velocity.x = rnd() * 5 - rnd() * 5;

	missiles.exp[i].velocity.y = rnd() * player.height/vely - rnd() * player.height/vely ;
    }
    setMissiles = true;

}

/*
   void Game::drawMissilesExp()
   {
   glBindTexture(GL_TEXTURE_2D, 0);
// draw gut particles particles 
int randColorWater = 0;
for(int i = 0; i < missiles.numExp; ++i)
{
if(randColorWater == 100)
randColorWater = 0;

if(setbackground)
glColor3ub(255 - randColorWater,10 ,5);// reD? water
else
glColor3ub(150,160,255);
//glColor3ub(0+randColorWater ,0+randColorWater ,255);// looks best 
//glColor3ub(150 + randColorWater, 160 + randColorWater,255); // too light colored
Vec *c = &missiles.exp[i].s.center;
float w = 2; //- rnd() * 1;
float h = 2; //- rnd() * 1;
glBegin(GL_QUADS);
glVertex2i(c->x-w, c->y-h);
glVertex2i(c->x-w, c->y+h);
glVertex2i(c->x+w, c->y+h);
glVertex2i(c->x+w, c->y-h);
glEnd();
glPopMatrix();
randColorWater+= 10;
}
}
*/

// more collisions!!!
