#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Players/Player.hpp"

namespace TAKEnhancedLibrary
{
    std::shared_ptr<Player> NewPlayer(const TAKCore::Player* rawPlayer);

    std::vector<std::shared_ptr<Player>> GetPlayers();
    std::shared_ptr<Player> GetCurrentPlayer();

    bool IsMe(int playerIndex);
    bool IsMe(std::shared_ptr<Player> player);
    bool IsEnemy(std::shared_ptr<Player> player);
    bool IsAlly(std::shared_ptr<Player> player);
    bool AreAllies(const std::shared_ptr<Player>& p1, const std::shared_ptr<Player>& p2);
    bool AreAllies(int p1, int p2);
    bool AreEnemies(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
    bool AreEnemies(int p1, int p2);
}
