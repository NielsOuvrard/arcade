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

LIB_SRC = lib.cpp

SRC = file.cpp

NAME = arcade

LIB = libm.so

SFML = lib_arcade_sfml.so

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
	g++ -o $(NAME) $(SRC) -std=c++11 -ldl -fno-gnu-unique -g3

games:
	g++ -c lib/game/*.cpp

graphicals:
	g++ -o $(NAME) $(SRC) -std=c++11 -ldl -fno-gnu-unique -g3


.PHONY: $(NAME) clean fclean all re custom
