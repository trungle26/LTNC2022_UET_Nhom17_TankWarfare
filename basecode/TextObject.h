#pragma once
#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_



#include "Game.h"

class TextObject
{
public:
	TextObject();
	~TextObject();
	void free();
	enum TextColour
	{
		RED_TEXT,
		WHITE_TEXT,
		BLACK_TEXT,
	};

	void draw(std::string path, SDL_Renderer* renderer);
	bool loadFromRenderedText(std::string textureText, SDL_Color textCcolor);
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setColor(int type);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	bool loadMedia();
	void close();
	int getWidth() {
		return width;
	}
	int getHeight()
	{
		return height;
	}

	void draw();
	TTF_Font* getFont()
	{
		return font;
	}
private:
	SDL_Color text_color;

	//The actual hardware texture
	SDL_Texture* texture;
	std::string context;
	int height;
	int width;

	TTF_Font* font = NULL;

};
#endif // !TEXT_OBJECT_H_