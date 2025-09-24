#include "BattleManager.hpp"
#include "AttributeComponent.hpp"

std::string BattleManager::encounterTypeToString(EncounterType type)
{
    switch (type)
    {
    case EncounterType::Física:
        return "Física";
    case EncounterType::Ingenio:
        return "Ingenio";
    case EncounterType::Espiritual:
        return "Espiritual";
    default:
        return "Desconocida";
    }
}

BattleManager::Battle BattleManager::fight(Entity *e1, Entity *e2, EncounterType battleType)
{
    AttributeComponent *attrs1 = e1->getComponent<AttributeComponent>();
    AttributeComponent *attrs2 = e2->getComponent<AttributeComponent>();
    if (!attrs1 || !attrs2)
        return {};

    int puntos1 = 0, puntos2 = 0;
    int total1 = 0, total2 = 0;
    switch (battleType)
    {
    case EncounterType::Física: // Física: fuerza + agilidad
        total1 = attrs1->getFuerza() + attrs1->getAgilidad();
        total2 = attrs2->getFuerza() + attrs2->getAgilidad();
        break;
    case EncounterType::Ingenio: // Ingenio: agilidad + inteligencia
        total1 = attrs1->getAgilidad() + attrs1->getInteligencia();
        total2 = attrs2->getAgilidad() + attrs2->getInteligencia();
        break;
    case EncounterType::Espiritual: // Espiritual: fuerza + inteligencia
        total1 = attrs1->getFuerza() + attrs1->getInteligencia();
        total2 = attrs2->getFuerza() + attrs2->getInteligencia();
        break;
    default:
        return {};
    }

    std::vector<Entity *> results;

    // Simulación de 3 encuentros
    for (int i = 0; i < 3; ++i)
    {
        int sum = total1 + total2;
        int rand_val = rand() % sum;
        if (rand_val < total1)
        {
            puntos1++;
            results.push_back(e1);
        }
        else
        {
            puntos2++;
            results.push_back(e2);
        }
    }

    Entity *winner;

    if (puntos1 > puntos2)
        winner = e1;
    else
        winner = e2;

    return {e1, e2, battleType, results, winner};
}
