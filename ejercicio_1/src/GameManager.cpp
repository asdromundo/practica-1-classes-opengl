#include "GameManager.hpp"
#include "Entity.hpp"
#include "SpeciesComponent.hpp"
#include "AttributeComponent.hpp"
#include "Battle.hpp"
#include "Tournament.hpp"
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
            Entity *ganador = Battle::fight(&e1, &e2, tipoBatalla);
            std::ostringstream oss;
            oss << nombre1 << " vs " << nombre2 << " → Gana " << ganador->getName();
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
        Tournament torneo(participantes);
        torneo.runTournament();
        // Para simplificar, no se guardan los resultados de cada ronda aquí
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
