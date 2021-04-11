#pragma once

#include "Core/Core.h"

#include <cstdint>
#include <glm/glm.hpp>

namespace Xeno
{
    struct XENO_API Color
    {
        explicit Color(const uint8_t red = 255,
                       const uint8_t green = 255,
                       const uint8_t blue = 255,
                       const uint8_t alpha = 255) :
            r(red), g(green), b(blue), a(alpha)
        { }

        static Color Black() { return Color(0, 0, 0, 255); }
        static Color White() { return Color(255, 255, 255, 255); }
        static Color Red() { return Color(255, 0, 0, 255); }
        static Color Green() { return Color(0, 255, 0, 255); }
        static Color Blue() { return Color(0, 0, 255, 255); }
        static Color Yellow() { return Color(255, 255, 0, 255); }
        static Color Magenta() { return Color(255, 0, 255, 255); }
        static Color Cyan() { return Color(0, 255, 255, 255); }
        static Color Transparent() { return Color(0, 0, 0, 0); }
        static Color Opaque() { return Color(0, 0, 0, 1); }

        [[nodiscard]] Color ToFloat() const { return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f); }
        [[nodiscard]] glm::vec4 ToVec4() const { return glm::vec4(r, g, b, a); }
        
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
}