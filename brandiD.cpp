// ----------------------------------------------
// 
// -----------------------------------------
// collisions!

void Game::checkBottomScreen()
{
	// bottom of screen, allow double jump
	if(player.position.y - player.height <= 0) // WORKS!!!
	{
		setPosY(player.height);
		setAccel(velX(),0);
		if_jump = true;
	}

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

bool Game::checkCollision()
{
    for(int i =0; i <5; i++)
    {
    	Platform *p = &platform[i];
	if((player.position.y - player.height) >= (p->pos.y + p->height) && (player.position.x <= (p->pos.x + p->width) && player.position.x >= (p->pos.x - p->width)))
    	{
	setPosY(player.height + (p->pos.y + p->height));
	setAccel(velX(),0);
	//if_jump = true;
	return true;
    }
    }
    return false;


}
// more collisions!!!
