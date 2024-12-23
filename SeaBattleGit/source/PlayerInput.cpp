#include "../include/PlayerInput.hpp"


PlayerInput::PlayerInput() {
    this->commands = {
        {'i', Commander::info},
        {'a', Commander::attack},
        {'b', Commander::ability},
        {'l', Commander::load},
        {'s', Commander::save},
        {'q', Commander::quit}
    };
}

void PlayerInput::SetCommands(std::map <char, Commander> newCommands) {
    this->commands = newCommands;
} 

Commander PlayerInput::CommandInput() {
    std::string line;
    std::cin >> line;
    if (line.size() == 1 && this->commands.find(line[0]) != this->commands.end()) {
        return this->commands[line[0]];
    }
    return Commander::info;
}

Coord PlayerInput::CoordInput() {
    int x, y;
    while (true) {
        std::cin >> x >> y;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    return Coord{x, y};
}