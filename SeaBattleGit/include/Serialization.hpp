#pragma once

#include "ShipManager.hpp"
#include "Map.hpp"
#include "AbilityManager.hpp"

#include <string.h>
#include <nlohmann/json.hpp>

class Serialization {
    private:
        nlohmann::json& file;
    public:
        Serialization(nlohmann::json& file) : file(file) {};

        void to_json(ShipManager& shipmanager, std::string key);
        void to_json(Map& map, std::string key);
        void to_json(AbilityManager& abilitymanager, std::string key);
};