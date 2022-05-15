
#ifndef LTEXTURE_H_
#define LTEXTURE_H_
#include "Game.h"
#include "Menu.h"
#include < vector>



class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	enum TextColour
	{
		RED_TEXT,
		WHITE_TEXT,
		BLACK_TEXT,
	};
	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Set color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetColor(int type);// cac mau co ban
	SDL_Color GetColour();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	//Gets image dimensions
	int getWidth();
	int getHeight();
	static SDL_Window* window;
	static TTF_Font* font;
	static SDL_Renderer* renderer;
	//std::vector <LTexture> textTexture;
	bool loadMedia();
	void init(const char* title);
	void Render();
private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;

	SDL_Color text_color;
};
extern LTexture textTexture[];
#endif