#pragma once

#include "Core/Core.h"

#include <cstdint>
#include <glm/glm.hpp>

namespace Xeno
{
    class XENO_API Color
    {
    public:
        explicit Color(const float red = 1.0f,
                       const float green = 1.0f,
                       const float blue = 1.0f,
                       const float alpha = 1.0f) :
            r(red), g(green), b(blue), a(alpha)
        { }

        static Color CreateColorInt(const uint8_t red,
                                    const uint8_t green,
                                    const uint8_t blue,
                                    const uint8_t alpha)
        {
            return Color(red / 255.0f, 
                         green / 255.0f, 
                         blue / 255.0f, 
                         alpha / 255.0f);
        }

        static Color Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
        static Color Gray() { return Color(0.5f, 0.5f, 0.5f, 1.0f); }
        static Color White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
        static Color Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
        static Color Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
        static Color Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
        static Color Yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
        static Color Magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
        static Color Cyan() { return Color(0, 1.0f, 1.0f, 1.0f); }
        static Color Transparent() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }
        static Color Opaque() { return Color(0.0f, 0.0f, 0.0f, 1.0f / 255.0f); }

        [[nodiscard]] Color ToInt() const
        {
            return Color(uint8_t(r * 255), 
                         uint8_t(g * 255), 
                         uint8_t(b * 255), 
                         uint8_t(a * 255));
        }

        [[nodiscard]] glm::vec4 ToVec4() const { return glm::vec4(r, g, b, a); }

        float r;
        float g;
        float b;
        float a;
    };
}