#pragma once

#include "Map.hpp"
#include "AbilityParams.hpp"
#include <string>
#include <random>


class Ability {
    public:
        virtual void TakeAbility() = 0;
        virtual ~Ability() {};
};
class DoubleDamage: public Ability{
    private:
        int& damage;
    public:
        DoubleDamage(int& damage);
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