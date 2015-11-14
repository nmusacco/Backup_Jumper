// CS335 fall 2015
// ===========================
// Final Project: Group 2
// 
// student: Nicholas Musacco
// 
// ===========================


//OLD:
//Currently contains the physics function along with basic 
//pause features to stop motion when the game is paused
//
//Future addition will include a pause screen that will
//pop up with the Esc key is pressed
//
//The pause screen will have a few options that will be
//selected by the keyboard, the buttons will be resume and quit
//Also when the game is paused the score will be put up in the middle of the
//screen in a larger text size.


//NEW:
//As of 11/11 I created sounds, which are kept in nicholasMSounds.cpp
//the code is mostly Gordon Griesel's openal example with only my minor changes
//to allow a sound initialization function, a play sound function, 
//and a cleanup function
//
//As of 11/11 I created the PlayGame() function, which contains the loop 
//to play the game. This was deemed necessary as the main() function
//had become littered with my changes to allow for state changes to the game.


struct button {
	float width, height;
	Vec center;			//struct to hold button info
};

//bool bloodToggle = false;
bool pausegame = true;

void setMenuBackground()
{
	button startb;
	startb.center.y  =  window_height/2;	//green start game button
	startb.center.x  = (window_width/3);
	startb.width = 50;
	startb.height = 50;

	button exitb;
	exitb.center.y = window_height/2;	//red exit game button
	exitb.center.x = (window_width * 2 / 3);
	exitb.width  = 50;
	exitb.height = 50;

	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, menuTexture);		//This section of code renders the menu background
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2i(0,0);
	glTexCoord2f(0,0);
	glVertex2i(0, window_height);//height/2);//window_height);
	glTexCoord2f(1,0);
	glVertex2i(window_width, window_height);//width/2, height/2);//window_width, window_height);
	glTexCoord2f(1,1);
	glVertex2i(window_width, 0);//width/2,0);//window_width, 0);
	glEnd();



	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3ub(0, 200, 0);
	glPushMatrix();
	glTranslatef(startb.center.x, startb.center.y, 0);

	glBegin(GL_QUADS);
	glVertex2i(-startb.width, -startb.height);
	glVertex2i(-startb.width,  startb.height);
	glVertex2i( startb.width,  startb.height);			//These sections of code render the buttons.
	glVertex2i( startb.width, -startb.height);
	glEnd();
	glPopMatrix();

	glColor3ub(200, 0, 0);
	glPushMatrix();
	glTranslatef(exitb.center.x, exitb.center.y, 0);

	glBegin(GL_QUADS);
	glVertex2i(-exitb.width, -exitb.height);
	glVertex2i(-exitb.width,  exitb.height);
	glVertex2i( exitb.width,  exitb.height);
	glVertex2i( exitb.width, -exitb.height);
	glEnd();
	glPopMatrix();


}



void physics(Game * game)
{

	if(STATE == RUN_GAME && !pausegame)	//if the game is playing and not paused, run all the physics checks and apply movement and gravity
	{					//I have it set up this way, so that when the game is paused, the game no longer checks for physics
		game->inAir(); 
		game->updatePlatforms();
		game->applyGravity();
		if(game->checkBottomScreen() && bloodToggle) // spikes collision    bloodToggle is a switch that is turned off once this statement has run once. This means when
		{					     //the character hits the spikes, the sounds wont play multiple times
			int choice = rand() % 3;

			if(choice == 1)
				alBuffer = alutCreateBufferFromFile("./Sounds/death1.wav");
			if(choice == 2)
				alBuffer = alutCreateBufferFromFile("./Sounds/death2.wav");	//random sound selection
			if(choice == 0)
				alBuffer = alutCreateBufferFromFile("./Sounds/death3.wav");
			playSound();
			game->guts = true;
			bloodToggle = false;

		}

		game->missileChasePlayer();
		game->removeMissiles();
		game->checkCollision();

		if(game->checkMissileHit())
		{
			alBuffer = alutCreateBufferFromFile("./Sounds/explosion.wav");
			playSound();			
			game->guts = true;
			game->setMissiles = false;
		}

		if(keys[XK_Left]) // left arrow
		{
			game->player.right = false;
			game->player.left = true;
			if(frames == 1)
				frame += 0.125;
			game->accelX(-1 * INITIAL_VELOCITY);
		}

		if(keys[XK_Right]) // right arrow
		{
			game->player.left = false;
			game->player.right = true;
			if(frames == 1)
				frame +=  0.125;
			game->accelX(INITIAL_VELOCITY);
		}

		if(keys[XK_space] && game->if_jump) // spacebar
		{
			int choice = rand() % 4;
			if(choice == 1)
				alBuffer = alutCreateBufferFromFile("./Sounds/jump1.wav");
			if(choice == 2)
				alBuffer = alutCreateBufferFromFile("./Sounds/jump2.wav");	//random sound selection
			if(choice == 3)
				alBuffer = alutCreateBufferFromFile("./Sounds/jump3.wav");
			if(choice == 0)
				alBuffer = alutCreateBufferFromFile("./Sounds/jump4.wav");

			playSound();

			game->accelY(2 * INITIAL_VELOCITY);
		}

		if(killmovement && game->inAir()) // kill movement on x axis only
			game->player.velocity.x = 0;


		if(game->velX() > MAX_VELOCITY)
			game->player.velocity.x = MAX_VELOCITY;
		if(game->velX() < -1 * MAX_VELOCITY)
			game->player.velocity.x = -1 * MAX_VELOCITY;

		game->move();
	}
	int x_bubbler = 100;
	int y_bubbler = window_height;

	if(bubbler) // if bubbler is toggled only stream water from the top, no mouse involved
	{
		for(int i = 0; i < window_height * 0.15; i++)
		{
			x_bubbler += rnd()*10;
			makeParticle(x_bubbler, y_bubbler);
		}
	}


	

	// waterfall particle settings
	Particle *p = &par[numParticles];
	if(!pausegame)
	{
		for(int i = 0; i < numParticles; ++i)
		{
			p = &par[i];
			p->s.center.x += p->velocity.x;
			p->s.center.y += p->velocity.y;
			p->velocity.y -= 0.1; 

			if (p->s.center.y < 0.0 || p->s.center.y > window_height) 
			{
				memcpy(&par[i], &par[numParticles -1], 
						sizeof(Particle));
				numParticles--;
			}
		}
	}

	// blood particle settings
	Particle *p2 = &blood[numblood];
	if(!pausegame)
	{
		for(int i = 0; i < numblood; ++i)
		{
			p2 = &blood[i];
			p2->s.center.x += p2->velocity.x;
			p2->s.center.y += p2->velocity.y;
			p2->velocity.y -= 0.1; 

			if (p2->s.center.y < 0.0 || p2->s.center.y > window_height) 
			{
				memcpy(&blood[i], &blood[numblood -1], 
						sizeof(Particle));
				numblood--;
			}
		}
	}

	//making missile exp particles
	Particle *p3 = &game->missiles.exp[game->missiles.numExp];
	if(!pausegame)
	{
		for(int i = 0; i < game->missiles.numExp; ++i)
		{
			p3 = &game->missiles.exp[i];
			p3->s.center.x += p3->velocity.x;
			p3->s.center.y += p3->velocity.y;
			p3->velocity.y -= 0.1;

			if (p3->s.center.y < 0.0 || p3->s.center.y > window_height)
			{
				memcpy(&game->missiles.exp[i], &game->missiles.exp[game->missiles.numExp -1],
						sizeof(Particle));
				game->missiles.numExp--;
			}
		}

	}
}

int check_keys(XEvent *e, Game * game)
{
	int key = XLookupKeysym(&e->xkey, 0);


	killmovement = true;
	if(e->type == KeyRelease) 
	{
		keys[key] = 0;
		if(key == XK_space)
			killmovement = false;
	}

	if(e->type == KeyPress)
	{
		keys[key] = 1;

		if(STATE != DEATH) //this turns off keys except for ESC when you are dead
		{
			if(key == XK_k) // respawn
			{
				if(game->guts == true) // 
				{
					game->setPos(window_width/2, window_height);
					game->guts = false;
					bloodToggle = false;
				}
			}

			if(key == XK_p)
			{
				if(!pausegame)
					pausegame = true;
				else
					pausegame = false;

			}
			if(STATE == RUN_GAME && !pausegame)
			{
				if(key != XK_Left || key != XK_Right)
					killmovement = false;

				if(key == XK_b)
				{
					if(bubbler)
						bubbler = false;
					else
						bubbler = true;
				}

				if(key == XK_m)
				{
					game->createMissiles();
				}
			}
			if(key == XK_w)
			{
				if(setbackground)
					setbackground = false;
				else 
					setbackground = true;
			}
		}
		if(key == XK_Escape)
		{
			if(STATE != DEATH)
				game->run = false;
			else
				STATE = MAIN_MENU;
			pausegame = true;
		}
	}	
	return 0;
}



// check for button clicks?
void check_mouse(XEvent *e, Game *game)
{
	int mousex = e->xbutton.x;
	int mousey = e->xbutton.y;
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button was pressed
			if(STATE == MAIN_MENU)
			{
				if((window_height - mousey >= window_height - (window_height/2) - 50 ) 			//button click areas
						&& window_height - mousey <= window_height - (window_height/2) + 50)
				{
					if(mousex >= (window_width/3) - 50 && mousex <= (window_width/3) + 50)
					{
						STATE = RUN_GAME;
					}
					if(mousex <= (window_width * 2 / 3) + 50
							&& mousex >= (window_width * 2 / 3) - 50)
					{
						game->run = false;
					}
				}
			}
			return;
		}

	}

}

void PlayGame()
{
	Game game;


	if(window_height > 1080)
	{
		//game.gravity = 9;
		MAX_VELOCITY = 12;
		INITIAL_VELOCITY = 7;
	}

	srand(time(NULL));

	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	clock_gettime(CLOCK_REALTIME, &start);
	while(game.run)
	{	
		game = Game();

		game.setGravity(GRAVITY);

		// set players position

		game.setResolution(window_width, window_height);
		makePlatform(5,&game);
		
		// Pedro here
		// For the love of zeus don't touch
		//game.setPos(window_width/2, window_height);

		if(TOGGLE_SOUND)		//Sound switch so that the background music doesnt get recalled after the initial call
		{
			Buffer = alutCreateBufferFromFile("./Sounds/music.wav");
			playBackgroundSound();
			TOGGLE_SOUND = false;
		}

		gutsToggle = true;
		bloodToggle = true;		//Reset switches to clear the prev game information. This includes the score and blood particles
		TOGGLE_PAUSE = true;
		numblood = 0;
		SCORE = 0;
		
		while(STATE == MAIN_MENU && game.run)
		{

			XEvent menu;
			while(XPending(dpy))
			{
				XNextEvent(dpy, &menu);
				check_keys(&menu, &game);
				check_mouse(&menu, &game);
				game.setResolution(window_width, window_height);
			}
			setMenuBackground();
			glXSwapBuffers(dpy, win);
		}

		usleep(1000);

		while(STATE == RUN_GAME && game.run)
		{

			// check input
			XEvent e;
			while(XPending(dpy))
			{
				if(TOGGLE_PAUSE)
				{
					TOGGLE_PAUSE = false;
					pausegame = false;
				}

				XNextEvent(dpy, &e);
				check_keys(&e, &game);
				check_resize(&e);
				game.setResolution(window_width, window_height);
			}



			if(game.guts && numblood == 0)
			{
				STATE = DEATH;	//changes the game state to the death screen once the person has died and the blood particles are off the screen
			}

			clock_gettime(CLOCK_REALTIME, &timeCurrent);
			timeSpan = timeDiff(&timeStart, &timeCurrent);
			timeCopy(&timeStart, &timeCurrent);

			if(!pausegame)
			{

				SCORE++;		//iterates the score every loop that the game is not paused
			}

			physicsCountdown += timeSpan;

			// check for collisions, move player
			while(physicsCountdown >= physicsRate) {
				physics(&game);

				physicsCountdown -= physicsRate;
			}

			// used for sprite timing DON'T TOUCH
			if(frames > 2)
				frames = 0;
			frames++;

			// FPS COUNTER/RESET
			if(fps > 100)
			{
				clock_gettime(CLOCK_REALTIME, &start);
				fps = 0;
			}
			fps++;

			render(&game);
			glXSwapBuffers(dpy, win);

		}
		
		while(STATE == DEATH && game.run)
		{
			XEvent death;
			while(XPending(dpy))
			{
				XNextEvent(dpy, &death);
				check_keys(&death, &game);
				game.setResolution(window_width, window_height);
			}
			
			clock_gettime(CLOCK_REALTIME, &timeCurrent);
			timeSpan = timeDiff(&timeStart, &timeCurrent);
			timeCopy(&timeStart, &timeCurrent);
			physicsCountdown += timeSpan;
			while(physicsCountdown >= physicsRate)
			{
				physics(&game);
				physicsCountdown -= physicsRate;		//this will keep the game rendering so that the user can see the players full body explosion
			}
			render(&game);
			glXSwapBuffers(dpy, win);
	
		}

	}
	return;
}
