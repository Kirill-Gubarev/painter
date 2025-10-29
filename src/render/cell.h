#pragma once

#include "core/rgb.h"

namespace render{
    struct Cell{
        wchar_t glyph;
        RGB fg, bg;
        bool changed;

        Cell(wchar_t glyph = L' ',
                const RGB& fg = RGB(255, 255, 255),
                const RGB& bg = RGB(0, 0, 0),
                bool changed = false);
    };
    bool operator==(const Cell& c1, const Cell& c2);
    bool operator!=(const Cell& c1, const Cell& c2);
}
