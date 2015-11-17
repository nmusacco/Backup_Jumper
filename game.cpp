// CS335 fall 2015
// ===========================
// Final Project: Group 2
// 
// student: Pedro Gonzalez
// 
// ===========================


#include "game.h"

#include <stdlib.h>
#include <math.h> // atan2(); 

Game::Game()
{
    setPos(30,1000);
    setAccel(0,0);
    gravity = 1;

    powerupTimer = 14;

    powerups = NULL;
    //missiles = NULL;

    accelY(-1);
    if_jump = false;
    if_hit = false;
    run = true;
    guts = false;
    missiles.numExp = 0;
    platformHead = NULL;
}

// create ONE missile
void Game::createMissiles()
{
    setMissiles = true;
	missiles.missileType = rand() % 3;
    missiles.numExp = -1;
    clock_gettime(CLOCK_REALTIME, &missiles.MissilesStart);
    missiles.nextframe = 0;
    int x;
    int y;
    switch(rand()%2)
    {
         case 0:  y = this->window_height / 2;
                  x = this->window_width / 2 * -1;
                  break;
         case 1:  y = this->window_height / 2;
                  x = this->window_width + this->window_width / 2;
                  break;
   }
    
    int width = 2*player.width;
    int height = 6*player.height;

    missiles.position.x = x;
    missiles.position.y = y;
    missiles.width = width;
    missiles.height = height;

   // cout << "missile created" << endl;
}



bool Game::inAir()
{
    //if(checkCollision())
    //return false;

    if(player.position.y > 0 && if_jump == true)
    {
	if_jump = false;
	return true;
    }
    return false;
}

void Game::applyGravity()
{

    if(player.position.y - player.height > 0)
    {
	accelY(-0.25 * gravity);
        //std::cout<<"\n now it is: " << gravity;
    }
    Powerup * p = powerups;
    while(p != NULL)
    {
		if(p->position.y - p->height > 0)
			p->velocity.y += -0.25 * gravity;
		p = p->next;
    }
}

void Game::missileChasePlayer()
{
    if(!setMissiles)
		return;
	
	float PI = 3.14159265359;
	
    float x = missiles.position.x;
    float y = missiles.position.y;
	
	missiles.angle = atan2(posX() - x, posY() - y) * 180 / PI;
	
    float speed;
	if(missiles.missileType == 1)
		speed = 2;
	else if(missiles.missileType == 2)
		speed = 18;
	else
		speed = 6;
	
    float x_vel;
    float y_vel;

    missiles.nextframe++;

    if(posX() > x)   
		x_vel = speed;
    else if(posX() == x)
		x_vel = 0;
    else	
		x_vel = -speed;

    if(posY() > y)
		y_vel = speed;
    else if(posY() == y)
		y_vel = 0;
    else
		y_vel = -speed;

    missiles.velocity.x = x_vel;
    missiles.velocity.y = y_vel;
}

void Game::setGravity(int g)
{
    gravity = g;//(float)g * aspect;
}


float Game::posX()
{
    return player.position.x;
}

float Game::posY()
{
    return player.position.y;
}


float Game::velY()
{
    return player.velocity.y;
}

float Game::velX()
{
    return player.velocity.x;
}

// TODO fix gravity when window resizes
void Game::setResolution(int x, int y)
{
    window_width = x;
    window_height = y;
    player.width = window_height*0.01;
    player.height = window_height*0.05;
    missiles.width = 3*player.width;
    missiles.height = 6*player.height;

	Platform * p = platformHead;
    while(p)
    {
		p->width = player.width * 15;
		p->height = player.height * 0.35;
		p = p->next;
	}
    
    //aspect = (window_height / 600.0) / (window_width / 800.0); // these numbers are divided by the original game windows size in order 
                                                               //to get a ratio so we could tinker with a small window and have it work the same on a large window

}

void Game::setPos(float x = 0, float y = 0)
{
    player.position.x = x;
    player.position.y = y;
}

void Game::setPosX(float x)
{
    player.position.x = x;
}

void Game::setPosY(float y)
{
    player.position.y = y;
}

void Game::setAccel(float x, float y)
{
    player.velocity.x = x;
    player.velocity.y = y;
}

void Game::accelX(float x)
{
    player.velocity.x += x;
}

void Game::accelY(float y)
{
    player.velocity.y += y;
}

void Game::move()
{
    player.position.x += player.velocity.x;
    player.position.y += player.velocity.y;

    missiles.position.x += missiles.velocity.x;
    missiles.position.y += missiles.velocity.y;

    float y = 0.04;
    if(window_height > 1080)
		y = 0.06;
    
	//player.position.y -= 0.1 *player.height;
	Platform * p = platformHead;
    while(p)
	{
		p->pos.y -= y * player.height;
		p = p->next;
	}
}

int xd = 0;
// removes platforms that go out of screen 
// and places new ones on top of the window screen
void Game::updatePlatforms()
{
	int w = player.width * 15;
    int h = player.height * 0.35;

	Platform * p = platformHead;
	Platform * next = p->next;
	Vec pos;
	//srand (time(NULL));
	if(!p)
		return;
	
	pos.y = window_height + p->height;
		
	if(p->pos.y + h < 0) // move the first element
	{
		delete p;
		pos.x = rand() % (window_width - w) + w;
		platformHead = new Platform(pos, w, h, next);
		//p = platformHead->next;
	}


	while(p) // move the rest of the elements in the list
	{
		if(p->next)
			if(p->next->pos.y  < -h)
			{
				int hold = p->next->num;
				next = p->next->next;
				pos.x = rand() % (int)(window_width - w) + w;
				//cout << "delete" << hold << endl;
				delete p->next;

				p->next = new Platform(pos, w, h, next);
				p->next->num = hold;
			}
		p = p->next;
	}
}

#include "brandiD.cpp"

// remove all missiles, platforms etc that are remaining in game?
// deallocate here!
Game::~Game()
{
	int x = 0;
	Platform * p = platformHead;
	Platform * hold = NULL;
	
	while(p)
	{
		x++;
		hold = p;
		p = p->next;
		delete hold;
	}
	
	platformHead = NULL;
	//cout << "NUMBER OF PLATFORMS DELETED: " << x << endl;
}
