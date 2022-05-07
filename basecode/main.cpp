#include "Game.h"
#include "Menu.h"
#include "TextObject.h"
Game* game = NULL;
TextObject textobject;
Menu* menu = NULL;
int main(int argc, char *argv[]) 
{
	
	
	//

	game = new Game();
	game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1246 , 736, false);
	

	menu->init();

	while (game->running()) {
		game->handleEvent();
		game->update();		
		game->render();
	}

	game->close();
	return 0;
}