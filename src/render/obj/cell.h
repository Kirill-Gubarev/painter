#pragma once

#include "core/rgb.h"
#include "render/obj/update_state.h"

namespace render::detail{
    struct Cell{
        wchar_t glyph;
        core::RGB fg, bg;
        Update_state update;

        explicit Cell(wchar_t glyph = L' ',
                const core::RGB& fg = core::RGB(255, 255, 255),
                const core::RGB& bg = core::RGB(0, 0, 0),
                Update_state update = Update_state::None);
    };
    bool operator==(const Cell& c1, const Cell& c2);
    bool operator!=(const Cell& c1, const Cell& c2);
}
