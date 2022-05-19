#include "Menu.h"
//tao texture tu anh de co the ve duoc
//Screen dimension constants
double Menu::GetScale = 0.5;
bool Menu::checkShowBullet = false;
bool Menu::checkAccessShowBulletFromGame = false;

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
	KEY_Yes_No,
	KEY_Check_Show_Bullet
};

SDL_Event Menu::event;
SDL_Surface* Menu::screenSurface = NULL;
SDL_Surface* Menu::PNGSurface = NULL;
SDL_Window* Menu::window = NULL;
SDL_Renderer* Menu::renderer = NULL;
SDL_Surface* MenuSurface[10];
SDL_Surface* OptionSurface[10];
SDL_Surface* SoundSurface[10];
Mix_Music* Menu::sound = NULL; // tắt
bool exitMenu;
Menu::Menu() {

}
Menu::~Menu() {}

void Menu::close()
{
	MenuTexture::close();
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_FreeSurface(PNGSurface);
	SDL_FreeSurface(screenSurface);
	PNGSurface = NULL;
	screenSurface = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	Mix_FreeMusic(sound);
	sound = NULL;

	for (int i = 0; i < 10; i++)
	{
		SDL_FreeSurface(MenuSurface[i]);
		MenuSurface[i] = NULL;
		SDL_FreeSurface(OptionSurface[i]);
		OptionSurface[i] = NULL;
		SDL_FreeSurface(SoundSurface[i]);
		SoundSurface[i] = NULL;
	}


	std::cout << "Menu closed! " << std::endl;
}
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
	SDL_Renderer* renderer = Game::renderer;
	if (renderer != NULL)
	{
		std::cout << "menu renderer using game renderer" << std::endl;
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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
	}
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		//success = false;
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
	MenuSurface[KEY_Yes_No] = loadSurface("assets/YESorNO.png");
	if (!MenuSurface[KEY_Yes_No])
	{
		std::cout << "Failed to load YESorNO.png" << std::endl;
		success = false;
	}

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
	OptionSurface[KEY_Show_Bullet_Trajectory] = loadSurface("assets/checkShowBullet.png");
	if (!OptionSurface[KEY_Show_Bullet_Trajectory])
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

//open music at beginning
bool firstTime = true;

void Menu::handleMenuEvent()
{
	std::cout << "Went into menu func" << std::endl;
	if (firstTime)
	{
		//Mix_PlayMusic(sound, 0);
		firstTime = !firstTime;
	}
	bool quit = false;
	PNGSurface = MenuSurface[KEY_Menu];
	while (!quit)
	{
		if (exitMenu)
		{
			std::cout << "cant access further bc exitMEnu" << std::endl;
			return;
		}
		if (quit == true) std::cout << "Abcd " << std::endl;
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
					exitMenu = true;
					return;
				case SDLK_n:
					PNGSurface = MenuSurface[KEY_Menu];
					break;
				case SDLK_1:
					PNGSurface = MenuSurface[KEY_Exit];
					break;
					//return;
				case SDLK_2:
					Menu::handleOptionsEvent();
					break;
				case SDLK_3:
					PNGSurface = MenuSurface[KEY_How_To_Play];
					break;
				}
			}
		}
		Menu::renderMenu();
	}
}

enum TankSize
{
	small,
	medium,
	large
};
enum TextColour
{
	RED_TEXT,
	WHITE_TEXT,
	BLACK_TEXT,
};
void Menu::handleOptionsEvent()
{
	std::cout << "Went into option func" << std::endl;
	PNGSurface = MenuSurface[KEY_Option];
	bool quit = false;
	while (!quit)
	{
		if (exitMenu)
		{
			std::cout << "cant access further bc exitMenu" << std::endl;
			return;
		}
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
					handleSoundEvent();
					break;
				case SDLK_2:
					handleTankSizeEvent();
					break;
				case SDLK_3:
					//PNGSurface = OptionSurface[KEY_Show_Bullet_Trajectory];
					handleShowBullet();
					PNGSurface = MenuSurface[KEY_Option];
					break;
				case SDLK_4:
					PNGSurface = OptionSurface[KEY_Blood_Regenaration];
					//handleBloodRegenaration();
					break;

				case SDLK_5:
					Menu::handleMenuEvent();
					break;

				}
			}
		}
		Menu::renderMenu();
	}
}
void Menu::handleShowBullet()
{
	std::cout << "went into showbullet func" << std::endl;
	PNGSurface = OptionSurface[KEY_Show_Bullet_Trajectory];
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
				case SDLK_y:
					checkShowBullet = true;
					std::cout << "SHOW BULLET" << std::endl;
					if (!checkAccessShowBulletFromGame) {
						handleOptionsEvent();
					}
					return;
				case SDLK_n:
					checkShowBullet = false;
					std::cout << "DONT SHOW BULLET" << std::endl;
					if (!checkAccessShowBulletFromGame) {
						handleOptionsEvent();
					}
					return;
				}
			}
		}
		Menu::renderMenu();
	}
}
void Menu::handleSoundEvent()
{
	std::cout << "Went into sound func" << std::endl;
	PNGSurface = OptionSurface[KEY_Sound];
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
				std::cout << "KEYDOWN" << std::endl;
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					if (Mix_PlayingMusic()) Mix_PauseMusic();
					break;
				case SDLK_2:
					if (Mix_PausedMusic()) Mix_PlayMusic(sound, 1);
					break;
				case SDLK_3:
					handleOptionsEvent();
					return;
				}
			}
		}
		Menu::renderMenu();
	}
}

void Menu::handleTankSizeEvent()
{
	PNGSurface = OptionSurface[KEY_Tank_Size];
	std::cout << "Went into tanksize func" << std::endl;
	double scale = 1;
	bool quit = false;
	while (!quit)
	{
		if (exitMenu)
		{
			std::cout << "cant access further bc exitMEnu" << std::endl;
			return;
		}
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (Menu::event.type == SDL_KEYDOWN)
			{
				std::cout << "KEYDOWN" << std::endl;

				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					scale = 0.5;
					std::cout << 0.5 << std::endl;
					ShowTextWindowWhileSelectingTank(event);
					break;
				case SDLK_2:
					scale = 1;
					std::cout << 1 << std::endl;
					ShowTextWindowWhileSelectingTank(event);
					break;
				case SDLK_3:
					scale = 2;
					std::cout << 2 << std::endl;
					ShowTextWindowWhileSelectingTank(event);
					break;
				case SDLK_4:
					handleOptionsEvent();
					return;
				case SDLK_5:
					handleYN();
					break;
				}
			}
		}
		GetScale = scale;
		Menu::renderMenu();
	}
}




void Menu::handleYN()
{
	PNGSurface = MenuSurface[KEY_Exit];
	bool quit = false;
	while (!quit)
	{	//PNGSurface = MenuSurface[KEY_Yes_No];

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
					exitMenu = true;
					quit = true;
					std::cout << "EXIT MENU" << std::endl;
					//PNGSurface = OptionSurface[KEY_Tank_Size];
					return;
				case SDLK_n:
					PNGSurface = OptionSurface[KEY_Tank_Size];
					Menu::renderMenu();
					return;
				}
				std::cout << "still running" << std::endl;
			}
		}
		Menu::renderMenu();
	}
	std::cout << "exit from yes no func" << std::endl;
}

void Menu::renderMenu()
{
	SDL_BlitSurface(PNGSurface, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
}



void Menu::ShowTextWindowWhileSelectingTank(SDL_Event e)
{
	/*text->init("tank size");
	text->loadMedia(); */
	textTexture->init("tanksize");
	if (e.key.keysym.sym == SDLK_1)
	{
		//textTexture->loadMedia(e);
		textTexture[small].loadMedia(e);
		textTexture[small].Render(e);
		//textTexture[small][1].Render();
		return;
	}
	else if (e.key.keysym.sym == SDLK_2)
	{
		textTexture[medium].loadMedia(e);
		textTexture[medium].Render(e);
		return;
	}
	else if (e.key.keysym.sym == SDLK_3)
	{
		//textTexture->loadMedia(e);
		textTexture[large].loadMedia(e);
		textTexture[large].Render(e);
		return;
	}
}
