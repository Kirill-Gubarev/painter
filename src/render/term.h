#pragma once

#include "core/point.h"
#include "core/rgb.h"

namespace term{
    core::Point get_size();
    core::Point get_position();
    char get_char();

    void write(wchar_t glyph);
    void write(const wchar_t* str);

    void flush_in();
    void flush_out();

    //set cursor status
    void set_fg_color(core::RGB c);
    void set_bg_color(core::RGB c);
    void set_position(int x, int y);
    void set_position(core::Point p);

    //set terminal mode
    void set_alt_buf(bool enable);
    void set_cursor_visible(bool enable);
    void set_echo_mode(bool enable);
    void set_canonical_mode(bool enable);
    void set_locale();

    //reset terminal
    void return_cursor();
    void reset_color();
    void clear();
}
