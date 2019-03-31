#ifndef COLLISIONUNITS_H
#define COLLISIONUNITS_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <queue>


class CollisionUnits {
	private:
	        CollisionUnits();
		~CollisionUnits();
		int num;
		std::queue <sf::RectangleShape> floorQueue;
		float screenWidth;
	public:
		static CollisionUnits& instance() {
			static CollisionUnits collisionUnits;
			return collisionUnits;
		}

		void printNum();
		void setNum(int num);
		void setFloor(sf::RectangleShape floor);
		sf::RectangleShape getFloor();
		void setWidth(float screenWidth);
		float getWidth();

};
#define sCollisionUnits CollisionUnits::instance()
#endif
