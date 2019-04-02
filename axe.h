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

	private:
		AnimatedSprite axeSprite;
		//Animations
		Animation axeAnimation;

		Animation* currentAnimation;
};
#endif
