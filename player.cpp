#include "player.h"

#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>

bool facingRight = true;


//Constr/Destr
Player::Player(AnimatedSprite playerSprite, sf::Vector2f startPos, sf::Texture* sheetTexture){
	this->playerSprite = playerSprite;
	ySpeed = 0;
	xSpeed = 0;

	//ANIMATION TEXTURE STUFF
	this->walkLeft.setSpriteSheet(*sheetTexture);
	this->walkLeft.addFrame(sf::IntRect(60, 0, 35, 60));
	this->walkLeft.addFrame(sf::IntRect(92, 0, 37, 60));

	this->walkRight.setSpriteSheet(*sheetTexture);
	this->walkRight.addFrame(sf::IntRect(0, 62, 30, 120));
	this->walkRight.addFrame(sf::IntRect(30, 62, 60, 120));

	this->jumpRight.setSpriteSheet(*sheetTexture);
	this->jumpRight.addFrame(sf::IntRect(30, 0, 40, 60));

	this->jumpLeft.setSpriteSheet(*sheetTexture);
	this->jumpLeft.addFrame(sf::IntRect(0, 0, 30, 60));

	this->standLeft.setSpriteSheet(*sheetTexture);
	this->standLeft.addFrame(sf::IntRect(92, 0, 37, 60));

	this->standRight.setSpriteSheet(*sheetTexture);
	this->standRight.addFrame(sf::IntRect(30, 63, 35, 65));

}

Player::~Player(){

}

//Private

bool Player::isGrounded(){
	sf::RectangleShape floor = sCollisionUnits.getFloor();
	//Gets the vertical position of the player
	float yPlayer = this->playerSprite.getPosition().y;
	float yFloor = floor.getPosition().y;

	if(yPlayer >= yFloor - 60){
		return true;
	}else{
		return false;
	}
}

// Moves the player rectangle
void Player::movePlayer(float xSpeed, float ySpeed){
	float maxWidth = sCollisionUnits.getWidth();
	for(int i = 0; i < 5; i++){
		float x = playerSprite.getPosition().x;
		float y = playerSprite.getPosition().y;
		if(ySpeed > 0){
			if(!isGrounded()){
				this->playerSprite.move(0.f, ySpeed);	
			}
		
		}else{
			//Moves player up (if jumping)
			this->playerSprite.move(0.f, ySpeed);	
		}
		if(xSpeed > 0){
		//Moving right
			if(x < maxWidth){
				this->playerSprite.move(xSpeed, 0.f);	
			}
		}else{
		//Moving left
			if(x > 0){
				this->playerSprite.move(xSpeed, 0.f);	
			}
		}
	}	
}

//Public

//Updates position and this->currentAnimation based on state
void Player::update(sf::Time frameTime, bool moveRight, bool moveLeft, bool jump){
	bool inAir = false;
	//If on ground
	if(isGrounded()){
		//Handles jump
		if(jump){
			ySpeed = -6.0;
			//Used for selecting animation
			inAir = true;
		}
	}else{
		//In air
		//Gravity
		ySpeed += 0.5;
		//Used for selecting animation
		inAir = true;
	}
	//
	if(moveRight and !moveLeft){
		facingRight = true;
		xSpeed = 1.0; 	
		if(inAir){
			this->currentAnimation = &jumpRight;
		}else{
			this->currentAnimation = &walkRight;
		}
	}else if(moveLeft){
		facingRight = false;
		xSpeed = -1.0; 	
		if(inAir){
			this->currentAnimation = &jumpLeft;
		}else{
			this->currentAnimation = &walkLeft;
		}
	}else{
		xSpeed = 0;
		if(facingRight){
			if(inAir){
				this->currentAnimation = &jumpRight;
			}else{
				this->currentAnimation = &standRight;
			}
		}else{
			if(inAir){
				this->currentAnimation = &jumpLeft;
			}else{
				this->currentAnimation = &standLeft;
			}
		}
	}

	//Updates the animation frame
	(this->playerSprite).play(*currentAnimation);
	(this->playerSprite).update(frameTime);
	
	//Moves the player
	Player::movePlayer(xSpeed, ySpeed);
}

//Returns sprite  (to game for drawing)
AnimatedSprite Player::getSprite(){
	return this->playerSprite;	
}
