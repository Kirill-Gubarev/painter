#pragma once

#include "core/rgb.h"

namespace render::detail{
    struct Pixel{
        bool filled;
        core::RGB color;
        bool changed;

        Pixel(bool filled = false,
                const core::RGB& color = core::RGB(255, 255, 255),
                bool changed = false);
    };
    bool operator==(const Pixel& p1, const Pixel& p2);
    bool operator!=(const Pixel& p1, const Pixel& p2);
}
