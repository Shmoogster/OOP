#include <iostream>
#include "../include/Map.hpp"

Map::Map(int rows,int cols): rows(rows),cols(cols){
    for(int i=0; i< rows; i++){
            for(int j=0; j < cols; j++){
            map.push_back(Point{{i,j}, PointState::Empty, PointOwner::Hidden});
        }
    }
}
//копирующий конструктор
Map::Map(const Map& other) : rows(other.rows), cols(other.cols), map(other.map) {}

//копирующий оператор присваивания
Map& Map::operator=(const Map& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        map = other.map;
    }
    return *this;
}
//перемещающий конструктор
Map::Map(Map&& other) : rows(other.rows), cols(other.cols), map(std::move(other.map)){
    other.rows = 0;
    other.cols = 0;
    other.map.clear();
}

//перемещающий оператор присваивания
Map& Map::operator=(Map&& other) {
    if (this != &other) {
        rows = other.rows;
        cols = other.cols;
        map = std::move(other.map);
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

int Map::GetRows() const{
    return this->rows;
}
int Map::GetCols() const{
    return this->cols;
}
std::vector<Point> Map::GetMap() const{
    return this->map;
}

Point& Map::GetPoint(Coord coord) {
    return this->map[coord.y * this->cols + coord.x];
}

bool Map::CheckForCoord(Coord coord){
    if(coord.x<0 || coord.x>=cols || coord.y<0 || coord.y>=rows){
        return true;
    }
    return false;
}

bool Map::CheckCoordAround(Coord coord){
    if (CheckForCoord(coord)){
        return true;
    }
        for (int i=-1; i<=1; i++){
            for (int j=-1; j<=1; j++){
                if (!CheckForCoord({coord.x+i, coord.y+j})){
                    if(map[coord.x+i+(coord.y+j)*cols].param!=nullptr){
                        return true;
                    }
                }
        }
    }
        return false;
}

bool Map::CheckShipCoord(Coord coord){
    Point point = this->map[this->cols*coord.y+coord.x];
    return (point.state == PointState::TwoHp ||point.state == PointState::OneHp || point.state == PointState::Dead);
}

bool Map::PlaceShip(Ship* ship, Coord coord){
    if(coord.x <0 || coord.x < 0){
        return false;
    }
    if(ship->CheckPosture()){
        if(coord.x+ship->getLength()>this->cols){
            return false;
        }
        
        for(int i=0; i< ship->getLength(); i++){
            if(CheckCoordAround({coord.x+i,coord.y})){
                throw ShipPlacementException();
            }
            if(this->CheckShipCoord({coord.x+i, coord.y})){
                throw ShipPlacementException();
            }
        }
        for(int i=0; i< ship->getLength(); i++){
            ship->getParams(i)->coord=Coord{coord.x,coord.y+i};
            map[coord.y*this->cols+coord.x+i].param=ship->getParams(i);
            map[coord.y*this->cols+coord.x+i].state=PointState::TwoHp;        
        }
        return true;
    }

    if(coord.y+ship->getLength()>this->rows){
        return false;
    }
    if(coord.x>= this->cols){
        return false;
    }
    for(int i=0; i< ship->getLength(); i++){
        if(CheckCoordAround({coord.x,coord.y+i})){
            throw ShipPlacementException();
        }
        if(this->CheckShipCoord({coord.x, coord.y+i})){
           throw ShipPlacementException();
        }
    }
    for(int i=0; i< ship->getLength(); i++){
        ship->getParams(i)->coord=Coord{coord.x+i,coord.y};
        map[(coord.y+i)*this->cols+coord.x].param=ship->getParams(i);
        map[(coord.y+i)*this->cols+coord.x].state=PointState::TwoHp;        
    }
    return true;
}

void Map::PlaceShipRandom(Ship* ship){
    std::random_device RD;
    std::mt19937 gen(RD());
    std::uniform_int_distribution<> uidX(0, cols - 1);
    std::uniform_int_distribution<> uidY(0, rows - 1);
    std::uniform_int_distribution<> uidPosture(0, 1);

    int j=0;
    while(true){
        int randX=uidX(gen);
        int randY=uidY(gen);
        int randPosture=uidPosture(gen);
        if(randPosture==1){
            ship->SetPosture(Posture::Vertic);
        }
        try {
            if(this->PlaceShip(ship, {randX, randY})){
                ship->SetCoord({randX,randY});
                return;
            }
        }
        catch (ShipPlacementException& e){
            j++;
            if (j >= 30){
                throw UnableToPlaceShipsException();
            }
            continue;
        }
    }
}

void Map::initMap(std::vector<Ship*> navy){
    for(auto& ship: navy){
        this->PlaceShipRandom(ship);
    }
}
bool Map::Attack(Coord coord){
    if(this->CheckForCoord(coord)){
        throw OutOfRangeException();
    }

    Point& mappoint= this->map[this->cols*coord.y + coord.x];
    mappoint.owner=PointOwner::Revealed;
    switch(mappoint.state){
        case PointState::Empty:
            mappoint.state=PointState::Missed;
            break;
        case PointState::TwoHp:
            mappoint.param->health=HealthPosition::Onehp;
            mappoint.state=PointState::OneHp;
            break;
        case PointState::OneHp:
            mappoint.param->health=HealthPosition::Destroyed;
            mappoint.state=PointState::Dead;
            break;
        default:
            throw RevealedPointAttackException();
            break;
    }
    return true;
}
Coord Map::AttackRandom(){
    std::random_device RD;
    std::mt19937 gen(RD());
    std::uniform_int_distribution<> uidX(0, cols - 1);
    std::uniform_int_distribution<> uidY(0, rows - 1);
    while(true){
        int randX=uidX(gen);
        int randY=uidY(gen);
        if (!this->CheckForCoord({randX,randY}) && this->Attack({randX, randY})){
            return {randX, randY};
        }
       
    }
}

void Map::OpeningPoint(){
    for(auto& point: this->map) {
        point.owner = PointOwner::Revealed;
    }
}

void Map::OpeningCoordsAround(Ship* ship){
    for (int k = 0; k < ship->getLength(); k++){
        for(int i=-1; i<=1; i++){
            for(int j=-1; j<=1;j++){
                if (!CheckForCoord({ship->getParams(k)->coord.x + i, ship->getParams(k)->coord.y + j})) {
                    Point& mappoint = this->map[this->cols*(ship->getParams(k)->coord.y + j) + ship->getParams(k)->coord.x + i];
                    if (mappoint.state != PointState::Empty) {
                        continue;
                    }
                    mappoint.state=PointState::Missed;
                    mappoint.owner=PointOwner::Revealed;
                }
            }
        }
    }

}