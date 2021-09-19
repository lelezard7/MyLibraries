#include "ConsoleConstructor.h"


bool
ONF::ConsoleTextEdit::
setWidth(int value)
{
//    if (value < 0)

    size_.first = value;
    return true;
}

int
ONF::ConsoleTextEdit::
getWidth() const
{
    return size_.first;
}

bool
ONF::ConsoleTextEdit::
setHeight(int value)
{
//    if (value < 0)

    size_.second = value;
    return true;
}

int
ONF::ConsoleTextEdit::
getHeight() const
{
    return size_.second;
}

bool
ONF::ConsoleTextEdit::
setBgColor(unsigned value)
{
//    if (value < 0)

    bg_color_ = value;
    return true;
}

bool
ONF::ConsoleTextEdit::
setBgColor(short r, short g, short b)
{
//    if (value < 0)

    bg_color_ = rgb_to_hex(r, g, b);
    return true;
}

unsigned
ONF::ConsoleTextEdit::
getBgColor() const
{
    return bg_color_;
}

bool
ONF::ConsoleTextEdit::
setTextColor(unsigned value)
{
//    if (value < 0)

    text_color_ = value;
    return true;
}

bool
ONF::ConsoleTextEdit::
setTextColor(short r, short g, short b)
{
//    if (value < 0)

    text_color_ = rgb_to_hex(r, g, b);
    return true;
}

unsigned
ONF::ConsoleTextEdit::
getTextColor() const
{
    return text_color_;
}

bool
ONF::ConsoleTextEdit::
setPosition(int x, int y)
{
    position_.first = x;
    position_.second = y;

    return true;
}

std::pair<int, int>
ONF::ConsoleTextEdit::
getPosition() const
{
    return position_;
}

bool
ONF::ConsoleTextEdit::
refresh()
{
    wresize(window_, size_.second, size_.first);
    mvwin(window_, position_.second, position_.first);

    wrefresh(window_);
    refresh();
}







void
ONF::
addWindowToConsole(ConsoleTextEdit* window)
{
    window->window_ = newwin(window->getHeight(), window->getWidth(),
                               window->getPosition().second, window->getPosition().first);

    wrefresh(window->window_);
    refresh();

    wprintw(window->window_, "Hello, World!\n");

    wrefresh(window->window_);
    refresh();


}



constexpr unsigned
ONF::
rgb_to_hex(short r, short g, short b) //TODO: проверка на диапазон от 0 до 255.
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void ONF::start()
{
    initscr();

    start_color();
//    init_color(768, 229, 43, 80);
//    init_pair(22, COLOR_BLACK, 768);
//    attron(COLOR_PAIR(22));
//    refresh();

//    WINDOW ddd = newwin()

//    printw("Colors: %d\n", COLORS);
//    printw("Color pairs: %d\n", COLOR_PAIRS);
//    printw("Hello, World!\n");
//    hline(ACS_HLINE, 3);
//    border(ACS_HLINE, ACS_HLINE, ACS_HLINE, ACS_HLINE, ACS_HLINE, ACS_HLINE, ACS_HLINE, ACS_HLINE);
//    printw("Hello, World!\n");
//    mvprintw(10, 10, "Hello, World!\n");
//    refresh();
//    chtype ch = 'w' | A_BLINK;
//    addch(ch);
//    addch(ch);
//    printw("Hello, World!\n");

//    getch();

//    endwin();
}
