#pragma once
#include "TAKEnhancedLibrary/common.hpp"
#include "TAKEnhancedLibrary/Graphics/HpBarRenderer.hpp"

enum class TextureDisplayMode {
    ORIGINAL_SIZE,
    INCREASED_SIZE
};

namespace TAKEnhancedLibrary
{
    extern std::shared_ptr<HpBarRenderer> hpBarRenderer;

    TextureDisplayMode GetTextureDisplayMode();
}
