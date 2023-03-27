/*
**  ______   ______     ______     __    __     ______     __   __
** /\  == \ /\  __ \   /\  ___\   /\ "-./  \   /\  __ \   /\ "-.\ \
** \ \  _-/ \ \  __ \  \ \ \____  \ \ \-./\ \  \ \  __ \  \ \ \-.  \
**  \ \_\    \ \_\ \_\  \ \_____\  \ \_\ \ \_\  \ \_\ \_\  \ \_\\"\_\
**   \/_/     \/_/\/_/   \/_____/   \/_/  \/_/   \/_/\/_/   \/_/ \/_/
**
*/

#include "pacman.hpp"
#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> fileToArray (std::string filepath)
{
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: file " << filepath << " not found" << std::endl;
        exit(84);
    }
    std::string line;
    std::vector<std::string> array;
    while (getline(inputFile, line)) {
        array.push_back(line);
    }
    inputFile.close();
    return array;
}

// int _pos_x = 0;
// int _pos_y = 0;
// int _score = 0;
// int _lives = 3;
// int _invincible = 0;
void Pacman::getInfoMap (std::vector<std::string> map)
{
    int color_ennemy = 0;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '@') {
                _pos_x = j;
                _pos_y = i;
            } else if (map[i][j] == 'X') {
                ennemy_t ennemy;
                ennemy.color = (color_ennemy % 4);
                ennemy.x = j;
                ennemy.y = i;
                ennemy.avlive = true;
                ennemy.direction = 0;
                _ennemy.push_back(ennemy);
                color_ennemy++;
            }
        }
    }
}

void writeAtEnd(std::string str)
{
    std::ofstream file;
    file.open("file.txt", std::ios::app);
    file << str << std::endl;
    file.close();
}

void Pacman::fillGumsRemain()
{
    _nbr_gums_remain = 0;
    for (int i = 0; i < getGrid().size(); i++)
        for (int j = 0; j < getGrid()[i].size(); j++)
            if (getGrid()[i][j] >= 2 && getGrid()[i][j] <= 4)
                    _nbr_gums_remain++;
}

Pacman::Pacman()
{
    std::vector<std::string> map = fileToArray("lib/games/pacman/map" + std::to_string(_level) + ".txt");
    // compt _nmbr_gums_remain
    // # = wall
    // . = small food   (+1)
    // o = medium food  (+5)
    // 0 = big food     (+10)
    // @ = spawn
    // X = ennemy
    generateGrid(map, true);
    fillGumsRemain();
    getInfoMap(map);
    dataToEntity();
    setDirection(DIRECTION::RIGHT);
}

Pacman::~Pacman()
{
}

void Pacman::pacmanPart()
{
    // TODO : 1 frame / 2 sprite
    int index = 0;
    if (getDirection() == DIRECTION::RIGHT)
        index = 1;
    if (getDirection() == DIRECTION::LEFT)
        index = 3;
    if (getDirection() == DIRECTION::UP)
        index = 5;
    if (getDirection() == DIRECTION::DOWN)
        index = 7;
    if (_second_sprite)
        index++;
    Entity newEntity = {
        index,
        "@",
        "",
        _pos_x,
        _pos_y + _decal_y,
        false,
        false,
        {255, 255, 0},
        {0, 0, 0},
    };
    setNewEntity("Pacman", newEntity);
}

int Pacman::chooseEnnemySprite (int color, int direction)
{
    // begin at 9
    int index = 9;
    // TODO : when color is implemented
    if (color > 0)
        index += 8;
    if (color > 1)
        index += 8;
    if (color > 2)
        index += 8;
    if (direction == DIRECTION::RIGHT)
        index += 0;
    if (direction == DIRECTION::LEFT)
        index += 2;
    if (direction == DIRECTION::UP)
        index += 4;
    if (direction == DIRECTION::DOWN)
        index += 6;
    if (_invincible) {
        index = 44;
        if (_invincible < 10 && _invincible % 2 == 0)
            index = 46;
    }
    if (_second_sprite)
        index++;
    return index;
}

void Pacman::ennemyPart(ennemy_t ennemy, int i, int row)
{
    if (ennemy.avlive == false)
        return;
    int index = chooseEnnemySprite(ennemy.color, ennemy.direction);
    int red = 0;
    int green = 0;
    int blue = 0;
    if (ennemy.color == 0) {
        red = 255;
        green = 0;
        blue = 0;
    } else if (ennemy.color == 1) {
        red = 0;
        green = 255;
        blue = 0;
    } else if (ennemy.color == 2) {
        red = 100;
        green = 100;
        blue = 255;
    } else if (ennemy.color == 3) {
        red = 255;
        green = 255;
        blue = 0;
    }
    Entity newEntity = {
        index,
        "X",
        "",
        ennemy.x,
        ennemy.y + _decal_y,
        false,
        false,
        {red, green, blue},
        {0, 0, 0},
    };
    setNewEntity(std::to_string(i) + "ennemy" + std::to_string(row), newEntity);
}

void Pacman::dataToEntity(void)
{
    float y = 0, x = 0;
    int row = 0;
    clearEntities();
    for (std::vector<int> value : getGrid()) {
        for (int i = 0; y <= getGrid().size() && i < getGrid()[y].size(); i++) {
            // # = wall
            // . = small food   (+1)
            // o = medium food  (+5)
            // O = big food     (+10)
            // @ = spawn
            // X = ennemy
            if (value[i] == -2) { // walls
                Entity newEntity = {
                    0,
                    "#",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {0, 0, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "walls" + std::to_string(row), newEntity);
            } else if (value[i] == 2) { // small food
                Entity newEntity = {
                    41, // nothing
                    ".",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {255, 255, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "small food" + std::to_string(row), newEntity);
            } else if (value[i] == 3) { // medium food
                Entity newEntity = {
                    42, // nothing
                    "o",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {255, 255, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "medium food" + std::to_string(row), newEntity);
            } else if (value[i] == 4) { // big food
                Entity newEntity = {
                    43, // TODO: add big food
                    "O",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {255, 255, 255},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "big food" + std::to_string(row), newEntity);
            } else if (value[i] == 6 || value[i] == 7) { // teleport
                Entity newEntity = {
                    -1, // TODO: add teleport
                    "",
                    "",
                    x,
                    y + _decal_y,
                    false,
                    false,
                    {0, 255, 0},
                    {0, 0, 0},
                };
                setNewEntity(std::to_string(i) + "teleport" + std::to_string(row), newEntity);
            }
            x += 1;
        }
        x = 0;
        y += 1;
        row++;
    }
    pacmanPart();
    for (int i = 0; i != _ennemy.size(); i++) {
        ennemyPart(_ennemy[i], i, row++);
    }
    setNewEntity("gum", {
        -1,
        "Gum remain: " + std::to_string(_nbr_gums_remain),
        "",
        0,
        0,
        true,
        true,
        {255, 255, 255},
        {0, 0, 0},
    });
}

void Pacman::positionToThisValue(int value)
{
    for (int y = 0; y < getGrid().size(); y++) {
        for (int x = 0; x < getGrid()[y].size(); x++) {
            if (getGrid()[y][x] == value) {
                _pos_x = x;
                _pos_y = y;
            }
        }
    }
}

bool Pacman::eventAfterMoving(int x, int y)
{
    // eventAfterMoving
    if (getGrid()[_pos_y + y][_pos_x + x] == 2) {
        _score += 1;
        _nbr_gums_remain--;
    } else if (getGrid()[_pos_y + y][_pos_x + x] == 3) {
        _nbr_gums_remain--;
        _score += 5;
    } else if (getGrid()[_pos_y + y][_pos_x + x] == 4) {
        _nbr_gums_remain--;
        _score += 10;
        _invincible += 30; // TODO 10 secondes ?
    }
    if (!_nbr_gums_remain) {
        _level++;
        resetGame();
        // setGameStatus(FINISHED);
    }
    return 0;
}

void Pacman::move(void)
{
    if (_next_direction == UP && _pos_y >= 0 && getGrid()[_pos_y - 1][_pos_x] > -2) {
        setDirection(UP);
    } else if (_next_direction == DOWN && getGrid().size() >= _pos_y && getGrid()[_pos_y + 1][_pos_x] > -2) {
        setDirection(DOWN);
    } else if (_next_direction == LEFT && _pos_x >= 0 && getGrid()[_pos_y][_pos_x - 1] > -2) {
        setDirection(LEFT);
    } else if (_next_direction == RIGHT && getGrid()[_pos_y].size() >= _pos_x && getGrid()[_pos_y][_pos_x + 1] > -2) {
        setDirection(RIGHT);
    }
    if (getDirection() == UP && _pos_y > 0 && getGrid()[_pos_y - 1][_pos_x] > -2) {
        // teleport
        if (_pos_y - 1 == 0) {
            _pos_y = getGrid().size() - 1;
            return;
        }
        eventAfterMoving(0, -1);
        setGridValue(--_pos_y, _pos_x, 0);
    } else if (getDirection() == DOWN && getGrid().size() >= _pos_y && getGrid()[_pos_y + 1][_pos_x] > -2) {
        // teleport
        if (_pos_y + 1 == getGrid().size() - 1) {
            _pos_y = 0;
            return;
        }
        eventAfterMoving(0, 1);
        setGridValue(++_pos_y, _pos_x, 0);
    } else if (getDirection() == LEFT && _pos_x > 0 && getGrid()[_pos_y][_pos_x - 1] > -2) {
        // teleport
        if (_pos_x - 1 == 0) {
            _pos_x = getGrid()[_pos_y].size() - 1;
            return;
        }
        eventAfterMoving(-1, 0);
        setGridValue(_pos_y, --_pos_x, 0);
    } else if (getDirection() == RIGHT && getGrid()[_pos_y].size() >= _pos_x && getGrid()[_pos_y][_pos_x + 1] > -2) {
        // teleport
        if (_pos_x + 1 == getGrid()[_pos_y].size() - 1) {
            _pos_x = 0;
            return;
        }
        eventAfterMoving(1, 0);
        setGridValue(_pos_y, ++_pos_x, 0);
    } else {
        _isMoving = false;
    }
}

// check if pacman touch ennemy
int Pacman::checkIfPacmanTouchEnnemy(void)
{
    for (int i = 0; i != _ennemy.size(); i++) {
        if (_pos_x == _ennemy[i].x && _pos_y == _ennemy[i].y) {
            if (_invincible) {
                _ennemy[i].avlive = false;
                _score += 100;
                return 0;
            } else {
                _isAlive = false;
                return 1;
            }
        }
    }
    return 0;
}

void Pacman::update(std::string key)
{
    if (key == "LeftArrow") {
        _next_direction = LEFT;
        _isMoving = true;
    } else if (key == "RightArrow") {
        _next_direction = RIGHT;
        _isMoving = true;
    } else if (key == "UpArrow") {
        _next_direction = UP;
        _isMoving = true;
    } else if (key == "DownArrow") {
        _next_direction = DOWN;
        _isMoving = true;
    }
    if (getTimeElapsed(start) < std::chrono::milliseconds(200)) {
        return;
    } else {
        _second_sprite = !_second_sprite;
        if (_invincible)
            _invincible -= 1;
        setChronoValue(std::chrono::high_resolution_clock::now());
    }
    // check if pacman touch ennemy
    if (checkIfPacmanTouchEnnemy())
        resetGame();
    if (_isMoving)
        move();
    dataToEntity();
    if (key.empty())
        return;
    if (key == "close") {
        setGameStatus(FINISHED);
    }
}

void Pacman::resetGame(void)
{
    clearGrid();
    _isAlive = true;
    _isMoving = false;
    _score = 0;
    _invincible = 0;
    _ennemy.clear();
    std::vector<std::string> map = fileToArray("lib/games/pacman/map" + std::to_string(_level) + ".txt");
    generateGrid(map, true);
    fillGumsRemain();
    getInfoMap(map);
    dataToEntity();
    setDirection(DIRECTION::RIGHT);
    _next_direction = RIGHT;
}

extern "C" IGameModule *create(void) {
    return new Pacman();
}

extern "C" void destroy(IGameModule* obj) {
    delete obj;
}

extern "C" std::string getType() {
    return "Game";
}

std::vector<std::string> Pacman::getTextures() {
    std::vector<std::string> files_path = {
        "lib/games/Pacman/files/wall.png",
        // lib/games/pacman/files/player-down-1.png
        "lib/games/Pacman/files/player-right-1.png",
        "lib/games/Pacman/files/player-right-2.png",
        "lib/games/Pacman/files/player-left-1.png",
        "lib/games/Pacman/files/player-left-2.png",
        "lib/games/Pacman/files/player-up-1.png",
        "lib/games/Pacman/files/player-up-2.png",
        "lib/games/Pacman/files/player-down-1.png",
        "lib/games/Pacman/files/player-down-2.png",
        // lib/games/pacman/files/ghost-blue-1.png
        "lib/games/Pacman/files/ghost-blue-1.png", // right
        "lib/games/Pacman/files/ghost-blue-2.png",
        "lib/games/Pacman/files/ghost-blue-3.png", // left
        "lib/games/Pacman/files/ghost-blue-4.png",
        "lib/games/Pacman/files/ghost-blue-5.png", // up
        "lib/games/Pacman/files/ghost-blue-6.png",
        "lib/games/Pacman/files/ghost-blue-7.png", // down
        "lib/games/Pacman/files/ghost-blue-8.png",
        // lib/games/pacman/files/ghost-pink-1.png
        "lib/games/Pacman/files/ghost-pink-1.png", // right
        "lib/games/Pacman/files/ghost-pink-2.png",
        "lib/games/Pacman/files/ghost-pink-3.png", // left
        "lib/games/Pacman/files/ghost-pink-4.png",
        "lib/games/Pacman/files/ghost-pink-5.png", // up
        "lib/games/Pacman/files/ghost-pink-6.png",
        "lib/games/Pacman/files/ghost-pink-7.png", // down
        "lib/games/Pacman/files/ghost-pink-8.png",
        // lib/games/pacman/files/ghost-orange-1.png
        "lib/games/Pacman/files/ghost-orange-1.png", // right
        "lib/games/Pacman/files/ghost-orange-2.png",
        "lib/games/Pacman/files/ghost-orange-3.png", // left
        "lib/games/Pacman/files/ghost-orange-4.png",
        "lib/games/Pacman/files/ghost-orange-5.png", // up
        "lib/games/Pacman/files/ghost-orange-6.png",
        "lib/games/Pacman/files/ghost-orange-7.png", // down
        "lib/games/Pacman/files/ghost-orange-8.png",
        // lib/games/pacman/files/ghost-red-1.png
        "lib/games/Pacman/files/ghost-red-1.png", // right
        "lib/games/Pacman/files/ghost-red-2.png",
        "lib/games/Pacman/files/ghost-red-3.png", // left
        "lib/games/Pacman/files/ghost-red-4.png",
        "lib/games/Pacman/files/ghost-red-5.png", // up
        "lib/games/Pacman/files/ghost-red-6.png",
        "lib/games/Pacman/files/ghost-red-7.png", // down
        "lib/games/Pacman/files/ghost-red-8.png",
        // food
        "lib/games/Pacman/files/small-food.png",
        "lib/games/Pacman/files/medium-food.png",
        "lib/games/Pacman/files/big-food.png",
        // ghost-weak-9 = 44
        "lib/games/Pacman/files/ghost-weak-9.png",
        "lib/games/Pacman/files/ghost-weak-10.png",
        "lib/games/Pacman/files/ghost-weak-11.png",
        "lib/games/Pacman/files/ghost-weak-12.png",
    };
    return files_path;
}
