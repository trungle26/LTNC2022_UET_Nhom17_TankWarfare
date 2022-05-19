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
	
	menu->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1248, 736);
	Menu::handleOptionsMedia();
	Menu::loadMenuMedia();
	Menu::loadSoundMedia();
	while (exitMenu == false) {
		Menu::handleMenuEvent();
	}
	
	game = new Game();
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
	menu->close();
	game->close();
	return 0;
}