/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#include "Cell.h"

Cell::Cell()
{
    setTextColor(BLUE,WHITE);
}

void Cell::init(short x,short y)
{
    number = -1;
    coord.x = x;
    coord.y = y;
    type = none;
    letter = ' ';
}

void Cell::init(short x,short y,short number,cell_type type,direction dir)
{
    this->number = number;
    this->type = type;
    coord.x = x;
    coord.y = y;
    this->dir = dir;
}



void Cell::draw(RGBI const& background)
{
    global.x = (coord.x*4)+1;
    global.y = (coord.y*4)+1;
    if(type==head)
    {
        pretty_cout(number,(number < 10)?" ":""," ", global.x, global.y, BRIGHTWHITE, background);
        pretty_cout(" ",letter," ", global.x, global.y+1, LIGHTYELLOW, background);
        pretty_cout(" "," "," ", global.x, global.y+2, BRIGHTWHITE, background);
    }
    else if(type==tail)
    {
        pretty_cout(" "," "," ", global.x, global.y, BRIGHTWHITE, background);
        pretty_cout(" ",letter," ", global.x, global.y+1, LIGHTYELLOW, background);
        pretty_cout(" "," "," ", global.x, global.y+2, BRIGHTWHITE, background);
    }
    else if(type==none)
    {
        pretty_cout(char(176),char(176),char(176), global.x, global.y, BRIGHTWHITE, background);
        pretty_cout(char(176),char(176),char(176), global.x, global.y+1, BRIGHTWHITE, background);
        pretty_cout(char(176),char(176),char(176), global.x, global.y+2, BRIGHTWHITE, background);
    }
}

short Cell::getNumber()
{
    return number;
}

direction Cell::getDirection()
{
    return dir;
}

void Cell::setLetter(char letter)
{
    this->letter = letter;
}
