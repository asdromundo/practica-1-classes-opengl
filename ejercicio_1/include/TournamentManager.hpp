#pragma once
#include "Entity.hpp"
#include "BattleManager.hpp"
#include <vector>
#include <string>

class TournamentManager
{
public:
    struct Round
    {
        std::vector<BattleManager::Battle> battles;
    };
    static std::vector<Round> runTournament(const std::vector<Entity *> &participants);

private:
    static std::vector<Entity *> conductRound(const std::vector<Entity *> &participants);
};
