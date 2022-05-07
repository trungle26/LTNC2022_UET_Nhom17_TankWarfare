#pragma once
#ifndef MENU_H_
#define MENU_H_

#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class Menu
{
public:
	Menu();
	~Menu();

	bool init(const char* title, int x, int y, int width, int height);

	void handleMenuEvent();

	bool loadMenuMedia();

	SDL_Surface* loadMenuSurface(std::string path);

	void close();

	// lieu co nen dung dung 1 bien window cho toan bo cac event con lai
	static SDL_Window* window;//???
	////
	static SDL_Renderer* renderer;
	//khong can font chu nua
	//static TTF_Font* font[2];

	//Current displayed texture
	//va tham chi ban chua he dung texture
	static SDL_Texture* texture;
	// chua tinh den load text oke?

	static SDL_Event event;

private:
	SDL_Surface* screenSurface = NULL; // dest surface
	SDL_Surface* PNGSurface = NULL;// source surface
};

#endif