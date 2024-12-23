#include <iostream>
#include <vector>
#include "../include/ShipManager.hpp"

ShipManager::ShipManager(int shipCount, std::vector<int>shipsize) : shipCount(shipCount), shipsAlive(shipCount){
    for (auto& length : shipsize){
        ships.push_back(Ship(length));
    }
}


std::vector<Ship> ShipManager::getShips() const{
    return ships;
}

int ShipManager::GetShipCount() const {
    return this->shipCount;
}

void ShipManager::SetShipCount(int count) {
    this->shipCount = count;
}


Ship& ShipManager::getIndexShip(int index) {
    return this->ships[index];
}

void ShipManager::addShip(int length){
    this->ships.push_back(Ship(length));
}

Ship* ShipManager::GetShip(Coord coord) {
    for (auto& ship : this->ships) {
        for (int i = 0; i < ship.getLength(); i++) {
            if (ship.getParams(i)->coord.x == coord.x && ship.getParams(i)->coord.y == coord.y) {
                return &ship;
            }
        }
    }
    return nullptr;
}

int ShipManager::getShipsAlive() const {
    return this->shipsAlive;
}

void ShipManager::setShipsAlive(int count) {
    this->shipsAlive = count;
}
 