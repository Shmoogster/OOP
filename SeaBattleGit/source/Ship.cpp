#include "../include/Ship.hpp"
#include<iostream>
#include<vector>

Ship::Ship(int length): length(length){
    this->orientation = Posture::Horizont;
    for(int i=0; i< length; i++){
        this -> params.push_back(ShipParams());
    }

}
int Ship::getLength() const{
    return this-> length;
}

ShipParams* Ship::getParams(int index) {
    return &this-> params[index];
}

void Ship::SetPosture(Posture newposture) {
    if (newposture == Posture::Horizont) {
        this->orientation = Posture::Vertic;
        return;
    }
    this->orientation = Posture::Horizont;
}

bool Ship::CheckPosture() const{
    if (this-> orientation == Posture::Horizont){
        return true;
    }
    return false;
}

bool Ship::isDestroyed() const {
    for(auto& param: this->params){
        if(param.health != HealthPosition::Destroyed){
            return false;
        }
    }
    return true;
}
void Ship::SetCoord(Coord coord){
    int i=0;
    for(auto& param: this->params){
        if (orientation == Posture::Horizont){
            param.coord.x=coord.x+i;
            param.coord.y=coord.y;
        }else{
            param.coord.x=coord.x;
            param.coord.y=coord.y+i;            
        }
        ++i;
    }
}
