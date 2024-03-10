#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Players/Player.hpp"
#include "TAKEnhancedLibrary/Configs/CustomizableHpBarsSettings.hpp"

namespace TAKEnhancedLibrary
{
    class HpBarRenderer
    {
        uintptr_t originalHpBarGraphicObjAddr;
        std::unordered_map<int, uintptr_t> colorIdToGraphicObjAddr;

        std::vector<std::string> hpBarsFileNames = {
            "lightblue.jpg",
            "red.jpg",
            "white.jpg",
            "green.jpg",
            "darkblue.jpg",
            "purple.jpg",
            "yellow.jpg",
            "black.jpg",
            "orange.jpg",
            "brown.jpg"
        };

    public:
        HpBarRenderer();

        void init();

        void setNextHpBarColor(const std::shared_ptr<Player>&, const CustomizableHpBarSetting&);
    };
}
