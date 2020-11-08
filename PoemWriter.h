#ifndef UNTITLED_POEMWRITER_H
#define UNTITLED_POEMWRITER_H

#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include "PoemReader.h"

using namespace std;

class PoemWriter{
private:
    PoemReader pReader; //poem reader object that allows us to actually read through poems

    map<string, vector<string>> wordPairs; //map with words and their trailing words to use to build the poems
    map<string, vector<string>>::iterator it; //iterator for the wordPairs map
    map<string, int> syllableCount; //map containing a word, and the number of syllables that that word is
    map<string, int>::iterator it2; //iterator for syllableCount

    string poemType; //determines the type of poem we will have the computer write
    bool syllablesMatter; //determines whether or not the computer does a free verse or structured poem

    ofstream outFS; //ofstream object used to put content in output files

public:
    PoemWriter(); //Poem Writer Constructor
    void openFile(); //opens the output file
    void closeFile(); //closes the output file
    void writePoem(); //program will write a poem based on specifications and learnings from PoemReader class
    void writeIambic(int); //holds the code to write an Iambic poem
    void writeHaiku(); //holds the code to write a Haiku
    void writeFree(); //holds the code to write a free verse poem
    bool onlySpaces(); //checks if the trailing words vector only contains spaces and new lines
};

#endif //UNTITLED_POEMWRITER_H