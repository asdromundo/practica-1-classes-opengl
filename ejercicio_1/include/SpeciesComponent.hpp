#pragma once
#include "Component.hpp"

class SpeciesComponent : public Component
{
public:
    SpeciesComponent(const std::string &speciesChar);
    std::string getType() const override;
    const std::string &getSpeciesChar() const;

private:
    std::string speciesChar;
};
