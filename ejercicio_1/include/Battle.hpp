#pragma once
#include "Entity.hpp"
#include <string>

class Battle
{
public:
    static std::string battleTypeToString(char type);
    static Entity *fight(Entity *e1, Entity *e2, char battleType);
};
