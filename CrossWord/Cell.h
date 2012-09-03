/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
using namespace std;
#include "PrettyConsole.hpp"

/*! Colors for foreground and background colors */
#define WHITE RGBI(1,1,1,0)
#define BRIGHTWHITE RGBI(1,1,1,1)
#define RED RGBI(1,0,0,0)
#define LIGHTYELLOW RGBI(1,1,0,1)
#define BLUE RGBI(0,0,1,0)
#define CYAN RGBI(0,1,1,0)
#define GRAY RGBI(0,0,0,1)
#define GREEN RGBI(0,1,0,0)
#define BLACK RGBI(0,0,0,0)

enum direction {U,D,L,R,Invalid,skip};

/**  Print 3 variables based on formatting
*    @Param T1 to T3 variable
*           x,y coordinates
*           foreground, background colors
*    @Post  three variables are printed adjacently at coordinate with colors */
template<typename T1,typename T2,typename T3>
void pretty_cout(T1 prefix, T2 middlefix, T3 suffix, int x,int y,RGBI const& foreground,RGBI const& background)
{
    setTextColor(foreground,background);
    setCursorXY(x,y);
    cout << prefix << middlefix << suffix;
}

struct Coordinate
{
    Coordinate() {}
    Coordinate(short x,short y): x(x), y(y) {}
    short x,y;
};

enum cell_type {head, tail, none};
class Cell
{
    Coordinate coord,global;

    int number; // number of cell
    char letter;
    cell_type type; // type of cell: head, tail, none
    direction dir; // direction of tailing cells

public:
    Cell();

    /**  Initialize empty cells for drawing
    *    @Param x,y coordinates
    *    @Post number=-1 , type=none , letter =' ' */
    void init(short x,short y);

    /**  Initialize cells for drawing
    *    @Param x,y coordinates
    *           number is cell number for head
    *           type is type of cell. head, tail or none
    *            direction is direction of tail cells  */
    void init(short x,short y,short number,cell_type type=tail,direction dir=skip);

    /**  Draw cells with desired bg color
    *    @Param color */
    void draw(RGBI const& background=RED);

    /**  Return the number of cell (head)
    *    @Return cell head number */
    short getNumber();

    /**  Return the direction of cell (head)
    *    @Return cell head direction */
    direction getDirection();

    /**  Set the letter for the cell
    *    @Param letter single character */
    void setLetter(char letter);
};


#endif
