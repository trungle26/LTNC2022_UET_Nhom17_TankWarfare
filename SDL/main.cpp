#pragma once
#include "Game.h"
#include "Menu.h"
#include "MenuTexture.h"
Game* game = NULL;

Menu* menu = NULL;
//LTexture* text = NULL;
int main(int argc, char* argv[]) {


	const int FPS = 60;
	const int frameDelay = 1000 / 60;
	Uint32 frameStart;
	int frameTime;
	game = new Game();
	//text->init("text window");
	//if (text->loadMedia())
	//{
	//	std::cout << "media for text is loaded " << std::endl;
	//}


	//game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
	menu->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1248, 736);
	Menu::handleOptionsMedia();
	Menu::loadMenuMedia();
	Menu::loadSoundMedia();
	while (exitMenu == false) {
		if (exitMenu) std::cout << "exit menu " << std::endl;
		Menu::handleMenuEvent();
		//menu->renderMenu();
		std::cout << "still runnig" << std::endl;
	}
	std::cout << "Game inited" << std::endl;
	game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1248, 736, false);

	while (game->running()) {
		exitMenu = false;
		frameStart = SDL_GetTicks();
		//menu->render();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		// delay to only 60 frame rates per second . Source: Lets make game
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	game->close();
	return 0;
}