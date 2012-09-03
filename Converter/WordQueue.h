/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#ifndef __WORDQUEUE_H__
#define __WORDQUEUE_H__

#include <string>
#include <vector>
using namespace std;

struct DefGroup
{
    string synonyms;
    short numOfDefs;

    vector<string> defs;
};

struct Word
{
    string word;
    short numOfDefGroups;
    vector<DefGroup> defGroups;
    string getFirstDef();

    Word* next;
};

/** ADT Specification
    The queue holds elements of type Word
    the elements can only be added to the
    back of queue and retrieved from the
    front. Elements will be deleted after
    retrieval from the front.
    This queue can grow in size.  **/
class WordQueue
{
private:
    int size;
    Word *headP;
    Word *tailP;

public:
    WordQueue();

    /** Check whether queue is empty or not
    * @Return true if queue is empty, false if not. */
    bool isEmpty();

    /** Enter word into queue
    * @Param thisword is a Word
    * @Post thisword is entered to the queue */
    void enqueue(Word thisword);

    /** Get the front element of queue and then remove it
    * @Post word is removed from the queue (dequeued)
      @Return the element at front of queue */
    Word* getFront();

    /** Find size of queue
    * @Return returns the size of queue */
    int getSize();

//    void dequeue(); // combined with getFront
//    ~WordQueue();
};

#endif
