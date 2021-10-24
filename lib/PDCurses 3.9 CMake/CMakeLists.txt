cmake_minimum_required(VERSION 3.5)
project(dd LANGUAGES C CXX)

set(CMAKE_RC_COMPILER_INIT windres)
  ENABLE_LANGUAGE(RC)
  SET(CMAKE_RC_COMPILE_OBJECT
    "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")



add_library(PDc
    wincon/pdcclip.c
    wincon/pdcdisp.c
    wincon/pdcgetsc.c
    wincon/pdckbd.c
    wincon/pdcscrn.c
    wincon/pdcsetsc.c
    wincon/pdcutil.c
    wincon/pdcwin.h

    curses.h
    curspriv.h
    panel.h

    pdcurses/addch.c
    pdcurses/addchstr.c
    pdcurses/addstr.c
    pdcurses/attr.c
    pdcurses/beep.c
    pdcurses/bkgd.c
    pdcurses/border.c
    pdcurses/clear.c
    pdcurses/color.c
    pdcurses/debug.c
    pdcurses/delch.c
    pdcurses/deleteln.c
    pdcurses/getch.c
    pdcurses/getstr.c
    pdcurses/getyx.c
    pdcurses/inch.c
    pdcurses/inchstr.c
    pdcurses/initscr.c
    pdcurses/inopts.c
    pdcurses/insch.c
    pdcurses/insstr.c
    pdcurses/instr.c
    pdcurses/kernel.c
    pdcurses/keyname.c
    pdcurses/mouse.c
    pdcurses/move.c
    pdcurses/outopts.c
    pdcurses/overlay.c
    pdcurses/pad.c
    pdcurses/panel.c
    pdcurses/printw.c
    pdcurses/refresh.c
    pdcurses/scanw.c
    pdcurses/scr_dump.c
    pdcurses/scroll.c
    pdcurses/slk.c
    pdcurses/termattr.c
    pdcurses/touch.c
    pdcurses/util.c
    pdcurses/window.c

    common/pdcurses.rc)

target_include_directories(PDc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(PDc PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

target_link_directories(PDc PUBLIC ${CMAKE_CURRENT_BINARY_DIR})



#if(WIN32) #Windows_NT

#endif()

