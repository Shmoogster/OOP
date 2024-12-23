#pragma once

#include "../include/ShipManager.hpp"
#include "../include/Map.hpp"
#include "../include/AbilityManager.hpp"
#include "../include/Display.hpp"
#include "../include/AbilityParams.hpp"

class Player {
    protected:
        ShipManager& shipmanager;
        Map& map;
    public:
        Player(ShipManager& shipmanager, Map&map) : shipmanager(shipmanager), map(map){}
        virtual ShipManager& getShipManager()=0;
        virtual Map& getMap() =0;
        virtual ~Player(){};
};

class Human : public Player {
    private:
        AbilityManager& abilitymanager;
        int damage;
    public:
        Human(ShipManager& shipmanager, Map&map, AbilityManager& abilitymanager) : Player(shipmanager, map), abilitymanager(abilitymanager), damage(1){}
        Human(const Human& other) : Player(other.shipmanager, other.map), abilitymanager(other.abilitymanager), damage(other.damage) {}
        Human& operator = (const Human& other){
            if(this != &other){
                this->shipmanager = other.shipmanager;
                this->map = other.map;
                this->abilitymanager = other.abilitymanager;
                this->damage = other.damage;
            }
            return *this;
        }
        ShipManager& getShipManager() override { return shipmanager; };
        Map& getMap() override { return map; };
        AbilityManager& getAbilityManager() { return abilitymanager; };
        int& getDamage() { return damage; };
        void setDamage(int curdamage) { damage = curdamage; };
};      

class Bot : public Player {
    public:
        Bot(ShipManager& shipmanager, Map& map): Player(shipmanager, map) {}
        Bot(const Bot& other) : Player(other.shipmanager, other.map){}
        Bot& operator=(const Bot& other) {
            if (this != &other){
                this->shipmanager = other.shipmanager;
                this->map = other.map;
            }
            return *this;
        }
        ShipManager& getShipManager() override {return shipmanager;};
        Map& getMap() override { return map; };
};