#pragma once
#include "AmmoManager.h"

AmmoManager::AmmoManager() {
	tank1 = new ShootComponent(10, 1, 3, 1);
	tank2 = new ShootComponent(10, 1, 3, 2);
}
void AmmoManager::addToSDLRect1(float x, float y) {
	tankRect1.x = (int)x;
	tankRect1.y = (int)y;
	tankRect1.w = 32;
	tankRect1.h = 32;
	//std::cout << "Successful addtoSDLRect1" << std::endl;
}
void AmmoManager::addToSDLRect2(float x, float y) {
	tankRect2.x = (int)x;
	tankRect2.y = (int)y;
	tankRect2.w = 32;
	tankRect2.h = 32;
	//std::cout << "Successful addtoSDLRect2" << std::endl;
}
void AmmoManager::addTankShootComponent(ShootComponent* tank1_, ShootComponent* tank2_) {
	
	std::cout << "Tank1 address: " << tank1 << std::endl;
	std::cout << "Tank2 address: " << tank2 << std::endl;
	tank1 = tank1_;
	tank2 = tank2_;
}
//PROJECTILE_INIT -> PROJECTILE_PUSH_BACK -> PROJECTILE_ADD_VECTOR -> CHECKBULLET
//IF POSSIBLE TRY TO USE STATIC VARIABLE (NOT NOW)
void AmmoManager::getProjectilesVector1() {
	this->projectilesPlayer1 = tank1->projectiles;
	
	
	std::cout << "Successful get Projectiles of tank 1" << std::endl;
}
void AmmoManager::getProjectilesVector2() {

	this->projectilesPlayer2 = tank2->projectiles;

	std::cout << "Successful get Projectiles of tank 2" << std::endl;
}
void AmmoManager::addAngleOfProjectile(double angle, int player) {
	if (player == 1) {
		projectilesAnglesPlayer1.push_back(angle);
	}
	else {
		projectilesAnglesPlayer2.push_back(angle);
	}
	needToRerenderScoreBoard_ = true;
//	std::cout << "Completely added angle. Current projectile angle of player 1: " <<projectilesAnglesPlayer1[projectilesAnglesPlayer1.size() - 1] << std::endl;

}

void AmmoManager::checkBulletForPlayer1() {
	//std::cout << "currently checking checkBulletForPlayer1" << std::endl;
	//std::cout << "Size of projectiles1: " << projectilesPlayer1.size() << std::endl;
	for (int i = 0; i < projectilesPlayer1.size(); i++) {
		//std::cout << "Time in for loop checkingbulletplayer1: " << i << std::endl;
		//it happens because we must storage the value of initial angle when tank starts shooting,
		//if we use current angle of this tank, bullet will change direction paralllel with tank
		//kind of fucking weird
		projectilesPlayer1[i].update(projectilesAnglesPlayer1[i]);
		SDL_Rect tempToCheck;
		tempToCheck.x = projectilesPlayer1[i].x;
		tempToCheck.y = projectilesPlayer1[i].y;
		tempToCheck.w = 32;
		tempToCheck.h = 32;

		//SDL_Texture* loadProjectiles = TextureManager::LoadTexture("assets/ammo.png");
		//TextureManager::Draw(loadProjectiles, tempToCheck, tempToCheck);


		//IMPORTANT: CHANGE W AND H RIGHT IF CHECKED FUNCTIONALLY.
		//BECAUSE I DON'T KNOW HOW TO MAKE BULLET :))))
		//IDEAL SIZE OF BULLET: 4X4 PIXEL
		if (Collision::AABB(tempToCheck, tankRect2)) { //if hit
			
			tank2->currentHealth -= tank1->damagePerShot;
			projectilesPlayer1.erase(projectilesPlayer1.begin() + i);
			projectilesAnglesPlayer1.erase(projectilesAnglesPlayer1.begin() + i);
			std::cout << "Projectile hit tank 2. Current tank 2 health: " << tank2->currentHealth << std::endl;
			std::cout << "Damage per shot of tank 1: " << tank1->damagePerShot << std::endl;
			needToRerenderScoreBoard_ = true;
			if (tank2->currentHealth <= 0) {
				std::cout << "tank 2 dead." << std::endl;
				//UI part goes here
			}
		}
		else if (projectilesPlayer1[i].frames >= 200) {
			projectilesPlayer1.erase(projectilesPlayer1.begin() + i);
			projectilesAnglesPlayer1.erase(projectilesAnglesPlayer1.begin() + i);
		}
		else {
			continue;
		}
	}
	//std::cout << "finished checking checkBulletForPlayer1" << std::endl;
	tank1->projectiles = projectilesPlayer1; //return back projectiles vector
	tank1->angles = projectilesAnglesPlayer1;
	//std::cout << "1 P: " << projectilesPlayer1.size() << " A: " << projectilesAnglesPlayer1.size() << std::endl;

}
void AmmoManager::checkBulletForPlayer2() {
	//std::cout << "currently checking checkBulletForPlayer2" << std::endl;
	for (int i = 0; i < projectilesPlayer2.size(); i++) {
		projectilesPlayer2[i].update(projectilesAnglesPlayer2[i]);
		SDL_Rect tempToCheck;
		tempToCheck.x = projectilesPlayer2[i].x;
		tempToCheck.y = projectilesPlayer2[i].y;
		tempToCheck.w = 32;
		tempToCheck.h = 32;

		
		//IMPORTANT: CHANGE W AND H RIGHT IF CHECKED FUNCTIONALLY.
		//BECAUSE I DON'T KNOW HOW TO MAKE BULLET :))))
		//IDEAL SIZE OF BULLET: 4X4 PIXEL
		if (Collision::AABB(tempToCheck, tankRect1)) { //if hit
			//needToRerenderScoreBoard_ = true;
			projectilesPlayer2.erase(projectilesPlayer2.begin() + i);
			projectilesAnglesPlayer2.erase(projectilesAnglesPlayer2.begin() + i);
			tank1->currentHealth -= tank2->damagePerShot;
			std::cout << "Projectile hit tank 1. Current tank 1 health: " << tank1->currentHealth << std::endl;
			std::cout << "Damage per shot of tank 2: " << tank2->damagePerShot << std::endl;
			needToRerenderScoreBoard_ = true;
			if (tank1->currentHealth <= 0) {
				std::cout << "tank 1 dead." << std::endl;
				//UI part goes here
			}
		}
		else if (projectilesPlayer2[i].frames >= 200) {
			projectilesPlayer2.erase(projectilesPlayer2.begin() + i);
			projectilesAnglesPlayer2.erase(projectilesAnglesPlayer2.begin() + i);
		}else {
			continue;
		}
	}
	//std::cout << "finished checking checkBulletForPlayer2" << std::endl;
	tank2->projectiles = projectilesPlayer2; //return back projectiles vector
	tank2->angles = projectilesAnglesPlayer2;
	//std::cout << "2 P: " << projectilesPlayer2.size() << " A: " << projectilesAnglesPlayer2.size() << std::endl;
}
//use 2 separate functions to avoid redundant reload times
bool AmmoManager::needToRerenderScoreBoard() {
	if (needToRerenderScoreBoard_) {
		needToRerenderScoreBoard_ = false;
		return !needToRerenderScoreBoard_;
	}
	else {
		return needToRerenderScoreBoard_;
	}
}
bool AmmoManager::needToRerenderTextStatusPlayer1() {

		return renderTextStatusPlayer1;
}
bool AmmoManager::needToRerenderTextStatusPlayer2() {

		return renderTextStatusPlayer2;
}

void AmmoManager::tankShoot(Vector2D position, double angle, int player) {
	if (player == 1) {	
		std::cout << "DirectionInstate4 created" << std::endl;
		tank1->addAmmoInformation(position);
		std::cout << "addAmmoIn4 finished" << std::endl;
		tank1->shoot();
		getProjectilesVector1();
		addAngleOfProjectile(angle,1);
	}
	else {
		std::cout << "DirectionInstate4 created" << std::endl;
		tank2->addAmmoInformation(position);
		std::cout << "addAmmoIn4 finished" << std::endl;
		tank2->shoot();
		getProjectilesVector2();
		addAngleOfProjectile(angle,2);
	}
}
