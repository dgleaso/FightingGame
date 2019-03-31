#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include "collisionUnits.h"

class Player {
	public:
		Player(AnimatedSprite playerSprite, sf::Vector2f startPos, sf::Texture* sheetTexture);
		~Player();
		void update(sf::Time frameTime, bool moveRight, bool moveLeft, bool jump);
		Animation getCurrentAnimation();
		AnimatedSprite getSprite();
		//sf::Vector2f getCurrentPosition();

	private:
		AnimatedSprite playerSprite;
		//sf::Texture* playTexture;
		//std::queue <sf::Texture> textureQueue;
		sf::Vector2f getRectPos(sf::RectangleShape rect);
		float getRectX(sf::RectangleShape rect);
		float getRectY(sf::RectangleShape rect);
		bool isGrounded(sf::RectangleShape player);
		bool isGroundedNew();
		void movePlayer(float xSpeed, float ySpeed);
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
