#pragma once

#include <iostream>
#include <vector>
#include "Ship.hpp"
using namespace std;
class ShipManager{
    private:
        std::vector<Ship> ships;
        int shipCount;
        int shipsAlive;
    public:
        ShipManager() : ships({}) {};
        ShipManager(int shipCount, std::vector<int>shipsize);

        //методы
        std::vector<Ship> getShips() const;
        Ship* GetShip(Coord coord);
        int GetShipCount() const;
        Ship& getIndexShip(int index);
        void SetShipCount(int count);
        void addShip(int length);
        int getShipsAlive() const;
        void setShipsAlive(int count);
};