#include "TournamentManager.hpp"
#include "BattleManager.hpp"
#include <iostream>

std::vector<TournamentManager::Round> TournamentManager::runTournament(const std::vector<Entity *> &participants)
{
    std::vector<Entity *> ronda = participants;
    int ronda_num = 1;
    std::vector<Round> rounds;
    while (ronda.size() > 1)
    {
        Round round;
        std::vector<Entity *> ganadores;
        // std::cout << "--- Ronda " << ronda_num << " ---\n";
        for (size_t i = 0; i < ronda.size(); i += 2)
        {
            Entity *e1 = ronda[i];
            Entity *e2 = ronda[i + 1];

            static const BattleManager::EncounterType opciones[] = {
                BattleManager::EncounterType::Física,
                BattleManager::EncounterType::Espiritual,
                BattleManager::EncounterType::Ingenio};
            BattleManager::EncounterType tipo = opciones[std::rand() % (sizeof(opciones) / sizeof(opciones[0]))];
            BattleManager::Battle resultado = BattleManager::fight(e1, e2, tipo);
            Entity *ganador = resultado.winner;
            // std::cout << e1->getName() << " vs " << e2->getName() << " → Gana " << ganador->getName() << "\n";
            round.battles.push_back(resultado);
            ganadores.push_back(ganador);
        }
        ronda = ganadores;
        ronda_num++;
        rounds.push_back(round);
    }
    // std::cout << "Campeón: " << ronda[0]->getName() << std::endl;
    return rounds;
}
