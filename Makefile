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

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SDL2_FLAGS :=

# OS detection
ifeq ($(shell uname -s),Linux)
	# Linux
	# SFML_FLAGS +=
	SDL2_FLAGS += -lSDL2
endif
ifeq ($(shell uname -s),Darwin)
	# Mac OS X
	SFML_FLAGS += -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib
	# SDL2_FLAGS += -lSDL2
endif

NAME = arcade

.DEFAULT_GOAL := all

# -fno-gnu-unique

core:
	echo $(OSFLAG)
	g++ -o $(NAME) $(SRC) -std=c++11 -ldl -g3 -fno-gnu-unique 

sfml:
	g++ -shared -o lib/arcade_sfml.so  -fno-gnu-unique  -fPIC $(SRC_LIB_GRAPHICALS)/sfml/*.cpp -std=c++11 -g3 $(SFML_FLAGS)

ncurses:
	g++ -shared -o lib/arcade_ncurses.so  -fno-gnu-unique  -fPIC $(SRC_LIB_GRAPHICALS)/ncurses/*.cpp -std=c++11 -g3 -lncurses

sdl2:
	g++ -shared -o lib/arcade_sdl2.so  -fno-gnu-unique  -fPIC $(SRC_LIB_GRAPHICALS)/sdl2/*.cpp -std=c++11 -g3 $(SDL2_FLAGS)

snake:
	g++ -shared -o lib/arcade_snake.so  -fno-gnu-unique  -fPIC $(SRC_LIB_GAMES)/snake/*.cpp -std=c++11 -g3

nibbler:
	g++ -shared -o lib/arcade_nibbler.so -fno-gnu-unique   -fPIC $(SRC_LIB_GAMES)/nibbler/*.cpp -std=c++11 -g3

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
