#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "collisionUnits.h"

class Game {
	public:
		static Game& instance() {
			static Game game;
			return game;
		}
		
		int Update();

	private:
	        Game();
		~Game();
		sf::Vector2f getRectPos(sf::RectangleShape rect);
		int getRectX(sf::RectangleShape rect);
		int getRectY(sf::RectangleShape rect);
		bool isGrounded(sf::RectangleShape player, sf::RectangleShape floor);
};

#define hGame Game::instance()
