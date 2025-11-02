#include "term.h"

#include <cwchar>
#include <cstdio>
#include <clocale>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

core::Point term::get_size(){
    winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return {};
    return {w.ws_col, w.ws_row};
}
core::Point term::get_position(){
    static thread_local char buf[128];
    term::write(L"\033[6n");
    term::flush_in();

    size_t i = 0;
    char ch;
    while(read(STDIN_FILENO, &ch, 1) == 1 && ch != 'R') {
        buf[i++] = ch;
    }
    buf[i] = '\0';

    core::Point pos;
    if (sscanf(buf, "\033[%d;%d", &pos.y, &pos.x) == 2)
        return pos;
    return {};
}
char term::get_char(){
    return getchar();
}

void term::write(wchar_t glyph){
    wprintf(L"%lc", glyph);
}
void term::write(const wchar_t* str){
    wprintf(L"%ls", str);
}
void term::flush_in(){
    std::fflush(stdin);
}
void term::flush_out(){
    std::fflush(stdout);
}

void term::set_fg_color(core::RGB c){
    wprintf(L"\033[38;2;%u;%u;%um", c.r, c.g, c.b);
}
void term::set_bg_color(core::RGB c){
    wprintf(L"\033[48;2;%u;%u;%um", c.r, c.g, c.b);
}
void term::set_position(int x, int y){
    wprintf(L"\033[%d;%dH", y + 1, x + 1);
}
void term::set_position(core::Point p){
    term::set_position(p.x, p.y);
}

void term::set_alt_buf(bool enable){
    if(enable)
        term::write(L"\033[?1049h");
    else
        term::write(L"\033[?1049l");
}
void term::set_cursor_visible(bool enable){
    if(enable)
        term::write(L"\033[?25h");
    else
        term::write(L"\033[?25l");
}
void term::set_echo_mode(bool enable){
    termios mode;
    tcgetattr(STDIN_FILENO, &mode);
    if(enable)
        mode.c_lflag |= ECHO;
    else
        mode.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &mode);
}
void term::set_canonical_mode(bool enable){
    termios mode;
    tcgetattr(STDIN_FILENO, &mode);
    if(enable)
        mode.c_lflag |= ICANON;
    else
        mode.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &mode);
}
void term::set_locale(){
    std::setlocale(LC_ALL,"");
}

void term::return_cursor(){
    term::write(L"\033[H");
}
void term::reset_color(){
    term::write(L"\033[0m");
}
void term::clear(){
    term::write(L"\033[2J");
}
