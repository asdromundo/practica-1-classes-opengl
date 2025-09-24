#include "AttributeComponent.hpp"

AttributeComponent::AttributeComponent(int fuerza, int agilidad, int inteligencia)
    : fuerza(fuerza), agilidad(agilidad), inteligencia(inteligencia) {}

std::string AttributeComponent::getType() const
{
    return "Attribute";
}

int AttributeComponent::getFuerza() const { return fuerza; }
int AttributeComponent::getAgilidad() const { return agilidad; }
int AttributeComponent::getInteligencia() const { return inteligencia; }
