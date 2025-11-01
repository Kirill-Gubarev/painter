#pragma once

#include <cstdint>

struct RGB{
    uint8_t r, g, b;
    RGB();
    RGB(uint8_t value);
    RGB(uint8_t r, uint8_t g, uint8_t b);

    bool operator==(const RGB& other) const;
    bool operator!=(const RGB& other) const;
    bool operator<(const RGB& other) const;
    bool operator>(const RGB& other) const;
    bool operator<=(const RGB& other) const;
    bool operator>=(const RGB& other) const;

    RGB operator+() const;
    RGB operator-() const;

    RGB operator+(const RGB& other) const;
    RGB operator-(const RGB& other) const;
    RGB operator*(const RGB& other) const;
    RGB operator/(const RGB& other) const;
    RGB operator%(const RGB& other) const;

    RGB& operator+=(const RGB& other);
    RGB& operator-=(const RGB& other);
    RGB& operator*=(const RGB& other);
    RGB& operator/=(const RGB& other);
    RGB& operator%=(const RGB& other);

    RGB& operator++();
    RGB operator++(int);
    RGB& operator--();
    RGB operator--(int);
};

RGB operator+(const RGB& c, uint8_t value);
RGB operator-(const RGB& c, uint8_t value);
RGB operator*(const RGB& c, uint8_t value);
RGB operator/(const RGB& c, uint8_t value);
RGB operator%(const RGB& c, uint8_t value);

RGB operator+(uint8_t value, const RGB& c);
RGB operator-(uint8_t value, const RGB& c);
RGB operator*(uint8_t value, const RGB& c);
