#pragma once
#include "Component.hpp"

class AttributeComponent : public Component
{
public:
    AttributeComponent(int fuerza, int agilidad, int inteligencia);
    std::string getType() const override;
    int getFuerza() const;
    int getAgilidad() const;
    int getInteligencia() const;

private:
    int fuerza, agilidad, inteligencia;
};
