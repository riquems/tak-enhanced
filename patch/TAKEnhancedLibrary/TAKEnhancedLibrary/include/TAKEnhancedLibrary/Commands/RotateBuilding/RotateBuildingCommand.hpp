#pragma once
#include "TAKEnhancedLibrary/Commands/Command.hpp"
#include "TAKEnhancedLibrary/Commands/Params.hpp"
#include "Utils/json.hpp"

typedef uint Degree;

struct RotateOrientation
{
    std::string name;

    RotateOrientation() {}
    RotateOrientation(std::string name) : name(name) {}

    static RotateOrientation Clockwise;
    static RotateOrientation CounterClockwise;

    bool operator==(const RotateOrientation& rhs) {
        return this->name == rhs.name;
    }

    bool operator==(const std::string& rhs) {
        return this->name == rhs;
    }

    static std::optional<RotateOrientation> fromString(const std::string& str) {
        if (str == RotateOrientation::Clockwise)
            return RotateOrientation::Clockwise;
        if (str == RotateOrientation::CounterClockwise)
            return RotateOrientation::CounterClockwise;

        return std::optional<RotateOrientation>();
    }

    static std::string toString(const RotateOrientation& orientation) {
        return orientation.name;
    }
};

struct RotateBuildingCommandParams : Params
{
    RotateOrientation orientation;
    int step;
};

struct RotateBuildingCommand : public Command
{
    RotateBuildingCommandParams params;

    static RotateBuildingCommand Clockwise;
    static RotateBuildingCommand CounterClockwise;

    RotateBuildingCommand();
    RotateBuildingCommand(RotateBuildingCommandParams params);
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RotateOrientation, name)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RotateBuildingCommandParams, orientation)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RotateBuildingCommand, params)
