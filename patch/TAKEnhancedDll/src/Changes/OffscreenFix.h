#pragma once
#include "Context.h"
#include "GameFunctions.h"

/******************************************************************

    The Offscreen Fix is done by starting a monitor thread which
    monitors units, ensuring every unit doesn't surpass the top
    edge of the map.

*******************************************************************/

bool is_offscreen_monitor_thread_running = false;

void startOffscreenMonitor()
{
    if (game.players.empty()) {
        throw std::exception("Players Wrappers array is empty.                                   \
                              It must be initialized in order to use the offscreen functionality!");
    }

    while (true) {
        for (int i = 0; i < game.players.size(); i++) {
            for (int j = 0; j < game.players[i].units.size(); j++) {
                PlayerWrapper player = game.players[i];
                
                if (!game.match->isRunning()) {
                    std::cout << "Stopping OffScreen Monitor..." << std::endl;
                    is_offscreen_monitor_thread_running = false;
                    return;
                }

                UnitWrapper unit = player.units[j];

                if (unit.isInitialized()) {
                    if (unit.isFlying() && unit.getZpos() < unit.getYpos() * 0.55) {
                        unit.setZpos(50 + unit.getYpos() * 0.55);
                    }
                }
            }
        }

        Sleep(10);
    }
}

void startOffscreenMonitorThread()
{
    if (is_offscreen_monitor_thread_running)
        return;

    game.refreshPlayersWrappers();

    std::cout << "Starting OffScreen Monitor..." << std::endl;
    std::thread offscreen_monitor_thread(startOffscreenMonitor);
    offscreen_monitor_thread.detach();

    is_offscreen_monitor_thread_running = true;
}