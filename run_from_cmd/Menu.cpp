#include "Menu.h"

const int TEXTURE_H = 1200;
const int TEXTURE_W = 1500;
Menu* HTPtexture = NULL;
//Screen dimension constants
const int SCREEN_W = 1248;
const int SCREEN_H = 736;
int Menu::mWidth;
int Menu::mHeight;
double Menu::GetScale = 1;
bool Menu::checkShowBullet = true;
bool Menu::checkAccessShowBulletFromGame = false;
bool Menu::checkAccessSoundFromGame = false;
bool Menu::inGame = false;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
enum KeyPressMenuSurfaces
{
	KEY_Exit,
	KEY_Option,
	KEY_How_To_Play,
	KEY_Sound,
	KEY_Sound_Without_Option,
	KEY_Tank_Size,
	KEY_Show_Bullet_Trajectory,
	KEY_Menu,
	KEY_Yes_No,
	KEY_Check_Show_Bullet,
	KEY_Map1,
	KEY_Map2,
	KEY_Map3,
	KEY_Blood_YN,
	KEY_Choose_Map
};

SDL_Event Menu::event;
SDL_Surface* Menu::screenSurface = NULL;
SDL_Surface* Menu::PNGSurface = NULL;
SDL_Window* Menu::window = NULL;
//SDL_Renderer* Menu::renderer = NULL;
//SDL_Texture* Menu::texture = NULL;
SDL_Surface* MenuSurface[20];
SDL_Surface* OptionSurface[20];
SDL_Surface* SoundSurface[20];
Mix_Music* Menu::sound = NULL; // tắt'
bool Menu::needToChangeTankSize = true;
int Menu::newTankWidth = 32;
int Menu::newTankHeight = 32;
bool Menu::healingOrNot = true;
bool exitMenu;
std::string Game::mapPath;

Menu::Menu() {}
Menu::~Menu() {}

void Menu::close()
{
	MenuTexture::close();

	
	SDL_FreeSurface(PNGSurface);
	Mix_FreeMusic(sound);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	PNGSurface = NULL; sound = NULL; renderer = NULL; window = NULL;
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
		success = false;
	}
	//SDL_Renderer* renderer = Game::renderer;
	//renderer = Game::renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H);
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
	//MenuSurface[KEY_How_To_Play] = loadSurface("assets/How_To_Play.png");//da co
	//if (!MenuSurface[KEY_How_To_Play])
	//{
	//	std::cout << "Failed to load How_To_Play image" << std::endl;
	//	success = false;
	//}
	MenuSurface[KEY_How_To_Play] = loadSurface("assets/HTP.png");//da co
	if (!MenuSurface[KEY_How_To_Play])
	{
		std::cout << "Failed to load HTP image" << std::endl;
		success = false;
	}
	MenuSurface[KEY_Yes_No] = loadSurface("assets/YESorNO.png");
	if (!MenuSurface[KEY_Yes_No])
	{
		std::cout << "Failed to load YESorNO.png" << std::endl;
		success = false;
	}
	Menu::handleOptionsMedia();
	Menu::loadSoundMedia();
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
	OptionSurface[KEY_Map1] = loadSurface("assets/Map1.png");
	if (!OptionSurface[KEY_Map1])
	{
		std::cout << "Failed to load Map1.png" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Map2] = loadSurface("assets/Map2.png");
	if (!OptionSurface[KEY_Map2])
	{
		std::cout << "Failed to load Map2.png" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Map3] = loadSurface("assets/Map3.png");
	if (!OptionSurface[KEY_Map3])
	{
		std::cout << "Failed to load Map3.png" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Blood_YN] = loadSurface("assets/Blood_YN.png");
	if (!OptionSurface[KEY_Blood_YN])
	{
		std::cout << "Failed to loadBlood_YN.png" << std::endl;
		success = false;
	}
	OptionSurface[KEY_Choose_Map] = loadSurface("assets/chooseMap.png");
	if (!OptionSurface[KEY_Choose_Map])
	{
		std::cout << "Failed to load chooseMap.png" << std::endl;
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
	SoundSurface[KEY_Sound_Without_Option] = loadSurface("assets/Sound without Option.png");
	if (SoundSurface[KEY_Sound_Without_Option] == NULL)
	{
		std::cout << "Failed to load Sound without option image" << std::endl;
		success = false;
	}
	return success;
}


SDL_Rect source{ 0,0, SCREEN_W ,SCREEN_H };
SDL_Rect dest{ 50, 10,SCREEN_W - 100 , SCREEN_H - 20 };

//open music at beginning
bool firstTime = true;

void Menu::handleMenuEvent()
{
	std::cout << "Went into menu func" << std::endl;
	if (firstTime)
	{
		Mix_PlayMusic(sound, 0);
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
				exitMenu = true;
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
					Menu::handleHTP();
					break;
				}
			}
		}
		Menu::renderMenu();
	}
}

void Menu::handleHTP()
{
	
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//The camera area

	//While application is running
	while (!quit)
	{
		if (HTPtexture->loadFromFile("assets/HTP.png") != NULL)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				SDL_Rect renderQuad = { 0, 0, mWidth, mHeight };

				//Set clip rendering dimensions
				//if (clip != NULL)
				//{
				//	renderQuad.w = clip->w;
				//	renderQuad.h = clip->h;
				//}

				//Render to screen
				SDL_RenderCopyEx(renderer, texture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				if (e.type == SDL_KEYDOWN)
				{//std::cout << source.x << ' ' << source.y << std::endl;
					switch (e.key.keysym.sym)
					{
					case SDLK_UP: source.y -= 10; break;
					case SDLK_DOWN: source.y += 10; break;
					case SDLK_1: source.w *= 2; source.h *= 2; break;
					case SDLK_2: source.w /= 2; source.h /= 2; break;
					}
				}
				if (e.type == SDL_MOUSEWHEEL)
				{
					if (e.wheel.y > 0) // scroll up
					{
						source.y -= 50; break;
					}
					else if (e.wheel.y < 0) // scroll down
					{
						source.y += 50; break;
					}
				}

			}
			if (source.y <= 0) source.y = 0;
			if (source.y >= 465) source.y = 465;
				//Set rendering space and render to screen
		
			SDL_SetRenderTarget(renderer, NULL);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, &source, &dest);
			SDL_RenderPresent(renderer);
		}
		//PNGSurface = MenuSurface[KEY_How_To_Play];
		//Handle events on queue
	}
}

bool Menu::loadFromFile(std::string path)
{

		//Get rid of preexisting texture
		//free();

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}
			else
			{
				//Get image dimensions
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		//Return success
		texture = newTexture;
		return texture != NULL;
	
}

enum TankSize
{
	small,
	medium,
	large
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
				exitMenu = true;
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
					handleShowBullet();
					PNGSurface = MenuSurface[KEY_Option];
					break;
				case SDLK_4:
				
					handleBloodEvent();
					break;

				case SDLK_5:
					Menu::handleMenuEvent();
					break;
				case SDLK_6:
					if (Menu::inGame == false)
						Menu::chooseMap();
					else
					{
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Game is still running!","Cannot change map while game is running",window);
					}
					break;
				}
			}
		}
		Menu::renderMenu();
	}
}

void Menu::chooseMap()
{
	std::cout << "went into showbullet func" << std::endl;
	PNGSurface = OptionSurface[KEY_Choose_Map];
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				exitMenu = true;
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					Game::mapPath = "assets/map.map";
					PNGSurface = OptionSurface[KEY_Map1];
					Menu::renderMenu();
					SDL_Delay(1000);
					chooseMap();
					return;
				case SDLK_2:
					Game::mapPath = "assets/map2.map";
					PNGSurface = OptionSurface[KEY_Map2];
					Menu::renderMenu();
					SDL_Delay(1000);
					chooseMap();
					return;
				case SDLK_3:
					Game::mapPath = "assets/map3.map";
					PNGSurface = OptionSurface[KEY_Map3];
					Menu::renderMenu();
					SDL_Delay(1000);
					chooseMap();
					return;
				case SDLK_4:

					Menu::handleOptionsEvent();
					return;
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
				exitMenu = true;
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
				exitMenu = true;
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				std::cout << "KEYDOWN" << std::endl;
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					if (Mix_PlayingMusic()) Mix_PauseMusic();
					if (checkAccessSoundFromGame)
					{
						return;
					}
					break;
				case SDLK_2:
					if (Mix_PausedMusic()) Mix_PlayMusic(sound, 1);
					if (checkAccessSoundFromGame)
					{
						return;
					}
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
				exitMenu = true;
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

void Menu::handleBloodEvent()
{
	PNGSurface = OptionSurface[KEY_Blood_YN];
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&Menu::event) != 0)
		{
			if (Menu::event.type == SDL_QUIT)
			{
				exitMenu = true;
				quit = true;
			}
			else if (Menu::event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_1:
					healingOrNot = true;
					handleOptionsEvent();
					return;
				case SDLK_2:
					healingOrNot = false;
					handleOptionsEvent();
					return;
				}
				std::cout << "still running" << std::endl;
			}
		}
		Menu::renderMenu();
	}
}




void Menu::handleYN()
{
	PNGSurface = MenuSurface[KEY_Exit];
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
	textTexture->init("tanksize");
	if (e.key.keysym.sym == SDLK_1)
	{
		textTexture[small].loadMedia(e);
		textTexture[small].Render(e);
		needToChangeTankSize = true;
		newTankWidth = 20;
		newTankHeight = 18;
		return;
	}
	else if (e.key.keysym.sym == SDLK_2)
	{
		textTexture[medium].loadMedia(e);
		textTexture[medium].Render(e);
		needToChangeTankSize = true;
		newTankWidth = 40;
		newTankHeight = 36;
		return;
	}
	else if (e.key.keysym.sym == SDLK_3)
	{
		//textTexture->loadMedia(e);
		textTexture[large].loadMedia(e);
		textTexture[large].Render(e);
		needToChangeTankSize = true;
		newTankWidth = 80;
		newTankHeight = 72;
		return;
	}
}

