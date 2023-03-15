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

SRC =	src/main.cpp \
		src/core/Core.cpp \
		src/core/Menu.cpp

SRC_LIB_GAMES = lib/games

SRC_LIB_GRAPHICALS = lib/graphicals

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SDL2_FLAGS :=

INCLUDE_PATH = -I./src/display -I./src/game -I./src/core
# OS detection
ifeq ($(shell uname -s),Linux)
	# Linux
	# SFML_FLAGS +=
	SDL2_FLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf
	INCLUDE_PATH += -fno-gnu-unique
endif
ifeq ($(shell uname -s),Darwin)
	# Mac OS X
	SFML_FLAGS += -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib
	# SDL2_FLAGS += -lSDL2
endif

NAME = arcade

.DEFAULT_GOAL := all

core:
	echo $(OSFLAG)
	g++ -o $(NAME) $(SRC) -std=c++20 -ldl -g3 $(INCLUDE_PATH)

sfml:
	g++ -shared -o lib/arcade_sfml.so -fPIC $(SRC_LIB_GRAPHICALS)/sfml/*.cpp -std=c++20 -g3 $(SFML_FLAGS) $(INCLUDE_PATH)

ncurses:
	g++ -shared -o lib/arcade_ncurses.so -fPIC $(SRC_LIB_GRAPHICALS)/ncurses/*.cpp -std=c++20 -g3 -lncurses $(INCLUDE_PATH)

sdl2:
	g++ -shared -o lib/arcade_sdl2.so -fPIC $(SRC_LIB_GRAPHICALS)/sdl2/*.cpp -std=c++20 -g3 $(SDL2_FLAGS) $(INCLUDE_PATH)

snake:
	g++ -shared -o lib/arcade_snake.so -fPIC $(SRC_LIB_GAMES)/snake/*.cpp -std=c++20 -g3 $(INCLUDE_PATH)

nibbler:
	g++ -shared -o lib/arcade_nibbler.so -fPIC $(SRC_LIB_GAMES)/nibbler/*.cpp -std=c++20 -g3 $(INCLUDE_PATH)

games: snake \
	nibbler

graphicals:	sfml ncurses sdl2

all: core \
	graphicals
#games \

clean:
	rm -f *~ \
	rm -f *.o

fclean: clean
	rm -f $(NAME) \
	rm -f lib/*.so
	# find . -type d -name "*.dSYM" -exec rm -Rf {} \;

re: fclean all

.PHONY: all $(NAME) clean fclean all re custom
