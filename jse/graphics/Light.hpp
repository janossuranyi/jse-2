#ifndef JSE_GRAPHICS_LIGHT_H
#define JSE_GRAPHICS_LIGHT_H

#include "core/Types.hpp"
#include "core/math/Vector.hpp"

namespace jse {

    enum lightType_t : int
    {
        LT_POINT,
        LT_SPOT,
        LT_DIR
    };

    class Light
    {
    public:
        lightType_t type;
        std::string name;
        vec4 color;
        vec4 attenuation;       // x= kc, y= kl, z= kq, w= cutoff
        float innerConeAngle;
        float outerConeAngle;
        Light();
    };

    inline Light::Light() : 
        type(LT_POINT),
        name("Point001"),
        color(vec4(1.0f, 1.0f, 1.0f, 10.0f)),
        attenuation(vec4(1.0f, 0.09f, 0.032f, 0.0005f)),
        innerConeAngle(0.0f),
        outerConeAngle(0.0f) {}
}

#endif //! JSE_GRAPHICS_LIGHT_H