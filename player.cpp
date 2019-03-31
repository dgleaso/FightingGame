#include "player.h"

#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>

//Needed new names??? !!!
bool qfacingRight = true;
bool qisMoving = false;
//sf::RectangleShape playerRect(sf::Vector2f(30, 60));
//AnimatedSprite playerSprite(sf::seconds(0.2), true, false);


float ySpeed = 0;
float xSpeed = 0;

//float xPos;
//float yPos;


//Constr/Destr
Player::Player(AnimatedSprite playerSprite, sf::Vector2f startPos, sf::Texture* sheetTexture){
	this->playerSprite = playerSprite;
	//playerRect.setPosition(startPos);
	//xPos = startPos.x;
	//yPos = startPos.y;
	//this->playerSprite.setPosition(startPos);

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
//
sf::Vector2f Player::getRectPos(sf::RectangleShape rect){
	sf::Vector2f rectP = rect.getPosition();
	return rectP;
}
float Player::getRectX(sf::RectangleShape rect){
	return Player::getRectPos(rect).x;
}
float Player::getRectY(sf::RectangleShape rect){
	return Player::getRectPos(rect).y;
}
bool Player::isGrounded(sf::RectangleShape player){
	sf::RectangleShape floor = sCollisionUnits.getFloor();
	//Gets the vertical position of the player
	float yPlayer = getRectY(player);
	float yFloor = getRectY(floor);

	if(yPlayer >= yFloor - 60){
		return true;
	}else{
		return false;
	}
}

bool Player::isGroundedNew(){
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
			if(!isGroundedNew()){
				//playerRect.move(0.f, ySpeed);	
				this->playerSprite.move(0.f, ySpeed);	
			}
		
		}else{
			//Moves player up (if jumping)
			//playerRect.move(0.f, ySpeed);	
			this->playerSprite.move(0.f, ySpeed);	
		}
		if(xSpeed > 0){
		//Moving right
			if(x < maxWidth){
				//playerRect.move(xSpeed, 0.f);	
				this->playerSprite.move(xSpeed, 0.f);	
			}
		}else{
		//Moving left
			if(x > 0){
				//playerRect.move(xSpeed, 0.f);	
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
	if(isGroundedNew()){
		//Handles jump
		if(jump){
			ySpeed = -6.0;
			//Need to move player now?  I dont think so
			
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
		qfacingRight = true;
		xSpeed = 1.0; 	
		if(inAir){
			this->currentAnimation = &jumpRight;
		}else{
			this->currentAnimation = &walkRight;
		}
	}else if(moveLeft){
		qfacingRight = false;
		xSpeed = -1.0; 	
		if(inAir){
			this->currentAnimation = &jumpLeft;
		}else{
			this->currentAnimation = &walkLeft;
		}
	}else{
		xSpeed = 0;
		if(qfacingRight){
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

	//std::cout << "Xspeed: " << xSpeed << " Yspeed: " << ySpeed << "\n";
	(this->playerSprite).play(*currentAnimation);
	(this->playerSprite).update(frameTime);
	
	Player::movePlayer(xSpeed, ySpeed);

	//sCollisionUnits.printNum();
}

//Returns the current Animation of the player
Animation Player::getCurrentAnimation(){
	return *this->currentAnimation;
}
AnimatedSprite Player::getSprite(){
	return this->playerSprite;	
}

//Returns the current position of the player
//sf::Vector2f Player::getCurrentPosition(){
//	sf::Vector2f v(xPos, yPos);	
//	return v;
//}
