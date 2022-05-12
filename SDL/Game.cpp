#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Map.h"
#include "Collision.h"
#include "RenderText.h"

// create 
Manager manager;
auto& player(manager.addEntity());
auto& player2(manager.addEntity());
Map* map;


AmmoManager* ammoManager = new AmmoManager(); //testing
SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;
LTexture* ltexture = new LTexture();

//for reloading and healing purposes
std::vector<int> player1Functions;
std::vector<int> player2Functions;
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
	if (TTF_Init() < 0) {
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
	}
	//things to reload and healing AND ALLAH MODE
	player1Functions.push_back(clock()); 
	player1Functions.push_back(clock());
	player2Functions.push_back(clock());
	player2Functions.push_back(clock());
	player2Functions.push_back(clock());
	player1Functions.push_back(clock());

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


clock_t prevTimeForShootingPurpose = clock();
clock_t prevTimeShootingPlayer2 = clock();


//for render scoreboard
bool needRerenderScoreBoard = false;

//for render text
TTF_Font* font = NULL;
SDL_Surface* text;
SDL_Surface* text2;
SDL_Texture* text_texture;
SDL_Texture* text_texture2;
//for lock keydown events
bool lockKeyDownPlayer1 = false;
bool lockKeyDownPlayer2 = false;
void Game::handleEvents()
{
	SDL_PollEvent(&event);


	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		//player 2
		if (!lockKeyDownPlayer2) {
			if (Game::event.key.keysym.sym == SDLK_LEFT) states2[left] = true;
			if (Game::event.key.keysym.sym == SDLK_RIGHT) states2[right] = true;
			if (Game::event.key.keysym.sym == SDLK_UP) states2[up] = true;
			if (Game::event.key.keysym.sym == SDLK_DOWN) states2[down] = true;
		}
		

		//player1
		if (!lockKeyDownPlayer1) {
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
		}
		
		if (!lockKeyDownPlayer2) {
			//tank2 shoot function 
			if (Game::event.key.keysym.sym == SDLK_KP_0) states3[0] = true;
			if (Game::event.key.keysym.sym == SDLK_KP_PERIOD) states3[1] = true;
			if (Game::event.key.keysym.sym == SDLK_KP_1) states3[2] = true;
			if (Game::event.key.keysym.sym == SDLK_KP_2) states3[3] = true;
			//NOT YET DONE: TWO TANK CHEAT CODES 
		}

		break;
	case SDL_KEYUP:
		
		if (!lockKeyDownPlayer1) {
			if (Game::event.key.keysym.sym == SDLK_a) states1[left] = false;
			if (Game::event.key.keysym.sym == SDLK_d) states1[right] = false;
			if (Game::event.key.keysym.sym == SDLK_w) states1[up] = false;
			if (Game::event.key.keysym.sym == SDLK_s) states1[down] = false;
			//for new shoot function
			if (Game::event.key.keysym.sym == SDLK_SPACE) states4[0] = false;
			if (Game::event.key.keysym.sym == SDLK_r) states4[1] = false;
			if (Game::event.key.keysym.sym == SDLK_q) states4[2] = false;
			if (Game::event.key.keysym.sym == SDLK_TAB) states4[3] = false;
		}
		if (!lockKeyDownPlayer2) {
			if (Game::event.key.keysym.sym == SDLK_LEFT) states2[left] = false;
			if (Game::event.key.keysym.sym == SDLK_RIGHT) states2[right] = false;
			if (Game::event.key.keysym.sym == SDLK_UP) states2[up] = false;
			if (Game::event.key.keysym.sym == SDLK_DOWN) states2[down] = false;
			// tank2 shoot function
			if (Game::event.key.keysym.sym == SDLK_KP_0) states3[0] = false;
			if (Game::event.key.keysym.sym == SDLK_KP_PERIOD) states3[1] = false;
			if (Game::event.key.keysym.sym == SDLK_KP_1) states3[2] = false;
			if (Game::event.key.keysym.sym == SDLK_KP_2) states3[3] = false;
			//NOT YET DONE: TWO TANK CHEAT CODES (FOR TESTING PURPOSES)
		}

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
		if (!player2.getComponent<ShootComponent>().allahMode) {
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
			//SET TIME TO LIMIT SHOOT PER SECOND
			prevTimeForShootingPurpose = currentTimeForShootingPurpose;
		}
	}
	//When reloading
	if (states4[1]) {
		if (!lockKeyDownPlayer1) {
			clock_t tempClock = clock();
			player1Functions[0] = tempClock;
		}
		lockKeyDownPlayer1 = true;
		clock_t compareClock = clock();
		states1[up] = false;
		states1[down] = false;
		states1[left] = false;
		states1[right] = false;
		//player.getComponent<TransformComponent>().dungDotNgot();
		if (compareClock - player1Functions[0] <= player.getComponent<ShootComponent>().delayTimeReload*1000) {
			//std::cout << "Please waiting! Time 1" <<clock()<<" Time 2 "<<player1Functions[0]<< std::endl;
			states4[1] = true;
		}
		else {
			player.getComponent<ShootComponent>().reloading();
			ammoManager->needToRerenderScoreBoard_ = true;
			lockKeyDownPlayer1 = false;
			states4[1] = false;
		}
		
	//	std::cout << "Current bullet after reloading: " << player.getComponent<ShootComponent>().currentBullet << std::endl;
	}
	// When healing
	if (states4[2]) {
		if (!lockKeyDownPlayer1) {
			clock_t tempClock = clock();
			player1Functions[1] = tempClock;
		}
		lockKeyDownPlayer1 = true;
		clock_t compareClock = clock();
		states1[up] = false;
		states1[down] = false;
		states1[left] = false;
		states1[right] = false;
		//player.getComponent<TransformComponent>().dungDotNgot();
		if (compareClock - player1Functions[1] <= player.getComponent<ShootComponent>().delayTimeReload * 1000) {
			//std::cout << "Please waiting! Time 1" <<clock()<<" Time 2 "<<player1Functions[0]<< std::endl;
			states4[2] = true;
		}
		else {
			player.getComponent<ShootComponent>().healing();
			ammoManager->needToRerenderScoreBoard_ = true;
			lockKeyDownPlayer1 = false;
			states4[2] = false;
		}
	//	std::cout << "Current health after healing: " << player.getComponent<ShootComponent>().currentHealth << std::endl;
	}

	//When tank enable allahMode
	if (states4[3]) {
		player.getComponent<ShootComponent>().allahStyle();
		ammoManager->needToRerenderScoreBoard_ = true;
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
		if (!lockKeyDownPlayer2) {
			clock_t tempClock = clock();
			player2Functions[0] = tempClock;
		}
		lockKeyDownPlayer2 = true;
		clock_t compareClock = clock();
		states2[up] = false;
		states2[down] = false;
		states2[left] = false;
		states2[right] = false;
		//player.getComponent<TransformComponent>().dungDotNgot();
		if (compareClock - player2Functions[0] <= player2.getComponent<ShootComponent>().delayTimeReload * 1000) {
			//std::cout << "Please waiting! Time 1" <<clock()<<" Time 2 "<<player1Functions[0]<< std::endl;
			states3[1] = true;
		}
		else {
			player2.getComponent<ShootComponent>().reloading();
			ammoManager->needToRerenderScoreBoard_ = true;
			lockKeyDownPlayer2 = false;
			states3[1] = false;
		}
	//	std::cout << "Current bullet after reloading: " << player2.getComponent<ShootComponent>().currentBullet << std::endl;
	}
	if (states3[2]) {
		if (!lockKeyDownPlayer2) {
			clock_t tempClock = clock();
			player2Functions[1] = tempClock;
		}
		lockKeyDownPlayer2 = true;
		clock_t compareClock = clock();
		states2[up] = false;
		states2[down] = false;
		states2[left] = false;
		states2[right] = false;
		//player.getComponent<TransformComponent>().dungDotNgot();
		if (compareClock - player2Functions[1] <= player2.getComponent<ShootComponent>().delayTimeReload * 1000) {
			//std::cout << "Please waiting! Time 1" <<clock()<<" Time 2 "<<player1Functions[0]<< std::endl;
			states3[2] = true;
		}
		else {
			player2.getComponent<ShootComponent>().healing();
			ammoManager->needToRerenderScoreBoard_ = true;
			lockKeyDownPlayer2 = false;
			states3[2] = false;
		}
	//	std::cout << "Current health after healing: " << player2.getComponent<ShootComponent>().currentHealth << std::endl;
	}
	if (states3[3]) {
		player2.getComponent<ShootComponent>().allahStyle();
		ammoManager->needToRerenderScoreBoard_ = true;
	}
	//----------end added functions


	//THINGS HAVE TO CHECK EVERY FRAME
	//CHECK BULLET 
	ammoManager->checkBulletForPlayer1();
	ammoManager->checkBulletForPlayer2();
	//CHECK MINUSHEALTH OF PLAYER 1 IN ALLAH MODE
	if (player.getComponent<ShootComponent>().allahMode) {
		player.getComponent<ShootComponent>().autoMinusHealthOfAllahStyle();
		ammoManager->needToRerenderScoreBoard_ = true;
	}
		
		
	//CHECK MINUSHEALTH OF PLAYER 2 IN ALLAH MODE
	if (player2.getComponent<ShootComponent>().allahMode) {
		player2.getComponent<ShootComponent>().autoMinusHealthOfAllahStyle();
		ammoManager->needToRerenderScoreBoard_ = true;
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
	
	//Render projectiles player1
	for (int i = 0; i < ammoManager->projectilesPlayer1.size(); i++) {
		SDL_Texture* loadProjectiles = TextureManager::LoadTexture("assets/ammo.png");
		std::cout << "Get load texture" << std::endl;
		SDL_Rect tempToRenderProjectile;
		tempToRenderProjectile.x = ammoManager->projectilesPlayer1[i].x;
		tempToRenderProjectile.y = ammoManager->projectilesPlayer1[i].y;
		std::cout << "Get SDL_REct x and y" << std::endl;
		tempToRenderProjectile.w = 32; //Projectiles size
		tempToRenderProjectile.h = 32; //Projectiles size
		SDL_Rect sourceRect;
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = sourceRect.h = 32;
		TextureManager::Draw(loadProjectiles, sourceRect, tempToRenderProjectile);
	}
	//Render projectiles player2
	for (int i = 0; i < ammoManager->projectilesPlayer2.size(); i++) {
		SDL_Texture* loadProjectiles = TextureManager::LoadTexture("assets/ammo.png");
		std::cout << "Get load texture" << std::endl;
		SDL_Rect tempToRenderProjectile;
		tempToRenderProjectile.x = ammoManager->projectilesPlayer2[i].x;
		tempToRenderProjectile.y = ammoManager->projectilesPlayer2[i].y;
		std::cout << "Get SDL_REct x and y" << std::endl;
		tempToRenderProjectile.w = 128; //Projectiles size
		tempToRenderProjectile.h = 32; //Projectiles size
		SDL_Rect sourceRect;
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = 128;
			sourceRect.h = 32;
		TextureManager::Draw(loadProjectiles, sourceRect, tempToRenderProjectile);
	}
	//SCOREBOARD
	//ltexture->renderScoreBoardPlayer1(renderer, player.getComponent<ShootComponent>().currentBullet, player.getComponent<ShootComponent>().currentHealth);
	//ltexture->renderScoreBoardPlayer2(renderer, player2.getComponent<ShootComponent>().currentBullet, player2.getComponent<ShootComponent>().currentHealth);

		
	if (ammoManager->needToRerenderScoreBoard()) {
		SDL_DestroyTexture(text_texture);
		SDL_FreeSurface(text);
		std::string scoreBoard = "Player1: Bullet: " + std::to_string(player.getComponent<ShootComponent>().currentBullet)
			+ " Health: " + std::to_string(player.getComponent<ShootComponent>().currentHealth);
		std::string scoreBoardPlayer2 = " Player2: Bullet: "
			+ std::to_string(player2.getComponent<ShootComponent>().currentBullet) + " Health: "
			+ std::to_string(player2.getComponent<ShootComponent>().currentHealth);
		font = TTF_OpenFont("assets/OpenSans-ExtraBold.ttf", 24);
		if (!font)std::cout << "Can't load font" << std::endl;
		SDL_Color color = { 255,255,255 }; //white color
		text = TTF_RenderText_Solid(font, scoreBoard.c_str(), color);
		if (!text)std::cout << "Can't load text" << std::endl;
		text_texture = SDL_CreateTextureFromSurface(renderer, text);
		SDL_Rect textDest = { 0,0,text->w,text->h };
		SDL_RenderCopy(renderer, text_texture, NULL, &textDest);
		//player2 part
		text2 = TTF_RenderText_Solid(font, scoreBoardPlayer2.c_str(), color);
		text_texture2 = SDL_CreateTextureFromSurface(renderer, text2);
		textDest = { 1248 / 2 ,0,text2->w,text2->h };
		SDL_RenderCopy(renderer, text_texture2, NULL, &textDest);
		//------------end testing
	}
	else {
		SDL_Rect textDest = { 0,0,text->w,text->h };
		SDL_RenderCopy(renderer, text_texture, NULL, &textDest);
		textDest = { 1248/2,0,text2->w,text2->h };
		SDL_RenderCopy(renderer, text_texture2, NULL, &textDest);
	}
	
		
	
	
	SDL_RenderPresent(renderer);


	//SDL_DestroyTexture(text_texture);
	
	
}

void Game::close()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	SDL_Quit();
	std::cout << "game closed!\n";
}