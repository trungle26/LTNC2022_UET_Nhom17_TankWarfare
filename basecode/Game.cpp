#include "Game.h"
#include "Menu.h"
#include "LTexture.h"
SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;

LTexture TextTexture;


//thu 1 doi tuong 
Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	bool flags = false;

	bool success = true;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL initialized! \n";
		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window) 
		{
			std::cout << "created window!\n";
		}
		
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			ScreenSurface = SDL_GetWindowSurface(window);
		}
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);// thay doi mau nen renderer
			std::cout << "renderer initialized!" << std::endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}
}

enum {
	up,
	down,
	left,
	right
};
bool states1[] = { false, false , false, false };
bool states2[] = { false, false, false ,false };

void Game::handleEvent()
{
	if (!loadMedia()) {
		printf("Failed to load media!\n");
	}
	else {
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_LEFT) states1[left] = true;
			if (Game::event.key.keysym.sym == SDLK_RIGHT) states1[right] = true;
			if (Game::event.key.keysym.sym == SDLK_UP) states1[up] = true;
			if (Game::event.key.keysym.sym == SDLK_DOWN) states1[down] = true;
			if (Game::event.key.keysym.sym == SDLK_a) states2[left] = true;
			if (Game::event.key.keysym.sym == SDLK_d) states2[right] = true;
			if (Game::event.key.keysym.sym == SDLK_w) states2[up] = true;
			if (Game::event.key.keysym.sym == SDLK_s) states2[down] = true;
			break;
		case SDL_KEYUP:
			if (Game::event.key.keysym.sym == SDLK_LEFT) states1[left] = false;
			if (Game::event.key.keysym.sym == SDLK_RIGHT) states1[right] = false;
			if (Game::event.key.keysym.sym == SDLK_UP) states1[up] = false;
			if (Game::event.key.keysym.sym == SDLK_DOWN) states1[down] = false;
			if (Game::event.key.keysym.sym == SDLK_a) states2[left] = false;
			if (Game::event.key.keysym.sym == SDLK_d) states2[right] = false;
			if (Game::event.key.keysym.sym == SDLK_w) states2[up] = false;
			if (Game::event.key.keysym.sym == SDLK_s) states2[down] = false;
			break;
		
		}
		
	}
}

void Game::update()
{
	
	SDL_BlitSurface(gPNGSurface, NULL, ScreenSurface, NULL);
	SDL_UpdateWindowSurface(window);
}

void Game::render()
{
	SDL_Rect textRect;
	//SDL_RenderClear(renderer);
	SDL_QueryTexture(TextTexture.getTexture(), NULL, NULL, &textRect.w, &textRect.h);
	//SDL_RenderCopy(renderer, TextTexture.getTexture(), NULL, NULL);
	//TextTexture.render((1246 - TextTexture.getWidth()) / 2, (736 - TextTexture.getHeight()) / 2);
		
	//menu->draw("Menu.png", Game::renderer);
	//SDL_RenderCopy(Game::renderer, TextTexture.getTexture(), NULL, NULL);
	TextTexture.render(100,100);
	SDL_RenderPresent(Game::renderer);
}


SDL_Surface* Game::loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen forma
		optimizedSurface = SDL_ConvertSurface(loadedSurface, ScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);

	}

	return optimizedSurface;
}

bool Game::loadMedia()//check;
{
	bool success = true;
	gPNGSurface = loadSurface("Menu.png");
	if (!gPNGSurface) {
		std::cout << "Failed to load anh PNG" << std::endl;
		success = false;
	}
	font[0] = TTF_OpenFont("Candarab.ttf", 50);
	font[1] = TTF_OpenFont("Candarab.ttf", 39);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!TextTexture.loadFromRenderedText("PLAY GAME", textColor, font[0]) && !TextTexture.loadFromRenderedText("OPTIONS", textColor, font[1] )&& !TextTexture.loadFromRenderedText("ABOUT", textColor, font[1]));
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void Game::close() {// check

	//Free global font

	TextTexture.free_texture();

	//Free global font
	//TTF_CloseFont(font);
	//font = NULL;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(gPNGSurface);
	gPNGSurface = NULL;
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	std::cout << "game closed!\n";
}