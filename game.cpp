#include "game.h"
#include "player.h"
#include "collisionUnits.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"

#include<iostream>

//Dimensions of window
int windowHeight = 480;
int windowWidth = 640;




//DELETE ONCE IMPLEMENTED PROJECTILE
//Declares projectile and speed
//sf::CircleShape shot(5.f);
//float shotVelocity = 1.f;	

Game::Game(){

}

Game::~Game(){

}


int Game::Update(){

	float vSpeed = 0;
	//bool isShot = false;

	//Create window
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Hammer Mercenary!");
	sCollisionUnits.setWidth(windowWidth);


	//ANIMATION TEXTURE STUFF
	sf::Texture sheetTexture;
	if (!sheetTexture.loadFromFile("images/playerSheet.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}


	
	//Creates Player Object
	AnimatedSprite ps(sf::seconds(0.2), true, false);
	sf::Vector2f startingPos(100, 100);
	ps.setPosition(startingPos);
	Player player(ps, startingPos, &sheetTexture);



	//Create Floor (and adds to collision units)
	sf::RectangleShape floor(sf::Vector2f(windowWidth, 20));
	floor.setPosition(0.f, windowHeight - 20.f);
	floor.setFillColor(sf::Color::Black);

	sCollisionUnits.setFloor(floor);

	//Frame limit
	window.setFramerateLimit(30);

	//Frameclock to be used for animations (in player update)
	sf::Clock frameClock;

	while (window.isOpen()) {
		//To be used for player movement (in player update)
		bool moveRight = false;
		bool moveLeft = false;
		bool jump = false;

		sf::Time frameTime = frameClock.restart();

		//Keyboard input for closing
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		//Event polling for window close
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Moving right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			moveRight = true;
		}
		//Moving left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			moveLeft = true;
		}
		//Jumping
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			jump = true;
		}

		/*
		//Shoot ball
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			shot.setPosition(xPlayer + 50.f, yPlayer);
			shot.setFillColor(sf::Color::Red);
			isShot = true;
		}
		*/ 

		player.update(frameTime, moveRight, moveLeft, jump);


		//Makes background color white
		sf::Color c(255, 255, 255);
		window.clear(c);
		//window.clear();

		window.draw(player.getSprite());

		/*
		if(isShot){
			window.draw(shot);
		}
		*/
		window.draw(floor);
		window.display();
	}

	return 0;
}
