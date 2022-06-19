#ifndef JSE_GRAPHICS_LIGHT_H
#define JSE_GRAPHICS_LIGHT_H

#include "core/Types.hpp"

namespace jse::graphics {

    enum lightType_t
    {
        LT_POINT,
        LT_SPOT,
        LT_DIR
    };

    class Light
    {
    public:
        lightType_t type{ LT_POINT };
        core::String name;
        float color[3]{ 1.0f,1.0f,1.0f };
        float intensity{ 1.0f };
        float range{};
        float innerConeAngle{};
        float outerConeAngle{};
    };
}

#endif //! JSE_GRAPHICS_LIGHT_H