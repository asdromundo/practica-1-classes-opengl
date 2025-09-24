#pragma once
#include "Entity.hpp"
#include <string>
#include <vector>

class BattleManager
{
public:
    enum class EncounterType : char
    {
        Física = 'f',
        Ingenio = 'i',
        Espiritual = 'e'
    };
    struct Battle
    {
        Entity *e1 = nullptr;
        Entity *e2 = nullptr;
        EncounterType type;
        std::vector<Entity *> results;
        Entity *winner;
    };

    static std::string encounterTypeToString(EncounterType);
    static Battle fight(Entity *e1, Entity *e2, EncounterType encounter);
};
