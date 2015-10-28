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

// rotate sprite texture
// https://www.opengl.org/discussion_boards/showthread.php/165578-Rotating-a-Texture-on-a-Quad

// sprite animation helpful
// http://forum.devmaster.net/t/spritesheet-animation-in-opengl/24020

// using this site for help with missile chasing algorithm
// http://code.tutsplus.com/tutorials/hit-the-target-with-a-deadly-homing-missile--active-8933

// using this site https://convertio.co/png-ppm/ for png to ppm conversion 
// Skeleton spritesheet by MoikMellah
// http://opengameart.org/content/mv-platformer-skeleton
// platformer spritesheet by clint bellanger
// http://opengameart.org/content/platformer-animations
// metal slug 2 rocket
// http://www.spriters-resource.com/arcade/ms2/sheet/53203/

#include <math.h> // atan2();  

Ppmimage * spike = NULL;
GLuint spikeTexture; 

Ppmimage * missile = NULL;
GLuint missileTexture;

// skeleton is the player's texture
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
	glTexImage2D(GL_TEXTURE_2D, 0, 3, background->width, background->height,
	0, GL_RGB, GL_UNSIGNED_BYTE, background->data);
	
	
}

void drawBackground()
{
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);
	glVertex2i(0,0);
	glTexCoord2f(0,0);
	glVertex2i(0, window_height);
	glTexCoord2f(1,0);
	glVertex2i(window_width, window_height);
	glTexCoord2f(1,1);
	glVertex2i(window_width, 0);
	glEnd();
}


void drawMissile(Game * game)
{
	// used to allow non textures objects to maintain their color
	glBindTexture(GL_TEXTURE_2D, 0);

	//cout << "missile checked" << endl;
	float x = game->missiles.position.x;
	float y = game->missiles.position.y;
	
	// 12 missiles on spritesheet 1/12 is 0.083
	float x_i = 1.0/12.0;
	// 3 missiles on spritesheet, 2 big 1 small
	// 1 big missiles has a height of 134px and spritetexture's height is 380 so 134/380 = 0.352...
	float y_i =  0.352632;
	
	float PI = 3.14159265359;
	float angle = atan2(game->posX() - x, game->posY() - y) * 180 / PI;
	int wid = 3*game->player.width;
	int height = 2*game->player.height;
	
	float rad = (((-angle)+90.0) / 360.0f) * PI * 2.0;
	//convert angle to a vector
	float xdir = cos(rad);
	float ydir = sin(rad);
	glColor3ub(150 ,160 ,255);
	float xs,ys,xe,ye,r;
	glBegin(GL_LINES);
	for (int i=0; i<16; i++) 
	{
		xs = -xdir * 11.0f + rnd() * 4.0 - 2.0;
		ys = -ydir * 11.0f + rnd() * 4.0 - 2.0;
		r = rnd()*40.0+  height;
		xe = -xdir * r + rnd() * 18.0 - 9.0;
		ye = -ydir * r + rnd() * 18.0 - 9.0;
		glColor3f(rnd()*.3+.7, rnd()*.3+.7, 0);
		glVertex2f(x+xs, y+ys);
		glVertex2f(x+xe, y+ye);
	}
	glEnd();
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(angle,0,0.0,-1.0);
	glBindTexture(GL_TEXTURE_2D, missileTexture);

	glBindTexture(GL_TEXTURE_2D, silhouetteTextureMissile);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	
	int x_frame = game->missiles.nextframe;
	float toplvl = 0;
	
	if(game->missiles.nextframe > 23)
	{
		game->missiles.nextframe = 0;
		toplvl = 0;
		x_frame = 0;
	}
	else if(game->missiles.nextframe > 11)
	{
		cout << x_frame << endl;
		toplvl = y_i;
		x_frame -= 12; 
	}

	glBegin(GL_QUADS);
	glTexCoord2f( x_frame*x_i, toplvl + y_i); glVertex2i(-wid, -height); // bottom left
	glTexCoord2f( x_frame*x_i,  toplvl); glVertex2i(-wid,height); //top left
	glTexCoord2f(x_i + x_frame*x_i,toplvl); glVertex2i( wid,height); // top right
	glTexCoord2f(x_i + x_frame*x_i, toplvl + y_i); glVertex2i( wid, -height); // bottom right
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
		lvl = 2;
		toplvl = 1 * 0.111111111;
	}
	
	
	if(frame > 11 * x_increment)
	{
		lvl = 1;
		toplvl = 0.0;
		frame = 4*x_increment;
	}

	renderCell(frame, x_increment, y_increment, lvl, toplvl, game);
}

