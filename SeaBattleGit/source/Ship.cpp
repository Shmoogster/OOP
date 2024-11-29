#include "../include/Ship.hpp"
#include<iostream>
#include<vector>

Ship::Ship(int length): length(length){
    if (length < 0 || length > 4){
        throw std::invalid_argument("Length of ship must be 1,2,3 or 4");
    }
    this->orientation = Posture::Horizont;
    for(int i=0; i< length; i++){
        this -> params.push_back(new ShipParams());
    }

}

Ship::~Ship(){
    for(auto& param: params){
       delete param; 
    }
}
int Ship::getLength() const{
    return this-> length;
}

std::vector<ShipParams*> Ship::getParams() const{
    return this-> params;
}

bool Ship::CheckPosture() const{
    if (this-> orientation == Posture::Horizont){
        return true;
    }
    return false;
}
void Ship::ChangePosture(){
    switch (this->orientation){
        case Posture::Horizont:
            this->orientation = Posture::Vertic;
            break;
        case Posture::Vertic:
            this->orientation = Posture::Horizont;
            break;
    }
}
bool Ship::isDestroyed() const {
    for(auto& param: this->params){
        if(param->health != HealthPosition::Destroyed){
            return false;
        }
    }
    return true;
}
void Ship::SetCoord(Coord coord){
    int i=0;
    for(auto& param: this->params){
        if (orientation == Posture::Horizont){
            param->coord.x=coord.x+i;
            param->coord.y=coord.y;
        }else{
            param->coord.x=coord.x;
            param->coord.y=coord.y+i;            
        }
        ++i;
    }
}
