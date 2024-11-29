#pragma once

#include <iostream>
#include <vector>
#include "Ship.hpp"
using namespace std;
class ShipManager{
    private:
        std::vector<Ship*> ships;
        int shipCount;
    public:
        ShipManager(int shipCount, std::vector<int>shipsize);
        ~ShipManager();

        //методы
        std::vector<Ship*> getShips() const;
        Ship* GetShip(Coord coord);
        int GetShipCount() const;
        void SetShipCount(int count);
        void addShip(int length);
        void CheckHP(Coord coord);
        void printShips() const;
};