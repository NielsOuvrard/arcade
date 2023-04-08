# Arcade - Documentation

## How to add a game

In order to add a game to the Arcade, you need to create a class inheriting from the `AGameModule` class
Then you'll need to implement a few functions to make your game work, and edit the Makefile

### Functions to implement

- `update(std::string key)`
This function is the entry point of your game and the graphic lib, it's in this function that you'll have to handle the key event of your game

- `std::vector<std::string> getTextures();`
This is the function that will return a list of strings that represents the path of the sprites your game will use (can be empty, if it's a text-only game)

- `resetGame(void)`
Resets the game variables, entities to it's original state

### Edit the Makefile
To add your game to the compilation process, you need to edit the makefile and add the following line :
`{GAMENAME}: @ g++ -shared -o lib/arcade_{GAMENAME}.so -fPIC $(SRC_LIB_GAMES)/{GAMENAME}/*.cpp ./src/game/AGameModule.cpp $(INCLUDE_PATH)`


## How to add a graphic lib
In order to add a graphic lib to the Arcade, you need to create a class inheriting from the `IDisplayModule` class
Then you'll need to implement a few functions to make your lib work, and edit the Makefile


### Functions to implement

- `void init(void)`
Initialize the graphic lib

- `void stop(void)`
Destroys the graphic lib and it's associated libs (font, sound..)

- `void update(std::map<std::string, IGameModule::Entity> entities)`
Update the screen using the entities sent by the game, the struct of the entities are as follow :
`int id_file // File number`
`std::string text; // Text if there is one`
`std::string background_color;`
`float x; // Position x`
`float y; // Position y`
`bool underline;`
`bool bold;`
`color_t color_fg; // Foreground color`
`color_t color_bg; // Background color`

- `virtual void draw();`
Draws the window

- `void saveTextures(const std::vector<std::string> &texture)`
Saves the textures used by the graphics libs, so that they are loaded once, for optimization.

- `std::string getEvent()`
Return the keys corresponding to an event. For special event e.g 'F1', please return the name of the key in uppercase. For ASCII keys, please only return they're ascii values as std::string

- `const std::string &getName() const`
Return the name of the graphic lib.

- `void resetDisplay();`
Resets display stored values such as textures.