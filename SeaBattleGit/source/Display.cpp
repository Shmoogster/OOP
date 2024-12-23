#include "../include/Display.hpp"

void Display::PrintException(std::exception& e) const {
    std::cerr << "\033[1;31m" <<  "Exception: " << e.what() << "\033[0m" << std::endl;
}

void Display::printAbilityName(std::string name) const {
    std::cout << name << std::endl;
}

void Display::printAbilityNames(AbilityManager abilityManager) const {
    for (int i = 0; i < abilityManager.GetAbilCount(); i++) {
        std::cout << abilityManager.getCreator(i).getTitle() << std::endl;
    }
}

void Display::printString(std::string data) const {
    std::cout << data << std::endl;
}


void Display::printShip(Ship ship) const {
    std::cout << "length: " << ship.getLength()  << std::endl;
    if (ship.CheckPosture()) {
        std::cout << "orientation: horizontal" << std::endl;
    } else {
        std::cout << "orientation: vertical" << std::endl;
    }
    std::cout << "Param health:" << std::endl;

    for (int i = 0; i < ship.getLength(); i++) {
        switch(ship.getParams(i)->health) {
            case HealthPosition::Fullhp:
                std::cout << "Untouched" << std::endl;
                break;
            case HealthPosition::Onehp:
                std::cout << "Damaged" << std::endl;
                break;
            case HealthPosition::Destroyed:
                std::cout << "Destroyed" << std::endl;
                break;
        }    
    }
}


void Display::printPointState(Map self, Coord coord) const {
    switch (self.GetMap()[coord.y*self.GetRows() + coord.x].state) {
        case PointState::TwoHp:
            std::cout << "\033[1;36m" << "S";
            break;
        case PointState::OneHp:
            std::cout << "\033[1;31m" << "X";
            break;
        case PointState::Dead:
            std::cout << "\033[1;30m" << "^";
            break;
        case PointState::Empty:
            std::cout << "\033[1;34m" << "~";
            break;
        case PointState::Missed:
            std::cout << "\033[1;37m" << "*";
            break;
    }
}

void Display::printMap(Map self) const {
    int rows = self.GetRows();
    int cols = self.GetCols();
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
        
    }

    std::cout << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[30m" << "+---";
    }

    std::cout << "\033[30m" << "+" << std::endl;
    for (int y = 0; y < rows; y++) {
        std::cout << "\033[30m" << "| ";
        for (int x = 0; x < cols; x++) {
            if (self.GetMap()[y*rows + x].owner == PointOwner::Revealed) {
                this->printPointState(self, {x, y});
            } else {
                std::cout << "\033[1;34m" << "~";
            }
            std::cout << "\033[30m" << " | ";
        }
        std::cout << "\033[0m" << y;
        std::cout << std::endl;
        for (int i = 0; i < rows; i++) {
            std::cout << "\033[30m" << "+---";
        }
        std::cout << "\033[30m" << "+" << std::endl;
    }
    std::cout << "\033[0m";
}

void Display::printMaps(Map self, Map other) const {
    int rows = self.GetRows();
    int cols = self.GetCols();
    std::cout << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
        
    }

    std::cout << "    ";
    for (int i = 0; i < rows; i++) {
        std::cout << "\033[0m" << "  " << i;
        if (i < 10) {
            std::cout << " ";
        }
        
    }

    std::cout << std::endl;
    for (int i = 0; i < rows * 2; i++) {
        if (i == rows) {
            std::cout << "+   ";
        }
        std::cout << "\033[1;30m" << "+---";
        
    }
    
    std::cout << "\033[30m" << "+" << std::endl;
    for (int y = 0; y < rows; y++) {
        std::cout << "\033[30m" << "| ";
        int ind = 0;
        for (int x = 0; x < cols*2; x++) {
            if (x < cols) {
                if (self.GetMap()[y*rows + x].owner == PointOwner::Revealed) {
                    this->printPointState(self, {x, y});
                } else {
                    std::cout << "\033[1;34m" << "~";
                }
            }
            
            if (x == cols) {
                std::cout << "\033[0m" << y;
                std::cout << "\033[30m" << " | ";
            }
            
            if (x >= cols) {
                if (other.GetMap()[(y-1)*other.GetRows() + ind].owner == PointOwner::Revealed) {
                    this->printPointState(other, {ind, y-1});
                } else {
                    std::cout << "\033[1;34m" << "~";
                }
            }
            ind++;
            std::cout << "\033[30m" << " | ";
        }
        
        std::cout << std::endl;
        for (int i = 0; i < rows*2; i++) {
            if (i == rows) {
                std::cout << "+   ";
            }
            std::cout << "\033[30m" << "+---";
        }
        std::cout << "\033[30m" << "+" << std::endl;
    }
    std::cout << "\033[0m" << std::endl;
}

void Display::printInfo() const {
    std::cout << "Push i to print info, a to attack, b to use ability, l to load, s to save, q to quit." << std::endl;
}

void Display::printCoordNeeded() const {
    std::cout << "Input coordinate." << std::endl;
}