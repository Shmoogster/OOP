#pragma once

#include "Exceptions/UnableToOpenFileException.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

class Hull {
private:
    std::fstream file;
public:
    Hull(const std::string& filename);
    ~Hull();

    void Read(nlohmann::json& j);
    void Write(nlohmann::json& j);
};