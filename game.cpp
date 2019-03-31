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



bool facingRight = true;

//Declares projectile and speed
sf::CircleShape shot(5.f);
float shotVelocity = 1.f;	

Game::Game(){

}

Game::~Game(){

}

//Gets the position of the player
sf::Vector2f Game::getRectPos(sf::RectangleShape rect){
	sf::Vector2f rectP = rect.getPosition();
	return rectP;

}
int Game::getRectX(sf::RectangleShape rect){
	return Game::getRectPos(rect).x;
}
int Game::getRectY(sf::RectangleShape rect){
	return Game::getRectPos(rect).y;
}

//Checks if the character is on the ground
bool Game::isGrounded(sf::RectangleShape player, sf::RectangleShape floor){
	//Gets the vertical position of the player
	float yPlayer = getRectY(player);
	float yFloor = getRectY(floor);

	if(yPlayer >= yFloor - 60){
		return true;
	}else{
		return false;
	}
}



int Game::Update(){

	float vSpeed = 0;
	//bool isShot = false;
	bool isMoving = false;

	//Create window
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Hammer Mercenary!");
	sCollisionUnits.setWidth(windowWidth);


	//ANIMATION TEXTURE STUFF
	sf::Texture sheetTexture;
	if (!sheetTexture.loadFromFile("images/playerSheet.png")) {
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}

	//ANIMATIONS _______________________-
	Animation walkLeft;
	walkLeft.setSpriteSheet(sheetTexture);
	walkLeft.addFrame(sf::IntRect(60, 0, 35, 60));
	walkLeft.addFrame(sf::IntRect(90, 0, 35, 60));

	Animation walkRight;
	walkRight.setSpriteSheet(sheetTexture);
	walkRight.addFrame(sf::IntRect(0, 62, 30, 120));
	walkRight.addFrame(sf::IntRect(30, 62, 60, 120));

	Animation jumpRight;
	jumpRight.setSpriteSheet(sheetTexture);
	jumpRight.addFrame(sf::IntRect(30, 0, 40, 60));

	Animation jumpLeft;
	jumpLeft.setSpriteSheet(sheetTexture);
	jumpLeft.addFrame(sf::IntRect(0, 0, 30, 60));

	Animation standLeft;
	standLeft.setSpriteSheet(sheetTexture);
	standLeft.addFrame(sf::IntRect(90, 0, 35, 60));

	Animation standRight;
	standRight.setSpriteSheet(sheetTexture);
	standRight.addFrame(sf::IntRect(30, 63, 35, 65));



	Animation* currentAnimation = &walkLeft;

	//ANIMATIONS _______________________-
	
	//Creates Player Object
	
	AnimatedSprite ps(sf::seconds(0.2), true, false);
	sf::Vector2f startingPos(100, 100);
	ps.setPosition(startingPos);
	Player player(ps, startingPos, &sheetTexture);

	//std::cout << player.getCurrentPosition().x;



	// set up AnimatedSprite
	sf::RectangleShape playerRect(sf::Vector2f(30, 60));
	playerRect.setPosition(sf::Vector2f(300, 300));
	AnimatedSprite playerSprite(sf::seconds(0.2), true, false);
	playerSprite.setPosition(sf::Vector2f(300, 300));

	AnimatedSprite pSTwo(sf::seconds(0.2), true, false);
	
	//ANIMATION TEXTURE STUFF
	
	sCollisionUnits.setNum(3);
	sCollisionUnits.printNum();


	//Create Objects
	sf::RectangleShape floor(sf::Vector2f(windowWidth, 20));
	floor.setPosition(0.f, windowHeight - 20.f);
	floor.setFillColor(sf::Color::Black);

	sCollisionUnits.setFloor(floor);

	//Frame limit
	window.setFramerateLimit(30);
	sf::Clock frameClock;

	while (window.isOpen()) {
		bool moveRight = false;
		bool moveLeft = false;
		bool jump = false;

		sf::Time frameTime = frameClock.restart();

		isMoving = false;

		//Player Position
		int xPlayer = getRectX(playerRect);
		int yPlayer = getRectY(playerRect);


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
			isMoving = true;
			facingRight = true;
			currentAnimation = &walkRight;
			for(int i = 0; i < 5; i++){
				xPlayer = getRectX(playerRect);
				if(xPlayer < windowWidth - 30){
					playerSprite.move(1.f, 0.f);
					playerRect.move(1.f, 0.f);
				}
			}
		}
		//Moving left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			moveLeft = true;
			isMoving = true;
			facingRight = false;
			currentAnimation = &walkLeft;
			for(int i = 0; i < 5; i++){
			xPlayer = getRectX(playerRect);
				if(xPlayer > 1.f){
					playerRect.move(-1.f, 0.f);
					playerSprite.move(-1.f, 0.f);
				}
			}
		}
		//Jumping
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			jump = true;
			if(isGrounded(playerRect, floor)){
				vSpeed = -6.0;
				playerSprite.move(0.f, vSpeed);
				playerRect.move(0.f, vSpeed);
			}
		}

		/*
		//Shoot ball
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			shot.setPosition(xPlayer + 50.f, yPlayer);
			shot.setFillColor(sf::Color::Red);
			isShot = true;
		}
		*/ 
		//Gravity
		if(!isGrounded(playerRect, floor)){
			vSpeed += 0.5;
			if(facingRight){
				currentAnimation = &jumpRight;	
			}else{
				currentAnimation = &jumpLeft;	
			}
			for(int i = 0; i < 5; i++){
				if(!isGrounded(playerRect, floor)){
					playerSprite.move(0.f, vSpeed);
					playerRect.move(0.f, vSpeed);
				}
			}
		}else{
			if(!isMoving){
				if(facingRight){
					currentAnimation = &standRight;	
				}else{
					currentAnimation = &standLeft;	
				}
			}
		
		}

		/*
		if(isShot){
			for(int i = 0; i < 15; i++){
				float shotX = shot.getPosition().x;
				if(shotX >= windowWidth){
					shotVelocity = -1.f;
				}
				if(shotX <= 0){
					shotVelocity = 1.f;
				}
				shot.move(shotVelocity, 0.f);
			}
		}
		*/

		player.update(frameTime, moveRight, moveLeft, jump);

		pSTwo = player.getSprite();
	
		//std::cout << pSTwo.getPosition().y << '\n';

		//pSTwo.play(player.getCurrentAnimation());
		//pSTwo.play(*currentAnimation);

		//Has something to do with frametime   -fix this and u gucci
		//put it all in player.cpp
		//pSTwo.update(frameTime);

		//std::cout << (player.getCurrentAnimation()).getSize();


		//Plays the current animation
		//playerSprite.play(*currentAnimation);

		// update AnimatedSprite
		//playerSprite.update(frameTime);

		//Test prints
		//std::cout << isGrounded(player);

		//Makes background color white
		sf::Color c(255, 255, 255);
		window.clear(c);
		//window.clear();

		//window.draw(pSTwo);
		window.draw(player.getSprite());
		//window.draw(playerSprite);
		//std::cout << pSTwo.getPosition().x;

		//std::cout << "\n";
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
