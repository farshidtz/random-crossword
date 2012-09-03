/******************************************************************* 
TCS1011 - Data Structure & Algorithms
Farshid Tavakolizadeh
Email: email@farshid.ws
Project Page: https://farshid.ws/projects.php?id=114
Year: 2012
********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "WordQueue.h"

/** Import data from dictionary database and store in a queue
*   @Param queue
*   @Pre queue is not fixed size and can grow as large as the dictionary
*   @Post queue contains the dictionary data */
void importDic(WordQueue&);

/** Export the content of queue into seperate files based on their starting letters.
*   The words will be sorted with respect to their length before storage.
*   @Param queue
*   @Pre queue contains the dictionary data
*   @Post queue is empty */
void exportDic(WordQueue&);

int main ()
{
    WordQueue wordsQ;

    importDic(wordsQ);
    exportDic(wordsQ);

    return 0;
}


void importDic(WordQueue &wordsQ)
{
    string line;
    ifstream myfile ("dict.txt");
    if (myfile.is_open())
    {
        cout << "Loading Words...\n";
        while ( myfile.good() )
        {
            bool missing_def = false;
            Word* thisword = new Word();

            getline (myfile,line); // word
            thisword->word = line;
            //cout << "Word: " << line << endl;

            getline (myfile,line); // related words
            // throw

            getline (myfile,line); // defGroups
            thisword->numOfDefGroups = atoi(line.c_str());
            //cout << "# of Def Groups: " << thisword->numOfDefGroups << endl;

            for(short i = 0; i<thisword->numOfDefGroups; i++)
            {
                DefGroup* thisdefgroup = new DefGroup();

                getline (myfile,line); // word type
                // throw

                getline (myfile,line); // synonyms
                //thisdefgroup->synonyms = line;
                //cout << "Synonyms: " << line << endl;
                // throw

                getline (myfile,line); // # of defs
                thisdefgroup->numOfDefs = atoi(line.c_str());
                if(thisdefgroup->numOfDefs==0)
                    missing_def=true;
                //cout << "# of Definitions: " << thisdefgroup->numOfDefs << endl;
                for(short j = 0; j<thisdefgroup->numOfDefs; j++)
                {
                    getline (myfile,line);  // def
                    if(line.substr(0,3)=="See") // If definition is referring to another word
                        missing_def=true;
                    else
                        thisdefgroup->defs.push_back(line);

                    //cout << "Def" << j << ": " << thisdefgroup->defs[j] << endl;
                }
                if(!missing_def)thisword->defGroups.push_back(*thisdefgroup);
                delete thisdefgroup;
                thisdefgroup = NULL;
            }
            if(!missing_def)wordsQ.enqueue(*thisword);
            delete thisword;
            thisword = NULL;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    //system("pause");
}

/** container for words and clues only **/
struct SimpleWord
{
    string word;
    string def;
    SimpleWord(string word,string def):word(word),def(def) {}
};

/** This vector is to contain words with same starting letters, all As to all Zs **/
struct AtoZ
{
    vector<SimpleWord> simpleWords;
};

/** Sort the words based on the length **/
bool mysorter (SimpleWord i,SimpleWord j)
{
    return (i.word.length()<j.word.length());
}


/*
    create a vector with 26 ELEMENTS for each letter
    each ELEMENT is a struct that contains a vector for SIMPLEWORDS
    each SIMPLEWORD contains a word and a definition
    sort the SIMPLEWORDS vectors based on words' length
    write each of SIMPLEWORDS vectors to its equivalent file
*/
void exportDic(WordQueue &wordsQ)
{
    vector<AtoZ> alphabets (26); // this vector contains vectors of each letters. A kind of 2-D vector with more control !

    Word* outWord;
    char abc;
    int qsize = wordsQ.getSize();
    int length[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // to store number of words for all lengths
    for(int i=0; i<qsize-1; i++)
    {
        outWord = wordsQ.getFront();

        length[outWord->word.length()]++;
        abc = char(outWord->word[0])-97; // get 0-25 from a-z (starting letter of all words)
        alphabets[abc].simpleWords.push_back(SimpleWord(outWord->word,outWord->getFirstDef()));

        delete outWord; /* !!! IF NOT, WILL CAUSE MEMORY LEAK !!! */
    }

    /*! show some stats about the word lengths in dictionary. This will be used in CrossWord Project !*/
    cout << "\nDictionary words length stats:" << "\n[ Word length --> Number of occurrences ]\n";
    for(int k=0; k<25; k++)
        cout << k << " --> " << length[k] << endl;


    string ofilename;
    int vIndex; // vector index
    cout << "\nWriting Files...\n";
    for(int aIndex='a'; aIndex<='z'; aIndex++)
    {
        vIndex = aIndex-97;  // get 0-25 from a-z
        sort(alphabets[vIndex].simpleWords.begin(),alphabets[vIndex].simpleWords.end(),mysorter);

        ofilename = string("./data/") + static_cast<char>(aIndex-32) + string(".txt"); // ./data/A.txt to ./data/Z.txt
        cout << ofilename << endl;
        ofstream myofile (ofilename.c_str()); // use .c_str becouse it won't accept variable string
        if (myofile.is_open())
        {
            for(unsigned int i=0; i<alphabets[vIndex].simpleWords.size(); i++)
            {
                myofile << alphabets[vIndex].simpleWords[i].word << endl << alphabets[vIndex].simpleWords[i].def;
                if(i<alphabets[vIndex].simpleWords.size()-1) myofile << endl;
            }
            myofile.close();
        }
        else cout << "Unable to open ofile";
    }
    //system("pause");
}
