#include "rgb.h"

RGB::RGB():
    r(0),
    g(0),
    b(0)
{}
RGB::RGB(uint8_t r, uint8_t g, uint8_t b):
    r(r),
    g(g),
    b(b)
{}

bool operator==(const RGB& c1, const RGB& c2){
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}
bool operator!=(const RGB& c1, const RGB& c2){
    return c1.r != c2.r || c1.g != c2.g || c1.b != c2.b;
}
