#pragma once

#include <iostream>
#include <vector>

enum class PointState : char { Empty = '~', OneHp = 'X', TwoHp='S', Dead='^', Missed='*' };
enum class PointOwner {Hidden, Revealed};
enum class Posture {Horizont, Vertic};
enum class HealthPosition{Fullhp, Onehp, Destroyed};
struct Coord{ int x,y; };


struct ShipParams{
    HealthPosition health;
    Coord coord;
        void TakeDamage() {
        if (health == HealthPosition::Fullhp) {
            health = HealthPosition::Onehp;
        }
        else if (health == HealthPosition::Onehp) {
            health = HealthPosition::Destroyed;
        }
    }
};

struct Point {
public:
    Coord coord;
    PointState state;
    PointOwner owner;
    ShipParams* param=nullptr;
};