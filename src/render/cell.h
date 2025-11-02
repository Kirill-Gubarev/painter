#pragma once

#include "core/rgb.h"

namespace render::detail{
    struct Cell{
        wchar_t glyph;
        core::RGB fg, bg;
        uint8_t updates_left;

        Cell(wchar_t glyph = L' ',
                const core::RGB& fg = core::RGB(255, 255, 255),
                const core::RGB& bg = core::RGB(0, 0, 0),
                uint8_t updates_left = 0);
    };
    bool operator==(const Cell& c1, const Cell& c2);
    bool operator!=(const Cell& c1, const Cell& c2);
}
