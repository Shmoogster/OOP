#pragma once

#include "../include/AbilityCreator.hpp"
#include "../include/Map.hpp"
#include "../include/Struct.hpp"

class Display {
    public:
    void PrintException(std::exception& e) const; 
    void printAbilityName(Abilities name) const;
    void printPointState(Map self, Coord coord) const;
    void printMap(Map self) const;
    void printMaps(Map self, Map other) const;
};