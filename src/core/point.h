#pragma once

#include <iostream>

struct Point{
    int x, y;
    Point();
    Point(int x, int y);

    int area();
};

bool operator==(const Point& p1, const Point& p2);
bool operator!=(const Point& p1, const Point& p2);
