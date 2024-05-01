#include "TAKEnhancedLibrary/State.hpp"
#include "TAKEnhancedLibrary/Players/PlayerPool.hpp"

using namespace TAKEnhancedLibrary;

std::shared_ptr<Logger> TAKEnhancedLibrary::logger;

void TAKEnhancedLibrary::init(
    std::shared_ptr<Logger> logger
) {
    TAKEnhancedLibrary::logger = logger;
    TAKEnhancedLibrary::PlayerPool::init();
}
