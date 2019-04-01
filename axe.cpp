#include "axe.h"

#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>

Axe::Axe(AnimatedSprite axeSprite, sf::Texture* axeSheet){
	this->axeSprite = axeSprite;

	this->axeSprite.setPosition(400, 200);


	this->axeAnimation.setSpriteSheet(*axeSheet);
	this->axeAnimation.addFrame(sf::IntRect(0, 3, 35, 35));
	this->axeAnimation.addFrame(sf::IntRect(0, 38, 35, 35));
	this->axeAnimation.addFrame(sf::IntRect(0, 73, 35, 35));
	this->axeAnimation.addFrame(sf::IntRect(0, 108, 35, 35));

	this->currentAnimation = &axeAnimation;

}

Axe::~Axe(){

}

void Axe::update(sf::Time frameTime){

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
