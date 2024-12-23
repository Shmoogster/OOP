#include "../include/Serialization.hpp"
#include <fstream>

void Serialization::to_json(ShipManager& shipmanager, std::string key) {
    nlohmann::json jsm = nlohmann::json{};

    for (int i = 0; i < shipmanager.GetShipCount(); i++) {
        Ship& temp = shipmanager.getIndexShip(i);
        std::string key = "ship" + std::to_string(i);
        jsm[key] = {
            {"length", temp.getLength()},
            {"horizont", temp.CheckPosture()},
            {"params", nlohmann::json::array()}
        }; 

        for (int j = 0; j < temp.getLength(); j++) {
            ShipParams* tempShipParam = temp.getParams(j);
            jsm[key]["params"].push_back({
                {"x", tempShipParam->coord.x},
                {"y", tempShipParam->coord.y},
                {"health", tempShipParam->health}
            });
        }
    }

    file[key] = jsm;
}

void Serialization::to_json(Map& map, std::string key) {
    nlohmann::json jf = nlohmann::json{};

    jf["rows"] = map.GetRows();
    jf["cols"] = map.GetCols();

    std::vector<Point> temp = map.GetMap();
    for (int y = 0; y < map.GetRows(); y++) {
        for (int x = 0; x < map.GetCols(); x++) {
            std::string key = "point" + std::to_string(y) + std::to_string(x);
            jf[key] = {
                {"x", temp[y*map.GetRows() + x].coord.x},
                {"y", temp[y*map.GetRows() + x].coord.y},
                {"owner", temp[y*map.GetRows() + x].owner}, 
                {"state", temp[y*map.GetRows() + x].state} 
            };
        }
    }

    file[key] = jf;
}

void  Serialization::to_json(AbilityManager& abilitymanager, std::string key) {
    nlohmann::json jam = nlohmann::json{};

    for (int i = 0; i < abilitymanager.GetAbilCount(); i++) {
        jam["abilities"].push_back(
            abilitymanager.getCreator(i).getTitle()
        );
    }
    if (abilitymanager.GetAbilCount() == 0) {
        jam["abilities"].push_back("");
    }
    file[key] = jam;
}