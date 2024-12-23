#include "../include/AbilityManager.hpp"

AbilityManager::AbilityManager() {
    std::vector<AbilityCreator*> vec = {new DoubleDamageAbilityCreator(), new ScannerAbilityCreator() ,new ShellingAbilityCreator()};
    std::random_device RD;
    std::mt19937 gen(RD());
    std::shuffle(vec.begin(), vec.end(), gen);
    this->ability.push(vec[0]);
}
AbilityManager::~AbilityManager() {
    while (!this->ability.empty()) {
        this->ability.pop();
    }
}

int AbilityManager::GetAbilCount() const {
    return this->ability.size();
}

void AbilityManager::IfEmpty(){
    if(ability.empty()){
        throw NoAbilitiesAvailableException();
    }
}
void AbilityManager::AddAbility(AbilityCreator *create){
    this->ability.push(create);
}
void AbilityManager::RandomizeAbility(){
    std::random_device RD;
    std::mt19937 gen(RD());
    int RandNum=gen()%3;
    switch(RandNum){
        case 0: {
            this->AddAbility(new DoubleDamageAbilityCreator());
            break;
        }
        case 1: {
            this->AddAbility(new ScannerAbilityCreator());
            break;
        }
        case 2: {
            this->AddAbility(new ShellingAbilityCreator());
            break;
        }
        default:
            break;
    }
}
void AbilityManager::UseAbility(AbilityParams& abilpar){
    this->IfEmpty();
    AbilityCreator* createdAbility = this->ability.front();
    createdAbility->CreateAbility(abilpar)->TakeAbility();
    delete(createdAbility);
    this->ability.pop();
}
void AbilityManager::PopAbility() {
    this->ability.pop();
}

AbilityCreator& AbilityManager::getCreator(int index){
    IfEmpty();
    std::queue<AbilityCreator*> buf= this->ability;
    for (int i=0; i<index; i++){
        buf.pop();
    }
    return *buf.front();
}