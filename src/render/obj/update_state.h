#pragma once

#include <cstdint>

enum class Update_state : uint8_t{
    None = 0, // a clean cell
    Update = 1, // need to update
    Clear = 2, // need to clear
};
