#pragma once
#include "nana_common.h"

class tab_page_patches : public nana::panel<false>
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

	void initialize_checkboxes()
	{
		cb_noCD = std::make_unique<nana::checkbox>(*this, "No CD");
		cb_meleeStuckFix = std::make_unique<nana::checkbox>(*this, "Melee Stuck Fix");
		cb_pauseWhenUnfocused = std::make_unique<nana::checkbox>(*this, "Pause when Unfocused");
		cb_offscreenFix = std::make_unique<nana::checkbox>(*this, "Offscreen Fix");

		cb_noCD->bgcolor(default_bgcolor);
		cb_meleeStuckFix->bgcolor(default_bgcolor);
		cb_pauseWhenUnfocused->bgcolor(default_bgcolor);
		cb_offscreenFix->bgcolor(default_bgcolor);

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

		lbl_maxUnits->bgcolor(default_bgcolor);
		lbl_pathfindingCycles->bgcolor(default_bgcolor);
		lbl_forcedMinRangeForMelees->bgcolor(default_bgcolor);

		layout->field("maxUnits") << *lbl_maxUnits << *tb_maxUnits;
		layout->field("pathfindingCycles") << *lbl_pathfindingCycles << *tb_pathfindingCycles;
		layout->field("forcedMinRangeForMelees") << *lbl_forcedMinRangeForMelees << *tb_forcedMinRangeForMelees;
	}

public:
	tab_page_patches(nana::window parent) : nana::panel<false>(parent)
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
						<weight=150 vert                                                                   \
							<vert maxUnits arrange=[20, 20]>                                               \
							<vert margin=[10] pathfindingCycles arrange=[20, 20]>                          \
							<vert margin=[20] forcedMinRangeForMelees arrange=[35, 20]>                    \
							<>                                                                             \
						>                                                                                  \
					>");

		initialize_checkboxes();
		initialize_textboxes();

		layout->collocate();
	}

	std::string get_max_units()
	{
		return tb_maxUnits->text();
	}

	std::string get_pathfinding_cycles()
	{
		return tb_pathfindingCycles->text();
	}

	std::string get_forced_minrange_for_melees()
	{
		return tb_forcedMinRangeForMelees->text();
	}

	bool get_noCD()
	{
		return cb_noCD->checked();
	}

	bool get_meleeStuckFix()
	{
		return cb_meleeStuckFix->checked();
	}

	bool get_pauseWhenUnfocused()
	{
		return cb_pauseWhenUnfocused->checked();
	}

	bool get_offscreenFix()
	{
		return cb_offscreenFix->checked();
	}
};