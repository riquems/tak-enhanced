#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKCore/Commands.h"
#include <TAKEnhancedLibrary/KeyBinding.hpp>
#include <TAKEnhancedLibrary/Keys/Keys.hpp>
#include <TAKEnhancedLibrary/Commands/Commands.hpp>

struct UserConfig
{
    std::string onSpacebar = TAKCore::Commands::DoNothing;
    std::string onDoubleClick = TAKCore::Commands::SelectUnitsOnScreenSelectedType;
    std::string onTripleClick = TAKCore::Commands::DoNothing;
    std::string onCtrlDoubleClick = TAKCore::Commands::SelectAllUnitsSelectedType;
    std::vector<KeyBinding> keyBindings = {
        KeyBinding {
            .keyCombination = { Keys::Key_1 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 1 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_2 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 2 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_3 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 3 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_4 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 4 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_5 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 5 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_6 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 6 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_7 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 7 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_8 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 8 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_9 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 9 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_0 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 10 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_1 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 1 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_2 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 2 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_3 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 3 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_4 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 4 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_5 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 5 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_6 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 6 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_7 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 7 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_8 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 8 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_9 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 9 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_0 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 10 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_1 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 1 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_2 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 2 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_3 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 3 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_4 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 4 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_5 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 5 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_6 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 6 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_7 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 7 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_8 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 8 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_9 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 9 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Shift, Keys::Key_0 },
            .command = std::make_shared<SelectBuildingCommand>(SelectBuildingCommandParams { .building = 10 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_1 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 1 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_2 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 2 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_3 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 3 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_4 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 4 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_5 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 5 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_6 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 6 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_7 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 7 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_8 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 8 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_9 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 9 })
        },
        KeyBinding {
            .keyCombination = { Keys::Key_0 },
            .command = std::make_shared<RetrieveSquadCommand>(RetrieveSquadCommandParams { .squad = 10 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_1 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 1 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_2 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 2 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_3 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 3 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_4 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 4 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_5 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 5 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_6 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 6 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_7 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 7 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_8 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 8 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_9 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 9 })
        },
        KeyBinding {
            .keyCombination = { Keys::Shift, Keys::Key_0 },
            .command = std::make_shared<RetrieveSquadAddCommand>(RetrieveSquadAddCommandParams { .squad = 10 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_1 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 1 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_2 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 2 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_3 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 3 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_4 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 4 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_5 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 5 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_6 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 6 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_7 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 7 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_8 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 8 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_9 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 9 })
        },
        KeyBinding {
            .keyCombination = { Keys::Ctrl, Keys::Key_0 },
            .command = std::make_shared<CreateSquadCommand>(CreateSquadCommandParams { .squad = 10 })
        },
        KeyBinding {
            .keyCombination = { Keys::None },
            .command = std::make_shared<RotateBuildingCommand>(RotateBuildingCommand::Clockwise)
        },
        KeyBinding {
            .keyCombination = { Keys::None },
            .command = std::make_shared<RotateBuildingCommand>(RotateBuildingCommand::CounterClockwise)
        },
        KeyBinding {
            .keyCombination = { Keys::Alt, Keys::E },
            .command = std::make_shared<SetUnitStanceCommand>(SetUnitStanceCommand::Passive)
        },
        KeyBinding {
            .keyCombination = { Keys::Alt, Keys::W },
            .command = std::make_shared<SetUnitStanceCommand>(SetUnitStanceCommand::Defensive)
        },
        KeyBinding {
            .keyCombination = { Keys::Alt, Keys::Q },
            .command = std::make_shared<SetUnitStanceCommand>(SetUnitStanceCommand::Offensive)
        }
    };
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    UserConfig, onSpacebar, onDoubleClick, onTripleClick, onCtrlDoubleClick, keyBindings
)
