#pragma once
#ifndef MENU_H_
#define MENU_H_

//#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Game.h"
#include "LTexture.h"
#include <string>
class Menu
{
public:
	Menu();
	~Menu();

	bool init(const char* title, int x, int y, int width, int height);

	static SDL_Surface* loadSurface(std::string path);

	static bool loadMenuMedia();
	static bool handleOptionsMedia();// load cac media cua option? lieu sound co can load media ko
	static bool loadSoundMedia();

	static void handleYN();
	static void handleOptionsEvent();
	static void handleSoundEvent();
	static void handleMenuEvent();
	static void handleTankSizeEvent();
	void close();
	static double GetScale;
	static SDL_Window* window;//???
	static Mix_Music* sound;
	static SDL_Renderer* renderer;
	//khong can font chu nua
	//static TTF_Font* font[2];

	//Current displayed texture
	//va tham chi ban chua he dung texture

	// chua tinh den load text oke?
	bool running() { return isRunning; }
	void update();
	static void renderMenu();
	static void renderText();
	
	static void ShowTextWindowWhileSelectingTank(SDL_Event event);
	//test
	//static bool exitMenu ;
	static SDL_Event event;
protected:
	//SDL_Window* window;
	static SDL_Surface* screenSurface; // dest surface

	bool isRunning = true;
	static SDL_Surface* PNGSurface;// source surface
	
};
extern bool exitMenu;
#endif