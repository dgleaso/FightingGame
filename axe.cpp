#include "axe.h"

#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>

Axe::Axe(int playerNum, AnimatedSprite axeSprite, sf::Texture* axeSheet, 
int direction)
{
	this->axeSprite = axeSprite;

	this->axeSprite.setPosition(-300, -300);

	this->direction = direction;
	this->hasAttacked = 0;

	this->damageable = 0;


	this->axeAnimation.setSpriteSheet(*axeSheet);
	this->axeAnimation.addFrame(sf::IntRect(0, 3, 35, 35));
	this->axeAnimation.addFrame(sf::IntRect(0, 38, 35, 35));
	this->axeAnimation.addFrame(sf::IntRect(0, 73, 35, 35));


	this->temp.setSpriteSheet(*axeSheet);
	this->temp.addFrame(sf::IntRect(0, 3, 35, 35));


	this->currentAnimation = &axeAnimation;

}

Axe::~Axe(){

}

void Axe::update(sf::Time frameTime, bool hit){
	sf::Time finish = sf::seconds(0.5);
	if(animationClock.getElapsedTime() >= finish){
		this->damageable = 1;
		this->currentAnimation = &temp;
		this->hasAttacked = 0;
		Axe::setPosition(-300, -300);
	}

	(this->axeSprite).play(*currentAnimation);
	(this->axeSprite).update(frameTime);

}

//Returns sprite  (to game for drawing)
AnimatedSprite Axe::getSprite(){
	return this->axeSprite;	
}

void Axe::flip(){
	this->axeSprite.scale(-1.f, 1.f);
}
int Axe::getDirection(){
	return this->direction;
}
void Axe::setDirection(int direction){
	this->direction = direction;
}
void Axe::setPosition(float x, float y){
	this->axeSprite.setPosition(x, y);
}
int Axe::getHasAttacked(){
	return this->hasAttacked;
}
void Axe::setHasAttacked(int hA){
	if(hA == 1){
		animationClock.restart();	
		this->currentAnimation = &axeAnimation;
	}
	this->hasAttacked = hA;
}
int Axe::getDamageable(){
	return this->damageable;
}
void Axe::setDamageable(int d){
	this->damageable = d;
}
