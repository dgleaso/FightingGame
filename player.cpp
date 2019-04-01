#include "player.h"

#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>


//Constr/Destr
Player::Player(int playerNum, AnimatedSprite playerSprite, sf::Vector2f startPos, sf::Texture* sheetTexture){
	this->playerSprite = playerSprite;
	this->playerNum = playerNum;

	
	if(playerNum == 1){
		sCollisionUnits.setPlayerOne(&this->playerSprite);
	}else{
		sCollisionUnits.setPlayerTwo(&this->playerSprite);
	}

	ySpeed = 0;
	xSpeed = 0;

	facingRight = playerNum;

	//ANIMATION TEXTURE STUFF
	this->walkLeft.setSpriteSheet(*sheetTexture);
	this->walkLeft.addFrame(sf::IntRect(60, 0, 33, 60));
	this->walkLeft.addFrame(sf::IntRect(92, 0, 33, 60));

	this->walkRight.setSpriteSheet(*sheetTexture);
	this->walkRight.addFrame(sf::IntRect(0, 62, 33, 60));
	this->walkRight.addFrame(sf::IntRect(30, 62, 33, 60));

	this->jumpRight.setSpriteSheet(*sheetTexture);
	this->jumpRight.addFrame(sf::IntRect(30, 0, 33, 60));

	this->jumpLeft.setSpriteSheet(*sheetTexture);
	this->jumpLeft.addFrame(sf::IntRect(0, 0, 33, 60));

	this->standLeft.setSpriteSheet(*sheetTexture);
	this->standLeft.addFrame(sf::IntRect(92, 0, 33, 60));

	this->standRight.setSpriteSheet(*sheetTexture);
	this->standRight.addFrame(sf::IntRect(30, 63, 33, 60));

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
		AnimatedSprite enemy;
		if(this->playerNum == 0){
			enemy = *(sCollisionUnits.getPlayerOne());
		}else{
			enemy = *(sCollisionUnits.getPlayerTwo());
		}

		//Player Hitbox
		float playerLeft = playerSprite.getPosition().x;
		float playerRight = playerLeft + 33;
		float playerTop = playerSprite.getPosition().y;
		float playerBottom = playerTop + 60;

		//Enemy Hitbox  (other player)

		float enemyLeft = enemy.getPosition().x;
		float enemyRight = enemyLeft + 33;
		float enemyTop = enemy.getPosition().y;
		float enemyBottom = enemyTop + 60;
		



		if(ySpeed > 0){
			if(!isGrounded()){
				if(playerRight < enemyLeft or playerLeft > enemyRight){
					this->playerSprite.move(0.f, ySpeed);	
				}else{
					if(playerBottom < enemyTop or playerTop > enemyBottom){
						this->playerSprite.move(0.f, ySpeed);	
					}else{
						
						this->playerSprite.move(0.f, -45);	
					}
				}
			}
		
		}else{
			//Moves player up (if jumping)
			this->playerSprite.move(0.f, ySpeed);	
		}
		if(xSpeed > 0){
			if(this->playerNum == 1){
				//std::cout << "opl" << oPLeft <<"\n";
			}
		//Moving right
			if(playerRight < maxWidth and 
			(playerRight < enemyLeft or 
			playerLeft >= enemyRight or
			playerTop > enemyBottom or
			playerBottom < enemyTop
			)
			){
				this->playerSprite.move(xSpeed, 0.f);	
			}
		}else{
		//Moving left
			if(playerLeft > 0 and
			(playerLeft > enemyRight or
			playerRight <= enemyLeft or
			playerTop > enemyBottom or
			playerBottom < enemyTop
			)
			){
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
		facingRight = 1;
		xSpeed = 1.0; 	
		if(inAir){
			this->currentAnimation = &jumpRight;
		}else{
			this->currentAnimation = &walkRight;
		}
	}else if(moveLeft){
		facingRight = 0;
		xSpeed = -1.0; 	
		if(inAir){
			this->currentAnimation = &jumpLeft;
		}else{
			this->currentAnimation = &walkLeft;
		}
	}else{
		xSpeed = 0;
		if(facingRight == 1){
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
