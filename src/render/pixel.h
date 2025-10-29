#pragma once

#include "core/rgb.h"

namespace render{
    struct Pixel{
        bool filled;
        RGB color;
        bool changed;

        Pixel(bool filled = false,
                const RGB& color = RGB(255, 255, 255),
                bool changed = false);
    };
    bool operator==(const Pixel& p1, const Pixel& p2);
    bool operator!=(const Pixel& p1, const Pixel& p2);
}
