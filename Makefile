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

SRC = src/core/*.cpp \
	  src/game/*.cpp \
	  src/display/*.cpp \
	  src/main.cpp

SRC_LIB_GAMES = lib/game/*.cpp

SRC_LIB_GRAPHICALS = lib/graphicals/*.cpp

NAME = arcade

#  -ldl -fno-gnu-unique
all:
    g++ -shared -o $(LIB) -fPIC $(LIB_SRC) -std=c++11 -g3
    g++ -o $(NAME) $(SRC) -std=c++11 -ldl -fno-gnu-unique -g3

clean:
    rm -f libm.so
    rm -f pixel

fclean: clean
    rm -f $(NAME)

re: fclean all

core:
	g++ -c $(NAME) $(SRC)

games:
	g++ -c lib/game/*.cpp

graphicals:
	g++ -o $(NAME) $(SRC) -std=c++11 -ldl -fno-gnu-unique -g3


.PHONY: $(NAME) clean fclean all re custom
