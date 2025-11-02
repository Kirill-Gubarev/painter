#pragma once

#include "core/point.h"
#include "core/rgb.h"
#include "string"

namespace render{
    namespace detail{
        struct Cell;
        void resize(core::Point new_size);

        // optimizes terminal output
        void set_brush_fg(const core::RGB& color);
        // optimizes terminal output
        void set_brush_bg(const core::RGB& color);

        Cell& get_cell(int x, int y);
    }

    void init();
    void terminate();
    void update();

    core::Point get_size();
    const core::RGB& get_global_fg();
    const core::RGB& get_global_bg();

    // write spaces with the global background color
    void clear_screen();
    // write a space with the global background color
    void clear_screen_cell(int x, int y);

    void set_global_fg(const core::RGB& color);
    void set_global_bg(const core::RGB& color);

    void set_cell(const core::Point& p,
            wchar_t glyph = L' ',
            const core::RGB& fg = get_global_fg(),
            const core::RGB& bg = get_global_bg());
    void set_pixel(const core::Point& p,
            bool filled,
            const core::RGB& color);
    void set_text(const core::Point& p,
            const std::string& text,
            const core::RGB& fg = get_global_fg(),
            const core::RGB& bg = get_global_bg());
}
