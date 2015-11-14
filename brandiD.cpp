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

	float y = 0.04;
	if(window_height > 1080)
	y = 0.06;

	Platform *p = platformHead;
	while(p)
	{
		// checks x axis
		if(posX() <= (p->pos.x + p->width) && posX() >= (p->pos.x - p->width))
			// check y axis
			if(posY() - player.height >= p->pos.y  && posY() - player.height <= p->pos.y + p->height)
			// makes him land first before setting it as a collision
				if(velY() <= 0)
				{ 
					setPosY(player.height + (p->pos.y + p->height) - y * player.height);
					setAccel(velX(),0);
					if_jump = true;  
					return true;
				}
		p = p->next;
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

