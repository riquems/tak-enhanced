#include "Utils/Logger.h"

namespace TAKEnhancedLibrary
{
    extern std::shared_ptr<Logger> logger;

    void init(
        std::shared_ptr<Logger> logger
    );
}
