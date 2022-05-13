#include "Menu.h"
//tao texture tu anh de co the ve duoc
//Screen dimension constants

enum KeyPressMenuSurfaces
{
	KEY_Exit,
	KEY_Option,
	KEY_How_To_Play,
	KEY_Sound,
	KEY_Tank_Size,
	KEY_Show_Bullet_Trajectory,
	KEY_Blood_Regenaration,
	KEY_Menu,
	KEY_Yes_No
};
SDL_Event Menu::event;
SDL_Surface* Menu::screenSurface = NULL;
SDL_Surface* Menu::PNGSurface = NULL;
SDL_Window* Menu::window = NULL;

SDL_Surface* MenuSurface[10];
SDL_Surface* OptionSurface[10];
SDL_Surface* SoundSurface[10];
Mix_Music* Menu::sound = NULL; // tắt
Menu::Menu() {}
Menu::~Menu() {}

bool Menu::init(const char* title, int x, int y, int width, int height)
{
	bool success = true;

	window = SDL_CreateWindow(title, x, y, width, height, false);
	if (window)
	{
		std::cout << "Created window" << std::endl;
	}
	else
	{
		std::cout << "create window failed " << std::endl;
		//success = false;
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
	// sound 
	//Load Music
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
	}

	return success;
}
SDL_Surface* Menu::loadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image %s! SDL_image Error: " << path.c_str() << std::endl << IMG_GetError() << std::endl;
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			std::cout << "Unable to optimize image %s! SDL Error: " << path.c_str() << std::endl << SDL_GetError();
		}
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

bool Menu::loadMenuMedia()
{
	bool success = true;
	MenuSurface[KEY_Menu] = loadSurface("assets/Menu.png");
	if (MenuSurface[KEY_Menu] == NULL)
	{
		std::cout << "Failed to load menu image" << std::endl;
		success = false;
	}

	MenuSurface[KEY_Exit] = loadSurface("assets/Exit.png");//da co
	if (MenuSurface[KEY_Exit] == NULL)
	{
		std::cout << "Failed to load default image" << std::endl;
		success = false;
	}
	MenuSurface[KEY_Option] = loadSurface("assets/Options.png");// da co
	if (!MenuSurface[KEY_Option])
	{
		std::cout << "Failed to load Option image" << std::endl;
		success = false;
	}
	MenuSurface[KEY_How_To_Play] = loadSurface("assets/How_To_Play.png");//da co
	if (!MenuSurface[KEY_How_To_Play])
	{
		std::cout << "Failed to load How_To_Play image" << std::endl;
		success = false;
	}
	//font chu nua?
	// no khong can hehe vi ban da dung keypress
	return success;
}
bool Menu::handleOptionsMedia()
{
	bool success = true;
	OptionSurface[KEY_Menu] = loadSurface("assets/Menu.png");// da co
	if (!OptionSurface[KEY_Menu])
	{
		std::cout << "Failed to menu image" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Tank_Size] = loadSurface("assets/TankSize.png");
	if (!OptionSurface[KEY_Tank_Size])
	{
		std::cout << "Failed to load TankSize image" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Blood_Regenaration] = loadSurface("assets/BloodRegenaration.png");
	if (!OptionSurface[KEY_Blood_Regenaration])
	{
		std::cout << "Failed to load BloodRegenaration image" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Show_Bullet_Trajectory] = loadSurface("assets/ShowBullet.png");
	if (!OptionSurface[KEY_Tank_Size])
	{
		std::cout << "Failed to load ShowBullet image" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Sound] = loadSurface("assets/Sound.png");
	if (!OptionSurface[KEY_Sound])
	{
		std::cout << "Failed to load Sound image" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Yes_No] = loadSurface("assets/YESorNO.png");
	if (!OptionSurface[KEY_Yes_No])
	{
		std::cout << "Failed to load YESorNO.png" << std::endl;
		success = false;
	}
	//font chu nua?
	// no khong can hehe vi ban da dung keypress
	return success;
}
bool Menu::loadSoundMedia()
{
	bool success = true;
	sound = Mix_LoadMUS("assets/background_music.mp3");
	if (sound == NULL) {
		std::cout << Mix_GetError();
	}
	SoundSurface[KEY_Option] = loadSurface("assets/Options.png");
	if (SoundSurface[KEY_Option] == NULL)
	{
		std::cout << "Failed to load Option image" << std::endl;
		success = false;
	}
	return success;
}

void Menu::handleMenuEvent()
{
	Mix_PlayMusic(sound, 0);
	bool quit = false;
	PNGSurface = MenuSurface[KEY_Menu];
	while (!quit)
	{
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_y:
					return;
				case SDLK_n:
					PNGSurface = MenuSurface[KEY_Menu];
					break;
				case SDLK_1:
					PNGSurface = MenuSurface[KEY_Exit];
					break;
				case SDLK_2:
					PNGSurface = MenuSurface[KEY_Option];
					Menu::handleOptionsEvent();
					break;
				case SDLK_3:
					PNGSurface = MenuSurface[KEY_How_To_Play];
					break;
				}
			}
		}

		//Apply the current image
		SDL_BlitSurface(PNGSurface, NULL, screenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}
}
void Menu::handleOptionsEvent()
{
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					PNGSurface = OptionSurface[KEY_Sound];
					handleSoundEvent();
					break;
				case SDLK_2:
					PNGSurface = OptionSurface[KEY_Tank_Size];
					handleTankSizeEvent();
					break;
				case SDLK_3:
					PNGSurface = OptionSurface[KEY_Show_Bullet_Trajectory];
					//handleShowBullet();
					break;
				case SDLK_4:
					PNGSurface = OptionSurface[KEY_Blood_Regenaration];
					//handleBloodRegenaration();
					break;

				case SDLK_5:
					PNGSurface = OptionSurface[KEY_Menu];
					return;

				}
			}
		}

		//Apply the current image
		SDL_BlitSurface(PNGSurface, NULL, screenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}
}

void Menu::handleSoundEvent()
{
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					Mix_PauseMusic();
					break;
				case SDLK_2:
					Mix_PlayMusic(sound, 1);
					break;
				case SDLK_3:
					PNGSurface = SoundSurface[KEY_Option];
					return;
					break;
				}
			}
		}

		//Apply the current image
		SDL_BlitSurface(PNGSurface, NULL, screenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}
}

void Menu::handleTankSizeEvent()
{
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (Menu::event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					//stateTankSize[0] = true;
					break;
				case SDLK_2:
					//stateTankSize[1] = true;
					//do no
					break;
				case SDLK_3:
					//stateTankSize[2] = true;

					break;
				}
			}
		}

		//Apply the current image
		SDL_BlitSurface(PNGSurface, NULL, screenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}
}

void Menu::close()
{
	SDL_DestroyWindow(window);
	SDL_FreeSurface(PNGSurface);
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	std::cout << "Menu closed! " << std::endl;
}


void Menu::handleYN()
{
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (Menu::event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_y:
					//do yes
					break;
				case SDLK_n:
					//do no
					break;
				}
			}
		}

		//Apply the current image
		SDL_BlitSurface(PNGSurface, NULL, screenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(window);
	}
}
