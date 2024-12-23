#pragma once

#include "ShipManager.hpp"
#include "Map.hpp"
#include "AbilityManager.hpp"
#include "Commander.hpp"

#include <string.h>
#include <map>
#include <nlohmann/json.hpp>

class Deserialization {
    private:
        nlohmann::json& file;
    public:
        Deserialization(nlohmann::json& file) : file(file) {};

        void from_json(ShipManager& shipmanager, std::string key);
        void from_json(Map& map, std::string key);
        void from_json(AbilityManager& abilitymanager, std::string key);
        void from_json(std::map<char, Commander>& newCommands);
};