#pragma once

#include "Ability.hpp"
#include "AbilityCreator.hpp"
#include "Exceptions/NoAbilitiesAvailableException.hpp"
#include <queue>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>

class AbilityManager {
    private:
        std::queue<Abilities> ability;
        Map& map;
    public:
        AbilityManager(Map& map);
        int GetAbilCount() const;
        Abilities Front();
        void IfEmpty();
        void AddAbility(Abilities ability);
        void RandomizeAbility();
        void UseAbility(Coord coord = {-1, -1});
        void PopAbility();
};