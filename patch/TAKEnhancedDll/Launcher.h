#pragma once

#include "Context.h"

#include "nana/gui.hpp"
#include "nana/gui/place.hpp"
#include "nana/gui/widgets/form.hpp"
#include "nana/gui/widgets/label.hpp"
#include "nana/gui/widgets/textbox.hpp"
#include "nana/gui/widgets/checkbox.hpp"
#include "nana/gui/widgets/button.hpp"

#include "nana/gui/widgets/tabbar.hpp"
#include "nana/gui/widgets/combox.hpp"
#include "nana/gui/widgets/panel.hpp"

class ModsPanel
{

};

class PatchPanel
{

};

class Launcher
{
	nana::form fm_main;
	nana::place fm_main_layout;

	ModsPanel pnl_mods;
	PatchPanel pnl_patch;

	nana::place pnl_mods_layout;
	nana::place pnl_patch_layout;

};

void launcher()
{
	nana::API::window_icon_default(nana::paint::image("Kingdoms.exe"));

	nana::form form(nana::API::make_center(450, 280), nana::appearance(1, 1, 1, 0, 0, 0, 0));

	form.caption("TA:K Enhanced Settings");
	form.bgcolor(nana::color(255, 255, 255, 1));

	nana::place form_layout(form);

	form_layout.div("margin=[1] vert<weight=25 tabs><content>");

	nana::panel<false> pnl_Patch(form);

	nana::place layout(pnl_Patch);
	layout.div("margin=15                                                                             \
		        <vert <weight=60                                                                      \
						  <vert checkboxes1 arrange=[30, 30, 30, 30]><>                               \
					  >                                                                               \
					  <>                                                                              \
			    >                                                                                     \
				<weight=120                                                                           \
		            vert <weight=60 <                                                                 \
		                                <weight=30><vert buttons gap=5>                               \
                                    >                                                                 \
                         >                                                                            \
		                 <weight=150 vert                                                             \
							<vert margin = [20] maxUnits arrange = [20, 20] >                         \
							<vert margin = [30] pathfindingCycles arrange = [20, 20]>                 \
							<vert margin = [40] forcedMinRangeForMelees arrange = [35, 20]>           \
							<>                                                                        \
					     >                                                                            \
                >");

	nana::checkbox cb_noCD(pnl_Patch, "No CD");
	nana::checkbox cb_meleeStuckFix(pnl_Patch, "Melee Stuck Fix");
	nana::checkbox cb_pauseWhenUnfocused(pnl_Patch, "Pause when Unfocused");
	nana::checkbox cb_offscreenFix(pnl_Patch, "Offscreen Fix");

	if (settings.NoCD) {
		cb_noCD.check(true);
	}

	if (settings.MeleeStuckFix) {
		cb_meleeStuckFix.check(true);
	}

	if (settings.PauseWhenUnfocused) {
		cb_pauseWhenUnfocused.check(true);
	}

	if (settings.OffscreenFix) {
		cb_offscreenFix.check(true);
	}

	layout["checkboxes1"] << cb_noCD << cb_meleeStuckFix << cb_offscreenFix << cb_pauseWhenUnfocused;

	nana::label lbl_maxUnits(pnl_Patch, "Max Units:");
	nana::textbox tb_maxUnits(pnl_Patch, std::to_string(settings.MaxUnits));

	nana::label lbl_pathfindingCycles(pnl_Patch, "Pathfinding Cycles:");
	nana::textbox tb_pathfindingCycles(pnl_Patch, std::to_string(settings.PathfindingCycles));

	nana::label lbl_forcedMinRangeForMelees(pnl_Patch, "Forced minrange for Melees:");
	nana::textbox tb_forcedMinRangeForMelees(pnl_Patch, std::to_string(settings.ForcedMinRangeForMelees));

	layout["maxUnits"] << lbl_maxUnits << tb_maxUnits;
	layout["pathfindingCycles"] << lbl_pathfindingCycles << tb_pathfindingCycles;
	layout["forcedMinRangeForMelees"] << lbl_forcedMinRangeForMelees << tb_forcedMinRangeForMelees;

	nana::button btn_continue(pnl_Patch, "Continue");
	nana::button btn_exit(pnl_Patch, "Exit");

	layout["buttons"] << btn_continue << btn_exit;

	btn_continue.events().click([&]() {
		settings.MaxUnits = strtoul(tb_maxUnits.text().c_str(), nullptr, 0);
		settings.PathfindingCycles = strtoul(tb_pathfindingCycles.text().c_str(), nullptr, 0);
		settings.ForcedMinRangeForMelees = strtoul(tb_forcedMinRangeForMelees.text().c_str(), nullptr, 0);

		settings.NoCD = cb_noCD.checked();
		settings.MeleeStuckFix = cb_meleeStuckFix.checked();
		settings.OffscreenFix = cb_offscreenFix.checked();
		settings.PauseWhenUnfocused = cb_pauseWhenUnfocused.checked();

		settings.Save();
		nana::API::exit_all();
	});

	btn_exit.events().click([]() {
		nana::API::exit_all();
		ExitProcess(0);
	});

	nana::tabbar<nana::form> tabs(form);

	tabs.push_back("Mods");
	tabs.push_back("Patch");

	tabs.bgcolor(nana::color(255, 255, 255, 1));

	layout.collocate();

	form_layout["tabs"] << tabs;
	form_layout["content"] << pnl_Patch;

	tabs.attach(1, pnl_Patch);

	form_layout.collocate();

	form.show();

	nana::exec();
}