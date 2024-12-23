#include "../include/GameState.hpp"

std::string GameState::getHash(const std::string& data){
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(data);
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}


Hull& operator<<(Hull& fileHull, GameState& state) {
    nlohmann::json file;
    nlohmann::json data;
    Serialization seri(data);

    seri.to_json(state.getHuman().getShipManager(), "humanShipManager");
    seri.to_json(state.getHuman().getMap(), "humanMap");
    seri.to_json(state.getHuman().getAbilityManager(), "humanAbilityManager");
    seri.to_json(state.getBot().getShipManager(), "botShipManager");
    seri.to_json(state.getBot().getMap(), "botMap");
    data["currentDamage"] = state.getCurDamage();
    data["AbilityUsed"] = state.getAbilityUsed();

    std::string jsonString = data.dump();

    file["data"] = data;
    file["hashValue"] = state.getHash(jsonString);

    try {
        fileHull.Write(file);
    }
    catch (UnableToOpenFileException& e){
        std::cerr << e.what() << std::endl;
    }
    
    return fileHull;
}

Hull& operator>>(Hull& fileHull, GameState& state) {
    nlohmann::json file;
    
    try {
        fileHull.Read(file);
    }
    catch (UnableToOpenFileException& e) {
        std::cerr << e.what() << std::endl;
        return fileHull;
    }

    nlohmann::json data = file.at("data");

    std::string savedHashValue = file.at("hashValue");
    std::string jsonString = data.dump();
    if (savedHashValue != state.getHash(jsonString)) {
        throw HashMismatchException();
    }

    Deserialization deseri(data);
    ShipManager shipmanager;
    Map map;
    AbilityManager abilitymanager;

    ShipManager enemyShipManager;
    Map enemyMap;

    deseri.from_json(shipmanager, "humanShipManager");
    deseri.from_json(map, "humanMap");
    deseri.from_json(abilitymanager, "humanAbilityManager");
    deseri.from_json(enemyShipManager, "botShipManager");
    deseri.from_json(enemyMap, "botMap");

    state.setCurDamage(data.at("currentDamage"));
    state.setAbilityUsed(data.at("AbilityUsed"));

    state.getHuman().getShipManager() = shipmanager;
    state.getHuman().getMap() = map;
    state.getHuman().getAbilityManager() = abilitymanager;
    state.getBot().getShipManager() = enemyShipManager;
    state.getBot().getMap() = enemyMap;

    state.placeShips(state.getHuman().getShipManager(), state.getHuman().getMap());
    state.placeShips(state.getBot().getShipManager(), state.getBot().getMap());

    return fileHull;
}

void GameState::placeShips(ShipManager& shipmanager, Map& map) {
    for (int i = 0; i < shipmanager.GetShipCount(); i++) {
        for (int j = 0; j < shipmanager.getIndexShip(i).getLength(); j++) {
            Coord coord = shipmanager.getIndexShip(i).getParams(j)->coord;
            auto& cell = map.GetPoint(coord);
            cell.param = shipmanager.getIndexShip(i).getParams(j);
        }
    }
}

void GameState::LoadGame() {
    Hull fileHull("/home/shmooga/SeaBattleGit/.vscode/settings.json");
    fileHull >> *this;
}

void GameState::SaveGame() {
    std::ofstream ofs("/home/shmooga/SeaBattleGit/.vscode/settings.json", std::ofstream::out | std::ofstream::trunc);
    Hull fileHull("/home/shmooga/SeaBattleGit/.vscode/settings.json");
    fileHull << *this;
}