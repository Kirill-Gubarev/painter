#pragma once

#include <cstdint>
#include <iostream>

struct RGB{
    uint8_t r, g, b;
    RGB();
    RGB(uint8_t r, uint8_t g, uint8_t b);
};

bool operator==(const RGB& c1, const RGB& c2);
bool operator!=(const RGB& c1, const RGB& c2);
