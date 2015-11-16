// CS335 fall 2015
// ====================
// Final Project - Group 2
// Game: Doodle Jump
// Student: Pedro Gonzalez
// 
// ---------------------
// used the asteroids game as a template
// for animation/physics


// game class
#include "game.h"
#include <iostream>
// GLOBAL vars
int window_width = 800;
int window_height = 600;


// check key inputs
int keys[65536];
bool killmovement = false;


unsigned long SCORE = 0;

int calls = 0;
// Gordon's timer & x11/opengl code
#include "gordoncode.cpp"
#include "nicholasMSounds.cpp"

// NOT used for fps counter!
// now used for sprite timer
int frames = 0;
timespec start;
int fps = 0; // USED FOR FRAMES PER SECOND

timespec timeScore;

int check_keys(XEvent *e, Game * game);
void check_mouse(XEvent *e, Game *game);
void physics(Game * game);
void render(Game * game);
void makeParticle(int x, int y);
void makeMissilesExp(Game* game);

using std::cout;
using std::endl;


// TODO fix gravity when window resizes
float GRAVITY = 1.0; 
int MAX_VELOCITY = 30;
int INITIAL_VELOCITY = 16;


enum stage
{
	MAIN_MENU,
	HOW_TO,
	RUN_GAME,
	DEATH
};
stage STATE = MAIN_MENU;



bool TOGGLE_PAUSE;
bool TOGGLE_SOUND = true;


// random function
#define rnd() (float)rand() / (float)RAND_MAX
#define MAX_PARTICLES 10000
Particle par[MAX_PARTICLES];
int numParticles = 0;
bool bubbler = false;
bool setbackground = false;

Particle blood[MAX_PARTICLES];
int numblood = 0;
bool bloodToggle = true;

#include "nadiaS.cpp" // make platform and draw function
#include "pedroG.cpp" // game textures/sprite draw functions
#include "nicholasM.cpp" // input checking, call all game methods in physics()

int main(int argc, char ** argv)
{
	// makes the game run on a full window

	///*
	Display* disp = XOpenDisplay(NULL);
	Screen*  scrn = DefaultScreenOfDisplay(disp);
	window_height = scrn->height;
	
	
	
	if(window_height >= 1080)
	{
		window_height -= 60;
		cout << "big window" << endl;
		//INITIAL_VELOCITY = 12;
		//MAX_VELOCITY = 12;
	}
	else if(window_height > 800)
		window_height -= 50;
	window_width = scrn->width;
	
	//*/

	

	initXWindows();
	init_opengl();

	setupSound();

	loadTextures();
	loadTexture(); // nadias code 
	//assert(true);
	cout << "start game" << endl;

	PlayGame();

	cleanupXWindows();
	cleanup_fonts();
	cleanupSound();
	cout << "end game" << endl;
	return 0;
}

void makeParticle(int x, int y) 
{
	if (numParticles >= MAX_PARTICLES)
		return;

	Particle *p = &par[numParticles];
	p->s.center.x = x;
	p->s.center.y = y;
	p->velocity.x =  1.0 + rnd() * 2;
	//p->velocity.y = rnd() * 1.0 - 0.5;
	p->velocity.y = rnd() * 0.4 - 0.5;
	numParticles++;
}


void render(Game * game)
{

	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// makes sure not to draw past window edges!
	game->checkRightScreenHit();
	game->checkLeftScreenHit();


	// texture
	if(setbackground)
	{
		// draws background, player, spikes, missiles
		drawGame_Textures(game);
	}
	else
	// debug/retrostyle mode
		drawGame_TEST(game);
	

	// TEXT
	Rect r;
	r.bot = window_height - 90;
	r.left = 80;
	r.center = 0;
	Rect c;
	c.bot = window_height / 2;
	c.left = window_width / 2 - 225;
	c.center = 0;
	square overlay;
	overlay.center.x = window_width/2;
	overlay.center.y = window_height/2;
	overlay.height = 100;
	overlay.width = 250;
	//ggprint8b(&r, 16, 0x00FFFF00, "fps: %i",  static_cast<int>(fps/timeDiff(&start, &timeCurrent)));
	if(STATE != DEATH)
	{
		//ggprint8b(&r, 16, 0x00FFFF00, "PhysicsRate: %i", static_cast<int>(1/physicsRate));
		//ggprint8b(&r, 16, 0x00FFFF00, "water particles: %i", numParticles);
		//ggprint8b(&r, 16, 0x00FFFF00, "blood particles: %i", numblood);
		//ggprint8b(&r, 16, 0x00FFFF00, "Hit sides: %i", game->checkLeftScreenHit() || game->checkRightScreenHit());
	    ggprint16(&r, 16, 0x00FFFF00, "Score: %i", SCORE);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor3ub(0, 0, 0);
		glPushMatrix();
		glTranslatef(overlay.center.x, overlay.center.y, 0);

		glBegin(GL_QUADS);
		glVertex2i(-overlay.width, -overlay.height);
		glVertex2i(-overlay.width,  overlay.height);
		glVertex2i( overlay.width,  overlay.height);			//These sections of code render the buttons.
		glVertex2i( overlay.width, -overlay.height);
		glEnd();
		glPopMatrix();

		ggprint16(&c, 24, 0x00FF0000, "You have died!");
		ggprint16(&c, 24, 0x00FFFF00, "Score: %i", SCORE);	
		ggprint16(&c, 24, 0x0000FF00, "Click or press M to return to the main menu!");
	}
	



}
