#ifndef COLLISIONUNITS_H
#define COLLISIONUNITS_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <queue>

#include "AnimatedSprite.h"

class CollisionUnits {
	private:
	        CollisionUnits();
		~CollisionUnits();
		std::queue <sf::RectangleShape> floorQueue;
		float screenWidth;
		AnimatedSprite* playerOne;
		AnimatedSprite* playerTwo;
	public:
		static CollisionUnits& instance() {
			static CollisionUnits collisionUnits;
			return collisionUnits;
		}

		void setFloor(sf::RectangleShape floor);
		sf::RectangleShape getFloor();
		void setWidth(float screenWidth);
		float getWidth();
		AnimatedSprite* getPlayerOne();
		AnimatedSprite* getPlayerTwo();
		void setPlayerOne(AnimatedSprite* sprite);
		void setPlayerTwo(AnimatedSprite* sprite);

};
#define sCollisionUnits CollisionUnits::instance()
#endif
