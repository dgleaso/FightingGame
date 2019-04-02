#include "projectile.h"

#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>

Projectile::Projectile(int playerNum, AnimatedSprite throwSprite, 
sf::Texture* throwSheet, int direction){
	this->throwSprite = throwSprite;

	this->throwSprite.setPosition(-100, -100);


	this->playerNum = playerNum;

	this->direction = direction;


	this->hasThrown = 0;


	this->throwAnimation.setSpriteSheet(*throwSheet);
	this->throwAnimation.addFrame(sf::IntRect(0, 5, 20, 20));
	this->throwAnimation.addFrame(sf::IntRect(0, 25, 20, 20));
	this->throwAnimation.addFrame(sf::IntRect(0, 45, 20, 20));
	this->throwAnimation.addFrame(sf::IntRect(0, 65, 20, 20));



	this->currentAnimation = &throwAnimation;

}

Projectile::~Projectile(){

}

void Projectile::update(sf::Time frameTime, bool hit){
	if(hit){
		this->direction == 0;
		this->hasThrown = 0;
		this->throwSprite.setPosition(-100, -100);
	}

	if(this->direction == 1){
		this->throwSprite.move(10.f, 0.f);
	}else if (this->direction == 2){
		this->throwSprite.move(-10.f, 0.f);
	}

	(this->throwSprite).play(*currentAnimation);
	(this->throwSprite).update(frameTime);

}

//Returns sprite  (to game for drawing)
AnimatedSprite Projectile::getSprite(){
	return this->throwSprite;	
}

void Projectile::flip(){
	this->throwSprite.scale(-1.f, 1.f);
}
void Projectile::setDirection(int direction){
	this->direction = direction;
}
void Projectile::setPosition(float x, float y){
	this->throwSprite.setPosition(x, y);
}
int Projectile::getHasThrown(){
	return this->hasThrown;
}
void Projectile::setHasThrown(int hT){
	this->hasThrown = hT;
}
