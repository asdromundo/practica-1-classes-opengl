#pragma once
#include <string>

class Component
{
public:
    virtual ~Component() = default;
    virtual std::string getType() const = 0;
};
