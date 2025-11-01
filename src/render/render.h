#pragma once

#include "core/point.h"
#include "core/rgb.h"
#include "string"

namespace render{
    namespace detail{
        struct Cell;
        void resize(Point new_size);

        // optimizes terminal output
        void set_brush_fg(const RGB& color);
        // optimizes terminal output
        void set_brush_bg(const RGB& color);

        Cell& get_cell(int x, int y);
    }

    void init();
    void terminate();
    void update();

    Point get_size();
    const RGB& get_global_fg();
    const RGB& get_global_bg();

    // write spaces with the global background color
    void clear_screen();
    // write a space with the global background color
    void clear_screen_cell(int x, int y);

    void set_global_fg(const RGB& color);
    void set_global_bg(const RGB& color);

    void set_cell(const Point& p,
            wchar_t glyph = L' ',
            const RGB& fg = get_global_fg(),
            const RGB& bg = get_global_bg());
    void set_pixel(const Point& p,
            bool filled,
            const RGB& color);
    void set_text(const Point& p,
            const std::string& text,
            const RGB& fg = get_global_fg(),
            const RGB& bg = get_global_bg());
}
