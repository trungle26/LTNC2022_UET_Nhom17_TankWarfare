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
Map* map;


AmmoManager* ammoManager = new AmmoManager(); //testing
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
		map = new Map("assets/terrain.png", 1, 32);// map scale:1, tile size: 32
		map->LoadMap("assets/map.map", 39, 23);

		player.addComponent<TransformComponent>(34, 34);
		player.addComponent<SpriteComponent>("assets/tank.png");
		player.addComponent<CollisionComponent>("player1");
		player.addComponent<ShootComponent>(); //default option
		player2.addComponent<TransformComponent>(1000, 33);
		player2.addComponent<SpriteComponent>("assets/tank2.png");
		player2.addComponent<CollisionComponent>("player2");
		player2.addComponent<ShootComponent>(); //default option
		ShootComponent* test1 = &player.getComponent<ShootComponent>();
		ShootComponent* test2 = &player2.getComponent<ShootComponent>();
		std::cout << "Test1 address: " << test1 << std::endl;
		std::cout << "Test2 address: " << test2 << std::endl;
		ammoManager->addTankShootComponent(test1, test2);
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
bool states1[] = { false, false , false, false };//tank 1
bool states2[] = { false, false, false ,false };//tank 2
bool states3[] = { false,false,false,false };//shoot, reload, healing, allahMode for player of tank 2 
bool states4[] = { false, false, false, false };//tank 1
bool tank1Hit = false;
bool tank2Hit = false;
bool tank1Dead = false;
bool tank2Dead = false;

clock_t prevTimeForShootingPurpose = clock();
clock_t prevTimeShootingPlayer2 = clock();

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (Game::event.key.keysym.sym == SDLK_LEFT) states2[left] = true;
		if (Game::event.key.keysym.sym == SDLK_RIGHT) states2[right] = true;
		if (Game::event.key.keysym.sym == SDLK_UP) states2[up] = true;
		if (Game::event.key.keysym.sym == SDLK_DOWN) states2[down] = true;
		if (Game::event.key.keysym.sym == SDLK_a) states1[left] = true;
		if (Game::event.key.keysym.sym == SDLK_d) states1[right] = true;
		if (Game::event.key.keysym.sym == SDLK_w) states1[up] = true;
		if (Game::event.key.keysym.sym == SDLK_s) states1[down] = true;
		//for new shoot function
		//tank1 shoot function
		if (Game::event.key.keysym.sym == SDLK_SPACE) states4[0] = true;
		if (Game::event.key.keysym.sym == SDLK_r) states4[1] = true;
		if (Game::event.key.keysym.sym == SDLK_q) states4[2] = true;
		if (Game::event.key.keysym.sym == SDLK_TAB) states4[3] = true;
		//tank2 shoot function (missing)
		if (Game::event.key.keysym.sym == SDLK_KP_0) states3[0] = true;
		if (Game::event.key.keysym.sym == SDLK_KP_PERIOD) states3[1] = true;
		if (Game::event.key.keysym.sym == SDLK_KP_1) states3[2] = true;
		if (Game::event.key.keysym.sym == SDLK_KP_2) states3[3] = true;
		//NOT YET DONE: TWO TANK CHEAT CODES 


		break;
	case SDL_KEYUP:
		if (Game::event.key.keysym.sym == SDLK_LEFT) states2[left] = false;
		if (Game::event.key.keysym.sym == SDLK_RIGHT) states2[right] = false;
		if (Game::event.key.keysym.sym == SDLK_UP) states2[up] = false;
		if (Game::event.key.keysym.sym == SDLK_DOWN) states2[down] = false;
		if (Game::event.key.keysym.sym == SDLK_a) states1[left] = false;
		if (Game::event.key.keysym.sym == SDLK_d) states1[right] = false;
		if (Game::event.key.keysym.sym == SDLK_w) states1[up] = false;
		if (Game::event.key.keysym.sym == SDLK_s) states1[down] = false;
		//for new shoot function
		if (Game::event.key.keysym.sym == SDLK_SPACE) states4[0] = false;
		if (Game::event.key.keysym.sym == SDLK_r) states4[1] = false;
		if (Game::event.key.keysym.sym == SDLK_q) states4[2] = false;
		if (Game::event.key.keysym.sym == SDLK_TAB) states4[3] = false;
		// tank2 shoot function
		if (Game::event.key.keysym.sym == SDLK_KP_0) states3[0] = false;
		if (Game::event.key.keysym.sym == SDLK_KP_PERIOD) states3[1] = false;
		if (Game::event.key.keysym.sym == SDLK_KP_1) states3[2] = false;
		if (Game::event.key.keysym.sym == SDLK_KP_2) states3[3] = false;
		//NOT YET DONE: TWO TANK CHEAT CODES (FOR TESTING PURPOSES)


		break;
	}

}
//---------------------------------------------------------

void Game::update()
{
	clock_t currentTimeForShootingPurpose = clock();
	clock_t currentTimeShootingPlayer2 = clock();
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
			player.getComponent<TransformComponent>().diThang(player.getComponent<TransformComponent>().speed * -1);
			
		}

		if (Collision::AABB(player2Col, cCol))
		{
			player2.getComponent<TransformComponent>().diThang(player2.getComponent<TransformComponent>().speed * -1);
		}
		//CHECK COLLISION OF PROJECTILES WITH COLLIDER tank 1
		//remember: Allah mode allow projectile to bypass colliders
		if (!player.getComponent<ShootComponent>().allahMode) {
			for (int iter = 0; iter < ammoManager->projectilesPlayer1.size(); iter++) {
				SDL_Rect tempToCheck;
				tempToCheck.x = ammoManager->projectilesPlayer1[iter].x;
				tempToCheck.y = ammoManager->projectilesPlayer1[iter].y;
				tempToCheck.w = 32;
				tempToCheck.h = 32;
				if (Collision::AABB(tempToCheck, cCol)) {
					std::cout << "Detect collision with collider. Position: " << tempToCheck.x << " " << tempToCheck.y << std::endl;
					ammoManager->projectilesPlayer1.erase(ammoManager->projectilesPlayer1.begin() + iter);
					ammoManager->projectilesAnglesPlayer1.erase(ammoManager->projectilesAnglesPlayer1.begin() + iter);
				}
			}
		}
		
		// CHECK COLLISION OF PROJECTILES WITH COLLIDER tank 2
		//remember: Allah mode allow projectile to bypass colliders
		if (!player.getComponent<ShootComponent>().allahMode) {
			for (int iter = 0; iter < ammoManager->projectilesPlayer2.size(); iter++) {
				SDL_Rect tempToCheck;
				tempToCheck.x = ammoManager->projectilesPlayer2[iter].x;
				tempToCheck.y = ammoManager->projectilesPlayer2[iter].y;
				tempToCheck.w = 32;
				tempToCheck.h = 32;
				if (Collision::AABB(tempToCheck, cCol)) {
					std::cout << "Detect collision with collider. Position: " << tempToCheck.x << " " << tempToCheck.y << std::endl;
					ammoManager->projectilesPlayer2.erase(ammoManager->projectilesPlayer2.begin() + iter);
					ammoManager->projectilesAnglesPlayer2.erase(ammoManager->projectilesAnglesPlayer2.begin() + iter);
				}
			}
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
		
		player.getComponent<TransformComponent>().speed = -2.5;
		player.getComponent<TransformComponent>().diThang();
		
	}
	if (states2[right]) player2.getComponent<TransformComponent>().rePhai();
	if (states2[left]) player2.getComponent<TransformComponent>().reTrai();
	if (states2[up])
	{
		
		player2.getComponent<TransformComponent>().speed = 2;
		player2.getComponent<TransformComponent>().diThang();
		
	}
	if (states2[down])
	{
		
		player2.getComponent<TransformComponent>().speed = -2;
		player2.getComponent<TransformComponent>().diThang();
		
	}
	//bo sung: Neu tank di tran man hinh
	//tank1 tran man hinh
	if (player.getComponent<TransformComponent>().position.x < 0 ||
		player.getComponent<TransformComponent>().position.x > 1248 - player.getComponent<TransformComponent>().width*player.getComponent<TransformComponent>().scale ||
		player.getComponent<TransformComponent>().position.y > 736 - player.getComponent<TransformComponent>().height * player.getComponent<TransformComponent>().scale ||
		player.getComponent<TransformComponent>().position.y < 0
		) {

		player.getComponent<TransformComponent>().vaChamManHinh();

	}

	//tank 2 tran man hinh
	if (player2.getComponent<TransformComponent>().position.x < 0 ||
		player2.getComponent<TransformComponent>().position.x > 1248 - player2.getComponent<TransformComponent>().width * player2.getComponent<TransformComponent>().scale ||
		player2.getComponent<TransformComponent>().position.y > 736 - player2.getComponent<TransformComponent>().height * player2.getComponent<TransformComponent>().scale ||
		player2.getComponent<TransformComponent>().position.y < 0
		) {

		player2.getComponent<TransformComponent>().vaChamManHinh();

	}
	//-----------het bo sung khi tank di tran man hinh

	//---------------------------------------------------------------------------- va cham

	/*
	Tank1 shooting ok, other not yet
	Tank 2 not yet all functions
	*/
	
	
	//When shooting
	//tank 1 shooting
	if (states4[0]) {
		if (currentTimeForShootingPurpose - prevTimeForShootingPurpose >= player.getComponent<ShootComponent>().delayBetweenProjectiles){//HAVE TO MODIFIED
			Vector2D directionInState4;
			directionInState4.x = player.getComponent<TransformComponent>().position.x; //LEGACY
			directionInState4.y = player.getComponent<TransformComponent>().position.y; ///LEGACY
			//LEGACY BUT DOESN'T MEAN REMOVE IT.
			std::cout << "DirectionInstate4 created" << std::endl;

			player.getComponent<ShootComponent>().addAmmoInformation(player.getComponent<TransformComponent>().position);
			std::cout << "addAmmoIn4 finished" << std::endl;
			player.getComponent<ShootComponent>().shoot();

			ammoManager->getProjectilesVector1(); //ACTUALY BOTH PROJECTTILES
			ammoManager->addAngleOfProjectile(player.getComponent<TransformComponent>().angle, 1);
			ammoManager->addToSDLRect1(directionInState4.x, directionInState4.y);

			ammoManager->addToSDLRect2(player2.getComponent<TransformComponent>().position.x, player2.getComponent<TransformComponent>().position.y);


			//add ammo infor -> push_back angle and projectile -> 
			//transfer to ammo manager -> do sth elsE

			//SET TIME TO LIMIT SHOOT PER SECOND
			prevTimeForShootingPurpose = currentTimeForShootingPurpose;
		}
		

	}
	

	//When reloading
	if (states4[1]) {
		player.getComponent<ShootComponent>().reloading();
	//	std::cout << "Current bullet after reloading: " << player.getComponent<ShootComponent>().currentBullet << std::endl;
	}
	// When healing
	if (states4[2]) {
	//	std::cout << "Current health before healing: " << player.getComponent<ShootComponent>().currentHealth << std::endl;
		player.getComponent<ShootComponent>().healing();
	//	std::cout << "Current health after healing: " << player.getComponent<ShootComponent>().currentHealth << std::endl;
	}

	//When tank enable allahMode
	if (states4[3]) {
		player.getComponent<ShootComponent>().allahStyle();
	}

	// Tank2 functions goes here
	if (states3[0]) {
		if (currentTimeShootingPlayer2 - prevTimeShootingPlayer2 >= player2.getComponent<ShootComponent>().delayBetweenProjectiles) {
			Vector2D directionInState3;
			directionInState3.x = player2.getComponent<TransformComponent>().position.x; //LEGACY
			directionInState3.y = player2.getComponent<TransformComponent>().position.y; ///LEGACY
			//LEGACY BUT DOESN'T MEAN REMOVE IT.
			std::cout << "DirectionInstate3 created" << std::endl;

			player2.getComponent<ShootComponent>().addAmmoInformation(player2.getComponent<TransformComponent>().position);
			std::cout << "addAmmoIn4 finished" << std::endl;
			player2.getComponent<ShootComponent>().shoot();

			ammoManager->getProjectilesVector1(); //ACTUALY BOTH PROJECTTILES
			ammoManager->addAngleOfProjectile(player2.getComponent<TransformComponent>().angle, 2);
			ammoManager->addToSDLRect1(player.getComponent<TransformComponent>().position.x, player.getComponent<TransformComponent>().position.y);

			ammoManager->addToSDLRect2(player2.getComponent<TransformComponent>().position.x, player2.getComponent<TransformComponent>().position.y);


			//add ammo infor -> push_back angle and projectile -> 
			//transfer to ammo manager -> do sth elsE

			//SET TIME TO LIMIT SHOOT PER SECOND
			prevTimeShootingPlayer2 = currentTimeShootingPlayer2;
		}
	}
	if (states3[1]) {
	//	std::cout << "Current bullet before reloading: " << player2.getComponent<ShootComponent>().currentBullet << std::endl;
		player2.getComponent<ShootComponent>().reloading();
	//	std::cout << "Current bullet after reloading: " << player2.getComponent<ShootComponent>().currentBullet << std::endl;
	}
	if (states3[2]) {
		//std::cout << "Current health before healing: " << player2.getComponent<ShootComponent>().currentHealth << std::endl;
		player2.getComponent<ShootComponent>().healing();
	//	std::cout << "Current health after healing: " << player2.getComponent<ShootComponent>().currentHealth << std::endl;
	}
	if (states3[3]) {
		player2.getComponent<ShootComponent>().allahStyle();
	}
	//----------end added functions


	//THINGS HAVE TO CHECK EVERY FRAME
	//CHECK BULLET 
	ammoManager->checkBulletForPlayer1();
	ammoManager->checkBulletForPlayer2();
	//CHECK MINUSHEALTH OF PLAYER 1 IN ALLAH MODE
	if (player.getComponent<ShootComponent>().allahMode)player.getComponent<ShootComponent>().autoMinusHealthOfAllahStyle();
	//CHECK MINUSHEALTH OF PLAYER 2 IN ALLAH MODE
	if (player2.getComponent<ShootComponent>().allahMode)player2.getComponent<ShootComponent>().autoMinusHealthOfAllahStyle();

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
	//NOT YET DONE: render projectiles of player 1
	/*
	for (int i = 0; i < ammoManager->projectilesPlayer1.size(); i++) {
		SDL_Texture* loadProjectiles = TextureManager::LoadTexture("assets/ammo.png");
		SDL_Rect tempToRenderProjectile;
		tempToRenderProjectile.x = ammoManager->projectilesPlayer1[i].x;
		tempToRenderProjectile.y = ammoManager->projectilesPlayer2[i].y;
		tempToRenderProjectile.w = 32;
		tempToRenderProjectile.h = 32;
		TextureManager::Draw(loadProjectiles, tempToRenderProjectile, tempToRenderProjectile);
	}
	*/
	SDL_RenderPresent(renderer);

}

void Game::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game closed!\n";
}