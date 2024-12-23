#pragma once

#include "Ship.hpp"
#include "ShipManager.hpp"
#include "Map.hpp"
#include "Display.hpp"
#include "Player.hpp"
#include "GameState.hpp"
#include "Ability.hpp"
#include "AbilityManager.hpp"
#include "Warden.hpp"
#include "../include/Exceptions/InvalidShipSizeException.hpp"
#include "../include/Exceptions/HashMismatchException.hpp"
#include "Exceptions/InvalidCoordException.hpp"

class Game {
    private:
        Human human;
        Bot bot;
        GameState gameState;
        Display display;
        std::vector<Warden*> warden;
    public:
        Game(Human human, Bot bot, GameState gameState, Display display)
            : human(human), bot(bot), gameState(gameState), display(display) {}
            
        void useHumanAbility();
        void HumanAttack();
        void BotAttack();

        void resetBot();
        void resetGame();

        void addWarden(Warden* warden);

        void LoadGame();
        void SaveGame();

        GameState& getGameState() {return gameState; };
};