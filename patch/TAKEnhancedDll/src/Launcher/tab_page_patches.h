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
	std::unique_ptr<nana::spinbox> sb_maxUnits;

	std::unique_ptr<nana::label> lbl_pathfindingCycles;
	std::unique_ptr<nana::spinbox> sb_pathfindingCycles;

	std::unique_ptr<nana::label> lbl_forcedMinRangeForMelees;
	std::unique_ptr<nana::spinbox> sb_forcedMinRangeForMelees;

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

		if (settings.no_cd) {
			cb_noCD->check(true);
		}

		if (settings.melee_stuck_fix) {
			cb_meleeStuckFix->check(true);
		}

		if (settings.pause_when_unfocused) {
			cb_pauseWhenUnfocused->check(true);
		}

		if (settings.offscreen_fix) {
			cb_offscreenFix->check(true);
		}

		layout->field("checkboxes1") << *cb_noCD << *cb_meleeStuckFix << *cb_offscreenFix << *cb_pauseWhenUnfocused;
	}

	void initialize_textboxes()
	{
		lbl_maxUnits = std::make_unique<nana::label>(*this, "Max Units:");
		sb_maxUnits = std::make_unique<nana::spinbox>(*this);
		sb_maxUnits->range(0, INT_MAX, 1);
		sb_maxUnits->value(std::to_string(settings.max_units));

		lbl_pathfindingCycles = std::make_unique<nana::label>(*this, "Pathfinding Cycles:");
		sb_pathfindingCycles = std::make_unique<nana::spinbox>(*this);
		sb_pathfindingCycles->range(0, INT_MAX, 1);
		sb_pathfindingCycles->value(std::to_string(settings.pathfinding_cycles));

		lbl_forcedMinRangeForMelees = std::make_unique<nana::label>(*this, "Forced minrange for Melees:");
		sb_forcedMinRangeForMelees = std::make_unique<nana::spinbox>(*this);
		sb_forcedMinRangeForMelees->range(0, INT_MAX, 1);
		sb_forcedMinRangeForMelees->value(std::to_string(settings.forced_minrange_for_melees));

		lbl_maxUnits->bgcolor(default_bgcolor);
		lbl_pathfindingCycles->bgcolor(default_bgcolor);
		lbl_forcedMinRangeForMelees->bgcolor(default_bgcolor);

		layout->field("maxUnits") << *lbl_maxUnits << *sb_maxUnits;
		layout->field("pathfindingCycles") << *lbl_pathfindingCycles << *sb_pathfindingCycles;
		layout->field("forcedMinRangeForMelees") << *lbl_forcedMinRangeForMelees << *sb_forcedMinRangeForMelees;
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
					>                                                                                      \
					<weight=120 vert                                                                       \
						<weight=150 vert                                                                   \
							<vert maxUnits arrange=[20, 25]>                                               \
							<vert margin=[20] pathfindingCycles arrange=[20, 25]>                          \
							<vert margin=[35] forcedMinRangeForMelees arrange=[35, 25]>                    \
							<>                                                                             \
						>                                                                                  \
					>");

		initialize_checkboxes();
		initialize_textboxes();

		layout->collocate();
	}

	int get_max_units()
	{
		return sb_maxUnits->to_int();
	}

	int get_pathfinding_cycles()
	{
		return sb_pathfindingCycles->to_int();
	}

	int get_forced_minrange_for_melees()
	{
		return sb_forcedMinRangeForMelees->to_int();
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