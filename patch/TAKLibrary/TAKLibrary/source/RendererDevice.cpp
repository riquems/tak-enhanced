#include "RendererDevice.hpp"

RendererDevice::RendererDevice(uintptr_t baseAddress) : _baseAddress(baseAddress) {}

TextureDisplayMode RendererDevice::getTextureDisplayMode()
{
    uintptr_t* rendererDevicePtr = (uintptr_t*) (GlobalPointers::RendererDevice + _baseAddress);

    uintptr_t* currentRendererDevice = (uintptr_t*) (*(uintptr_t*) ((*rendererDevicePtr) + 0x08));

    rendererVTable_offset_0x20_t fcn = *(rendererVTable_offset_0x20_t*) (*currentRendererDevice + 0x20);

    if (fcn(currentRendererDevice, 1)) {
        return TextureDisplayMode::INCREASED_SIZE;
    }

    return TextureDisplayMode::ORIGINAL_SIZE;
}
