#include <iostream>
#include "GameManager.hpp"

void runGameMode(GameManager::Mode mode, const std::string &inputFile, const std::string &outputFile);

int main()
{
    std::cout << "MONSTER TOURNAMENT!!!\n";

    runGameMode(GameManager::Mode::Battle, "batallas.txt", "resultados.txt");
    runGameMode(GameManager::Mode::Tournament, "torneo.txt", "resultados_torneo.txt");
}

void runGameMode(GameManager::Mode mode, const std::string &inputFile, const std::string &outputFile)
{
    GameManager manager(mode);
    manager.read(inputFile);
    std::vector<GameManager::BattleResult> results = manager.getResults();
    for (const auto &result : results)
    {
        std::cout << result << std::endl;
        manager.save(result, outputFile);
    }
}
