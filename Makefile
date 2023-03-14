##
##  ________  ________  ________  ________  ________  _______
## |\   __  \|\   __  \|\   ____\|\   __  \|\   ___ \|\  ___ \
## \ \  \|\  \ \  \|\  \ \  \___|\ \  \|\  \ \  \_|\ \ \   __/|
##  \ \   __  \ \   _  _\ \  \    \ \   __  \ \  \ \\ \ \  \_|/__
##   \ \  \ \  \ \  \\  \\ \  \____\ \  \ \  \ \  \_\\ \ \  \_|\ \
##    \ \__\ \__\ \__\\ _\\ \_______\ \__\ \__\ \_______\ \_______\
##     \|__|\|__|\|__|\|__|\|_______|\|__|\|__|\|_______|\|_______|
##
##

SRC =	src/main.cpp

SRC_LIB_GAMES = lib/games

SRC_LIB_GRAPHICALS = lib/graphicals

NAME = arcade

.DEFAULT_GOAL := all

core:
	g++ -o $(NAME) $(SRC) -std=c++11 -ldl -fno-gnu-unique -g3

sfml:
	g++ -shared -o lib/arcade_sfml.so -fPIC $(SRC_LIB_GRAPHICALS)/sfml/*.cpp -std=c++11 -g3 -lsfml-graphics -lsfml-window -lsfml-system

ncurses:
	g++ -shared -o lib/arcade_ncurses.so -fPIC $(SRC_LIB_GRAPHICALS)/ncurses/*.cpp -std=c++11 -g3 -lncurses

sdl2:
	g++ -shared -o lib/arcade_sdl2.so -fPIC $(SRC_LIB_GRAPHICALS)/sdl2/*.cpp -std=c++11 -g3 -lSDL2

snake:
	g++ -shared -o lib/arcade_snake.so -fPIC $(SRC_LIB_GAMES)/snake/*.cpp -std=c++11 -g3

nibbler:
	g++ -shared -o lib/arcade_nibbler.so -fPIC $(SRC_LIB_GAMES)/nibbler/*.cpp -std=c++11 -g3

games: snake \
	nibbler

graphicals:	sfml ncurses sdl2

all: core \
	games \
	graphicals

clean:
	rm -f *~ \
	rm -f *.o

fclean: clean
	rm -f $(NAME) \
	rm -f lib/*.so

re: fclean all

.PHONY: all $(NAME) clean fclean all re custom
