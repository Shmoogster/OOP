#pragma once

#include "Map.hpp"
#include "ShipManager.hpp"
#include "Struct.hpp"

struct AbilityParams {
    Map& map;
    ShipManager& shipmanager;
    Coord& coord;
    int& damage;
    AbilityParams(Map& map, ShipManager& shipmng, Coord& coord, int& damage) : map(map), shipmanager(shipmng), coord(coord), damage(damage) {};
};