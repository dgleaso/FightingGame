#include "game.h"
#include "player.h"
#include "collisionUnits.h"
#include "projectile.h"
#include "axe.h"

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
	sf::Texture throwTexture;
	if (!throwTexture.loadFromFile("images/throwSheet.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}
	sf::Texture axeTexture;
	if (!axeTexture.loadFromFile("images/axeSheet.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}

	//Creates a projectile and an axe
	AnimatedSprite tSprite(sf::seconds(0.08), true, false);
	Projectile tProj(tSprite, &throwTexture);

	AnimatedSprite aSprite(sf::seconds(0.4), true, false);
	Axe axe(tSprite, &axeTexture);

	//tProj.flip();

	//done proj/axe

	
	//Creates Player Object
	AnimatedSprite ps(sf::seconds(0.2), true, false);
	sf::Vector2f startingPos(120, 100);
	ps.setPosition(startingPos);
	Player player(1, ps, startingPos, &sheetTexture);

	//Player 2
	AnimatedSprite pst(sf::seconds(0.2), true, false);
	sf::Vector2f startingPosT(440, 100);
	pst.setPosition(startingPosT);
	Player playerT(0,pst, startingPos, &sheetTexture);



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
		bool oneMoveRight = false;
		bool oneMoveLeft = false;
		bool oneJump = false;
		bool twoMoveRight = false;
		bool twoMoveLeft = false;
		bool twoJump = false;

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

		//Player One Controls
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			oneMoveRight = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			oneMoveLeft = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			oneJump = true;
		}
		//Player Two Controls
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			twoMoveRight= true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			twoMoveLeft = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			twoJump = true;
		}

		/*
		//Shoot ball
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			shot.setPosition(xPlayer + 50.f, yPlayer);
			shot.setFillColor(sf::Color::Red);
			isShot = true;
		}
		*/ 

		player.update(frameTime, oneMoveRight, oneMoveLeft, oneJump);
		playerT.update(frameTime, twoMoveRight, twoMoveLeft, twoJump);


		//Updates throw/axe
		tProj.update(frameTime);
		axe.update(frameTime);


		//Makes background color white
		sf::Color c(255, 255, 255);
		window.clear(c);
		//window.clear();
		//
		//std::cout << sCollisionUnits.getPlayerOne() << '\n';
		//std::cout << sCollisionUnits.getPlayerTwo() << '\n';

		window.draw(player.getSprite());
		window.draw(playerT.getSprite());

		//Draws throw/axe
		window.draw(tProj.getSprite());
		window.draw(axe.getSprite());

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
