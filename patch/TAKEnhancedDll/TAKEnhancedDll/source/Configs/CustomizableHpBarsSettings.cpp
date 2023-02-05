#include "TAKEnhancedDll/Configs/CustomizableHpBarsSettings.hpp"

std::unordered_map<ShowMode::Enum, std::string> showModeToString = {
    std::pair(ShowMode::Always, "Always"),
    std::pair(ShowMode::OnlyIfDamaged, "Only If Damaged"),
    std::pair(ShowMode::Never, "Never"),
};

std::unordered_map<ColorMode::Enum, std::string> colorModeToString = {
    std::pair(ColorMode::Original, "Original"),
    std::pair(ColorMode::MatchPlayerColor, "Match Player Color"),
    std::pair(ColorMode::Custom, "Custom")
};

std::unordered_map<Color::Enum, std::string> colorToString = {
    std::pair(Color::LightBlue, "Light Blue"),
    std::pair(Color::Red, "Red"),
    std::pair(Color::White, "White"),
    std::pair(Color::Green, "Green"),
    std::pair(Color::Blue, "Blue"),
    std::pair(Color::Purple, "Purple"),
    std::pair(Color::Yellow, "Yellow"),
    std::pair(Color::Black, "Black"),
    std::pair(Color::Orange, "Orange"),
    std::pair(Color::Brown, "Brown")
};

