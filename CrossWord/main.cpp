/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <map>
#include <time.h>
#include <stdexcept>
#include <sstream>

using namespace std;
#include "Cell.h"
#include "Puzzle.h"
#include "ListP.h"

//! based on stats in Converter application, we know that: Min length = 2 , Max length = 20
const int minLength = 2;
const int maxLength = puzzle_dimen+1;
//! ****************************************************************************************/

/** Draw a box
*    @Pre x>y and more than 0
*         length,heigth must be more than 0
*    @Param x,y are coordinates, length,heigth are width and heigth of the box */
void draw_box(int x, int y, int lenght, int height)
{
    int l=0;
    for(int i=0; i<lenght; i++)
    {
        setCursorXY(x+i,y+l);

        if((i == (lenght-1)) && (l <= height))
        {
            l++;
            i = -1;
        }
        if((x != 0)&&(y !=0)) setTextColor(RGBI(1,1,1,1),RGBI(1,1,1,1));
        cout << " ";
    }
    setTextColor(RGBI(0,0,0,0),RGBI(1,1,1,1));
}

/** Show list of clues
*    @Pre x>y and more than 0
*         x2>x , y2>y
*    @Param x,y are starting coordinates, x2,y2 are ending coordinates */
void showClues(string clues, short x, short y, short x2, short y2)
{
    setTextColor(GRAY,BRIGHTWHITE);
    unsigned int index = 0, clues_length = clues.size();
    for(short j = y; j<=y2 ; j++)
    {
        for(short i = x; i<=x2 && index<clues_length ; i++)
        {
            setCursorXY(i,j);
            if(clues[index]==';')
            {
                j+=2; // break two lines after each clue
                i = x-1; // set cursor back to starting x
            }
            else if(index<clues.length()-1) cout << clues[index];
            index++;
        }

    }
}

/**  Adds all clues to a single container
*    @Param clue is the clue to be added to container
*           number is the clue number
*           clues is the container
*    @Post  number and clue are appended to clues container */
void addtoClueContainer(string clue,short number, string &clues)
{
    stringstream ss;
    ss << number << ". " << clue << ";";
    clues.append(ss.str());
}


/** The struct that contains words and clues during the word import from database */
struct Word_Clue
{
    Word_Clue() {}
    Word_Clue(string word,string clue) : word(word), clue(clue) {}
    string word;
    string clue;
};


/** Go through the map and turn it into hash table
*    @Pre   map<length, number of occurances>
*    @Post  map<length, index> ; index = -1 for occurances of 0
*    @Param map with short key and int element  */
void turn_it_to_hashtable(map<short,int> &length_indexMap)
{
    int temp = length_indexMap[minLength], temp2;
    length_indexMap[minLength] = 0;
    for(int it=minLength; it<=maxLength+1; it++) // until maxLength+1 so that it checks for occurances until maxLength
    {
        if(it%2==0)
        {
            temp2 = length_indexMap[it+1];
            length_indexMap[it+1] = length_indexMap[it] + temp;
        }
        else
        {
            temp = length_indexMap[it+1];
            length_indexMap[it+1] = length_indexMap[it] + temp2;
        }
        if(it!=minLength && length_indexMap[it]==length_indexMap[it-1]) length_indexMap[it-1] = -1; // if occurance is 0, index=-1
    }
}

/**  Imports data from required database file into a vector and creates a map based on length of letters
*    @Param letter is the name of required file.
*           word_clues is container of importing words and clues
*           length_indexMap is the map for tracking elements based on their lengths
*    @Post  word_clues will contain words and clues
*           length_indexMap will contain map of words */
void importData(char letter, vector<Word_Clue> &word_clue, map<short,int> &length_indexMap)
{
    string filename = string("./data/") + letter + string(".txt");
    ifstream datafile(filename.c_str());
    if (datafile.is_open())
    {
        //! Loading Words

        // initialize map elements to 0
        // maxLength+1 is used to get number of occurances for letters with the longest length
        for(int it=minLength; it<=maxLength+1; it++)
            length_indexMap[it] = 0;


        while ( datafile.good() )
        {
            static string word,clue;
            getline (datafile,word);
            getline (datafile,clue);
            word_clue.push_back(Word_Clue(word,clue));
            length_indexMap[word.length()]++; // increment the map element for the key of that word's length
        }
        datafile.close();

        // turn length_index map into a hash table to find word index based on word length
        turn_it_to_hashtable(length_indexMap);
    }
    else
    {
        cout << "Unable to open file";
        exit(0);
    }
}

/**  Provide a starting letter and length to get a random word and its clue
*    @Pre   A word with these parameters exist
*    @Param myword is the word to be found
*           starting_letter, will be random if not provided
*           required_length, will be random if not provided
*    @Post  myword contains the founded word */
void getRandom_Word_Clue(Word_Clue* myword, char letter = '-',short required_length = -1) throw(range_error,runtime_error)
{
    vector<Word_Clue> word_clue; // to contain all words starting with a character
    map<short,int> word_clue_Map; // to store a hash table for word lengths

    if(letter=='-') // no parameter given
        letter = char(rand()%26 +65); // randomely generate a letter from A to Z
    importData(letter,word_clue,word_clue_Map);

    int starting_index = -1;
    int rand_length;

    short thisMaxLength = (required_length==-1 ? maxLength-1 : required_length); // use required length if provided
    short randRange = thisMaxLength-minLength+1;
    while(starting_index==-1)
    {
        if(randRange<1)
            throw range_error("Invalid range for rand!"); // RandRange will be 0 before a direction is being closed by close_direction(dir,&env)
        rand_length = rand()%randRange +minLength; // randomely generate an integer between minLength and maxLength
        starting_index = word_clue_Map[rand_length];
        if(randRange==1 && starting_index==-1)
            throw runtime_error("No word exists with this length.");
    }

    int it;
    for(it=1; word_clue_Map[rand_length+it]==-1; it++); // skip lengths with no occurances
    int ending_index = word_clue_Map[rand_length+it];
    int interval = ending_index - starting_index;
    int rand_index = rand()%interval +starting_index; // randomely generate an integer between startin and ending index of words with rand_length

    *myword = word_clue[rand_index];
}

/**  Generate a random direction based on the environment
*    @Param env is the environment around the cell
*           length is the available free range along that direction
*    @Post  length is the available free range along that direction
*    @Return random direction , Invalid if not found */
direction getRandom_direction(Environment env,short* length)
{
    vector<direction> available_directions;
    vector<short> direction_lengths;
    if(env.U>0)
    {
        available_directions.push_back(U);
        direction_lengths.push_back(env.U+1);
    }
    if(env.D>0)
    {
        available_directions.push_back(D);
        direction_lengths.push_back(env.D+1);
    }
    if(env.R>0)
    {
        available_directions.push_back(R);
        direction_lengths.push_back(env.R+1);
    }
    if(env.L>0)
    {
        available_directions.push_back(L);
        direction_lengths.push_back(env.L+1);
    }
    short size = available_directions.size();

    //short random;
    short index_of_largest = 0;
    if(size>0)
    {
        // find the direction with more free space
        for(short s=1; s<size; s++)
            if( direction_lengths[s]   >   direction_lengths[index_of_largest] )
                index_of_largest = s;

        *length = direction_lengths[index_of_largest];
    }

    return (size==0 ? Invalid : available_directions[index_of_largest]); // return invalid direction if nothing is found
}

/**  Close a direction if no word can fit in it.
*    @Param dir, the direction to be observed
*           env, the surrounding space
*    @Post  env is updated with closed directions */
void close_direction(direction dir,Environment *env)
{
    if(dir==U) env->U=0;
    else if(dir==D) env->D=0;
    else if(dir==R) env->R=0;
    else if(dir==L) env->L=0;
}

/**  Print a string at specific coordinates
*    @Param s, the string to be printed
*           x,y coordinates */
void cout_XY(string s,int x,int y)
{
    setTextColor(BLACK,BRIGHTWHITE);
    setCursorXY(x,y);
    cout << s;
}

/**  Ask the word number from user and return it
*    @Param total_words
*    @Return the entered word number */
short askWordNumber(short total_words) throw(short)
{
    short wordNumber;
    cout_XY("You can enter (0) to open MENU.",3,72);
    cout_XY("Enter the word number-> ",3,64);
    cin >> wordNumber;
    if(cin.fail())
        throw wordNumber;
    return wordNumber; //! return 0 must be handled for menu
}

/**  Ask the word for a location from user
*    @Param userAnswers stores the word received from user.
*           word_number is the location that word is to be inserted to
*           word_length is the required length for that location
*    @Post userAnswers contains the entered word */
void askWord(vector<string> &userAnswers,short word_number,unsigned short word_length) throw(string)
{
    string word;
    cout_XY("You can enter (-) to skip.\t\t",3,72);
    cout_XY("Enter the word -> ",3,65);
    cin >> word;
    if(word=="-") // skip the session if dash is entered
        throw word;
    else if(word.length()!=word_length) // if length of entered word is not equivalent to required length
    {
        cout_XY("Word length does not match with cells!",3,66);
        throw word;
    }
    else
        userAnswers[word_number] = word; // insert the word in its position
}

/**  Show menu to user with choices to be returned and thrown in case in invalidation
*    @Return return choice of user */
short showMenu() throw(short)
{
    draw_box(1,62,60,10);
    short choice;
    cout_XY("Menu Choices:",3,64);
    cout_XY(" 1) Check answers",3,66);
    cout_XY(" 2) Enter more words",3,67);
    cout_XY(" 0) Quit",3,68);
    cout_XY(" -> ",3,69);
    cin >> choice;
    if(cin.fail())
        throw choice;
    else if(choice < 0 || choice > 2)
        throw choice;

    return choice;
}

/**  Compare words entered by user with the original data, highlight correct ones
*    @Param userAnswers stores the word received from user.
*           word_number is the location that word is to be inserted to
*           word_length is the required length for that location
*    @Post userAnswers contains the entered word */
void checkAnswers(List &wordList,vector<string> &userAnswers,Puzzle &crossword)
{
    string thisword;
    for(int i=1; i<=wordList.getLength(); i++)
    {
        wordList.retrieve(i,thisword);
        if(thisword==userAnswers[i]) crossword.selectWord(GREEN,i); // highlight the correctly enterred words
    }
}

int main()
{
    //while(true)
    {
        List wordList;

        srand ( time(NULL) );

        system("color 70");
        system("MODE 124,78"); // set console size

        cout << "\t\t      Cross Word Puzzle\t\t\t\t\t\t\t  Clues:"<< endl; // leave the first line as it is.

        /*! Set initial variables and containers */
        Puzzle crossword;
        crossword.init(); // initialize the cells
        //crossword.draw();
        Environment env;
        Coordinate coord(0,0);
        direction dir;
        short length;
        Word_Clue myword;
        short word_number = 1;
        string clues;

        getRandom_Word_Clue(&myword);  // get first word
        dir = R; // first word's direction

        while(dir!=Invalid)
        {
            try
            {
                wordList.insert(wordList.getLength()+1,myword.word); // insert word into the list
                crossword.insert(myword.word, word_number, coord, dir,env); // insert words into the puzzle for style matching
                addtoClueContainer(myword.clue,word_number,clues); // add clue to clues container
                dir = getRandom_direction(env,&length); // get random direction and random first letter for the next word
                getRandom_Word_Clue(&myword,env.letter,length); // get random word based on length and first letter
                word_number++;
            }
            catch(exception &e)
            {
                //setCursorXY(104,1); cout << e.what();
                //system("pause");
                close_direction(dir,&env); // close that direction so that it won't be chosen anymore
            }
        }
        short total_words = word_number-1;


        crossword.draw();
        draw_box(62,1,61,71);
        showClues(clues,63,2,121,68);

        /*! Show all words for testing purposes */
        setCursorXY(2,75);
        setTextColor(BLUE,WHITE);
        for (int i=1; i<=wordList.getLength(); i++)
        {
            string thisword;
            wordList.retrieve(i,thisword);
            cout << i << "." << thisword  << ((i==wordList.getLength())?"":" , ");
        }

        vector<string> userAnswers(total_words+1);
        bool next = true;
        while(next)
        {
            draw_box(1,62,60,10); // draw the box below for input/output contact with user
            try
            {
                word_number = askWordNumber(total_words);
                if(word_number==0)
                {
                    short choice = showMenu();
                    if(choice==0) next = false;
                    else if(choice==1)
                    {
                        checkAnswers(wordList,userAnswers,crossword); // check user answers with original data
                        throw choice;
                    }
                    else throw choice;
                }
                crossword.selectWord(CYAN,word_number); // highlight the selected word
                string thisword;
                wordList.retrieve(word_number,thisword);
                askWord(userAnswers,word_number,thisword.length()); // ask word from user
                crossword.enterWord(word_number,userAnswers[word_number]); // enter word that user entered into the puzzle
            }
            catch(short e)
            {
                cin.clear();
                cin.ignore(10000,'\n');
            }
            catch(string e)
            {
                //  word is skipped OR length of string is larger than cell word area
                crossword.selectWord(RED,word_number); // deselect the word
            }
        }

        //Sleep(500);
    }//end while

    //getch();
}
