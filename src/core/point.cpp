#include "point.h"

core::Point::Point():
    x(0),
    y(0)
{}
core::Point::Point(int value):
    x(value),
    y(value)
{}
core::Point::Point(int x, int y):
    x(x),
    y(y)
{}

int core::Point::area(){
    return x * y;
}

bool core::Point::operator==(const Point& other) const {
	return x == other.x && y == other.y;
}
bool core::Point::operator!=(const Point& other) const {
	return x != other.x || y != other.y;
}
bool core::Point::operator<(const Point& other) const {
	return x < other.x && y < other.y;
}
bool core::Point::operator>(const Point& other) const {
	return x > other.x && y > other.y;
}
bool core::Point::operator<=(const Point& other) const {
	return x <= other.x && y <= other.y;
}
bool core::Point::operator>=(const Point& other) const {
	return x >= other.x && y >= other.y;
}

core::Point core::Point::operator+() const {
	return *this;
}
core::Point core::Point::operator-() const {
	return Point(-x, -y);
}

core::Point core::Point::operator+(const Point& other) const {
	return Point(x + other.x, y + other.y);
}
core::Point core::Point::operator-(const Point& other) const {
	return Point(x - other.x, y - other.y);
}
core::Point core::Point::operator*(const Point& other) const {
	return Point(x * other.x, y * other.y);
}
core::Point core::Point::operator/(const Point& other) const {
	return Point(x / other.x, y / other.y);
}
core::Point core::Point::operator%(const Point& other) const {
	return Point(x % other.x, y % other.y);
}

core::Point& core::Point::operator+=(const Point& other){
    x += other.x;
    y += other.y;
	return *this;
}
core::Point& core::Point::operator-=(const Point& other){
    x -= other.x;
    y -= other.y;
	return *this;
}
core::Point& core::Point::operator*=(const Point& other){
    x *= other.x;
    y *= other.y;
	return *this;
}
core::Point& core::Point::operator/=(const Point& other){
    x /= other.x;
    y /= other.y;
	return *this;
}
core::Point& core::Point::operator%=(const Point& other){
    x %= other.x;
    y %= other.y;
	return *this;
}

core::Point& core::Point::operator++(){
    ++x; ++y;
	return *this;
}
core::Point core::Point::operator++(int){
    Point old = *this;
    ++x; ++y;
	return old;
}
core::Point& core::Point::operator--(){
    --x; --y;
	return *this;
}
core::Point core::Point::operator--(int){
    Point old = *this;
    --x; --y;
	return old;
}

core::Point operator+(const core::Point& p, int value){
	return core::Point(p.x + value, p.y + value);
}
core::Point operator-(const core::Point& p, int value){
	return core::Point(p.x - value, p.y - value);
}
core::Point operator*(const core::Point& p, int value){
	return core::Point(p.x * value, p.y * value);
}
core::Point operator/(const core::Point& p, int value){
	return core::Point(p.x / value, p.y / value);
}
core::Point operator%(const core::Point& p, int value){
	return core::Point(p.x % value, p.y % value);
}

core::Point operator+(int value, const core::Point& p){
	return core::Point(value + p.x, value + p.y);
}
core::Point operator-(int value, const core::Point& p){
	return core::Point(value - p.x, value - p.y);
}
core::Point operator*(int value, const core::Point& p){
	return core::Point(value * p.x, value * p.y);
}

std::string to_string(const core::Point& p){
    return "(" + std::to_string(p.x) + ";" + std::to_string(p.y) + ")";
}
