#include "TAKEnhancedLibrary/Graphics/Graphics.hpp"
#include "TAKEnhancedLibrary/Graphics/HpBarRenderer.hpp"
#include "TAKCore/Graphics/Graphics.hpp"

using namespace TAKEnhancedLibrary;

HpBarRenderer::HpBarRenderer() { }

void HpBarRenderer::init() {
    originalHpBarGraphicObjAddr = *TAKCore::HpBarGraphicObj;

    auto textureDisplayMode = TAKEnhancedLibrary::GetTextureDisplayMode();

    switch (textureDisplayMode)
    {
    case TextureDisplayMode::ORIGINAL_SIZE:

        for (int i = 0; i < this->hpBarsFileNames.size(); i++) {
            std::string hpBarFullPath = "anims\\hpbars_original_size\\" + this->hpBarsFileNames[i];

            uintptr_t hpBarAddr = TAKCore::CreateGraphicObjectFromJPG(hpBarFullPath.c_str(), 0);

            colorIdToGraphicObjAddr.insert(std::pair(i, hpBarAddr));
        }

        break;

    case TextureDisplayMode::INCREASED_SIZE:
        for (int i = 0; i < this->hpBarsFileNames.size(); i++) {
            std::string hpBarFullPath = "anims\\hpbars_increased_size\\" + this->hpBarsFileNames[i];

            uintptr_t hpBarAddr = TAKCore::CreateGraphicObjectFromJPG(hpBarFullPath.c_str(), 0);

            colorIdToGraphicObjAddr.insert(std::pair(i, hpBarAddr));
        }

        break;
    }
}

void HpBarRenderer::setNextHpBarColor(const std::shared_ptr<Player>& player, const CustomizableHpBarSetting& settings) {
    uintptr_t graphicObjAddr = 0;

    switch (settings.colorMode)
    {
    case ColorMode::Original: {
        graphicObjAddr = originalHpBarGraphicObjAddr;
        break;
    }
    case ColorMode::MatchPlayerColor: {
        int colorId = player->color();
        graphicObjAddr = colorIdToGraphicObjAddr[colorId];
        break;
    }
    case ColorMode::Custom: {
        int colorId = (int)settings.color;
        graphicObjAddr = colorIdToGraphicObjAddr[colorId];
        break;
    }
    }

    *TAKCore::HpBarGraphicObj = graphicObjAddr;
}
