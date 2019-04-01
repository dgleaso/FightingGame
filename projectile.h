#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include "collisionUnits.h"

class Projectile {
	public:
		Projectile(AnimatedSprite throwSprite, sf::Texture* throwSheet);
		~Projectile();
		void update(sf::Time frameTime);
		void flip();
		AnimatedSprite getSprite();

	private:
		AnimatedSprite throwSprite;
		//Animations
		Animation throwAnimation;

		Animation* currentAnimation;
};
#endif
