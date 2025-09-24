#pragma once
#include "Entity.hpp"
#include <vector>
#include <string>

class Tournament
{
public:
    Tournament(const std::vector<Entity *> &participants);
    void runTournament();

private:
    std::vector<Entity *> participants;
};
