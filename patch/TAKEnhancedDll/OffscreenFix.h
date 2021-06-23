#pragma once
#include "GameFunctions.h"
#include "PlayerWrapper.h"

/******************************************************************

	The Offscreen Fix is done by starting a monitor thread which
	monitors units, ensuring every unit doesn't surpass the top
	edge of the map.

*******************************************************************/

bool is_offscreen_monitor_thread_running = false;

void startOffscreenMonitor()
{
	if (players_wrappers.empty()) {
		throw std::exception("Player Wrappers array is empty.                                    \
			                  It must be initialized in order to use the offscreen functionality!");
	}

	while (true) {
		if (match_has_finished) {
			return;
		}

		for (int i = 0; i < players_wrappers.size(); i++) {
			for (int j = 0; j < players_wrappers[i].units.size(); j++) {
				UnitWrapper unit = players_wrappers[i].units[j];

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

void startOffscreenMonitor()
{
	if (!is_offscreen_monitor_thread_running)
	{
		std::thread offscreen_monitor_thread(startOffscreenMonitor);
		offscreen_monitor_thread.detach();

		is_offscreen_monitor_thread_running = true;
	}
}