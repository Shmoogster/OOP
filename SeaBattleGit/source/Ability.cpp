#include "../include/Ability.hpp"

DoubleDamage::DoubleDamage(int& damage) : damage(damage) {}
Scanner::Scanner(Map& map, Coord coord) : map(map), coord(coord) {}
Shelling::Shelling(Map& map) : map(map) {}

void DoubleDamage::TakeAbility(){
    this->damage = 2;
}
void Scanner::TakeAbility(){
    for(int y=0; y<=1; y++){
        for(int x=0; x<=1; x++){
            if(map.CheckForCoord({coord.x+x,coord.y+y})){
                throw OutOfRangeException();
            }                
            Point& mappoint = map.GetMap()[map.GetCols()*(coord.y+y) + coord.x + x];
            if (mappoint.param!=nullptr ){
                std::cout << "Ship is revealed"<< std::endl;
                return;
            }
        }
    }
    for(int y=0; y<=1; y++){
        for(int x=0; x<=1; x++){
            Point& mappoint= map.GetPoint({coord.x+x,coord.y+y});
            mappoint.owner=PointOwner::Revealed;
            mappoint.state=PointState::Missed;
        }
    }
    std::cout << "Ship is not found"<<std::endl;
}
void Shelling::TakeAbility(){
    std::random_device RD;
    std::mt19937 gen(RD());
    std::uniform_int_distribution<> uidX(0, map.GetCols() - 1);
    std::uniform_int_distribution<> uidY(0, map.GetRows() - 1);
        while(true){
        int randX=uidX(gen);
        int randY=uidY(gen);
        Point& mappoint=map.GetPoint({randX,randY});
        if(mappoint.param!=nullptr && mappoint.state!=PointState::Dead){
            mappoint.param->TakeDamage();
            if(mappoint.state==PointState::TwoHp){
                mappoint.state = PointState::OneHp;
            }else{
                mappoint.state = PointState::Dead;
            }
            return;
        }
    }
}