#include "../include/Hull.hpp"

Hull::Hull(const std::string& filename) : file(filename) {};

Hull::~Hull() {
    if (file.is_open())
        file.close();
}

void Hull::Read(nlohmann::json& j) {
    if (!file.is_open() || !file.good()) {
        throw UnableToOpenFileException();
    }
    file >> j;
}

void Hull::Write(nlohmann::json& j) {
    if (!file.is_open() || !file.good()) {
        throw UnableToOpenFileException();
    }
    file << j.dump(4);
}