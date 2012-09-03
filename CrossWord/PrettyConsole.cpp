/*
  version : 1Feb2010
  Copyright (C) 2010 Victor Soh Chien Ming <cmsoh@mmu.edu.my>

  The following code should work on Windows 2000 and above
*/
#ifndef   PrettyConsole_cpp
#define   PrettyConsole_cpp
#include "PrettyConsole.hpp"
#include <windows.h>
RGBI::RGBI( bool r, bool g, bool b, bool i ):r(r),g(g),b(b),i(i){}

void setTextColor( RGBI const& foreground, RGBI const& background )
{
    WORD              attribute =0;
    if( foreground.r )attribute|=FOREGROUND_RED;
    if( foreground.g )attribute|=FOREGROUND_GREEN;
    if( foreground.b )attribute|=FOREGROUND_BLUE;
    if( foreground.i )attribute|=FOREGROUND_INTENSITY;
    if( background.r )attribute|=BACKGROUND_RED;
    if( background.g )attribute|=BACKGROUND_GREEN;
    if( background.b )attribute|=BACKGROUND_BLUE;
    if( background.i )attribute|=BACKGROUND_INTENSITY;
    SetConsoleTextAttribute
    (GetStdHandle(STD_OUTPUT_HANDLE),attribute);
}

void setCursorXY( int x, int y )
{
    COORD coord;
    coord.X = static_cast<SHORT>(x);
    coord.Y = static_cast<SHORT>(y);
    SetConsoleCursorPosition
    (GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
#endif
