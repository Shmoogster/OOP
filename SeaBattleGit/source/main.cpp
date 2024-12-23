#include "../include/Game.hpp"
#include "../include/GameController.hpp"
#include "../include/PlayerInput.hpp"
#include "../include/Tuner.hpp"


int main() {
    Display display = Display();
    Map enemyMap = Map(10, 10);
    Map selfMap = Map(enemyMap);
    std::vector<int> shipSizes = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    try {
        for (auto& size : shipSizes) {
            if (size < 1 || size > 4) {
                throw InvalidShipSizeException();
            }
        }
    }
    catch (InvalidShipSizeException& e) {
        display.PrintException(e);
       return 0;
    }

    ShipManager enemyShips = ShipManager(shipSizes.size(), shipSizes);
    ShipManager selfShips = ShipManager(shipSizes.size(), shipSizes);
    
    try {
        for (size_t i = 0; i < shipSizes.size(); i++) {
            selfMap.PlaceShipRandom(&selfShips.getIndexShip(i));
            enemyMap.PlaceShipRandom(&enemyShips.getIndexShip(i));
        }
    }
    catch (UnableToPlaceShipsException& e) {
        display.PrintException(e);
        return 0;
    }

    selfMap.OpeningPoint();
    display.printMaps(selfMap, enemyMap);
    
    AbilityManager abilitymanager;
    Human human = Human(enemyShips, enemyMap, abilitymanager);
    Bot bot = Bot(selfShips, selfMap);
    GameState gameState = GameState(human, bot);
    Game game = Game(human, bot, gameState, display);
    
    PlayerInput playerInput = PlayerInput();
    Setup setup = Setup(playerInput);
    try {
        setup.deserializeSetup();
    } catch (std::exception& e) {
        display.PrintException(e);
    }

    OutputWarden<Display>* outputWarden = new OutputWarden<Display>(display, gameState);
    game.addWarden(outputWarden);

    GameController<PlayerInput, Display> gameController = GameController<PlayerInput, Display>(game, playerInput, display);
    gameController.Run();
    return 0;
}