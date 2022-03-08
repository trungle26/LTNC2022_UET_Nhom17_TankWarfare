#pragma once
#include "Game.h"

Game* game = NULL;

int main(int argc,  char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1000 / 60;
	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	game->close();
	return 0;
}