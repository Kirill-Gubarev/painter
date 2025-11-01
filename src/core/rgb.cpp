#include "rgb.h"

RGB::RGB():
    RGB(0){}
RGB::RGB(uint8_t value):
    RGB(value, value, value)
{}
RGB::RGB(uint8_t r, uint8_t g, uint8_t b):
    r(r),
    g(g),
    b(b)
{}

bool RGB::operator==(const RGB& other) const {
    return r == other.r && g == other.g && b == other.b;
}
bool RGB::operator!=(const RGB& other) const {
    return r != other.r || g != other.g || b != other.b;
}
bool RGB::operator<(const RGB& other) const {
    return r < other.r && g < other.g && b < other.b;
}
bool RGB::operator>(const RGB& other) const {
    return r > other.r && g > other.g && b > other.b;
}
bool RGB::operator<=(const RGB& other) const {
    return r <= other.r && g <= other.g && b <= other.b;
}
bool RGB::operator>=(const RGB& other) const {
    return r >= other.r && g >= other.g && b >= other.b;
}

RGB RGB::operator+() const {
    return *this;
}
RGB RGB::operator-() const {
    return RGB(256 - r, 256 - g, 256 - b);
}

RGB RGB::operator+(const RGB& other) const {
    return RGB(r + other.r, g + other.g, b + other.b);
}
RGB RGB::operator-(const RGB& other) const {
    return RGB(r - other.r, g - other.g, b - other.b);
}
RGB RGB::operator*(const RGB& other) const {
    return RGB(r * other.r, g * other.g, b * other.b);
}
RGB RGB::operator/(const RGB& other) const {
    return RGB(r / other.r, g / other.g, b / other.b);
}
RGB RGB::operator%(const RGB& other) const {
    return RGB(r % other.r, g % other.g, b % other.b);
}

RGB& RGB::operator+=(const RGB& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}
RGB& RGB::operator-=(const RGB& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
}
RGB& RGB::operator*=(const RGB& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
}
RGB& RGB::operator/=(const RGB& other) {
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
}
RGB& RGB::operator%=(const RGB& other) {
    r %= other.r;
    g %= other.g;
    b %= other.b;
    return *this;
}

RGB& RGB::operator++() {
    ++r; ++g; ++b;
    return *this;
}
RGB RGB::operator++(int) {
    RGB old = *this;
    ++r; ++g; ++b;
    return old;
}
RGB& RGB::operator--() {
    --r; --g; --b;
    return *this;
}
RGB RGB::operator--(int) {
    RGB old = *this;
    --r; --g; --b;
    return old;
}

RGB operator+(const RGB& c, uint8_t value) {
    return RGB(c.r + value, c.g + value, c.b + value);
}
RGB operator-(const RGB& c, uint8_t value) {
    return RGB(c.r - value, c.g - value, c.b - value);
}
RGB operator*(const RGB& c, uint8_t value) {
    return RGB(c.r * value, c.g * value, c.b * value);
}
RGB operator/(const RGB& c, uint8_t value) {
    return RGB(c.r / value, c.g / value, c.b / value);
}
RGB operator%(const RGB& c, uint8_t value) {
    return RGB(c.r % value, c.g % value, c.b % value);
}

RGB operator+(uint8_t value, const RGB& c) {
    return RGB(value + c.r, value + c.g, value + c.b);
}
RGB operator-(uint8_t value, const RGB& c) {
    return RGB(value - c.r, value - c.g, value - c.b);
}
RGB operator*(uint8_t value, const RGB& c) {
    return RGB(value * c.r, value * c.g, value * c.b);
}
