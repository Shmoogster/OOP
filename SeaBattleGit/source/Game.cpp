#include "../include/Game.hpp"

void Game::StartGame() {
    Display display;
    Map enemyMap = Map(10, 10);
    Map ourMap = Map(enemyMap);
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    try {
        for (auto& size : shipSizes) {
            if (size < 0 || size > 4) {
                throw InvalidShipSizeException();
            }
        }
    }
    catch (InvalidShipSizeException& e) {
        display.PrintException(e);
        return;
    }
    ShipManager* enemyShips = new ShipManager(10, shipSizes);
    ShipManager* selfShips = new ShipManager(10, shipSizes);
    
    try {
        enemyMap.initMap(enemyShips->getShips());
        ourMap.initMap(selfShips->getShips());
    }
    catch (UnableToPlaceShipsException& e) {
        display.PrintException(e);
        return;
    }
    ourMap.OpeningPoint();
    display.printMaps(ourMap, enemyMap);
    AbilityManager am(enemyMap);
    while (true) {
        int x, y;
        std::cout << "You have " << am.GetAbilCount() << " abilities available." << std::endl;
        std::cout << "Use random ability? 'y'" << std::endl;
        std::string result;
        std::cin >> result;
        if (result == "y" || result == "Y") {
            try {
                am.IfEmpty();
            }
            catch (NoAbilitiesAvailableException& e) {
                display.PrintException(e);
                continue;
            }
            Abilities name = am.Front();
            display.printAbilityName(name);
            x = y = 0;
            try {
                if (name == Abilities::DoubleDamage || name == Abilities::Scanner) {
                    std::cout << "Give coordinates for ability." << std::endl;
                    std::cin >> x >> y;
                    am.UseAbility({x, y});
                }
                else {
                    am.UseAbility();
                }
            }
            catch (RevealedPointAttackException& e) {
                am.PopAbility();
            }
            catch (OutOfRangeException& e) {
                display.PrintException(e);
                continue;
            }
            
            if (name == Abilities::DoubleDamage) {
                Ship* enemyShip = enemyShips->GetShip({x, y});
                if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
                    enemyMap.OpeningCoordsAround(enemyShip);
                    enemyShips->SetShipCount(enemyShips->GetShipCount() - 1);
                    
                    std::cout << "Ability added." << std::endl;
                    am.RandomizeAbility();
                }
            }
            display.printMaps(ourMap, enemyMap);
        }
        
        while (true) {
            try {
                std::cin >> x >> y;
                enemyMap.Attack({x, y});
            }
            catch (RevealedPointAttackException& e) {
                display.PrintException(e);
                continue;
            }
            catch (OutOfRangeException& e) {
                display.PrintException(e);
                continue;
            }
            break;
        }
        
        Ship* enemyShip = enemyShips->GetShip({x, y});
        if (enemyShip->getLength() != 0 && enemyShip->isDestroyed()) {
            enemyMap.OpeningCoordsAround(enemyShip);
            enemyShips->SetShipCount(enemyShips->GetShipCount() - 1);
            
            std::cout << "Ability added." << std::endl;
            am.RandomizeAbility();
            if (enemyShips->GetShipCount() == 0) {
                std::cout << "You win!" << std::endl;
                break;
            }
        }
        Coord coords = {-1, -1};
        try {
            coords = ourMap.AttackRandom();
        }
        catch (MultipleMissesException& e) {
            display.PrintException(e);
            continue;
        }
        Ship* selfShip = selfShips->GetShip(coords);
        if (selfShip->getLength() != 0 && selfShip->isDestroyed()) {
            ourMap.OpeningCoordsAround(selfShip);
            selfShips->SetShipCount(selfShips->GetShipCount() - 1);
            if (selfShips->GetShipCount() == 0) {
                std::cout << "You lose!" << std::endl;
                break;
            }
        }
        display.printMaps(ourMap, enemyMap);
    }
}