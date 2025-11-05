#pragma once

#include "core/point.h"
#include "core/rgb.h"

#include <string>

namespace render{
    using core::Point;
    using core::RGB;

    namespace detail{
        struct Cell;
        void resize(Point size);

        // optimizes terminal output
        void set_brush_fg(const RGB& color);
        // optimizes terminal output
        void set_brush_bg(const RGB& color);

        Cell& get_cell(const Point& p);
    }

    void init();
    void terminate();
    void update();

    Point get_screen_size();
    Point get_canvas_size();
    const RGB& get_default_fg();
    const RGB& get_default_bg();
    int get_count_updates();

    // write spaces with the default background color
    void clear_screen(const RGB& color = get_default_bg());
    // write a space with the default background color
    void clear_screen_cell(const Point& p, const RGB& color = get_default_bg());

    void set_default_fg(const RGB& color);
    void set_default_bg(const RGB& color);

    void set_cell(const Point& p,
            wchar_t glyph = L' ',
            const RGB& fg = get_default_fg(),
            const RGB& bg = get_default_bg());
    void set_pixel(const Point& p,
            const RGB& color = get_default_fg());
    void set_text(const Point& p,
            const std::string& text,
            const RGB& fg = get_default_fg(),
            const RGB& bg = get_default_bg());
}
