/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#include "Puzzle.h"


void Puzzle::init()
{
    for(short c = 0; c<puzzle_dimen; c++)
    {
        for(short r = 0; r<puzzle_dimen; r++ )
        {
            cells[c][r].init(c,r);
        }
    }
}

void Puzzle::draw()
{
    for(short c = 0; c<puzzle_dimen; c++)
    {
        for(short r = 0; r<puzzle_dimen; r++ )
        {
            cells[c][r].draw();
        }
    }
}

void Puzzle::draw(RGBI const& background,Coordinate coord,direction dir,int length, string word)
{
    bool draw_word = ( (word=="")?false:true ); // if word is not provided don't set letters
    for(int l=0; l<length; l++)
    {
        if(dir==R)
        {
            if(draw_word) cells[coord.x+l][coord.y].setLetter(word[l]);
            cells[coord.x+l][coord.y].draw(background);
        }
        else if(dir==L)
        {
            if(draw_word) cells[coord.x-l][coord.y].setLetter(word[l]);
            cells[coord.x-l][coord.y].draw(background);
        }
        else if(dir==D)
        {
            if(draw_word) cells[coord.x][coord.y+l].setLetter(word[l]);
            cells[coord.x][coord.y+l].draw(background);
        }
        else if(dir==U)
        {
            if(draw_word) cells[coord.x][coord.y-l].setLetter(word[l]);
            cells[coord.x][coord.y-l].draw(background);
        }

    }

}

void Puzzle::observeEnvironemt(Coordinate coord, Environment &env)
{
    int d=0;
    for(d = coord.y-1; d>=0 && cells[coord.x][d].getNumber()==-1; d--); // U
    env.U = abs(d-(coord.y-1));

    d=0;
    for(d = coord.y+1; d<puzzle_dimen && cells[coord.x][d].getNumber()==-1; d++); // D
    env.D = d-(coord.y+1);

    d=0;
    for(d = coord.x+1; d<puzzle_dimen && cells[d][coord.y].getNumber()==-1; d++); // R
    env.R = d-(coord.x+1);

    d=0;
    for(d = coord.x-1; d>=0 && cells[d][coord.y].getNumber()==-1; d--); // L
    env.L = abs(d-(coord.x-1));
}


void Puzzle::insert(string word, short number, Coordinate &coord, direction dir, Environment &env)
{
    unsigned short random_letter = rand()%(word.length()-1)+1;
    if(dir==R)
    {
        for(unsigned int l=0; l<word.length(); l++)
        {
            cells[coord.x+l][coord.y].init(coord.x+l,coord.y,number,((l==0)?head:tail),dir);
            if(l==random_letter) env.letter = char(word[l]-32);
        }
        headCoord[number] = coord;
        headWord[number] = word;
        coord.x += random_letter;
    }
    if(dir==L)
    {
        for(unsigned int l=0; l<word.length(); l++)
        {
            cells[coord.x-l][coord.y].init(coord.x-l,coord.y,number,((l==0)?head:tail),dir);
            if(l==random_letter) env.letter = char(word[l]-32);
        }
        headCoord[number] = coord;
        headWord[number] = word;
        coord.x -= random_letter;
    }
    if(dir==D)
    {
        for(unsigned int l=0; l<word.length(); l++)
        {
            cells[coord.x][coord.y+l].init(coord.x,coord.y+l,number,((l==0)?head:tail),dir);
            if(l==random_letter) env.letter = char(word[l]-32);
        }
        headCoord[number] = coord;
        headWord[number] = word;
        coord.y += random_letter;
    }
    if(dir==U)
    {
        for(unsigned int l=0; l<word.length(); l++)
        {
            cells[coord.x][coord.y-l].init(coord.x,coord.y-l,number,((l==0)?head:tail),dir);
            if(l==random_letter) env.letter = char(word[l]-32);
        }
        headCoord[number] = coord;
        headWord[number] = word;
        coord.y -= random_letter;
    }
    observeEnvironemt(Coordinate(coord.x,coord.y),env);
    //cout << "%" << word << "%";
}

void Puzzle::selectWord(RGBI const& background,short number) throw(short)
{
    if( number<1 || number>short(headWord.size()) ) throw number;
    Coordinate coord = headCoord[number];
    string word = headWord[number];
    direction dir = cells[coord.x][coord.y].getDirection();
    draw(background,coord,dir,word.length());
}

void Puzzle::enterWord(short number,string word) throw(short)
{
    if( number<1 || number>short(headWord.size()) ) throw number;
    Coordinate coord = headCoord[number];
    direction dir = cells[coord.x][coord.y].getDirection();
    draw(RED,coord,dir,word.length(),word);
}
