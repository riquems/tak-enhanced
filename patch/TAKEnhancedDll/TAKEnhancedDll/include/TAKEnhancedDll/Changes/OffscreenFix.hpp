#pragma once

/******************************************************************

    The Offscreen Fix is done by starting a monitor thread which
    monitors units, ensuring every unit doesn't surpass the top
    edge of the map.

*******************************************************************/

extern bool is_offscreen_monitor_thread_running;

void startOffscreenMonitor();

void startOffscreenMonitorThread();
