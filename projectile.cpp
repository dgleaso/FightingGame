#include "projectile.h"

#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>

Projectile::Projectile(int playerNum, AnimatedSprite throwSprite, sf::Texture* throwSheet){
	this->throwSprite = throwSprite;

	this->throwSprite.setPosition(300, 200);

	this->playerNum = playerNum;


	this->throwAnimation.setSpriteSheet(*throwSheet);
	this->throwAnimation.addFrame(sf::IntRect(0, 5, 20, 20));
	this->throwAnimation.addFrame(sf::IntRect(0, 25, 20, 20));
	this->throwAnimation.addFrame(sf::IntRect(0, 45, 20, 20));
	this->throwAnimation.addFrame(sf::IntRect(0, 65, 20, 20));

	this->currentAnimation = &throwAnimation;

}

Projectile::~Projectile(){

}

void Projectile::update(sf::Time frameTime){

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
