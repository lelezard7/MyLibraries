#ifndef CONSOLECONSTRUCTOR_H_
#define CONSOLECONSTRUCTOR_H_

#include <utility>

#include "curses.h"


namespace ONF
{
    constexpr unsigned rgb_to_hex(short r, short g, short b);

    class ConsoleTextEdit;
    void addWindowToConsole(ConsoleTextEdit* window);


    class ConsoleWindow {};

    class ConsoleTextEdit : public ConsoleWindow
    {
        std::pair<int, int> size_;
        std::pair<int, int> position_;
        int Z_Order_;
        unsigned bg_color_;
        unsigned text_color_;

        WINDOW* window_;

    public:
        bool setWidth(int value);
        int getWidth() const;

        bool setHeight(int value);
        int getHeight() const;

        bool setBgColor(unsigned value);
        bool setBgColor(short r, short g, short b);
        unsigned getBgColor() const;

        bool setTextColor(unsigned value);
        bool setTextColor(short r, short g, short b);
        unsigned getTextColor() const;

        bool setPosition(int x, int y);
        std::pair<int, int> getPosition() const;

        bool refresh();

        friend void ONF::addWindowToConsole(ConsoleTextEdit* window);

    };



    void start();
}

#endif
