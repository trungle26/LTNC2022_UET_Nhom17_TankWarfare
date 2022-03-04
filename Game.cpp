#include "Game.hpp"
Game::Game() 
{}
Game::~Game() {

}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	bool flags = false;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized! \n";

		window = SDL_CreateWindow(title, x, y,width, height, flags);
		if (window) 
		{
			std::cout << "created window!\n";
		}
			
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer initialized!\n";
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update()
{}

void Game::render()
{
	SDL_RenderClear(renderer);
	// here we add things to render
	SDL_RenderPresent(renderer);
}

void Game::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game closed!\n";
}