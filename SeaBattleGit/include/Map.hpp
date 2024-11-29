#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

#include "Exceptions/UnableToPlaceShipsException.hpp"
#include "Exceptions/MultipleMissesException.hpp"
#include "Exceptions/OutOfRangeException.hpp"
#include "Exceptions/RevealedPointAttackException.hpp"
#include "Exceptions/ShipPlacementException.hpp"

#include "Struct.hpp"
#include "Ship.hpp"
class Map{
private:    
    int rows;
    int cols;
    std::vector<Point>map;
public:
    Map(int rows,int cols);
    Map(const Map& other);
    Map& operator=(const Map& other);
    Map(Map&& other);
    Map& operator=(Map&& other); 

    //методы
    int GetRows() const;
    int GetCols() const;
    std::vector<Point> GetMap() const;
    Point& GetPoint(Coord coord);
    bool CheckForCoord(Coord coord);
    bool CheckCoordAround(Coord coord);
    bool CheckShipCoord(Coord coord);
    bool PlaceShip(Ship* ship, Coord coord);
    void PlaceShipRandom(Ship* ship);
    void initMap(std::vector<Ship*> navy);
    bool Attack(Coord coord);
    Coord AttackRandom();
    void OpeningPoint();
    void OpeningCoordsAround(Ship* ship);
};
