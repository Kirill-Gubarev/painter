#include "point.h"

Point::Point():
    x(0),
    y(0)
{}
Point::Point(int value):
    x(value),
    y(value)
{}
Point::Point(int x, int y):
    x(x),
    y(y)
{}

int Point::area(){
    return x * y;
}

bool Point::operator==(const Point& other) const {
	return x == other.x && y == other.y;
}
bool Point::operator!=(const Point& other) const {
	return x != other.x || y != other.y;
}
bool Point::operator<(const Point& other) const {
	return x < other.x && y < other.y;
}
bool Point::operator>(const Point& other) const {
	return x > other.x && y > other.y;
}
bool Point::operator<=(const Point& other) const {
	return x <= other.x && y <= other.y;
}
bool Point::operator>=(const Point& other) const {
	return x >= other.x && y >= other.y;
}

Point Point::operator+() const {
	return *this;
}
Point Point::operator-() const {
	return Point(-x, -y);
}

Point Point::operator+(const Point& other) const {
	return Point(x + other.x, y + other.y);
}
Point Point::operator-(const Point& other) const {
	return Point(x - other.x, y - other.y);
}
Point Point::operator*(const Point& other) const {
	return Point(x * other.x, y * other.y);
}
Point Point::operator/(const Point& other) const {
	return Point(x / other.x, y / other.y);
}
Point Point::operator%(const Point& other) const {
	return Point(x % other.x, y % other.y);
}

Point& Point::operator+=(const Point& other){
    x += other.x;
    y += other.y;
	return *this;
}
Point& Point::operator-=(const Point& other){
    x -= other.x;
    y -= other.y;
	return *this;
}
Point& Point::operator*=(const Point& other){
    x *= other.x;
    y *= other.y;
	return *this;
}
Point& Point::operator/=(const Point& other){
    x /= other.x;
    y /= other.y;
	return *this;
}
Point& Point::operator%=(const Point& other){
    x %= other.x;
    y %= other.y;
	return *this;
}

Point& Point::operator++(){
    ++x; ++y;
	return *this;
}
Point Point::operator++(int){
    Point old = *this;
    ++x; ++y;
	return old;
}
Point& Point::operator--(){
    --x; --y;
	return *this;
}
Point Point::operator--(int){
    Point old = *this;
    --x; --y;
	return old;
}

Point operator+(const Point& p, int value){
	return Point(p.x + value, p.y + value);
}
Point operator-(const Point& p, int value){
	return Point(p.x - value, p.y - value);
}
Point operator*(const Point& p, int value){
	return Point(p.x * value, p.y * value);
}
Point operator/(const Point& p, int value){
	return Point(p.x / value, p.y / value);
}
Point operator%(const Point& p, int value){
	return Point(p.x % value, p.y % value);
}

Point operator+(int value, const Point& p){
	return Point(value + p.x, value + p.y);
}
Point operator-(int value, const Point& p){
	return Point(value - p.x, value - p.y);
}
Point operator*(int value, const Point& p){
	return Point(value * p.x, value * p.y);
}

std::string to_string(const Point& p){
    return "(" + std::to_string(p.x) + ";" + std::to_string(p.y) + ")";
}
