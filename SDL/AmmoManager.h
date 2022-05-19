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

	float x;
	float y;
	SDL_Rect tankRect1;
	int TANK_SIZE_WIDTH = 32;
	int TANK_SIZE_HEIGHT = 32;
	int PROJECTILE_SIZE_WIDTH = 32;
	int PROJECTILE_SIZE_HEIGHT = 32;
	int maxFrameUpdated = 250;
	SDL_Rect tankRect2;
	std::vector<Projectile> projectilesPlayer1;
	std::vector<Projectile> projectilesPlayer2;
	
	std::vector<double>projectilesAnglesPlayer1;
	std::vector<double>projectilesAnglesPlayer2;
	bool needToRerenderScoreBoard_ = true;
	bool renderTextStatusPlayer1 = false;
	bool renderTextStatusPlayer2 = false;
	AmmoManager();
	void addToSDLRect1(float x, float y);
	void addToSDLRect2(float x, float y);
	void addTankShootComponent(ShootComponent *tank1_, ShootComponent *tank2_);
	void checkBulletForPlayer1();
	void checkBulletForPlayer2();
	void getProjectilesVector1();
	void getProjectilesVector2();
	void addAngleOfProjectile(double angle, int player);
	void setSizeTank(int width, int height);
	void setMaxFrame(int parameter);
	//void setSizeTank2(int width, int height);
	void setSizeProjectiles(int width, int height);
	bool needToRerenderScoreBoard();
	bool needToRerenderTextStatusPlayer1();
	bool needToRerenderTextStatusPlayer2();
	//void getProjectilesVector2(std::vector<Projectile> projectiles);
	void tankShoot(Vector2D position, double angle, int player);
	
	~AmmoManager();
};

