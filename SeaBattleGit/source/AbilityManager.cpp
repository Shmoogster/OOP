#include "../include/AbilityManager.hpp"

AbilityManager::AbilityManager(Map& map): map(map){
    std::vector<Abilities> vec = {Abilities::DoubleDamage, Abilities::Scanner,Abilities::Shelling};
    std::random_device RD;
    std::mt19937 gen(RD());
    std::shuffle(vec.begin(), vec.end(), gen);
    this->ability.push(vec[0]);
}

int AbilityManager::GetAbilCount() const {
    return this->ability.size();
}
Abilities AbilityManager::Front(){
    return this->ability.front();
}
void AbilityManager::IfEmpty(){
    if(ability.empty()){
        throw NoAbilitiesAvailableException();
    }
}
void AbilityManager::AddAbility(Abilities ability){
    this->ability.push(ability);
}
void AbilityManager::RandomizeAbility(){
    std::random_device RD;
    std::mt19937 gen(RD());
    int RandNum=gen()%3;
    switch(RandNum){
        case 0: {
            this->AddAbility(Abilities::DoubleDamage);
            break;
        }
        case 1: {
            this->AddAbility(Abilities::Scanner);
            break;
        }
        case 2: {
            this->AddAbility(Abilities::Shelling);
            break;
        }
        default:
            break;
    }
}
void AbilityManager::UseAbility(Coord coord){
    Abilities ability = this->ability.front();
    if (coord.x == -1 && coord.y == -1) {
        (new ShellingAbilityCreator(this->map))->CreateAbility()->TakeAbility();
        this->ability.pop();
        return;
    }
    
    if (ability == Abilities::DoubleDamage) {
        (new DoubleDamageAbilityCreator(this->map, coord))->CreateAbility()->TakeAbility();
        this->ability.pop();
        return;
    }
    
    if (ability == Abilities::Scanner) {
        (new ScannerAbilityCreator(this->map, coord))->CreateAbility()->TakeAbility();
        this->ability.pop();
        return;
    }
}
void AbilityManager::PopAbility() {
    this->ability.pop();
}