#pragma once

#include <cstdint>
#include <iostream>

struct RGB{
    uint8_t r, g, b;
    RGB();
    RGB(uint8_t r, uint8_t g, uint8_t b);
};

bool operator==(RGB c1, RGB c2);
bool operator!=(RGB c1, RGB c2);
