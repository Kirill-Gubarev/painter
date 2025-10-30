#pragma once

#include "core/point.h"
#include "core/rgb.h"

namespace render{
    void setup();
    void cleanup();
    void update();
    void clear_screen();

    void set_global_fg(const RGB& color);
    void set_global_bg(const RGB& color);

    void set_cell(const Point& p,
            wchar_t glyph = L' ',
            const RGB& fg = RGB(255, 255, 255),
            const RGB& bg = RGB(0, 0, 0));
    void set_pixel(const Point& p,
            bool filled = true,
            const RGB& color = RGB(255, 255, 255));
}
