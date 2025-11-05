#include "pixel.h"

render::detail::Pixel::Pixel(const core::RGB& color, Update_state update):
    color(color),
    update(update)
{}
bool render::detail::operator==(const Pixel& p1, const Pixel& p2){
    return p1.color == p2.color;
}
bool render::detail::operator!=(const Pixel& p1, const Pixel& p2){
    return p1.color != p2.color;
}
