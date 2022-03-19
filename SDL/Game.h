#pragma once
#include <SDL.h>
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void close();
	static SDL_Renderer* renderer;
	bool running() { return isRunning; };
	static SDL_Event event;


private:
	bool isRunning;
	SDL_Window* window;
	
};
