#include "SpeciesComponent.hpp"

SpeciesComponent::SpeciesComponent(const std::string &speciesChar) : speciesChar(speciesChar) {}

std::string SpeciesComponent::getType() const
{
    return "Species";
}

const std::string &SpeciesComponent::getSpeciesChar() const
{
    return speciesChar;
}
