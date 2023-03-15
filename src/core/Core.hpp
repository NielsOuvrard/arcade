/*
** EPITECH PROJECT, 2023
** B-OOP-400-MAR-4-1-arcade-adam.elaoumari [WSL : Ubuntu]
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>
#include <filesystem>
#include "DLLoader.hpp"
class Core {
    public:
        Core();
        ~Core();
        std::vector<std::string> getGamesLibs () const { return gameLibs;}
        std::vector<std::string> getGfxLibs () const { return gfxLibs;}

    protected:
    private:
        std::vector<std::string> gameLibs;
        std::vector<std::string> gfxLibs;
};

#endif /* !CORE_HPP_ */
