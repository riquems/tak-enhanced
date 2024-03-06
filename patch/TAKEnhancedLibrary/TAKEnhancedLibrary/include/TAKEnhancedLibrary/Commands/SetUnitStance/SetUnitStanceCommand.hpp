#pragma once
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Params.hpp"
#include "Utils/json.hpp"

struct UnitStance
{
    std::string name;

    UnitStance() {}
    UnitStance(std::string name) : name(name) {}

    static UnitStance Passive;
    static UnitStance Defensive;
    static UnitStance Offensive;

    bool operator==(const UnitStance& rhs) {
        return this->name == rhs.name;
    }

    bool operator==(const std::string& rhs) {
        return this->name == rhs;
    }

    static std::optional<UnitStance> fromString(const std::string& str) {
        if (str == UnitStance::Passive)
            return UnitStance::Passive;
        if (str == UnitStance::Defensive)
            return UnitStance::Defensive;
        if (str == UnitStance::Offensive)
            return UnitStance::Offensive;

        return std::optional<UnitStance>();
    }

    static std::string toString(const UnitStance& orientation) {
        return orientation.name;
    }
};

struct SetUnitStanceCommandParams : Params
{
    UnitStance stance;
};

struct SetUnitStanceCommand : public Command
{
    SetUnitStanceCommandParams params;

    static SetUnitStanceCommand Passive;
    static SetUnitStanceCommand Defensive;
    static SetUnitStanceCommand Offensive;

    SetUnitStanceCommand();
    SetUnitStanceCommand(SetUnitStanceCommandParams params);
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UnitStance, name)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SetUnitStanceCommandParams, stance)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SetUnitStanceCommand, params)
