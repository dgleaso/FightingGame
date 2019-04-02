#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include "collisionUnits.h"



class Projectile {
	public:
		Projectile(int playerNum, AnimatedSprite throwSprite,
		sf::Texture* throwSheet, int direction);
		~Projectile();
		void update(sf::Time frameTime, bool hit);
		void flip();
		AnimatedSprite getSprite();
		void setDirection(int direction);
		void setPosition(float x, float y);
		int getHasThrown();
		void setHasThrown(int hT);

	private:
		int direction;
		int hasThrown;
		AnimatedSprite throwSprite;
		//Animations
		Animation throwAnimation;

		Animation* currentAnimation;

		int playerNum;
};
#endif
