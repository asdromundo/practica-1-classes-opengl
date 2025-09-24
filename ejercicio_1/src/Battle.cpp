#include "Battle.hpp"
#include "AttributeComponent.hpp"

std::string Battle::battleTypeToString(char type)
{
    switch (type)
    {
    case 'f':
        return "Física";
    case 'i':
        return "Ingenio";
    case 'e':
        return "Espiritual";
    default:
        return "Desconocida";
    }
}

Entity *Battle::fight(Entity *e1, Entity *e2, char battleType)
{
    AttributeComponent *attrs1 = e1->getComponent<AttributeComponent>();
    AttributeComponent *attrs2 = e2->getComponent<AttributeComponent>();
    if (!attrs1 || !attrs2)
        return nullptr;

    int puntos1 = 0, puntos2 = 0;
    int total1 = 0, total2 = 0;
    switch (battleType)
    {
    case 'f': // Física: fuerza + agilidad
        total1 = attrs1->getFuerza() + attrs1->getAgilidad();
        total2 = attrs2->getFuerza() + attrs2->getAgilidad();
        break;
    case 'i': // Ingenio: agilidad + inteligencia
        total1 = attrs1->getAgilidad() + attrs1->getInteligencia();
        total2 = attrs2->getAgilidad() + attrs2->getInteligencia();
        break;
    case 'e': // Espiritual: fuerza + inteligencia
        total1 = attrs1->getFuerza() + attrs1->getInteligencia();
        total2 = attrs2->getFuerza() + attrs2->getInteligencia();
        break;
    default:
        return nullptr;
    }

    // Simulación de 3 encuentros
    for (int i = 0; i < 3; ++i)
    {
        int sum = total1 + total2;
        int rand_val = rand() % sum;
        if (rand_val < total1)
            puntos1++;
        else
            puntos2++;
    }
    if (puntos1 > puntos2)
        return e1;
    else
        return e2;
}
