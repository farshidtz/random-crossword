/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#ifndef __LIST_P__
#define __LIST_P__

#include "ListException.h"
#include "ListIndexOutOfRangeException.h"

typedef string ListItemType;

/**  Specification of the ADT List
* @Elements: Any valid data type. Ahmed
* @Structure: Elements are linearly arranged which
*           allow random access. There is a first
*           element that has a unique successor
*           and a last element that has a unique
*           predecessor, every other element has
*           a unique predecessor and a unique
*           successor .
* @Domain: The number of elements is bounded
*/
class List
{
public:
    /** Default constructor. */
    List();

    /** Deep Copy constructor.
     * @Param aList The list to copy. */
    List(const List& aList);

    /** Destructor. */
    ~List();

    /** Checks whether the list is empty or not
     * @Pre A list exists.
     * @Post None.
     * @Param None.
     * @Return returns true if the list is empty otherwise false. */
    bool isEmpty() const;

    /** Returns the length of list
     * @Pre A list exists..
     * @Post None.
     * @Param None.
     * @Return returns the length of list in integer */
    int getLength() const;

    /** Inserts new element to the list at desired index
     * @Pre Datatype is valid, index in in range
     * @Post Element is inserted at index
     * @Param index is the desired position of the newItem.
              newItem is the item
     * @Return None */
    void insert(int index, const ListItemType& newItem) throw(ListIndexOutOfRangeException, ListException);

    /** Remove an element from the list at desired index
     * @Pre index is in range
     * @Post Element is removed from index
     * @Param index is the desired position of the newItem.
     * @Return None */
    void remove(int index) throw(ListIndexOutOfRangeException);

    /** Retrieve element at desired index from the list
     * @Pre index is in range.
     * @Post dataItem is passed by reference
     * @Param index is the desired position of the newItem.
              dataItem is the item that is retrieved
     * @Return None */
    void retrieve(int index, ListItemType& dataItem) const throw(ListIndexOutOfRangeException);

private:
    /** A node on the list. */
    struct ListNode
    {
        /** A data item on the list. */
        ListItemType item;
        /** Pointer to next node. */
        ListNode    *next;
    }; // end ListNode

    /** Number of items in list. */
    int       size;
    /** Pointer to linked list of items. */
    ListNode *head;

    /** Locates a specified node in a linked list.
     * @Pre index is the number of the desired node.
     * @Post None.
     * @Param index The index of the node to locate.
     * @Return A pointer to the index-th node. If index < 1
     *         or index > the number of nodes in the list,
     *         returns NULL. */
    ListNode* find(int index) const;
}; // end List


#endif
