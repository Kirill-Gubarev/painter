#include "rgb.h"

RGB::RGB():
    RGB(0){}
RGB::RGB(uint8_t color):
    RGB(color, color, color)
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
RGB operator+(const RGB& c1, const RGB& c2){
    return RGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}
RGB operator-(const RGB& c1, const RGB& c2){
    return RGB(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}
RGB operator+(const RGB& c1, uint8_t c2){
    return RGB(c1.r + c2, c1.g + c2, c1.b + c2);
}
RGB operator-(const RGB& c1, uint8_t c2){
    return RGB(c1.r - c2, c1.g - c2, c1.b - c2);
}
