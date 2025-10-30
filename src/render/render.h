#pragma once

#include "core/point.h"
#include "core/rgb.h"

namespace render{
    namespace detail{
        struct Cell;
        void resize(Point new_size);

        // optimizes terminal output
        void set_brush_fg(const RGB& color);
        // optimizes terminal output
        void set_brush_bg(const RGB& color);

        Cell& get_cell(int x, int y);
        // write a space with the global background color
        void clear_screen_cell(int x, int y);
        // write spaces with the global background color
        void clear_screen();
    }

    void init();
    void terminate();
    void update();

    Point get_size();

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
