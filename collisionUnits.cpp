#include "collisionUnits.h"
#include<iostream>
#include <queue>
#include "AnimatedSprite.h"

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


void CollisionUnits::setWidth(float screenWidth){
	this->screenWidth = screenWidth;
}

float CollisionUnits::getWidth(){
	return this->screenWidth;
}
AnimatedSprite* CollisionUnits::getPlayerOne(){
	return this->playerOne;

}
AnimatedSprite* CollisionUnits::getPlayerTwo(){
	return this->playerTwo;
}
void CollisionUnits::setPlayerOne(AnimatedSprite* sprite){
	this->playerOne = sprite;
}
void CollisionUnits::setPlayerTwo(AnimatedSprite* sprite){
	this->playerTwo = sprite;
}
