#pragma once

#include "Game.hpp"
#include "Commander.hpp"
#include <map>

class PlayerInput {
    private:
        std::map <char, Commander> commands;
    public:
        PlayerInput();
        void SetCommands(std::map <char, Commander> newCommands);
        Commander CommandInput();
        Coord CoordInput();
};