/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#include "WordQueue.h"
using namespace std;
#include <iostream>

string Word::getFirstDef()
{
    return defGroups[0].defs[0];
}

WordQueue::WordQueue() : headP(NULL), tailP(NULL)
{
    size=0;
}

bool WordQueue::isEmpty()
{
    if(size==0)
        return true;
    else
        return false;
}

void WordQueue::enqueue(Word newword)
{
    Word *tempWord = new Word;
    *tempWord = newword;

    if(isEmpty())
    {
        headP = tempWord;
        tailP = tempWord;
    }
    else
    {

        tailP->next = tempWord;
        tailP = tempWord; // assigning the tail pointer to latest position
    }
    size++;
    //delete tempWord;
    tempWord = NULL;
}

Word* WordQueue::getFront()
{
    Word* temp = headP;
    headP = headP->next;
    size--;
    temp->next = NULL;
    return temp;
}

int WordQueue::getSize()
{
    return size;
}

//void WordQueue::dequeue()
//{
//    Word* temp = headP;
//    headP = headP->next;
//
//    temp->next = NULL;
//    delete temp;
//    size--;
//    cout << size << endl;
//}
//
//WordQueue::~WordQueue()
//{
//    for(int i = size-1; i>=0; i--)
//    {
//        dequeue();
//    }
//}
