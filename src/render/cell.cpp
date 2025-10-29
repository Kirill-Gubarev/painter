#include "cell.h"

render::Cell::Cell(wchar_t glyph, const RGB& fg, const RGB& bg, bool changed):
    glyph(glyph),
    fg(fg),
    bg(bg),
    changed(changed)
{}
bool render::operator==(const Cell& c1, const Cell& c2){
    return c1.glyph == c2.glyph && c1.fg == c2.fg && c1.bg == c2.bg;
}
bool render::operator!=(const Cell& c1, const Cell& c2){
    return c1.glyph != c2.glyph || c1.fg != c2.fg || c1.bg != c2.bg;
}
