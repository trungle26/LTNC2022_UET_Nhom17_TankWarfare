#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"


// tạo các nhân vật ở đây:
GameObject* player2 = NULL;
GameObject* player = NULL;
Map* map = NULL;

SDL_Renderer* Game::renderer = NULL;


Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	bool flags = false;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL initialized! \n";

		window = SDL_CreateWindow(title, x, y,width, height, flags);
		if (window) 
		{
			std::cout << "created window!\n";
		}
			
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer initialized!\n";
		}
		isRunning = true;

		player = new GameObject("assets/png/blue/char_blue_1.png",50,300);
		player2 = new GameObject("assets/png/red/char_red_1.png",  100, 300);
		map = new Map();
		
	}
	else {
		isRunning = false;
	}
}

enum {
	up,
	down,
	left,
	right

};
bool states1[4] = { false,false,false,false };
bool states2[4] = { false,false,false,false };

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_LEFT) states1[left] = true;
		if (event.key.keysym.sym == SDLK_RIGHT) states1[right] = true;
		if (event.key.keysym.sym == SDLK_UP) states1[up] = true;
		if (event.key.keysym.sym == SDLK_DOWN) states1[down] = true;
		if (event.key.keysym.sym == SDLK_a) states2[left] = true;
		if (event.key.keysym.sym == SDLK_d) states2[right] = true;
		if (event.key.keysym.sym == SDLK_w) states2[up] = true;
		if (event.key.keysym.sym == SDLK_s) states2[down] = true;
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_LEFT) states1[left] = false;
		if (event.key.keysym.sym == SDLK_RIGHT) states1[right] = false;
		if (event.key.keysym.sym == SDLK_UP) states1[up] = false;
		if (event.key.keysym.sym == SDLK_DOWN) states1[down] = false;
		if (event.key.keysym.sym == SDLK_a) states2[left] = false;
		if (event.key.keysym.sym == SDLK_d) states2[right] = false;
		if (event.key.keysym.sym == SDLK_w) states2[up] = false;
		if (event.key.keysym.sym == SDLK_s) states2[down] = false;
		break;
	}
		
	
}

void Game::update()
{
	if (states1[right]) player->UpdateX(2);
	if (states1[left]) player->UpdateX(-2);
	if (states1[up]) player->UpdateY(-2);
	if (states1[down]) player->UpdateY(2);
	if (states2[right]) player2->UpdateX(2);
	if (states2[left]) player2->UpdateX(-2);
	if (states2[up]) player2->UpdateY(-2);
	if (states2[down]) player2->UpdateY(2);

	player->Update();
	player2->Update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Render();
	player2->Render();
	// here we add things to render
	SDL_RenderPresent(renderer);
}

void Game::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game closed!\n";
}
