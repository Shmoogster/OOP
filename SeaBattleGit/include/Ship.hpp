#pragma once

#include <iostream>
#include <vector>
#include "Struct.hpp"

class Ship{
    private:
        int length;
        Posture orientation;
        std::vector<ShipParams*> params;
    public:
        Ship(int length);
        ~Ship();

        //методы
        int getLength() const;
        std::vector<ShipParams*> getParams() const;
        bool CheckPosture() const;
        void ChangePosture();
        bool isDestroyed() const;
        void SetCoord(Coord coord);
};