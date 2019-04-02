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

Game::Game(){

}

Game::~Game(){

}


int Game::Update(){

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
	//std::cout << "tes1t\n";

	//Creates the projectiles
	AnimatedSprite throwSprite(sf::seconds(0.08), true, false);
	Projectile throwOne(1, throwSprite, &throwTexture, 0);
	AnimatedSprite throwSpriteTwo(sf::seconds(0.08), true, false);
	Projectile throwTwo(0, throwSpriteTwo, &throwTexture, 0);
	//Creates the axes
	AnimatedSprite axeSprite(sf::seconds(0.2), true, false);
	Axe axeOne(1, axeSprite, &axeTexture, 1);
	AnimatedSprite axeSpriteTwo(sf::seconds(0.2), true, false);
	Axe axeTwo(2, axeSpriteTwo, &axeTexture, 2);

	//____________________________________________--

	
	//Creates Player Object
	AnimatedSprite playerOneSprite(sf::seconds(0.2), true, false);
	AnimatedSprite throwOneSprite(sf::seconds(0.2), true, false);
	sf::Vector2f startingPos(120, 100);
	playerOneSprite.setPosition(startingPos);
	Player playerOne(1, playerOneSprite, &sheetTexture);

	//Player 2
	AnimatedSprite playerTwoSprite(sf::seconds(0.2), true, false);
	AnimatedSprite throwTwoSprite(sf::seconds(0.2), true, false);
	sf::Vector2f startingPosT(440, 100);
	playerTwoSprite.setPosition(startingPosT);
	Player playerTwo(0, playerTwoSprite, &sheetTexture);



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

		bool oneThrow = false;
		bool twoThrow = false;

		bool oneAttack = false;
		bool twoAttack = false;

		bool projOneHit = false;
		bool projTwoHit = false;

		bool playerOneHit = false;
		bool playerTwoHit = false;

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			oneThrow = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			oneAttack = true;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
			twoThrow = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
			twoAttack = true;
		}



		/*
		//Shoot ball
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			shot.setPosition(xPlayer + 50.f, yPlayer);
			shot.setFillColor(sf::Color::Red);
			isShot = true;
		}
		*/ 
		//Projectile Colision (only checks if thrown)
		if(throwOne.getHasThrown() == 1){
			throwOneSprite	= throwOne.getSprite();
			float left = throwOneSprite.getPosition().x;
			float right = left + 20;
			float top = throwOneSprite.getPosition().y;
			float bot = top + 20;

			float pLeft = playerTwo.getSprite().getPosition().x;
			float pRight = pLeft + 33;
			float pTop = playerTwo.getSprite().getPosition().y;
			float pBot = pTop + 60;

			if(right > windowWidth or
			left < 0
			){
				projOneHit = true;
			}
			if(((top > pTop and top < pBot) or (bot < pBot and bot > pTop)) and
			((left > pLeft and left < pRight) or (right < pRight and right > pLeft))
			){
				projOneHit = true;
				playerOneHit = true;
			}
		}
		if(throwTwo.getHasThrown() == 1){
			throwTwoSprite	= throwTwo.getSprite();
			float left = throwTwoSprite.getPosition().x;
			float right = left + 20;
			float top = throwTwoSprite.getPosition().y;
			float bot = top + 20;

			float pLeft = playerOne.getSprite().getPosition().x;
			float pRight = pLeft + 33;
			float pTop = playerOne.getSprite().getPosition().y;
			float pBot = pTop + 60;

			if(right > windowWidth or
			left < 0
			){
				projTwoHit = true;
			}
			if(((top > pTop and top < pBot) or (bot < pBot and bot > pTop)) and
			((left > pLeft and left < pRight) or (right < pRight and right > pLeft))
			){
				projTwoHit = true;
				playerTwoHit = true;
			}
		}
		//END OF projectile colision
		//Axe (melee) colision
		if(axeOne.getHasAttacked() == 1){
			axeSprite = axeOne.getSprite();
			float left = axeSprite.getPosition().x;
			//Accounts for flipped axe sprite
			if(playerOne.getFacing() == 0){
				left = left - 35;	
			}
			float right = left + 20;
			float top = axeSprite.getPosition().y;
			float bot = top + 20;

			float pLeft = playerTwo.getSprite().getPosition().x;
			float pRight = pLeft + 33;
			float pTop = playerTwo.getSprite().getPosition().y;
			float pBot = pTop + 60;

			if(((top > pTop and top < pBot) or (bot < pBot and bot > pTop)) and
			((left > pLeft and left < pRight) or (right < pRight and right > pLeft))
			){
				std::cout << "test col\n";
			}
		}
		if(axeTwo.getHasAttacked() == 1){
			axeSpriteTwo = axeTwo.getSprite();
			float left = axeSpriteTwo.getPosition().x;
			//Accounts for flipped axe sprite
			if(playerTwo.getFacing() == 0){
				left = left - 35;	
			}
			float right = left + 20;
			float top = axeSpriteTwo.getPosition().y;
			float bot = top + 20;


			float pLeft = playerOne.getSprite().getPosition().x;
			float pRight = pLeft + 33;
			float pTop = playerOne.getSprite().getPosition().y;
			float pBot = pTop + 60;

			if(((top > pTop and top < pBot) or (bot < pBot and bot > pTop)) and
			((left > pLeft and left < pRight) or (right < pRight and right > pLeft))
			){
				std::cout << "test col 2\n";
			}
		}
		

		//END of axe colision

		playerOne.update(frameTime, oneMoveRight, oneMoveLeft, oneJump, 
		oneThrow, &throwOne,
		oneAttack, &axeOne,
		playerOneHit);
		playerTwo.update(frameTime, twoMoveRight, twoMoveLeft, twoJump,
		twoThrow, &throwTwo,
		twoAttack, &axeTwo,
		playerTwoHit);

		if(throwOne.getHasThrown() == 1){
			throwOne.update(frameTime, projOneHit);	
		}
		if(throwTwo.getHasThrown() == 1){
			throwTwo.update(frameTime, projTwoHit);	
		}

		if(axeOne.getHasAttacked() == 1){
			axeOne.update(frameTime);
		}
		if(axeTwo.getHasAttacked() == 1){
			axeTwo.update(frameTime);
		}


		//Makes background color white
		sf::Color c(255, 255, 255);
		window.clear(c);
		//window.clear();
		
		window.draw(playerOne.getSprite());
		window.draw(playerTwo.getSprite());
		if(throwOne.getHasThrown() == 1){
			window.draw(throwOne.getSprite());
		}
		if(throwTwo.getHasThrown() == 1){
			window.draw(throwTwo.getSprite());
		}
		if(axeOne.getHasAttacked() == 1){
			window.draw(axeOne.getSprite());
		}
		if(axeTwo.getHasAttacked() == 1){
			window.draw(axeTwo.getSprite());
		}



		window.draw(floor);
		window.display();
	}

	return 0;
}
