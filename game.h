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
};

#define hGame Game::instance()
