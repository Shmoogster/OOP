#pragma once

#include "Ability.hpp"
#include "AbilityParams.hpp"
#include <string.h>



class AbilityCreator {
    public:
        virtual Ability* CreateAbility(AbilityParams& abilpar) = 0;
        virtual std::string getTitle() const = 0;
        virtual bool isUseCoord() = 0;
        virtual ~AbilityCreator() {};
};

class DoubleDamageAbilityCreator : public AbilityCreator {
    public:
        DoubleDamageAbilityCreator() {};
        std::string getTitle() const override {return "Double Damage";};
        bool isUseCoord() override {return false;};
        Ability* CreateAbility(AbilityParams& abilpar) override { return new DoubleDamage(abilpar.damage); };
};

class ScannerAbilityCreator : public AbilityCreator {
    public:
        ScannerAbilityCreator() {};
        std::string getTitle() const override {return "Scanner";};
        bool isUseCoord() override {return true;};
        Ability* CreateAbility(AbilityParams& abilpar) override { return new Scanner(abilpar.map, abilpar.coord); };
};

class ShellingAbilityCreator : public AbilityCreator {
    public:
        ShellingAbilityCreator() {};
        std::string getTitle() const override {return "Shelling";};
        bool isUseCoord() override {return false;};
        Ability* CreateAbility(AbilityParams& abilpar) override { return new Shelling(abilpar.map); };
};