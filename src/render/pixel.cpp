#include "pixel.h"

render::Pixel::Pixel(bool filled, const RGB& color, bool changed):
    filled(filled),
    color(color),
    changed(changed)
{}
bool render::operator==(const Pixel& p1, const Pixel& p2){
    return p1.filled == p2.filled && p1.color == p2.color;
}
bool render::operator!=(const Pixel& p1, const Pixel& p2){
    return p1.filled != p2.filled || p1.color != p2.color;
}
