#pragma once
#ifndef GAME_H_
#define GAME_H_


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handleEvent();
	void update();
	void render();
	bool loadMedia();
	void close();
	static SDL_Renderer* renderer;
	bool running()
	{
		return isRunning;
	}
	static SDL_Event event;
	SDL_Surface* loadSurface(std::string path);
protected:
	SDL_Window* window;
	bool isRunning;
	//The surface contained by the window
	TTF_Font* font[3];
	SDL_Surface* ScreenSurface = NULL;
	SDL_Surface* gPNGSurface = NULL;
};

#endif // !GAME_H_
