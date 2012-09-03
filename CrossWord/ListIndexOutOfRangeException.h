/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#ifndef LISTINDEXOUTOFRANGEEXCEPTION
#define LISTINDEXOUTOFRANGEEXCEPTION

#include <stdexcept>
#include <string>

using namespace std;

class ListIndexOutOfRangeException : public out_of_range
{
public:
   ListIndexOutOfRangeException(const string & message = "")
      : out_of_range(message.c_str())
   { }  // end constructor
/**
  For eg:
     if ( (index < 1) || (index > getLength()) )
      throw ListIndexOutOfRangeException(
	 "ListIndexOutOfRangeException: remove index out of range");
*/
}; // end ListIndexOutOfRangeException

#endif
