#pragma once

#include "Game.hpp"
#include "PlayerInput.hpp"

template <class Input, class Output>
class GameController {
    private:
        Game& game;
        Input& input;
        Output& output;
    public:
        GameController(Game& game, Input& input, Output& output): game(game), input(input), output(output) {};
        void Run() {
            Commander commander = Commander::info;
            while (commander != Commander::quit) {
                switch (commander) {
                    case Commander::info:
                        output.printInfo();
                        break;

                    case Commander::attack:
                        output.printMaps(game.getGameState().getBot().getMap(), game.getGameState().getHuman().getMap());
                        attackCycle();
                        break;

                    case Commander::ability:
                        try {
                            if (game.getGameState().getHuman().getAbilityManager().getCreator(0).isUseCoord()) {
                                output.printAbilityName(game.getGameState().getHuman().getAbilityManager().getCreator(0).getTitle());
                                output.printCoordNeeded();
                                game.getGameState().setCoord(input.CoordInput());
                            }
                            game.useHumanAbility();
                        } catch (std::exception& e) {
                            output.PrintException(e);
                            break;
                        }
                        
                        attackCycle();
                        break;

                    case Commander::load:
                        output.printString("Loading the game.");
                        game.LoadGame();
                        break;

                    case Commander::save:
                        output.printString("Saving the game.");
                        game.SaveGame();
                        break;

                    default:
                        output.printString("Unknown command.");
                        break;
                }
                if (commander != Commander::info) {
                    output.printInfo();
                }
                commander = input.CommandInput();
            }
        }

        void attackCycle() {
            output.printCoordNeeded();
            while (true) {
                try {
                    game.getGameState().setCoord(input.CoordInput());
                    game.HumanAttack();
                }
                catch (RevealedPointAttackException& e) {
                    output.PrintException(e);
                    continue;
                }
                catch (OutOfRangeException& e) {
                    output.PrintException(e);
                    continue;
                }
                break;
            }
            game.BotAttack();
        }
};