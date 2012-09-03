/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include "Cell.h"
#include <windows.h>
#include <map>

//! dimentions of the puzzle, 15 means 15x15
const short puzzle_dimen = 15;

struct Environment
{
    char letter;
    short U,D,L,R;
};


class Puzzle
{
    Cell cells[puzzle_dimen][puzzle_dimen];
    map<short,Coordinate> headCoord;
    map<short,string> headWord;

public:
    /**  Initialize the coordinates for puzzle cells
    *    @Post 2D cells are initialized */
    void init();

    /**  Draw the 2D cells
    *    @Post 2D cells are drawn */
    void draw();

    /**  Draw the 2D cells specifying the color, direction and coordinates
    *    @Param color of cells to be drawn
    *           coordinated is starting coordinate of cells
    *           direction of drawing cells
    *           length of cells word
    *           word to be set in cells
    *    @Post 2D cells are drawn */
    void draw(RGBI const& background,Coordinate coord,direction dir,int length,string word="");

    /**  Observe the surrounding enviroment of a cell and check the space in each direction of puzzle
    *    @Pram coordinates of cell to be observed
    *          env is environment
    *    @Post env is updates with observation of 4 directions    */
    void observeEnvironemt(Coordinate coord, Environment &env);

    /**  Insert a word into the puzzle for style generation, generate a random starting letter for next word
    *    @Pram word, the original word
    *          number is the word number
    *          coord, coordinate of head
    *          dir, direction of word cells
    *          env, surrounding environment
    *    @Post coord is updated with the random cell coordinates
    *          env is updated with random letter and observation data*/
    void insert(string word, short number, Coordinate &coord, direction dir, Environment &env);

    /**  Highlight a word to show selection.
    *    @Pram background color
    *          number, word number
    *    @Post word is lighlighted to the color    */
    void selectWord(RGBI const& background,short number) throw(short);

    /**  Enter a user input word into equivalent cells
    *    @Pram number is word number
    *          word
    *    @Post word is entered into cells    */
    void enterWord(short number,string word) throw(short);
};

#endif
