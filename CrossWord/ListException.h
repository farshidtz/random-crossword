/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#ifndef LISTEXCEPTION
#define LISTEXCEPTION

#include <stdexcept>
#include <string>

using namespace std;

class ListException : public logic_error
{
public:
   ListException(const string & message = "")
      : logic_error(message.c_str())
   { }  // end constructor
/**
  For eg:
    catch (bad_alloc e)
    {
	  throw ListException(
	    "ListException: memory allocation failed on insert");
    }
*/
}; // end ListException

#endif
