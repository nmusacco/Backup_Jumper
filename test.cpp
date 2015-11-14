
#include "game.h"


void makePlatform(Game *game)
{
	int window_height = 1;
	if(!game) // error checking!!!
		return;
	if(game->platformHead) // if platforms exist get OUT OF HERE!!!
		return;
	
	Vec pos;
	int w = game->player.width * 15;
	int h = game->player.height * 0.35;

	pos.x = 2;//rand() % window_width;
	pos.y = window_height - 1.0/5.0 * window_height + h * 2;
	
	// first element in platformHead
	game->platformHead = new Platform(pos, w, h, NULL);
	
	// the rest of the linked list
	Platform * ptr = game->platformHead;
	for(int i = 1; i < 5; ++i)
	{
		pos.x = 2;//rand() % window_width;
		pos.y = window_height - 1.0/5.0 *window_height* (i + 1) + h*2;
		
		ptr->next = new Platform(pos, w, h, NULL);
		ptr = ptr->next;
		//ptr = new Platform(pos, w, h, NULL);

		int numofPlat_sameAxis = 2;//rand() % 2;
		for(int r = 0; r < numofPlat_sameAxis; ++r)
		{
			pos.x = 2;//rand() % window_width;
			ptr->next = new Platform(pos, w, h, NULL);
			ptr = ptr->next;
		}	
	}
	
	// sets the player's x axis to the first platforms x axis
	game->player.position.x = game->platformHead->pos.x;
}


int main()
{
	Game d;
	makePlatform(&d);
	makePlatform(&d);
	makePlatform(&d);
	d = Game();
	makePlatform(&d);
	
	return 0;
}
