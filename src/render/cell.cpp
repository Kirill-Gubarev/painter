#include "cell.h"

render::detail::Cell::Cell(wchar_t glyph, const RGB& fg, const RGB& bg, uint8_t updates_left):
    glyph(glyph),
    fg(fg),
    bg(bg),
    updates_left(updates_left)
{}
bool render::detail::operator==(const Cell& c1, const Cell& c2){
    return c1.glyph == c2.glyph && c1.fg == c2.fg && c1.bg == c2.bg;
}
bool render::detail::operator!=(const Cell& c1, const Cell& c2){
    return c1.glyph != c2.glyph || c1.fg != c2.fg || c1.bg != c2.bg;
}
