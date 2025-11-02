#include "rgb.h"

core::RGB::RGB():
    core::RGB(0){}
core::RGB::RGB(uint8_t value):
    RGB(value, value, value)
{}
core::RGB::RGB(uint8_t r, uint8_t g, uint8_t b):
    r(r),
    g(g),
    b(b)
{}

bool core::RGB::operator==(const RGB& other) const {
    return r == other.r && g == other.g && b == other.b;
}
bool core::RGB::operator!=(const RGB& other) const {
    return r != other.r || g != other.g || b != other.b;
}
bool core::RGB::operator<(const RGB& other) const {
    return r < other.r && g < other.g && b < other.b;
}
bool core::RGB::operator>(const RGB& other) const {
    return r > other.r && g > other.g && b > other.b;
}
bool core::RGB::operator<=(const RGB& other) const {
    return r <= other.r && g <= other.g && b <= other.b;
}
bool core::RGB::operator>=(const RGB& other) const {
    return r >= other.r && g >= other.g && b >= other.b;
}

core::RGB core::RGB::operator+() const {
    return *this;
}
core::RGB core::RGB::operator-() const {
    return RGB(256 - r, 256 - g, 256 - b);
}

core::RGB core::RGB::operator+(const RGB& other) const {
    return RGB(r + other.r, g + other.g, b + other.b);
}
core::RGB core::RGB::operator-(const RGB& other) const {
    return RGB(r - other.r, g - other.g, b - other.b);
}
core::RGB core::RGB::operator*(const RGB& other) const {
    return RGB(r * other.r, g * other.g, b * other.b);
}
core::RGB core::RGB::operator/(const RGB& other) const {
    return RGB(r / other.r, g / other.g, b / other.b);
}
core::RGB core::RGB::operator%(const RGB& other) const {
    return RGB(r % other.r, g % other.g, b % other.b);
}

core::RGB& core::RGB::operator+=(const RGB& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}
core::RGB& core::RGB::operator-=(const RGB& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
}
core::RGB& core::RGB::operator*=(const RGB& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
}
core::RGB& core::RGB::operator/=(const RGB& other) {
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
}
core::RGB& core::RGB::operator%=(const RGB& other) {
    r %= other.r;
    g %= other.g;
    b %= other.b;
    return *this;
}

core::RGB& core::RGB::operator++() {
    ++r; ++g; ++b;
    return *this;
}
core::RGB core::RGB::operator++(int) {
    RGB old = *this;
    ++r; ++g; ++b;
    return old;
}
core::RGB& core::RGB::operator--() {
    --r; --g; --b;
    return *this;
}
core::RGB core::RGB::operator--(int) {
    RGB old = *this;
    --r; --g; --b;
    return old;
}

core::RGB operator+(const core::RGB& c, uint8_t value) {
    return core::RGB(c.r + value, c.g + value, c.b + value);
}
core::RGB operator-(const core::RGB& c, uint8_t value) {
    return core::RGB(c.r - value, c.g - value, c.b - value);
}
core::RGB operator*(const core::RGB& c, uint8_t value) {
    return core::RGB(c.r * value, c.g * value, c.b * value);
}
core::RGB operator/(const core::RGB& c, uint8_t value) {
    return core::RGB(c.r / value, c.g / value, c.b / value);
}
core::RGB operator%(const core::RGB& c, uint8_t value) {
    return core::RGB(c.r % value, c.g % value, c.b % value);
}

core::RGB operator+(uint8_t value, const core::RGB& c) {
    return core::RGB(value + c.r, value + c.g, value + c.b);
}
core::RGB operator-(uint8_t value, const core::RGB& c) {
    return core::RGB(value - c.r, value - c.g, value - c.b);
}
core::RGB operator*(uint8_t value, const core::RGB& c) {
    return core::RGB(value * c.r, value * c.g, value * c.b);
}
