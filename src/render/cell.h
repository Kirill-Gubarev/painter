#pragma once

#include "core/rgb.h"

namespace render::detail{
    struct Cell{
        wchar_t glyph;
        RGB fg, bg;
        uint8_t updates_left;

        Cell(wchar_t glyph = L' ',
                const RGB& fg = RGB(255, 255, 255),
                const RGB& bg = RGB(0, 0, 0),
                uint8_t updates_left = 0);
    };
    bool operator==(const Cell& c1, const Cell& c2);
    bool operator!=(const Cell& c1, const Cell& c2);
}
