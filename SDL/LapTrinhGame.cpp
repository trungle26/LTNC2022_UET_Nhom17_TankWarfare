#include <SDL.h>
#include <stdio.h>
#include <string>

// global variables
const int SCREEN_WIDTH = 2256;
const int SCREEN_HEIGHT = 1504;

// Key press surfaces constants
enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};
// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The surface contained by the windows
SDL_Surface* gScreenSurface = NULL;
// load individual image
SDL_Surface* loadSurface(std::string path);

// the images correspond to the key
SDL_Surface* gKeyPressSurface[ KEY_PRESS_SURFACE_TOTAL];
// current displayed surface
SDL_Surface* gCurrentSurface = NULL;


bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("error: can not initialize SDL! SDL_Error: %s \n"
			, SDL_GetError());
		success = false;
	}
	else {
		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("cannot create window! SDL Error: %s \n", SDL_GetError());
			success = false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;
	//Load default surface
	gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/sample.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Can not load image! SDL Error: %s \n", SDL_GetError());
		success = false;
	}
	//Load up surface
	gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Can not load image! SDL Error: %s \n", SDL_GetError());
		success = false;
	}
	//Load down surface
	gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Can not load image! SDL Error: %s \n", SDL_GetError());
		success = false;
	}
	//Load left surface
	gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Can not load image! SDL Error: %s \n", SDL_GetError());
		success = false;
	}
	//Load right surface
	gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
	if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Can not load image! SDL Error: %s \n", SDL_GetError());
		success = false;
	}

	return success;
}

void close() {
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("cannot load image! %s SDL Error: \n %s ", path.c_str(), SDL_GetError());
	}
	else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL) {
			printf("cannot optimize surface! SDL Error: &s\n", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

int main(int argc, char* args[]) {
	bool quit = false;
	// event handler:
	if (!init()) {
		printf("Failed to start SDL! \n");
	}
	else {
		if (!loadMedia()) {
			printf("cannot load media!\n");
		}
		else {
			SDL_Event e;
			//set default current surface
			gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					// if user press X
					if (e.type == SDL_QUIT) quit = true;
					// if user press a key
					else if (e.type == SDL_KEYDOWN) {
						switch (e.key.keysym.sym) {
						case SDLK_UP:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
							break;

						case SDLK_DOWN:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
							break;

						case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
							break;

						case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
							break;

						default:
							gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
						//apply the image stretched
						SDL_Rect stretchRect;
						stretchRect.x = 0;
						stretchRect.y = 0;
						stretchRect.w = SCREEN_WIDTH;
						stretchRect.h = SCREEN_HEIGHT;
						SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &stretchRect);
						// update the surface
						SDL_UpdateWindowSurface(gWindow);
					}
				}
				
			}
			
		}
	}
	close();
	return 0;
}