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
	if (players_wrappers.empty()) {
		throw std::exception("Players Wrappers array is empty.                                   \
			                  It must be initialized in order to use the offscreen functionality!");
	}

	while (true) {
		for (int i = 0; i < players_wrappers.size(); i++) {
			for (int j = 0; j < players_wrappers[i].units.size(); j++) {
				PlayerWrapper player = players_wrappers[i];
				
				if (player._player->unitsCount == 0)
					return;

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
	if (!is_offscreen_monitor_thread_running)
	{
		std::thread offscreen_monitor_thread(startOffscreenMonitor);
		offscreen_monitor_thread.detach();

		is_offscreen_monitor_thread_running = true;
	}
}