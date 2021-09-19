#include "ConsoleConstructor.h"

using namespace ONF;

int main(int argc, char *argv[])
{
    start();

    ConsoleTextEdit cte;
    cte.setWidth(100);
    cte.setHeight(10);
    cte.setPosition(10, 10);

    addWindowToConsole(&cte);

    getch();

    cte.setWidth(10);
    cte.setHeight(20);
    cte.setPosition(15, 10);
    cte.refresh();
//    cte.text_color_ = 0;

    getch();
    endwin();
}
