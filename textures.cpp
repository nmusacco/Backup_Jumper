// cs335 Fall 2015
// ==========================
// student: Pedro Gonzalez
// ==========================

// Used lab2_rainforest texture code as template
// then used online sources for further explaination of code/magic

// sites I used to learn some of these commands/args
// https://open.gl/textures
// OLD!!! from 2007, hardware dependent!!!
// http://www.gamedev.net/page/resources/_/technical/opengl/rendering-efficient-2d-sprites-in-opengl-using-r2429

// explaination of texture sprite coordinates
// http://stackoverflow.com/questions/11457394/texture-sampling-coordinates-to-render-a-sprite

// sprite animation helpful
// http://forum.devmaster.net/t/spritesheet-animation-in-opengl/24020

// using this site https://convertio.co/png-ppm/ for png to ppm conversion 
// Skeleton spritesheet by MoikMellah
// http://opengameart.org/content/mv-platformer-skeleton
// platformer spritesheet by clint bellanger
// http://opengameart.org/content/platformer-animations
// metal slug 2 rocket
// http://www.spriters-resource.com/arcade/ms2/sheet/53203/
// explosions



Ppmimage * spike = NULL;
GLuint spikeTexture; 

Ppmimage * missile = NULL;
GLuint missileTexture;

Ppmimage * skeletonBase = NULL;
GLuint skeletonTexture;

Ppmimage *background = NULL;
GLuint backgroundTexture;

GLuint silhouetteTexture;
GLuint silhouetteTextureSpikes;
GLuint silhouetteTextureMissile;

void loadTextures()
{
	// load image from ppm structure
	skeletonBase = ppm6GetImage("./images/platformer_sprites_pixelized_0.ppm");
	background = ppm6GetImage("./images/background.ppm");
	spike = ppm6GetImage("./images/superspikes.ppm");
	missile = ppm6GetImage("./images/missile.ppm");
	
	// generate opengl texture element
	glGenTextures(1, &skeletonTexture);
	glGenTextures(1, &backgroundTexture);
	glGenTextures(1, &spikeTexture);
	glGenTextures(1, &missileTexture);
	
	glGenTextures(1, &silhouetteTexture);
	glGenTextures(1, &silhouetteTextureSpikes);
	glGenTextures(1, &silhouetteTextureMissile);
	
	//////////////////// Missile //////////////////////
	glBindTexture(GL_TEXTURE_2D, missileTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, missile->width, missile->height,
	0, GL_RGB, GL_UNSIGNED_BYTE, missile->data);
	
	
	/////////////////// spikes ////////////////
	glBindTexture(GL_TEXTURE_2D, spikeTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, spike->width, spike->height,
	0, GL_RGB, GL_UNSIGNED_BYTE, spike->data);
	
	
	/////////////////// Skeleton sprite texture ////////////////////////
	
	glBindTexture(GL_TEXTURE_2D, skeletonTexture);
	// bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// write to video memory
	glTexImage2D(GL_TEXTURE_2D, 0, 3, skeletonBase->width, skeletonBase->height,
	0, GL_RGB, GL_UNSIGNED_BYTE, skeletonBase->data);

	
	//////////////////// silhouette for character///////////////////////
	glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *silhouetteData = buildAlphaData(skeletonBase);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, skeletonBase->width, skeletonBase->height, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	delete [] silhouetteData;
	
	//////////////////// silhouette for spikes///////////////////////
	glBindTexture(GL_TEXTURE_2D, silhouetteTextureSpikes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	silhouetteData = buildAlphaData(spike);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spike->width, spike->height, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	delete [] silhouetteData;
	
	//////////////////// silhouette for missile///////////////////////
	glBindTexture(GL_TEXTURE_2D, silhouetteTextureMissile);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	silhouetteData = buildAlphaData(missile);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, missile->width, missile->height, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	delete [] silhouetteData;
	
	
	
	////////////// GAME BACKGROUND ////////////////////////////
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	background->width, background->height,
	0, GL_RGB, GL_UNSIGNED_BYTE, background->data);
	
	
}

void drawMissile(Game * game)
{
	glPushMatrix();
	glTranslatef(0, 100, 0);
	glBindTexture(GL_TEXTURE_2D, missileTexture);

	glBindTexture(GL_TEXTURE_2D, silhouetteTextureMissile);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	
	int wid = 80*game->player.width;
	cout << wid << endl;
	
	glBegin(GL_QUADS);
	// corner coordinates must follow this order
	//glTexCoord2f(0, 0.0); glVertex2i(-wid, wid); // top left
//	glTexCoord2f(0,  1); glVertex2i(-wid,-wid); //bottom left
	//glTexCoord2f(1, 1); glVertex2i( wid,-wid); // bottom right
	//glTexCoord2f(1, 0); glVertex2i( wid, wid); // top right 
	
	glTexCoord2f(0,1);
	glVertex2i(0,0);
	glTexCoord2f(0,0);
	glVertex2i(0, wid);
	glTexCoord2f(1,0);
	glVertex2i(wid, wid);
	glTexCoord2f(1,1);
	glVertex2i(wid, 0);
	glEnd();

	glEnd();
	glPopMatrix();
	
	glDisable(GL_ALPHA_TEST);
}

void drawSpike()
{
	glPushMatrix();
	glTranslatef(0, 5, 0);
	glBindTexture(GL_TEXTURE_2D, spikeTexture);

	glBindTexture(GL_TEXTURE_2D, silhouetteTextureSpikes);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	
	int wid = spike->width;
	
	glBegin(GL_QUADS);
	// corner coordinates must follow this order
	//glTexCoord2f(0, 0.0); glVertex2i(-wid, wid); // top left
	//glTexCoord2f(0,  1); glVertex2i(-wid,-wid); //bottom left
	//glTexCoord2f(1, 1); glVertex2i( wid,-wid); // bottom right
	//glTexCoord2f(1, 0); glVertex2i( wid, wid); // top right 
	
	glTexCoord2f(0,1);
	glVertex2i(0,0);
	glTexCoord2f(0,0);
	glVertex2i(0, wid);
	glTexCoord2f(1,0);
	glVertex2i(wid, wid);
	glTexCoord2f(1,1);
	glVertex2i(wid, 0);
	glEnd();

	glEnd();
	glPopMatrix();
	
	glDisable(GL_ALPHA_TEST);
}

// Don't touch works
void renderCell(float f, float x_i, float y_i, float lvl, float toplvl, Game * g)
{
	int wid = 10 * g->player.width;//skeletonBase->width;
	
	glPushMatrix();
	glTranslatef(g->player.position.x, g->player.position.y + g->player.width*5, 0);
	glBindTexture(GL_TEXTURE_2D, skeletonTexture);

	if(g->player.left)
	glScalef( -1.0f, 1, 1);
	if(g->player.right)
	glScalef(1.0f, 1, 1 );

	glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	
	if(lvl == 2)
		f -= 8*x_i;
	
	glBegin(GL_QUADS);
	// corner coordinates must follow this order
	glTexCoord2f(f, 0.0 + toplvl); glVertex2i(-wid, wid); // top left
	glTexCoord2f(f,  lvl * y_i); glVertex2i(-wid,-wid); //bottom left
	glTexCoord2f(f + x_i, lvl * y_i); glVertex2i( wid,-wid); // bottom right
	glTexCoord2f(f + x_i, 0.0 + toplvl); glVertex2i( wid, wid); // top right

	glEnd();
	glPopMatrix();
	
	glDisable(GL_ALPHA_TEST);
}

float frame = 0;

// frames determines how the sprite is drawn, timer
// frame is the x axis distance between cells
void drawSkeleton(Game * game)
{
	
	// spritesheet has 8 sprites cells on the x axis 1/8 = 0.125
	// spritesheet has 9 sprites cells on the y axis 1/9 = 0.111
	float x_increment = 0.125;
	float y_increment = 0.111;

	
	if(frame <= 3*x_increment)
	frame = 4*x_increment;
	
	int lvl = 1;
	float toplvl = 0.0f;
	
	
	if(game->player.velocity.y > 0) // up
	{
		frame = 5*x_increment;
		lvl = 1;
		toplvl = 0.0f;
	}
	if(game->player.velocity.y < 0) // down
	{
		frame = 3*x_increment;
		lvl = 1;
		toplvl = 0.0f;
	}
	if(game->player.velocity.x == 0)
	{
		frame = 0.0; // starting position 
		lvl = 9;
		toplvl =  8 * 0.1111111111;
		if(game->player.velocity.y > 0) // up
		{
			frame = 5*x_increment;
			lvl = 1;
			toplvl = 0.0f;
		}
		if(game->player.velocity.y < 0) // down
		{
			frame = 3*x_increment;
			lvl = 1;
			toplvl = 0.0f;
		}
	}
	
	
	// lower level of texture
	if(frame > 7 * x_increment)
	{
		//cout << "NEXT" << endl;

		lvl = 2;
		toplvl = 1 * 0.111111111;
	}
	
	
	if(frame > 11 * x_increment)
	{
		lvl = 1;
		toplvl = 0.0;
		frame = 4*x_increment;
	}

	//cout << frame/x_increment << endl;
	renderCell(frame, x_increment, y_increment, lvl, toplvl, game);
}

