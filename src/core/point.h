#pragma once

#include <string>

namespace core {
    struct Point{
        int x, y;
        Point();
        Point(int value);
        Point(int x, int y);

        int area();

        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        bool operator<(const Point& other) const;
        bool operator>(const Point& other) const;
        bool operator<=(const Point& other) const;
        bool operator>=(const Point& other) const;

        Point operator+() const;
        Point operator-() const;

        Point operator+(const Point& other) const;
        Point operator-(const Point& other) const;
        Point operator*(const Point& other) const;
        Point operator/(const Point& other) const;
        Point operator%(const Point& other) const;

        Point& operator+=(const Point& other);
        Point& operator-=(const Point& other);
        Point& operator*=(const Point& other);
        Point& operator/=(const Point& other);
        Point& operator%=(const Point& other);

        Point& operator++();
        Point operator++(int);
        Point& operator--();
        Point operator--(int);
    };
}

core::Point operator+(const core::Point& p, int value);
core::Point operator-(const core::Point& p, int value);
core::Point operator*(const core::Point& p, int value);
core::Point operator/(const core::Point& p, int value);
core::Point operator%(const core::Point& p, int value);

core::Point operator+(int value, const core::Point& p);
core::Point operator-(int value, const core::Point& p);
core::Point operator*(int value, const core::Point& p);

std::string to_string(const core::Point& p);
