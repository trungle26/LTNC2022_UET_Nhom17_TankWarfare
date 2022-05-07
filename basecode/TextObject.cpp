#include "TextObject.h"

//SDL_Renderer* Game::renderer = NULL;
TextObject::TextObject(){}
TextObject::~TextObject() {}
//su dung 1 object TextObject de dua vao su dung duoc
TextObject textTexture;

void TextObject::free()
{
	//Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

bool TextObject::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		if (texture == NULL) 
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{

			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return texture != NULL;
}

void TextObject::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextObject::setColor(int type) {
	if (type == RED_TEXT) {
		SDL_Color color = { 255, 0, 0 };
		text_color = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Colour color = { 255, 255, 255 };
	}
	else if (type == BLACK_TEXT) {
		SDL_Colour color = { 0, 0, 0 };
		text_color = color;
	}
}

void TextObject::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopyEx(Game::renderer, texture, clip, &renderQuad, angle, center, flip);
}
bool TextObject::loadMedia()
{
	bool success = true;
	font = TTF_OpenFont("Candara.ttf", 24);
	if (font == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		std::cout << "font o day lai load duoc" << std::endl;
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!textTexture.loadFromRenderedText("The quickthe lazy dog", textColor))
		{
			printf("Failed to render text texture!\n", SDL_GetError());
			success = false;
		}
	}
	return success;
}
void TextObject::close()
{
	textTexture.free();
	TTF_CloseFont(font);
	font = NULL;
	TTF_Quit();
}

//dang code lam cais textobject

// đã tạo đối tượng để đưa vào code, close() sắp xong 

 void TextObject::draw()
{

	if (loadMedia())
	{ 
		textTexture.render((1248 - textTexture.getWidth()) / 2, (736 - textTexture.getHeight()) / 2);
	}
	
}