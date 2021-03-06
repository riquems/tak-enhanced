#pragma once

#include "Context.h"

#include "nana/gui.hpp"
#include "nana/gui/place.hpp"
#include "nana/gui/widgets/form.hpp"
#include "nana/gui/widgets/panel.hpp"
#include "nana/gui/widgets/tabbar.hpp"

#include "nana/gui/widgets/label.hpp"
#include "nana/gui/widgets/textbox.hpp"
#include "nana/gui/widgets/checkbox.hpp"
#include "nana/gui/widgets/button.hpp"
#include "nana/gui/widgets/listbox.hpp"

class tab_page_mods : public nana::panel<false>
{
	std::unique_ptr<nana::place> layout;

	std::unique_ptr<nana::checkbox> cb_enable_mods;
	std::unique_ptr<nana::listbox> lb_listbox1;
	std::unique_ptr<nana::listbox> lb_listbox2;

	std::unique_ptr<nana::button> btn_moveAllRight;
	std::unique_ptr<nana::button> btn_moveSelectedRight;
	std::unique_ptr<nana::button> btn_moveSelectedLeft;
	std::unique_ptr<nana::button> btn_moveAllLeft;

	void initialize_checkboxes()
	{
		cb_enable_mods = std::make_unique<nana::checkbox>(*this, "Enable Mods");

		if (settings.EnableMods) {
			cb_enable_mods->check(true);
		}

		layout->field("checkboxes") << *cb_enable_mods;
	}

	void initialize_listbox1()
	{
		lb_listbox1 = std::make_unique<nana::listbox>(*this);

		layout->field("listbox1") << *lb_listbox1;
	}

	void initialize_buttons()
	{
		btn_moveAllRight = std::make_unique<nana::button>(*this, ">>");
		btn_moveSelectedRight = std::make_unique<nana::button>(*this, ">");
		btn_moveSelectedLeft = std::make_unique<nana::button>(*this, "<");
		btn_moveAllLeft = std::make_unique<nana::button>(*this, "<<");



		layout->field("buttons") << *btn_moveAllRight << *btn_moveSelectedRight
								 << *btn_moveSelectedLeft << *btn_moveAllLeft;
	}

	void initialize_listbox2()
	{
		lb_listbox2 = std::make_unique<nana::listbox>(*this);

		layout->field("listbox2") << *lb_listbox2;
	}

public:
	tab_page_mods(nana::window parent) : nana::panel<false>(parent)
	{
		layout = std::make_unique<nana::place>(*this);

		layout->div("margin=15 vert                                           \
			         <weight=30 checkboxes>                                   \
			         <                                                        \
			             <listbox1><weight=40 vert buttons><listbox2>         \
                     >");

		initialize_checkboxes();
		initialize_listbox1();
		initialize_buttons();
		initialize_listbox2();

		layout->collocate();
	}
};

class tab_page_panel : public nana::panel<false>
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
	tab_page_panel(nana::window parent) : nana::panel<false>(parent)
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
							<vert margin=[20] maxUnits arrange=[20, 20]>                                   \
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

class main_form
{
	std::unique_ptr<nana::form> fm_main;
	std::unique_ptr<nana::place> layout;

	std::unique_ptr<nana::tabbar<std::string>> tabs;

	std::unique_ptr<tab_page_mods> tp_mods;
	std::unique_ptr<tab_page_panel> tp_patch;

public:
	main_form()
	{
		nana::API::window_icon_default(nana::paint::image("Kingdoms.exe"));

		fm_main = std::make_unique<nana::form>(nana::API::make_center(450, 280), nana::appearance(1, 1, 1, 0, 0, 0, 0));

		fm_main->caption("TA:K Enhanced Settings");
		fm_main->bgcolor(nana::color(255, 255, 255, 1));

		layout = std::make_unique<nana::place>(fm_main->handle());
		layout->div("margin=[1] vert<weight=25 tabs><content>");

		tabs = std::make_unique<nana::tabbar<std::string>>(fm_main->handle());
		tabs->bgcolor(nana::color(255, 255, 255, 1));

		tp_mods = std::make_unique<tab_page_mods>(fm_main->handle());
		tp_patch = std::make_unique<tab_page_panel>(fm_main->handle());

		tabs->append("Mods", *tp_mods);
		tabs->append("Patch", *tp_patch);

		tabs->activated(0);

		layout->field("tabs") << *tabs;
		layout->field("content").fasten(*tp_mods).fasten(*tp_patch);

		layout->collocate();
	}

	void show()
	{
		fm_main->show();
		nana::exec();
	}
};