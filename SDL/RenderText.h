#pragma once
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<iostream>
#include<string>
#include<math.h>

const int SCREEN_WIDTH = 1248;
const int SCREEN_HEIGHT = 736;
//idea based on Lazyfoo; however, I trully understand what I'm typing.
class LTexture {
public:
	LTexture();
	~LTexture();
	bool loadFromFile(const char* path);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void getWindowAndRenderer(SDL_Window* window_, SDL_Renderer* renderer_);
	//Get image dimensions
	int getWidth();
	int getHeight();
	//init and load media
	bool init();
	bool loadMedia();
	//attribute below
	SDL_Texture* mTexture;
	//image dimensions
	int mWidth;
	int mHeight;
	TTF_Font* gFont = NULL;
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;

};


