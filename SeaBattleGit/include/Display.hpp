#pragma once

#include "../include/AbilityManager.hpp"
#include "../include/AbilityCreator.hpp"
#include "../include/Map.hpp"
#include "../include/Struct.hpp"

#include <fstream>
#include <string>

class Display {
    public:
    void PrintException(std::exception& e) const; 
    void printString(std::string data) const;
    void printAbilityName(std::string name) const;
    void printAbilityNames(AbilityManager abilityManager) const;
    void printShip(Ship ship) const;
    void printPointState(Map self, Coord coord) const;
    void printMap(Map self) const;
    void printMaps(Map self, Map other) const;
    void printCoordNeeded() const;
    void printInfo() const;
};