#include "collisionUnits.h"
#include<iostream>
#include <queue>

//Projectiles with queue 
//
//This is so that you can 
//loop through all (to check if collide)
//easily add (dynamic)


//Collide with
//sides
//floor
//projectile (enemy -> have projectile owner id- enum class)
//enemy attack

CollisionUnits::CollisionUnits(){
	this->num = 0;
	this->screenWidth = 0.0;
}


CollisionUnits::~CollisionUnits(){

}

void CollisionUnits::setFloor(sf::RectangleShape floor){
	floorQueue.push(floor);
}
sf::RectangleShape CollisionUnits::getFloor(){
	return floorQueue.front();
}

void CollisionUnits::setNum(int num){
	this->num = num;
}

void CollisionUnits::setWidth(float screenWidth){
	this->screenWidth = screenWidth;
}

float CollisionUnits::getWidth(){
	return this->screenWidth;
}

void CollisionUnits::printNum(){
	//std::cout << this->num;
	//std::cout << '\n';
}
