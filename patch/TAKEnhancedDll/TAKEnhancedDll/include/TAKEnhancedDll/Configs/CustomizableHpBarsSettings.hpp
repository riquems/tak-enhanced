#pragma once
#include "TAKEnhancedDll/Configs/GameSetting.hpp"

namespace ShowMode {
    enum Enum { Invalid, Always, OnlyIfDamaged, Never };

    NLOHMANN_JSON_SERIALIZE_ENUM(Enum, {
        { Invalid, nullptr },
        { Always, "always" },
        { OnlyIfDamaged, "onlyIfDamaged" },
        { Never, "never" }
    });
}

namespace ColorMode {
    enum Enum { Invalid, Original, MatchPlayerColor, Custom };

    NLOHMANN_JSON_SERIALIZE_ENUM(Enum, {
        { Invalid, nullptr },
        { Original, "original" },
        { MatchPlayerColor, "matchPlayerColor" },
        { Custom, "custom" }
    });
}

namespace Color {
    enum Enum { Invalid, LightBlue, Red, White, Green, Blue, Purple, Yellow, Black, Orange, Brown };

    NLOHMANN_JSON_SERIALIZE_ENUM(Enum, {
        { Invalid, nullptr },
        { LightBlue, "lightBlue" },
        { Red, "red" },
        { White, "white" },
        { Green, "green" },
        { Blue, "blue" },
        { Purple, "purple" },
        { Yellow, "yellow" },
        { Black, "black" },
        { Orange, "orange" },
        { Brown, "brown" }
    });
}

extern std::unordered_map<ShowMode::Enum, std::string> showModeToString;

extern std::unordered_map<ColorMode::Enum, std::string> colorModeToString;

extern std::unordered_map<Color::Enum, std::string> colorToString;

struct CustomizableHpBarSetting
{
    ShowMode::Enum showMode;
    ColorMode::Enum colorMode;
    Color::Enum color;
};

struct CustomizableHpBarsSettings : GameSetting
{
    bool enabled = true;

    CustomizableHpBarSetting mine = CustomizableHpBarSetting {
        .showMode = ShowMode::OnlyIfDamaged,
        .colorMode = ColorMode::MatchPlayerColor,
        .color = Color::Blue
    };

    CustomizableHpBarSetting ally = CustomizableHpBarSetting {
        .showMode = ShowMode::OnlyIfDamaged,
        .colorMode = ColorMode::MatchPlayerColor,
        .color = Color::LightBlue
    };

    CustomizableHpBarSetting enemy = CustomizableHpBarSetting {
        .showMode = ShowMode::OnlyIfDamaged,
        .colorMode = ColorMode::MatchPlayerColor,
        .color = Color::Red
    };
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CustomizableHpBarSetting, showMode, colorMode, color)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(CustomizableHpBarsSettings, enabled, mine, ally, enemy)
