#ifndef AXE_H
#define AXE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include "collisionUnits.h"

class Axe {
	public:
		Axe(int playerNum, AnimatedSprite axeSprite, sf::Texture* axeSheet,
		int direction);
		~Axe();
		void update(sf::Time frameTime, bool hit);
		void flip();
		AnimatedSprite getSprite();

		int damageable;

		int getDamageable();
		void setDamageable(int d);

		void setDirection(int direction);
		int getDirection();
		void setPosition(float x, float y);
		int getHasAttacked();
		void setHasAttacked(int hA);

	private:
		sf::Clock animationClock;
		sf::Time* timePoint;
		int direction;
		int hasAttacked;
		AnimatedSprite axeSprite;

		//Animations
		Animation axeAnimation;
		Animation temp;

		Animation* currentAnimation;
};
#endif
