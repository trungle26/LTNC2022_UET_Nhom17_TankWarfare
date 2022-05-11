#pragma once
#include <iostream>
#include "Collision.h"
#include "TankStatusFunction.h"
#include <SDL.h>

class Projectile;
class ShootComponent;

class AmmoManager {
public:
	ShootComponent* tank1;
	ShootComponent* tank2;
	int TANK_WIDTH = 32;
	int TANK_HEIGHT = 32;
	float x;
	float y;
	SDL_Rect tankRect1;
	
	SDL_Rect tankRect2;
	std::vector<Projectile> projectilesPlayer1;
	std::vector<Projectile> projectilesPlayer2;
	
	std::vector<double>projectilesAnglesPlayer1;
	std::vector<double>projectilesAnglesPlayer2;
	bool needToRerenderScoreBoard_ = true;

	AmmoManager();
	void addToSDLRect1(float x, float y);
	void addToSDLRect2(float x, float y);
	void addTankShootComponent(ShootComponent *tank1_, ShootComponent *tank2_);
	void checkBulletForPlayer1();
	void checkBulletForPlayer2();
	void getProjectilesVector1();
	void addAngleOfProjectile(double angle, int player);
	void getTank1();
	void getTank2();
	void renderProjectiles();
	bool needToRerenderScoreBoard();
	//void getProjectilesVector2(std::vector<Projectile> projectiles);
	~AmmoManager();
};

