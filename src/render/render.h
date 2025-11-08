#pragma once

#include "core/point.h"
#include "core/rgb.h"

#include <string>

namespace render{
    using core::Point;
    using core::RGB;

    struct Stats{
        int clear_count;
        int update_count;
    };

    namespace detail{
        struct Cell;
        void resize(Point size);
        Cell& get_cell(const Point& p);
    }

    // main functions
    void init();
    void terminate();
    void update();

    // getters
    Point get_screen_size();
    Point get_canvas_size();
    RGB get_default_fg();
    RGB get_default_bg();
    Stats get_stats();

    // write spaces with the default background color
    void clear();
    // write a space with the default background color
    void clear_screen_cell(const Point& p, const RGB& color = get_default_bg());

    // setters
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
