#include "LTexture.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


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
SDL_Window* LTexture::window = NULL;
TTF_Font* LTexture::font = NULL;
LTexture textTexture[10];
SDL_Renderer* LTexture::renderer = NULL;

//SDL_Surface* LTexture::screenSurface = NULL;
//SDL_Surface* LTexture::PNGSurface = NULL;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	text_color.r = 255;
	text_color.b = 255;
	text_color.g = 255;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

void LTexture::init(const char* title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized! \n";

		window = SDL_CreateWindow("nofTankSize", 0, 0, 400, 400, false);
		if (!window)
		{
			std::cout << "create window for text failed" << std::endl;
		}
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			//success = false;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer initialized!\n";
		}
	}
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

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
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::SetColor(int type) {
	if (type == RED_TEXT) {
		SDL_Color color = { 255, 0, 0 };
		text_color = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Colour color = { 255, 255, 255 };
		text_color = color;
	}
	else if (type == BLACK_TEXT) {
		SDL_Colour color = { 0, 0, 0 };
		text_color = color;
	}

}
SDL_Color LTexture::GetColour()
{
	return	text_color;
}
void LTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
	text_color.r = red;
	text_color.b = blue;
	text_color.g = green;
}



void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	std::cout << "went to render func" << std::endl;
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::loadMedia()
{
	bool success = true;
	font = TTF_OpenFont("assets/font/JetBrainsMono-Bold.ttf",20);
	if (font == NULL)
	{
		printf("Failed to load jetbrain font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		if (textTexture[small].loadFromFile("assets/tank.png"))
		{
			std::cout << "load duoc anh tank roi" << std::endl;
		}
		else
		{
			std::cout << "yup ko load duoc" << std::endl;
		}
		textTexture[small].SetColor(BLACK_TEXT);
		if (!textTexture[small].loadFromRenderedText("CHanged tanks size to 20*18", textTexture[small].GetColour()))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}

		textTexture[medium].SetColor(RED_TEXT);
		if (!textTexture[medium].loadFromRenderedText("Changed tanks size to 40*36", textTexture[medium].GetColour()))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		textTexture[large].SetColor(BLACK_TEXT);
		//textTexture[large].
		if (!textTexture[large].loadFromRenderedText("Changed tanks size to 80*72", textTexture[large].GetColour()))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}
	return success;
}


void LTexture::Render()
{
		SDL_RenderClear(renderer);
		//Render current frame
		int x = (SCREEN_WIDTH - textTexture[small].getWidth()) / 2;
		int y = (SCREEN_HEIGHT - textTexture[small].getHeight()) / 2;
		this->render(0, 0);

		//Update screen
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
		SDL_DestroyWindow(window);
}
