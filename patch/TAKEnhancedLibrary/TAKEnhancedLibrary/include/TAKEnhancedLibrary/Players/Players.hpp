#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Players/Player.hpp"

namespace TAKEnhancedLibrary
{
    std::vector<std::shared_ptr<Player>> GetPlayers();
    std::shared_ptr<Player> GetCurrentPlayer();

    bool IsMe(std::shared_ptr<Player> player);
    bool IsEnemy(std::shared_ptr<Player> player);
    bool IsAlly(std::shared_ptr<Player> player);
    bool AreAllies(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
    bool AreAllies(int p1, int p2);
    bool AreEnemies(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
    bool AreEnemies(int p1, int p2);
}
