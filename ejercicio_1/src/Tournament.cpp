#include "Tournament.hpp"
#include "Battle.hpp"
#include <iostream>

Tournament::Tournament(const std::vector<Entity *> &participants)
{
    this->participants = participants;
}

void Tournament::runTournament()
{
    std::vector<Entity *> ronda = participants;
    int ronda_num = 1;
    while (ronda.size() > 1)
    {
        std::vector<Entity *> ganadores;
        std::cout << "--- Ronda " << ronda_num << " ---\n";
        for (size_t i = 0; i < ronda.size(); i += 2)
        {
            Entity *e1 = ronda[i];
            Entity *e2 = ronda[i + 1];
            char tipos[3] = {'f', 'i', 'e'};
            char tipo = tipos[rand() % 3];
            Entity *ganador = Battle::fight(e1, e2, tipo);
            std::cout << e1->getName() << " vs " << e2->getName() << " → Gana " << ganador->getName() << "\n";
            ganadores.push_back(ganador);
        }
        ronda = ganadores;
        ronda_num++;
    }
    std::cout << "Campeón: " << ronda[0]->getName() << std::endl;
}
