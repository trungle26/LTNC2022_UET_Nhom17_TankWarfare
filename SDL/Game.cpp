#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Map.h"


// create characters here
Manager manager;
auto& player(manager.addEntity());
auto& player2(manager.addEntity());

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

		player.addComponent<TransformComponent>();
		player.addComponent<SpriteComponent>("assets/tank.png");
		player2.addComponent<TransformComponent>();
		player2.addComponent<SpriteComponent>("assets/tank2.png");
		//player = new GameObject("assets/tank.png",50,300);
		//player2 = new GameObject("assets/tank2.png",  360, 300);
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
	manager.refresh();
	manager.update();
	// di chuyen
	if (states1[right]) player.getComponent<TransformComponent>().rePhai();
	if (states1[left]) player.getComponent<TransformComponent>().reTrai();
	if (states1[up]) player.getComponent<TransformComponent>().diThang(2);
	if (states1[down]) player.getComponent<TransformComponent>().diThang(-2);
	if (states2[right]) player2.getComponent<TransformComponent>().rePhai();
	if (states2[left]) player2.getComponent<TransformComponent>().reTrai();
	if (states2[up]) player2.getComponent<TransformComponent>().diThang(2);
	if (states2[down]) player2.getComponent<TransformComponent>().diThang(-2);

	//neu co va cham
	/*
	SDL_bool collide = SDL_HasIntersection(&player->desRect, &player2->desRect);
	if (collide)
	{

		player->xpos+=2;
		player->ypos += 2;
		player2->xpos -= 2;
		player2->ypos -= 2;
	}
	*/
	
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	

	
	//player->Render();
	//player2->Render();
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