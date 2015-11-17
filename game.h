// CS335 fall 2015
// ===========================
// Final Project: Group 2
// 
// student: Pedro Gonzalez
// 
// ===========================

// game class 
// -----------------
// hold player and platform coordinates,
// manages movement and velocities of 
// game objects, checks for collisions
// prompts start menu, death/restart screen

#ifndef GAME_H
#define GAME_H

#include <iostream>

using std::cout;
using std::endl;

struct Vec
{
	float x;
	float y;
};

// TODO needs work
struct Powerup
{
	Vec position;
	Vec velocity;
	int width;
	int height;

	Powerup * next = NULL;
	Powerup * previous = NULL;
};


struct Shape {
	float width, height;
	float radius;
	Vec center;
};

struct Particle {
	Shape s;
	Vec velocity;
};

struct Guy
{
	bool left;
	bool right;
	Vec position;
	Vec velocity;
	int width;
	int height;
};

struct Missile
{
	Vec position;
	Vec velocity;
	int missileType;
	int width;
	int height;
	Missile * next;
	timespec MissilesStart;
	float angle;
	int nextframe; // used for sprite animation
	Particle exp[10000];
	int numExp;
};

struct Platform
{
	int num;
	Vec pos;
	int width;
	int height;
	Platform * next;
	Platform(Vec x, int w, int h, Platform * n): pos(x), width(w), height(h), next(n){}
};

class Game
{
	public:	
		Guy player;	

		bool if_hit; // collision then true, 
		bool if_jump; // if true allow jumping
		bool run; // runs main loop
		bool guts;
		bool setMissiles;
		int window_height;
		int window_width;
	
		//float aspect;	
		int int_vel;
		int max_vel;
		float gravity; // default is gonna be 1 unless set otherwise
		
		int powerupTimer; // in seconds
		
		Missile missiles;
		Powerup * powerups;
		Platform * platformHead;

		// initialized game objects
		// set player position, etc
		Game();
		
		// Game gets assigned a Game object later on so we needed an assign operator
		///*
		Game & operator = (const Game & other)
		{
			if(this != &other)
			{
				int x = 0;
				Platform * p = this->platformHead;
				Platform * hold = NULL;
				while(p)
				{
					x++;
					hold = p;
					p = p->next;
					delete hold;
				}
				cout << "COPY!!! OF PLATFORMS DELETED: " << x << endl;
				
				this->setPos(30,1000);
				this->setAccel(0,0);
				this->gravity = 1;

				this->powerupTimer = 14;

				this->powerups = NULL;
				//missiles = NULL;

				this->accelY(-1);
				this->if_jump = false;
				this->if_hit = false;
				this->run = true;
				this->guts = false;
				this->missiles.numExp = 0;
				this->platformHead = NULL;
			}
			return *this;
		}
		//*/
		
		void createMissiles();
		
		// if the player is in the air, deny multiple jumps
		bool inAir();
		
		// WORKS!
		void applyGravity();
		
		// sets missiles to chase player's coordinates
		void missileChasePlayer();
		
		void setGravity(int g);
				
		// return players x,y coordinates
		float posX();
		float posY();
		
		// return player velocity x/y axis
		float velY();
		float velX();
		
		// used to handle window resized events
		void setResolution(int x, int y);
		
		// set position of x,y coordinates
		void setPos(float x, float y);
		void setPosX(float x);
		void setPosY(float y);
		
		// set the velocity
		void setAccel(float x, float y);
		
		// increases player x/y axis velocity by x/y
		// velocity += x/y;
		void accelX(float x);
		void accelY(float y);
		
		// this function moves all game components
		// the platforms, player, missles, etc
		// increment x and y position with x and y velocity
		void move();
		
		void updatePlatforms();

		bool checkBottomScreen();
		bool checkLeftScreenHit();
		bool checkRightScreenHit();
		bool checkCollision();
		bool checkMissileHit();
		void removeMissiles(bool pausegame);
		void makeMissilesExp();
		//void drawMissileExp();
		
		
		
		~Game();
};


#endif
