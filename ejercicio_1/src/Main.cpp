#include <iostream>
#include "GameManager.hpp"

int main()
{
    std::cout << "MONSTER TOURNAMENT!!!\n";
    std::cout << "\n¡BATALLAS DE EXHIBICION!\n";
    GameManager::runGameMode(GameManager::Mode::Battle, "assets/batallas.txt", "resultados.txt");

    std::cout << "\n¡QUE EMPIECE EL TORNEO!\n";
    GameManager::runGameMode(GameManager::Mode::Tournament, "assets/torneo.txt", "resultados_torneo.txt");

    return 0;
}