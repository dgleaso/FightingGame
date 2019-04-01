#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include "collisionUnits.h"

class Player {
	public:
		Player(int playerNum, AnimatedSprite playerSprite, sf::Vector2f startPos, sf::Texture* sheetTexture);
		~Player();
		void update(sf::Time frameTime, bool moveRight, bool moveLeft, bool jump);
		AnimatedSprite getSprite();

	private:
		AnimatedSprite playerSprite;
		AnimatedSprite getEnemy();
		int playerNum;
		int facingRight;
		bool isGrounded();
		float xSpeed;
		float ySpeed;
		void movePlayer();
		//Animations
		Animation walkLeft;
		Animation walkRight;
		Animation jumpRight;
		Animation jumpLeft;
		Animation standLeft;
		Animation standRight;

		Animation* currentAnimation;
};
#endif
