#include "player.h"

#include "collisionUnits.h"
#include "projectile.h"
#include "axe.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>


//Constr/Destr
Player::Player(int playerNum, AnimatedSprite playerSprite,
sf::Texture* sheetTexture 
)
{
	this->playerSprite = playerSprite;
	this->playerNum = playerNum;


	
	if(playerNum == 1){
		sCollisionUnits.setPlayerOne(&this->playerSprite);
	}else{
		sCollisionUnits.setPlayerTwo(&this->playerSprite);
	}

	this->ySpeed = 0;
	this->xSpeed = 0;

	if(playerNum == 1){
		this->initFlip = 0;
		facingRight = 1;
	}else if (playerNum == 0){
		this->initFlip = 1;
		facingRight = 0;
	}

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
void Player::movePlayer(){
	float maxWidth = sCollisionUnits.getWidth();
	for(int i = 0; i < 5; i++){
		AnimatedSprite enemy = Player::getEnemy();

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
				if(playerRight < 1 + enemyLeft or playerLeft + 1 > enemyRight){
					this->playerSprite.move(0.f, ySpeed);	
				}else{
					if(playerBottom < enemyTop){
						this->playerSprite.move(0.f, ySpeed);	
					}else{
						
						//this->playerSprite.move(0.f, -45);	
						this->ySpeed = -3.0;
						Player::movePlayer();
					}
				}
			}
		}else{
			//Moves player up (if jumping)
			if(playerRight >= enemyLeft and playerRight <= enemyRight or
			(playerLeft <= enemyRight and playerLeft >= enemyLeft)){
				if(playerTop > enemyBottom and playerTop < enemyBottom + 10){
					//Moves player to side to get around collision
					float middle = sCollisionUnits.getWidth()/2;
					if(playerLeft < middle){
						this->playerSprite.move(25.f, 0.f);	
					}else{
						this->playerSprite.move(-25.f, 0.f);	
					}
				}else{
					this->playerSprite.move(0.f, ySpeed);	
				}
			}else{
				this->playerSprite.move(0.f, ySpeed);	
			}
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
void Player::update(sf::Time frameTime, bool moveRight, bool moveLeft, bool jump,
bool throwB, Projectile* hammer,
bool attackB, Axe* axe,
bool playerHit){
	bool inAir = false;
	if((*axe).getHasAttacked() == 0){
		//If on ground
		if(isGrounded()){
			//Handles jump
			if(jump){
				this->ySpeed = -6.0;
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
	
		//Throws projectile
		if(throwB){
			//std::cout << this->hasThrown << '\n';	
			if((*hammer).getHasThrown() == 0){
				Player::throwHammer(hammer);
				(*hammer).setHasThrown(1);
			}
		}
		//Attacks
		if(attackB){
			//std::cout << this->hasThrown << '\n';	
			if((*axe).getHasAttacked() == 0){
				Player::attack(axe);
				(*axe).setHasAttacked(1);
			}
		}
	
		//Updates the animation frame
		(this->playerSprite).play(*currentAnimation);
		(this->playerSprite).update(frameTime);
		
		//Moves the player
		Player::movePlayer();
	}
}

//Creates a projectile
void Player::throwHammer(Projectile* hammer){
	float playerLeft = playerSprite.getPosition().x;
	float playerRight = playerLeft + 33;
	float playerTop = playerSprite.getPosition().y;
	if(facingRight){
		(*hammer).setDirection(1);
		(*hammer).setPosition(playerRight, playerTop);
	}else{
		(*hammer).setDirection(2);
		(*hammer).setPosition(playerLeft, playerTop);
	}
}
//Creates an attack
void Player::attack(Axe* axe){
	float playerLeft = playerSprite.getPosition().x;
	float playerRight = playerLeft + 33;
	float playerTop = playerSprite.getPosition().y;
	if(this->initFlip == 1){
		this->initFlip = 0;	
		(*axe).flip();
	}
	if(facingRight){
		if((*axe).getDirection() == 2){
			(*axe).flip();
		}
		(*axe).setDirection(1);
		(*axe).setPosition(playerRight, playerTop);
	}else{
		if((*axe).getDirection() == 1){
			(*axe).flip();
		}
		(*axe).setDirection(2);
		(*axe).setPosition(playerLeft, playerTop);
	}
}

//Returns sprite  (to game for drawing)
AnimatedSprite Player::getSprite(){
	return this->playerSprite;	
}

AnimatedSprite Player::getEnemy(){
		if(this->playerNum == 0){
			return *(sCollisionUnits.getPlayerOne());
		}else{
			return *(sCollisionUnits.getPlayerTwo());
		}
}
int Player::getFacing(){
	return this->facingRight;
}
