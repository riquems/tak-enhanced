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

class mods_panel : public nana::panel<false>
{
	std::unique_ptr<nana::place> layout;

public:
	mods_panel(nana::window parent) : nana::panel<false>(parent)
	{
		layout = std::make_unique<nana::place>(*this);

		layout->div("");
	}
};

class patch_panel : public nana::panel<false>
{
	std::unique_ptr<nana::place> layout;

	// Checkboxes
	std::unique_ptr<nana::checkbox> cb_noCD;
	std::unique_ptr<nana::checkbox> cb_meleeStuckFix;
	std::unique_ptr<nana::checkbox> cb_pauseWhenUnfocused;
	std::unique_ptr<nana::checkbox> cb_offscreenFix;

	// Textboxes
	std::unique_ptr<nana::label> lbl_maxUnits;
	std::unique_ptr<nana::textbox> tb_maxUnits;

	std::unique_ptr<nana::label> lbl_pathfindingCycles;
	std::unique_ptr<nana::textbox> tb_pathfindingCycles;

	std::unique_ptr<nana::label> lbl_forcedMinRangeForMelees;
	std::unique_ptr<nana::textbox> tb_forcedMinRangeForMelees;

	// Buttons
	std::unique_ptr<nana::button> btn_continue;
	std::unique_ptr<nana::button> btn_exit;

	void initialize_checkboxes()
	{
		cb_noCD = std::make_unique<nana::checkbox>(*this, "No CD");
		cb_meleeStuckFix = std::make_unique<nana::checkbox>(*this, "Melee Stuck Fix");
		cb_pauseWhenUnfocused = std::make_unique<nana::checkbox>(*this, "Pause when Unfocused");
		cb_offscreenFix = std::make_unique<nana::checkbox>(*this, "Offscreen Fix");

		if (settings.NoCD) {
			cb_noCD->check(true);
		}

		if (settings.MeleeStuckFix) {
			cb_meleeStuckFix->check(true);
		}

		if (settings.PauseWhenUnfocused) {
			cb_pauseWhenUnfocused->check(true);
		}

		if (settings.OffscreenFix) {
			cb_offscreenFix->check(true);
		}

		layout->field("checkboxes1") << *cb_noCD << *cb_meleeStuckFix << *cb_offscreenFix << *cb_pauseWhenUnfocused;
	}

	void initialize_textboxes()
	{
		lbl_maxUnits = std::make_unique<nana::label>(*this, "Max Units:");
		tb_maxUnits = std::make_unique<nana::textbox>(*this, std::to_string(settings.MaxUnits));

		lbl_pathfindingCycles = std::make_unique<nana::label>(*this, "Pathfinding Cycles:");
		tb_pathfindingCycles = std::make_unique<nana::textbox>(*this, std::to_string(settings.PathfindingCycles));
		
		lbl_forcedMinRangeForMelees = std::make_unique<nana::label>(*this, "Forced minrange for Melees:");
		tb_forcedMinRangeForMelees = std::make_unique<nana::textbox>(*this, std::to_string(settings.ForcedMinRangeForMelees));

		layout->field("maxUnits") << *lbl_maxUnits << *tb_maxUnits;
		layout->field("pathfindingCycles") << *lbl_pathfindingCycles << *tb_pathfindingCycles;
		layout->field("forcedMinRangeForMelees") << *lbl_forcedMinRangeForMelees << *tb_forcedMinRangeForMelees;
	}

	void initialize_buttons()
	{
		btn_continue = std::make_unique<nana::button>(*this, "Continue");
		btn_exit = std::make_unique<nana::button>(*this, "Exit");

		btn_continue->events().click([&]() {
			settings.MaxUnits = strtoul(tb_maxUnits->text().c_str(), nullptr, 0);
			settings.PathfindingCycles = strtoul(tb_pathfindingCycles->text().c_str(), nullptr, 0);
			settings.ForcedMinRangeForMelees = strtoul(tb_forcedMinRangeForMelees->text().c_str(), nullptr, 0);

			settings.NoCD = cb_noCD->checked();
			settings.MeleeStuckFix = cb_meleeStuckFix->checked();
			settings.OffscreenFix = cb_offscreenFix->checked();
			settings.PauseWhenUnfocused = cb_pauseWhenUnfocused->checked();

			settings.Save();
			nana::API::exit_all();
			});

		btn_exit->events().click([]() {
			nana::API::exit_all();
			ExitProcess(0);
			});

		layout->field("buttons") << *btn_continue << *btn_exit;
	}

public:
	patch_panel(nana::window parent) : nana::panel<false>(parent)
	{
		layout = std::make_unique<nana::place>(*this);

		layout->div("margin=15                                                                             \
					<vert                                                                                  \
					    <weight=60                                                                         \
						    <vert checkboxes1 arrange=[30, 30, 30, 30]><>                                  \
						>                                                                                  \
						<>                                                                                 \
					>                                                                                      \
					<weight=120 vert                                                                       \
						<weight=60                                                                         \
					        <weight=30><vert buttons gap=5>                                                \
						>                                                                                  \
						<weight=150 vert                                                                   \
							<vert margin=[20] maxUnits arrange=[20, 20] >                                  \
							<vert margin=[30] pathfindingCycles arrange=[20, 20]>                          \
							<vert margin=[40] forcedMinRangeForMelees arrange=[35, 20]>                    \
							<>                                                                             \
						>                                                                                  \
					>");

		initialize_checkboxes();
		initialize_textboxes();
		initialize_buttons();

		layout->collocate();
	}
};

class Launcher
{
	std::unique_ptr<nana::form> fm_main;
	std::unique_ptr<nana::place> layout;

	std::unique_ptr<nana::tabbar<nana::form>> tabs;

	std::unique_ptr<mods_panel> pnl_mods;
	std::unique_ptr<patch_panel> pnl_patch;

public:
	Launcher()
	{
		nana::API::window_icon_default(nana::paint::image("Kingdoms.exe"));

		fm_main = std::make_unique<nana::form>(nana::API::make_center(450, 280), nana::appearance(1, 1, 1, 0, 0, 0, 0));

		fm_main->caption("TA:K Enhanced Settings");
		fm_main->bgcolor(nana::color(255, 255, 255, 1));

		layout = std::make_unique<nana::place>(fm_main->handle());
		layout->div("margin=[1] vert<weight=25 tabs><content>");

		tabs = std::make_unique<nana::tabbar<nana::form>>(fm_main->handle());
		tabs->bgcolor(nana::color(255, 255, 255, 1));
		tabs->push_back("Mods");
		tabs->push_back("Patch");

		pnl_mods = std::make_unique<mods_panel>(fm_main->handle());
		pnl_patch = std::make_unique<patch_panel>(fm_main->handle());

		tabs->attach(1, *pnl_patch);

		layout->field("tabs") << *tabs;
		layout->field("content") << *pnl_patch;

		layout->collocate();
	}

	void execute()
	{
		fm_main->show();
		nana::exec();
	}
};