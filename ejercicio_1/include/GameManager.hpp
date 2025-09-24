#pragma once
#include <string>
#include <vector>

class GameManager
{
public:
    enum class Mode
    {
        Battle,
        Tournament
    };
    struct BattleResult
    {
        std::string result;
    };
    GameManager(Mode mode);
    void read(const std::string &inputFile);
    std::vector<BattleResult> getResults() const;
    void save(const BattleResult &result, const std::string &outputFile) const;

private:
    Mode mode;
    std::vector<BattleResult> results;
};

// Sobrecarga del operador << para BattleResult (print)
inline std::ostream &operator<<(std::ostream &os, const GameManager::BattleResult &br)
{
    os << br.result;
    return os;
}
