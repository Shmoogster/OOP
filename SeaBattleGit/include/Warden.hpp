#pragma once

class Warden {
    public:
        virtual void AbilityUsed() = 0;
        virtual void EndTurn() = 0;
        virtual void HumanWin() = 0;
        virtual void BotWin() = 0;
        virtual ~Warden() {};
};

template <class Output>
class OutputWarden : public Warden {
    private:
        Output& output;
        GameState& gameState;
    public:
        OutputWarden(Output& output, GameState& gameState) : output(output), gameState(gameState) {};

        void AbilityUsed() override {
            output.printString("Ability used.");
            output.printMaps(gameState.getBot().getMap(), gameState.getHuman().getMap());
            output.printAbilityNames(gameState.getHuman().getAbilityManager());
        }

        void EndTurn() override {
            output.printString("Turn ended.");
            output.printMaps(gameState.getBot().getMap(), gameState.getHuman().getMap());
        }

        void HumanWin() override {
            output.printString("Human wins.");
        }

        void BotWin() override {
            output.printString("Bot wins.");
        }
};