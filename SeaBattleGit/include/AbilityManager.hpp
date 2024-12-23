#pragma once

#include "Ability.hpp"
#include "AbilityCreator.hpp"
#include "Exceptions/NoAbilitiesAvailableException.hpp"
#include "AbilityParams.hpp"
#include <queue>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>

class AbilityManager {
    private:
        std::queue<AbilityCreator*> ability;
    public:
        AbilityManager();
        ~AbilityManager();

        int GetAbilCount() const;
        void IfEmpty();
        void AddAbility(AbilityCreator* create);
        void RandomizeAbility();
        void UseAbility(AbilityParams& abilpar);
        void PopAbility();
        AbilityCreator& getCreator(int index);
};