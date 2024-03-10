#include "TAKEnhancedDll/Changes/OffscreenFix.hpp"
#include "TAKEnhancedDll/GlobalState.hpp"
#include "Utils/Windows.hpp"
#include "TAKEnhancedDll/Wrappers/GameWrapper.h"
#include "TAKEnhancedDll/Wrappers/MatchWrapper.h"
#include <thread>
#include "TAKEnhancedLibrary/Units/Unit.hpp"
#include "TAKEnhancedLibrary/Players/Players.hpp"

/******************************************************************

    The Offscreen Fix is done by starting a monitor thread which
    monitors units, ensuring every unit doesn't surpass the top
    edge of the map.

*******************************************************************/

bool offscreenMonitorThreadRunning = false;

void startOffscreenMonitor()
{
    while (true) {
        if (!gameWrapper->match->isRunning()) {
            logger->info("Stopping OffScreen Monitor...");
            offscreenMonitorThreadRunning = false;
            return;
        }

        auto players = TAKEnhancedLibrary::GetPlayers();

        for (auto& player : players) {
            auto units = player->units();

            for (auto& unit : units) {
                if (unit->isInitialized()) {
                    if (unit->isFlying() && unit->getZpos() < unit->getYpos() * 0.55) {
                        unit->setZpos(50 + unit->getYpos() * 0.55);
                    }
                }
            }
        }

        Sleep(10);
    }
}

void startOffscreenMonitorThread()
{
    logger->info("Starting OffScreen Monitor...");
    std::thread offscreen_monitor_thread(startOffscreenMonitor);
    offscreen_monitor_thread.detach();

    offscreenMonitorThreadRunning = true;
}
