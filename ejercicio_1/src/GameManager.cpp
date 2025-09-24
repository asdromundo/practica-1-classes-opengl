#include "GameManager.hpp"
#include "Entity.hpp"
#include "SpeciesComponent.hpp"
#include "AttributeComponent.hpp"
#include "BattleManager.hpp"
#include "TournamentManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

GameManager::GameManager(Mode mode) : mode(mode) {}

void GameManager::read(const std::string &inputFile)
{
    results.clear();
    switch (mode)
    {
    case Mode::Battle:
    {
        std::ifstream fin(inputFile);
        std::string line;
        while (std::getline(fin, line))
        {
            std::istringstream iss(line);
            std::string tipo1, nombre1, tipo2, nombre2;
            int f1, a1, i1, f2, a2, i2;
            char tipoBatalla;
            iss >> tipo1 >> nombre1 >> f1 >> a1 >> i1 >> tipo2 >> nombre2 >> f2 >> a2 >> i2 >> tipoBatalla;
            Entity e1(nombre1);
            e1.addComponent(std::make_shared<SpeciesComponent>(tipo1));
            e1.addComponent(std::make_shared<AttributeComponent>(f1, a1, i1));
            Entity e2(nombre2);
            e2.addComponent(std::make_shared<SpeciesComponent>(tipo2));
            e2.addComponent(std::make_shared<AttributeComponent>(f2, a2, i2));
            BattleManager::Battle result = BattleManager::fight(&e1, &e2, static_cast<BattleManager::EncounterType>(tipoBatalla));
            Entity *ganador = result.winner;
            std::ostringstream oss;
            oss << "--- Batalla " << BattleManager::encounterTypeToString(result.type) << " ---\n";
            for (size_t j = 0; j < result.results.size(); ++j)
            {
                oss << "Encuentro " << (j + 1) << ": " << result.results[j]->getName() << " gana\n";
            }
            oss << "Ganador de la batalla: " << ganador->getName();
            results.push_back({oss.str()});
        }
    }
    break;
    case Mode::Tournament:
    {
        std::ifstream fin(inputFile);
        std::string line;
        std::vector<Entity *> participantes;
        std::vector<std::unique_ptr<Entity>> entidades;
        while (std::getline(fin, line))
        {
            std::istringstream iss(line);
            std::string tipo, nombre;
            int f, a, i;
            iss >> tipo >> nombre >> f >> a >> i;
            entidades.push_back(std::make_unique<Entity>(nombre));
            entidades.back()->addComponent(std::make_shared<SpeciesComponent>(tipo));
            entidades.back()->addComponent(std::make_shared<AttributeComponent>(f, a, i));
            participantes.push_back(entidades.back().get());
        }
        std::ostringstream oss;
        oss << "\nTorneo iniciado con " << participantes.size() << " participantes\n";
        std::vector<TournamentManager::Round> rounds = TournamentManager::runTournament(participantes);

        for (const auto &round : rounds)
        {
            std::string ronda_info;
            switch (round.battles.size())
            {
            case 1:
                ronda_info = "Final";
                break;
            case 2:
                ronda_info = "Semifinales";
                break;
            default:
                ronda_info = "1/" + std::to_string(round.battles.size()) + " de final";
                break;
            }
            oss << "--- " << ronda_info << " ---\n";
            for (const auto &battle : round.battles)
            {
                oss << battle.e1->getComponent<SpeciesComponent>()->getSpeciesChar() << " " << battle.e1->getName() << " vs " << battle.e2->getComponent<SpeciesComponent>()->getSpeciesChar() << " " << battle.e2->getName() << " - Ganador: " << battle.winner->getName() << "\n";
            }
        }

        oss << "Campeón del torneo: " << rounds.back().battles.front().winner->getName();
        results.push_back({oss.str()});
        results.push_back({"Torneo finalizado"});
    }
    break;

    default:
        break;
    }
}

std::vector<GameManager::BattleResult> GameManager::getResults() const
{
    return results;
}

void GameManager::save(const BattleResult &result, const std::string &outputFile) const
{
    std::ofstream fout(outputFile, std::ios::app);
    fout << result.result << std::endl;
}

void GameManager::runGameMode(GameManager::Mode mode, const std::string &inputFile, const std::string &outputFile)
{
    GameManager manager(mode);
    manager.read(inputFile);
    std::vector<GameManager::BattleResult> results = manager.getResults();
    std::ofstream clearFile(outputFile, std::ios::trunc);
    clearFile.close();
    for (const auto &result : results)
    {
        std::cout << result << std::endl;
        manager.save(result, outputFile);
    }
}