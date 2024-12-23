#pragma once

#include <iostream>
#include <vector>
#include "Struct.hpp"

class Ship{
    private:
        int length;
        Posture orientation;
        std::vector<ShipParams> params;
    public:
        Ship(int length);

        //методы
        int getLength() const;
        ShipParams* getParams(int index);
        void SetPosture(Posture newposture);
        bool CheckPosture() const;
        bool isDestroyed() const;
        void SetCoord(Coord coord);
};