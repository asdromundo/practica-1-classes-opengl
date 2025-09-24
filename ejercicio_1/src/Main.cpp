#include <iostream>
#include "GameManager.hpp"

int main()
{
    std::cout << "MONSTER TOURNAMENT!!!\n";

    GameManager::runGameMode(GameManager::Mode::Battle, "batallas.txt", "resultados.txt");
    GameManager::runGameMode(GameManager::Mode::Tournament, "torneo.txt", "resultados_torneo.txt");

    return 0;
}