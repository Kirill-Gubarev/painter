#pragma once

#include <string>

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

Point operator+(const Point& p, int value);
Point operator-(const Point& p, int value);
Point operator*(const Point& p, int value);
Point operator/(const Point& p, int value);
Point operator%(const Point& p, int value);

Point operator+(int value, const Point& p);
Point operator-(int value, const Point& p);
Point operator*(int value, const Point& p);

std::string to_string(const Point& p);
