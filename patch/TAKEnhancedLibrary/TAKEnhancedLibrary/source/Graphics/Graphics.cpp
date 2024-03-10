#include "TAKEnhancedLibrary/Graphics/Graphics.hpp"
#include "TAKCore/Graphics/Graphics.hpp"

using namespace TAKEnhancedLibrary;

std::shared_ptr<HpBarRenderer> TAKEnhancedLibrary::hpBarRenderer = std::make_shared<HpBarRenderer>();

TextureDisplayMode TAKEnhancedLibrary::GetTextureDisplayMode() {
    uintptr_t* currentRendererDevice = (uintptr_t*)(*(uintptr_t*)((*TAKCore::RendererDevice) + 0x08));

    auto fcn = *(TAKCore::rendererVTable_offset_0x20_t*)(*currentRendererDevice + 0x20);

    if (fcn(currentRendererDevice, 1)) {
        return TextureDisplayMode::INCREASED_SIZE;
    }

    return TextureDisplayMode::ORIGINAL_SIZE;
}
