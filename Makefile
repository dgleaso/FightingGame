LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CC := g++


%.o: %.cpp
	$(CC) -c $< -o $@

%.o: %.h
	$(CC) -c $< -o $@

HammerMercenary: main.o game.o AnimatedSprite.o Animation.o player.o collisionUnits.o projectile.o axe.o
	$(CC) main.o game.o AnimatedSprite.o Animation.o player.o collisionUnits.o projectile.o axe.o -o HammerMercenary $(LIBS)
