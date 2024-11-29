#include <iostream>
#include <vector>
#include "../include/ShipManager.hpp"

ShipManager::ShipManager(int shipCount, std::vector<int>shipsize) : shipCount(shipCount){
    for (auto& length : shipsize){
        ships.push_back(new Ship(length));
    }
}

ShipManager::~ShipManager(){
    for (auto& ship: this->ships){
        delete ship;
    }
}

std::vector<Ship*> ShipManager::getShips() const{
    return ships;
}

int ShipManager::GetShipCount() const {
    return this->shipCount;
}

void ShipManager::SetShipCount(int count) {
    this->shipCount = count;
}

Ship* ShipManager::GetShip(Coord coord){
    for(auto& ship: this->ships){
        for(auto& param: ship->getParams()){
            if(param->coord.x == coord.x && param->coord.y == coord.y){
                return ship;
            }
        }
    }
    return new Ship(0);
}

void ShipManager::addShip(int length){
    this->ships.push_back(new Ship(length));
}

void ShipManager::CheckHP(Coord coord){
    for (auto& ship: this-> ships){
        std::vector<ShipParams*> params= ship-> getParams();
        for( auto& param: params) {
            if(param-> coord.x ==coord.x && param-> coord.y == coord.y){
                switch(param-> health){
                    case HealthPosition::Fullhp:
                        std::cout << "Not a single hole in the ship"<< std::endl;
                        break;
                    case HealthPosition::Onehp:
                        std::cout << "There are a couple of holes in the ship" << std::endl;
                        break;
                    case HealthPosition::Destroyed:
                        std::cout << "The ship is going to the bottom" << std::endl;
                        break;
                }
                return;
            }
        }
    }
    std::cout<<"There is no ship here"<< std::endl;
}