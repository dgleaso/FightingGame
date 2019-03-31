LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CC := g++


%.o: %.cpp
	$(CC) -c $< -o $@

%.o: %.h
	$(CC) -c $< -o $@

HammerMercenary: main.o game.o AnimatedSprite.o Animation.o player.o collisionUnits.o
	$(CC) main.o game.o AnimatedSprite.o Animation.o player.o collisionUnits.o -o HammerMercenary $(LIBS)
