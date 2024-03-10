#include "TAKCore/Graphics/Graphics.hpp"

namespace TAKCore
{
    const uintptr_t CreateGraphicObjectFromJPG_Offset = 0x022060;
    CreateGraphicObjectFromJPG_t CreateGraphicObjectFromJPG;

    const uintptr_t HpBarGraphicObj_Offset = 0x17454;
    uintptr_t* HpBarGraphicObj;

    uintptr_t* RendererDevice;
}
