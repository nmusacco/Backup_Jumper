/* ===============================================
* Nadia Salem
* this is to draw and make platforms for the game
* 
*/ 

// Pedro Gonzalez
// ---------------------
// made minor changes/reviews with makePlatform() and drawPlatform()

Ppmimage *platform = NULL;
GLuint platformTexture;

void loadTexture()
{
	//load platform texture image from ppm structure
	platform = ppm6GetImage("./images/metal1.ppm");
	glGenTextures(1, &platformTexture);
	glBindTexture(GL_TEXTURE_2D, platformTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, platform->width, platform->height,
		0, GL_RGB, GL_UNSIGNED_BYTE, platform->data);
}

// Pedro Gonzalez
// -------------------------------------------------------------
// This creates the initial platforms in the start of the game
// also this is more optimized
// this function should be called ONCE!
// UNLESS the game has no platforms allocated
// -------------------------------------------------------------
void makePlatform(int amt, Game *game)
{
	if(!game) // error checking!!!
		return;
	if(game->platformHead) // if platforms exist get OUT OF HERE!!!
		return;
	
	Vec pos;
	
	srand (time(NULL));
	int w = game->player.width * 15;
	int h = game->player.height * 0.35;
	pos.x = rand() % window_width;
	pos.y = window_height - 1.0/5.0 * window_height + h * 2;
	
	// first element in platformHead
	
	
	// the rest of the linked list
	Platform * ptr = game->platformHead;
	//ptr->num = 0;
	for(int i = 0; i < 5; ++i) // 5
	{
		if(i == 0)
		{
			game->platformHead = new Platform(pos, w, h, NULL); // top and first platform //1
			ptr = game->platformHead;
		}
		pos.x = rand() % window_width;
		pos.y = window_height - 1.0/5.0 *window_height* (i + 1) + h*2;

		ptr->next = new Platform(pos, w, h, NULL); // 1 - 5		
		//ptr->next->num = i;
		ptr = ptr->next;

		int xaxis = 3;
		if(window_width > 800)
			xaxis = 6;
		
		int numofPlat_sameAxis = rand() % xaxis + 1;
		cout << numofPlat_sameAxis << endl;
		for(int r = 0; r < numofPlat_sameAxis; ++r) // 
		{
			int newx = rand() % (window_width/(r + 1));
			//pos.x = (newx >= pos.x - w && newx <= pos.x + w) ? newx - w * 3 : newx;
			pos.x = newx;
			ptr->next = new Platform(pos, w, h, NULL);
			ptr->next->num = -1;
			ptr = ptr->next;
		}	
	}
	// sets the player's x axis to the first platforms x axis
	game->player.position.x = game->platformHead->pos.x;
}

// Pedro Gonzalez
// -----------------------
// This draws all platforms on screen
// also this is more optimized
void drawPlatform(Game *game, int x = 0)
{
	Platform * head = game->platformHead;
	int w = game->player.width * 15;
	int h = game->player.height * 0.35;

	while(head)
	{
		glPushMatrix();
		glColor3ub(255,255,255);
		glTranslatef(head->pos.x,head->pos.y,0);
		
		if(setbackground)
			glBindTexture(GL_TEXTURE_2D, platformTexture);

		glBegin(GL_QUADS);
		glTexCoord2f(0,1); // bottom left
		glVertex2i(-w,-h);
		glTexCoord2f(0,0); // top left
		glVertex2i(-w,h);
		glTexCoord2f(1,0); // top right
		glVertex2i(w,h);
		glTexCoord2f(1,1); // bottom right
		glVertex2i(w,-h);
		glEnd();
		glPopMatrix();
		
		head = head->next;
	}
}

