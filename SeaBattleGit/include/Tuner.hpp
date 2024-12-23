#pragma once

#include "PlayerInput.hpp"
#include "Deserialization.hpp"
#include "Hull.hpp"

class Setup {
    private:
        PlayerInput& playerInput;
    public:
        Setup(PlayerInput& playerInput) : playerInput(playerInput) {};
        void deserializeSetup() {
            nlohmann::json file;
            Hull fileHull = Hull("/home/shmooga/SeaBattleGit/.vscode/setup.json");
            std::map<char, Commander> newCommands;
            fileHull.Read(file);
            Deserialization(file).from_json(newCommands);
            playerInput.SetCommands(newCommands);
        }
};