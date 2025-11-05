#pragma once

#include "core/rgb.h"
#include "render/obj/update_state.h"

namespace render::detail{
    struct Pixel{
        core::RGB color;
        Update_state update;

        explicit Pixel(const core::RGB& color = core::RGB(255, 255, 255),
                Update_state update = Update_state::None);
    };
    bool operator==(const Pixel& p1, const Pixel& p2);
    bool operator!=(const Pixel& p1, const Pixel& p2);
}
