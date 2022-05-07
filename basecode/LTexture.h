#include "Game.h"
#include "TextObject.h"
class LTexture
{

private:
	SDL_Texture* Texture;
	int Width;
	int Height;
public:
	//Initializes variables
	LTexture() {
		this->Texture = NULL;
		this->Width = 0;
		this->Height = 0;
	}

	//Deallocates memory
	~LTexture() {
		this->free_texture();
	}
	bool loadFromFile(std::string path) {
		this->free_texture(); //free preexisting texture
		SDL_Surface* loadSurface = IMG_Load(path.c_str()); //temporary surface to load;
		if (loadSurface == NULL) {
			std::cout << "Unable to load image! SDL_image Error: " << std::endl << path << IMG_GetError();
		}
		else {
			SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0, 0xFF, 0xFF)); //color key image
			this->Texture = SDL_CreateTextureFromSurface(Game::renderer, loadSurface); //create texture from temporary surface
			if (this->Texture == NULL) {
				std::cout << "Unable to create texture from surface! SDL Error: " << std::endl << path << SDL_GetError();
			}
			else {
				this->Width = loadSurface->w;
				this->Height = loadSurface->h;
			}
			SDL_FreeSurface(loadSurface); //free temporary surface
		}
		return this->Texture != NULL;
	}
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font) {
		this->free_texture(); //delete preexisting texture
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
		if (textSurface == NULL) {
			std::cout << "Unable to render text surface! SDL_ttf Error: " << std::endl << TTF_GetError();
		}
		else {
			this->Texture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
			if (this->Texture == NULL) {
				std::cout << "Unable to create texture from rendered text! SDL Error: " << std::endl << SDL_GetError();
			}
			else {
				this->Width = textSurface->w;
				this->Height = textSurface->h;
			}
			SDL_FreeSurface(textSurface);
		}
		return this->Texture != NULL;
	}
	void free_texture()
	{
		if (this->Texture != NULL) 
		{
			SDL_DestroyTexture(this->Texture);
			this->Texture = NULL;
			this->Width = 0;
			this->Height = 0;
		}
	}
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		SDL_Rect render_space = { x, y, this->Width, this->Height };
		if (clip != NULL) {
			render_space.w = clip->w;
			render_space.h = clip->h;
		}
		SDL_RenderCopyEx(Game::renderer, this->Texture, clip, &render_space, angle, center, flip);
		//SDL_RenderPresent(Game::renderer);
	}
	//Gets image dimensions
	int getWidth() {
		return this->Width;
	}
	int getHeight() {
		return this->Height;
	}

	SDL_Texture* getTexture() {
		return this->Texture;
	}
};