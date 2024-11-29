#pragma once

#include <exception>

class RevealedPointAttackException : public std::exception {
    public:
        const char* what() const noexcept override { return "Attempt to attack already revealed point!"; }
};