#include "../include/Game.hpp"

void Game::useHumanAbility() {
    for(const auto& wardn: this-> warden){
        wardn->AbilityUsed();
    }
    Coord coord = {-1, -1};
    AbilityParams ap(human.getMap(), human.getShipManager(), coord, gameState.getCurDamage());
    human.getAbilityManager().IfEmpty();
    if (human.getAbilityManager().getCreator(0).isUseCoord()){
        ap.coord = gameState.getCoord();
    }
    human.getAbilityManager().UseAbility(ap);
    this->gameState.setAbilityUsed(true);
}

void Game::HumanAttack() {
    int successAttack = false;
    while (!successAttack) {
        try {
            for (int i = 0; i < gameState.getCurDamage(); i++) {
                human.getMap().Attack(gameState.getCoord());
                successAttack = true;
            }
        }
        catch (RevealedPointAttackException& e) {
            if (successAttack) {
                break;
            }
            throw RevealedPointAttackException();
        }
        break;
    }
    this->gameState.setCurDamage(1);

    Ship* enemyShip = human.getShipManager().GetShip(gameState.getCoord());
    if (enemyShip != nullptr && enemyShip->isDestroyed()) {
        human.getMap().OpeningCoordsAround(enemyShip);
        human.getShipManager().setShipsAlive(human.getShipManager().getShipsAlive() - 1); 
        std::cout << "Ability added." << std::endl;
        human.getAbilityManager().RandomizeAbility();
    }
    if (human.getShipManager().getShipsAlive() == 0) {
        for(const auto& wardn : this->warden){
            wardn->HumanWin();
        }
        this->resetBot();
    }
    this->gameState.setAbilityUsed(false);
}

void Game::BotAttack() {
    Coord coord = bot.getMap().AttackRandom();
    Ship* selfShip = bot.getShipManager().GetShip(coord);
    if (selfShip != nullptr && selfShip->isDestroyed()) {
        bot.getMap().OpeningCoordsAround(selfShip);
        bot.getShipManager().setShipsAlive(bot.getShipManager().getShipsAlive() - 1);
    }

    for(const auto& wardn : this->warden){
        wardn->EndTurn();
    }

    if (bot.getShipManager().getShipsAlive() == 0) {
        for(const auto& wardn : this->warden){
            wardn->BotWin();
        }
        this->resetGame();
    }
}

void Game::resetBot() {
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    Map newMap = Map(10, 10);
    ShipManager newShips = ShipManager(10, shipSizes);
    for (size_t i = 0; i < shipSizes.size(); i++) {
        newMap.PlaceShipRandom(&newShips.getIndexShip(i));
    }
    this->human = Human(newShips, newMap, human.getAbilityManager());
}

void Game::resetGame() {
    resetBot();
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    
    Map newMap = Map(10, 10);
    ShipManager newShips = ShipManager(10, shipSizes);
    for (size_t i = 0; i < shipSizes.size(); i++) {
        newMap.PlaceShipRandom(&newShips.getIndexShip(i));
    }
    newMap.OpeningPoint();
    this->bot = Bot(newShips, newMap);
}

void Game::addWarden(Warden* wardn){
    this->warden.push_back(wardn);
}

void Game::LoadGame() {
    try {
        this->gameState.LoadGame();
    } catch (nlohmann::json::exception& e) {
        std::cerr << "\033[1;31m" << "Error parsing JSON: " << e.what() << "\033[0m" << std::endl;
       return;
    } catch (HashMismatchException& e) {
        display.PrintException(e);
    }
}

void Game::SaveGame() {
    this->gameState.SaveGame();
}   