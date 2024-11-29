#pragma once

#include "Ability.hpp"

enum class Abilities { DoubleDamage, Scanner, Shelling };

class AbilityCreator {
    public:
        virtual Ability* CreateAbility() = 0;
        virtual ~AbilityCreator() {};
};

class DoubleDamageAbilityCreator : public AbilityCreator {
    private:
        Map& map;
        Coord coord;
    public:
        DoubleDamageAbilityCreator(Map& map, Coord coord) : map(map), coord(coord) {};
        Ability* CreateAbility() override { return new DoubleDamage(this->map, this->coord); };
};

class ScannerAbilityCreator : public AbilityCreator {
    private:
        Map& map;
        Coord coord;
    public:
        ScannerAbilityCreator(Map& map, Coord coord) : map(map), coord(coord) {};
        Ability* CreateAbility() override { return new Scanner(this->map, this->coord); };
};

class ShellingAbilityCreator : public AbilityCreator {
    private:
        Map& map;
    public:
        ShellingAbilityCreator(Map& map) : map(map) {};
        Ability* CreateAbility() override { return new Shelling(this->map); };
};