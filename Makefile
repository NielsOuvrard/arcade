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
		src/core/Menu.cpp \
		src/game/AGameModule.cpp

SRC_LIB_GAMES = lib/games

SRC_LIB_GRAPHICALS = lib/graphicals

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SDL2_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

INCLUDE_PATH = -I./src/display -I./src/game -I./src/core -std=c++20 -g3
HOMEBREW = /opt/homebrew/Cellar/

ifeq ($(shell uname -s),Linux)
	# Linux
	INCLUDE_PATH += -fno-gnu-unique
endif
ifeq ($(shell uname -s),Darwin)
	# Mac OS X
	SFML_FLAGS += -I$(HOMEBREW)sfml/2.5.1_2/include -L$(HOMEBREW)sfml/2.5.1_2/lib
	SDL2_FLAGS += -I$(HOMEBREW)sdl2/2.26.4/include/SDL2
	SDL2_FLAGS += -I$(HOMEBREW)sdl2/2.26.4/include -L$(HOMEBREW)sdl2/2.26.4/lib
	SDL2_FLAGS += -I$(HOMEBREW)sdl2_image/2.6.3/include -L$(HOMEBREW)sdl2_image/2.6.3/lib
	SDL2_FLAGS += -I$(HOMEBREW)sdl2_ttf/2.20.2/include -L$(HOMEBREW)sdl2_ttf/2.20.2/lib -lSDL2_ttf
	SDL2_FLAGS += -I$(HOMEBREW)sdl2_mixer/2.6.3_1/include -L$(HOMEBREW)sdl2_mixer/2.6.3_1/lib -lSDL2_mixer
endif

NAME = arcade

.DEFAULT_GOAL := all

core:
	@ g++ -o $(NAME) $(SRC) -ldl $(INCLUDE_PATH)

sfml:
	@ g++ -shared -o lib/arcade_sfml.so -fPIC $(SRC_LIB_GRAPHICALS)/sfml/*.cpp $(SFML_FLAGS) $(INCLUDE_PATH)

ncurses:
	@ g++ -shared -o lib/arcade_ncurses.so -fPIC $(SRC_LIB_GRAPHICALS)/ncurses/*.cpp -lncurses $(INCLUDE_PATH)

sdl2:
	@ g++ -v -shared -o lib/arcade_sdl2.so -fPIC $(SRC_LIB_GRAPHICALS)/sdl2/*.cpp $(SDL2_FLAGS) $(INCLUDE_PATH)

snake:
	@ g++ -shared -o lib/arcade_snake.so -fPIC $(SRC_LIB_GAMES)/snake/*.cpp ./src/game/AGameModule.cpp $(INCLUDE_PATH)

nibbler:
	@ g++ -shared -o lib/arcade_nibbler.so -fPIC $(SRC_LIB_GAMES)/nibbler/*.cpp ./src/game/AGameModule.cpp $(INCLUDE_PATH)

pacman:
	@ g++ -shared -o lib/arcade_pacman.so -fPIC $(SRC_LIB_GAMES)/pacman/*.cpp ./src/game/AGameModule.cpp $(INCLUDE_PATH)

gameMenu:
	@ g++ -shared -o lib/arcade_game_menu.so -fPIC $(SRC_LIB_GAMES)/game_menu/*.cpp ./src/game/AGameModule.cpp $(INCLUDE_PATH)

gameOver:
	@ g++ -shared -o lib/arcade_game_over.so -fPIC $(SRC_LIB_GAMES)/game_over/*.cpp ./src/game/AGameModule.cpp $(INCLUDE_PATH)

games: snake nibbler gameMenu pacman gameOver

graphicals:	sfml ncurses sdl2

all: core games graphicals

clean:
	@ rm -f *~
	@ rm -f *.o

fclean: clean
	@ rm -f $(NAME)
	@ rm -f lib/*.so

mac_clean:
	@ find . -type d -name "*.dSYM" -exec rm -Rf {} \;
	@ find . -name "*.DS_Store" -exec rm -Rf {} \;

re: fclean all

.PHONY: all $(NAME) clean fclean all re custom
