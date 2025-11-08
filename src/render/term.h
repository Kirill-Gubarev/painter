#pragma once

#include "core/point.h"
#include "core/rgb.h"

namespace term{
    char get_char();

    core::Point get_size();
    core::RGB get_default_fg();
    core::RGB get_default_bg();

    void write(wchar_t glyph);
    void write(const wchar_t* str);

    //set cursor status
    void set_fg_color(const core::RGB& c);
    void set_bg_color(const core::RGB& c);
    void set_position(const core::Point& new_pos);

    //set terminal mode
    void set_alt_buf(bool enable);
    void set_cursor_visible(bool enable);
    void set_echo_mode(bool enable);
    void set_canonical_mode(bool enable);
    void set_locale();

    void reset_color();
    void clear();
}
