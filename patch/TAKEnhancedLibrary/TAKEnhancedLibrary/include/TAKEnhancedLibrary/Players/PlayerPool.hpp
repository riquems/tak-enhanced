#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Players/Player.hpp"

namespace TAKEnhancedLibrary
{
    namespace PlayerPool
    {
        extern std::vector<std::shared_ptr<Player>> Instance;

        void init(int poolSize = 10);
        std::shared_ptr<Player> get_one();
    }
}
