#include "Menu.h"
//tao texture tu anh de co the ve duoc
//Screen dimension constants

enum KeyPressSurfaces
{
	KEY0,
	KEY1,
	KEY2,
	KEYTOTAL
};

SDL_Event Menu::event;

Menu::Menu(){}
Menu::~Menu() {}

SDL_Surface* keyPressSurfaces[KeyPressSurfaces::KEYTOTAL];

bool Menu::init(const char* title, int x, int y, int width, int height)
{
	bool success = true;

	window == SDL_CreateWindow("Menu Texture", x, y, width, height, false);
	if (window) 
	{
		std::cout << "Created window" << std::endl;
	}
	else
	{
		success = false;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!IMG_Init(imgFlags) & imgFlags)
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
		success = false;
	}
	else 
	{
		screenSurface = SDL_GetWindowSurface(window);
	}
	// SDL_ttf 
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
	else 
	{
		success = false;
	}
	return success;
}

void Menu::handleMenuEvent()
{
	if (!loadMenuMedia()) 
	{
		std::cout << "Failed to load media" << std::endl;
	}
	else 
	{
		screenSurface = 
		SDL_PollEvent(&event);
		switch(event.type == SDL_KEYDOWN) 
		{
			
		}
	}
}

bool Menu::loadMenuMedia()
{
	bool success = true;
	PNGSurface = loadMenuSurface("Menu.png");
	if (!PNGSurface)
	{
		std::cout << "Failed to load anh PNG" << std::endl;
		success = false;
	}
	//font chu nua?
	// no khong can hehe vi ban da dung keypress
	return success;
}

SDL_Surface* Menu::loadMenuSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) 
	{
		std::cout << "Unable to load image %s! SDL_image Error: " << path.c_str() << std::endl << IMG_GetError();
	}
	else 
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);// ??? format la nhu nao???
		if (optimizedSurface == NULL) 
		{
			std::cout << "Unable to optimize image %s! SDL Error: " << path.c_str() << std::endl << SDL_Error();
		}
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

void Menu::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(PNGSurface);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	std::cout << "Menu closed! " << std::endl;
}