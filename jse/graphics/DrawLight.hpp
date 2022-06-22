#ifndef JSE_GRAPHICS_DRAWLIGHT_H
#define JSE_GRAPHICS_DRAWLIGHT_H

#include "core/Types.hpp"
#include "core/math/Vector.hpp"

namespace jse {

    class DrawDirLight
    {
    public:
        vec4 color;
        vec4 direction;
    }; // 32

    class DrawPointLight
    {
    public:
        vec4 color;
        vec4 attenuation;
        vec4 position;
    }; // 48

    class DrawSpotLight
    {
    public:
        vec4 color;
        vec4 attenuation;
        vec4 position;
        vec4 spotDir;
        float innerConeAngle;
        float outerConeAngle;
    }; // 18*4 = 72
}

#endif //! JSE_GRAPHICS_DRAWLIGHT_H