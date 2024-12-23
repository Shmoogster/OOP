#include "../include/Deserialization.hpp"

void Deserialization::from_json(ShipManager& shipmanager, std::string key) {
    const auto& jsm = file.at(key);
    std::vector<int> shipSizes;

    for (const auto& jship : jsm) {
        shipSizes.push_back(jship.at("length"));
    }
    shipmanager = ShipManager(shipSizes.size(), shipSizes);

    for (size_t i = 0; i < shipSizes.size(); i++) {
        std::string key = "ship" + std::to_string(i);
        Ship& ship = shipmanager.getIndexShip(i);
        if (jsm.at(key).at("horizont") == true) {
            ship.SetPosture(Posture::Horizont);
        }
        else {
            ship.SetPosture(Posture::Vertic);
        }

        for (int j = 0; j < shipSizes[i]; j++) {
            ShipParams* param = ship.getParams(j);

            param->health = jsm.at(key).at("params").at(j).at("health");
            param->coord.x = jsm.at(key).at("params").at(j).at("x");
            param->coord.y = jsm.at(key).at("params").at(j).at("y");
        }
    }
}

void Deserialization::from_json(Map& map, std::string key) {
    const auto& jf = file.at(key);
    map = Map(jf.at("rows"), jf.at("cols"));

    for (int y = 0; y < map.GetRows(); y++) {
        for (int x = 0; x < map.GetCols(); x++) {
            std::string key = "point" + std::to_string(y) + std::to_string(x);
            Point& point = map.GetPoint({x, y});
            point.coord.x = jf.at(key).at("x");
            point.coord.y = jf.at(key).at("y");
            point.owner = jf.at(key).at("owner");
            point.state = jf.at(key).at("state");
        }
    }
}

void Deserialization::from_json(AbilityManager& abilitymanager, std::string key) {
    const auto& jam = file.at(key);
    abilitymanager = AbilityManager();
    abilitymanager.PopAbility();
    
    for (const auto& jability : jam.at("abilities")) {
       if (jability == "Double Damage") {
           abilitymanager.AddAbility(new DoubleDamageAbilityCreator());
       }
       else if(jability == "Scanner"){
           abilitymanager.AddAbility(new ScannerAbilityCreator());
       }
       else if (jability == "Shelling") {
           abilitymanager.AddAbility(new ShellingAbilityCreator());
       }
    }
}

void Deserialization::from_json(std::map<char, Commander>& newCommands) {
    const auto& j = file.at("commands");
    std::vector<int> values;

    for (const auto& pair : j.items()) {
        std::string key = pair.key();
        if (key.size() != 1) {
            throw std::invalid_argument("Invalid key.");
        }

        int value = pair.value();
        if (value < 0 || value > 5) {
            throw std::invalid_argument("Too many or too few commands");
        }
        values.push_back(value);
        newCommands[key[0]] = static_cast<Commander>(value);
    }

    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = i + 1; j < values.size(); j++) {
            if (values[i] == values[j]) {
                throw std::invalid_argument("Duplicates in command.");
            }
        }
    }

    if (values.size() != 6) {
        throw std::invalid_argument("Incorrect number of commands.");
    }
}