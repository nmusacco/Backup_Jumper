//	cs335 	Fall2015
// ========================
// student: Pedro Gonzalez
// ===========================
// all draw methods that get called in render funciton

drawBackground();
drawSpike();
drawMissile(game);

// used to allow non textures objects to maintain their color
glBindTexture(GL_TEXTURE_2D, 0);

drawPlatform(game,5);
drawSkeleton(game);	