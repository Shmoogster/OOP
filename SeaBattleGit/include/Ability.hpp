#pragma once

#include "Map.hpp"
#include <string>
#include <random>

//void DoubleDamage::TakeAbility(Map& map);
//void Scanner::TakeAbility(Map& map);
//void Shelling::TakeAbility(Map& map);

class Ability {
    public:
        virtual void TakeAbility() = 0;
        virtual ~Ability() = default;
};
class DoubleDamage: public Ability{
    private:
        Map& map;
        Coord coord;
    public:
        DoubleDamage(Map& map,Coord coord);
        void TakeAbility() override;
};

class Scanner: public Ability{
    private:
        Map& map;
        Coord coord;
    public:
        Scanner(Map& map,Coord coord);
        void TakeAbility() override;
};
class Shelling: public Ability{
    private:
        Map& map;
    public:
        Shelling(Map& map);
        void TakeAbility() override;
};