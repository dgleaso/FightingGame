#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include "collisionUnits.h"
#include "projectile.h"
#include "axe.h"

class Player {
	public:
		Player(int playerNum, AnimatedSprite playerSprite, 
		sf::Texture* sheetTexture,
		sf::Texture* throwTexture);
		~Player();
		void update(sf::Time frameTime, bool moveRight, bool moveLeft, bool jump,
		bool throwB);
		AnimatedSprite getSprite();

	private:
		void createThrow();

		int hasThrown;

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
