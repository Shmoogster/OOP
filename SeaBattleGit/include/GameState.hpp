#pragma once

#include "Serialization.hpp"
#include "Deserialization.hpp"
#include "Display.hpp"
#include "Player.hpp"
#include "Hull.hpp"
#include "Struct.hpp"
#include "Exceptions/HashMismatchException.hpp"
#include "Exceptions/UnableToOpenFileException.hpp"

#include <fstream>

class GameState {
    private:
        Human& human;
        Bot& bot;
        bool isAbilityUsed;
        Coord coord;
        int damage;
    public:
        GameState(Human& human, Bot& bot) : human(human), bot(bot), isAbilityUsed(false), damage(1) {};
        
        std::string getHash(const std::string& data);
        void placeShips(ShipManager& shipmanager, Map& map);
        
        void LoadGame();
        void SaveGame();

        Human& getHuman() { return this->human; };
        Bot& getBot() { return this->bot; };

        bool& getAbilityUsed() { return this->isAbilityUsed; };
        void setAbilityUsed(bool value) { this->isAbilityUsed = value; };
        
        int& getCurDamage() { return this->damage; };
        void setCurDamage(int curdamage) { this->damage = curdamage; };

        Coord& getCoord(){ return this->coord; };
        void setCoord(Coord coord){ this->coord = coord;};
};