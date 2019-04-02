#ifndef AXE_H
#define AXE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include "collisionUnits.h"

class Axe {
	public:
		Axe(int playerNum, AnimatedSprite axeSprite, sf::Texture* axeSheet,
		int direction);
		~Axe();
		void update(sf::Time frameTime);
		void flip();
		AnimatedSprite getSprite();

		void setDirection(int direction);
		void setPosition(float x, float y);
		int getHasAttacked();
		void setHasAttacked(int hA);

	private:
		int direction;
		int hasAttacked;
		AnimatedSprite axeSprite;
		//Animations
		Animation axeAnimation;

		Animation* currentAnimation;
};
#endif
