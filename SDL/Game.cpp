#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Map.h"
#include "Collision.h"


// create 
Manager manager;
auto& player(manager.addEntity());
auto& player2(manager.addEntity());
Map* map ;

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;




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

		window = SDL_CreateWindow(title, x, y, width, height, flags);
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

		// ecs
		map = new Map("assets/terrain.png",1,32);// map scale:1, tile size: 32
		map->LoadMap("assets/map.map", 39, 23);

		player.addComponent<TransformComponent>(34,34);
		player.addComponent<SpriteComponent>("assets/tank.png");
		player.addComponent<CollisionComponent>("player1");
		player2.addComponent<TransformComponent>(1000,33);
		player2.addComponent<SpriteComponent>("assets/tank2.png");
		player2.addComponent<CollisionComponent>("player2");
		player.addGroup(groupPlayers);
		player2.addGroup(groupPlayers);
		
	}
	else {
		isRunning = false;
	}
}

auto& tiles(manager.getGroup(Game::groupMap));// pass in all the tiles into this 
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

//chuyen dong cua xe tang---------------------------------
enum {
	up,
	down,
	left,
	right

};
bool states1[] = { false, false , false, false };
bool states2[] = { false, false, false ,false };

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (Game::event.key.keysym.sym == SDLK_LEFT) states1[left] = true;
		if (Game::event.key.keysym.sym == SDLK_RIGHT) states1[right] = true;
		if (Game::event.key.keysym.sym == SDLK_UP) states1[up] = true;
		if (Game::event.key.keysym.sym == SDLK_DOWN) states1[down] = true;
		if (Game::event.key.keysym.sym == SDLK_a) states2[left] = true;
		if (Game::event.key.keysym.sym == SDLK_d) states2[right] = true;
		if (Game::event.key.keysym.sym == SDLK_w) states2[up] = true;
		if (Game::event.key.keysym.sym == SDLK_s) states2[down] = true;
		break;
	case SDL_KEYUP:
		if (Game::event.key.keysym.sym == SDLK_LEFT) states1[left] = false;
		if (Game::event.key.keysym.sym == SDLK_RIGHT) states1[right] = false;
		if (Game::event.key.keysym.sym == SDLK_UP) states1[up] = false;
		if (Game::event.key.keysym.sym == SDLK_DOWN) states1[down] = false;
		if (Game::event.key.keysym.sym == SDLK_a) states2[left] = false;
		if (Game::event.key.keysym.sym == SDLK_d) states2[right] = false;
		if (Game::event.key.keysym.sym == SDLK_w) states2[up] = false;
		if (Game::event.key.keysym.sym == SDLK_s) states2[down] = false;
		break;
	}

}
//---------------------------------------------------------

void Game::update()
{
	SDL_Rect playerCol = player.getComponent<CollisionComponent>().collider;
	SDL_Rect player2Col = player2.getComponent<CollisionComponent>().collider;

	manager.refresh();
	manager.update();
	// neu co va cham
	
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<CollisionComponent>().collider;
		if (Collision::AABB(playerCol, cCol))
		{
			player.getComponent<TransformComponent>().diThang(player.getComponent<TransformComponent>().speed * -2);
			/*int gocdo = fmod(player.getComponent<TransformComponent>().angle, 360);
			std::cout << "hit" << " " << gocdo << std::endl;
			if (((gocdo > 0) && (gocdo < 90)) || ((gocdo > 180) && (gocdo < 270)))
			{
				player.getComponent<TransformComponent>().angle -= 2;
			}
			if (((gocdo > 90) && (gocdo < 180)) || ((gocdo > 270) && (gocdo <= 359)))
			{
				player.getComponent<TransformComponent>().angle += 2;
			}
			if (((gocdo < 0) && (gocdo > -90)) || ((gocdo < -180) && (gocdo > -270)))
			{
				player.getComponent<TransformComponent>().angle += 2;
			}
			if (((gocdo < -90) && (gocdo > -180)) || ((gocdo < -270) && (gocdo >= -359)))
			{
				player.getComponent<TransformComponent>().angle -= 2;
			}*/
		}

		if (Collision::AABB(player2Col, cCol))
		{
			player2.getComponent<TransformComponent>().diThang(player.getComponent<TransformComponent>().speed * -2);
			/*int gocdo = fmod(player.getComponent<TransformComponent>().angle, 360);
			std::cout << "hit" << " " << gocdo << std::endl;
			if (((gocdo > 0) && (gocdo < 90)) || ((gocdo > 180) && (gocdo < 270)))
			{
				player2.getComponent<TransformComponent>().angle += 12;
			}
			if (((gocdo > 90) && (gocdo < 180)) || ((gocdo > 270) && (gocdo <= 359)))
			{
				player2.getComponent<TransformComponent>().angle -= 12;
			}
			if (((gocdo < 0) && (gocdo > -90)) || ((gocdo < -180) && (gocdo > -270)))
			{
				player2.getComponent<TransformComponent>().angle -= 12;
			}
			if (((gocdo < -90) && (gocdo > -180)) || ((gocdo < -270) && (gocdo >= -359)))
			{
				player2.getComponent<TransformComponent>().angle += 12;
			}*/
		}
	}
	
	// di chuyen
	if (states1[right]) player.getComponent<TransformComponent>().rePhai();
	if (states1[left]) player.getComponent<TransformComponent>().reTrai();
	if (states1[up])
	{
		player.getComponent<TransformComponent>().speed = 2.5;
		player.getComponent<TransformComponent>().diThang();
	}
	if (states1[down])
	{
		{
			player.getComponent<TransformComponent>().speed = -2.5;
			player.getComponent<TransformComponent>().diThang();
		}
	}
	if (states2[right]) player2.getComponent<TransformComponent>().rePhai();
	if (states2[left]) player2.getComponent<TransformComponent>().reTrai();
	if (states2[up])
	{
		{
			player2.getComponent<TransformComponent>().speed = 2;
			player2.getComponent<TransformComponent>().diThang();
		}
	}
	if (states2[down])
	{
		{
			player2.getComponent<TransformComponent>().speed = -2;
			player2.getComponent<TransformComponent>().diThang();
		}
	}

}


void Game::render()
{
	SDL_RenderClear(renderer);
	//map->DrawMap();
	manager.draw();
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	SDL_RenderPresent(renderer);

}

void Game::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game closed!\n";
}
