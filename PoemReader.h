/**
 * This class will parse through the poems, and build up a map. This map will have an actual word as the key, and a vector of
 * words that commonly follow said word as the value. We will hopefully have more factors to determine poem writing in the future
 */
#ifndef UNTITLED_POEMREADER_H
#define UNTITLED_POEMREADER_H
#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;

class PoemReader{
private:
    ifstream inFS; //object used to open/close the input file(s) we work with
    string fileName = "C:\\Users\\sydne\\Desktop\\Computer Science Shiz\\HackSMU2020\\Poems.txt"; //holds the file name that will be used for analysis
    string poemType = ""; //holds the type of poem the computer will be writing
    bool syllablesMatter = false; //this flag determines whether or not the computer needs to take syllables into consideration (only is false when doing free verse)

    map<string, vector<string>> wordPairs; //map containing a word, and a vector of words that typically follow the first in a poem
    map<string, vector<string>>::iterator myIt; //iterator for wordPairs
    map<string, int> syllableCount; //map containing a word, and the number of syllables that that word is
    map<string, int>::iterator myIt2; //iterator for syllableCount

public:
    /**
     * Constructor
     */
    PoemReader(); //constructor that prompts for user input on which kind of poetry the user would like to analyze

    /**
     * Methods used to access input file
     */
    void openFile(); //opens the file that will be used for poem analysis
    void closeFile(); //closes the file that was used for poem analysis
    void parseFile(); //this function goes through the actual poems file line by line

    /**
     * Methods that allow the computer to analyze the poem structure
     */
    vector<string> tokenizeLine(string); //tokenizes a line from the file into actual words
    int countSyllables(string); //returns an int that contains the number of syllables for a word
    bool isVowel(char); //checks to see if a character is a vowel or not (used by syllable counter)
    string lowerCase(string); //converts a string completely to lowercase

    map<string, vector<string>> getWordPairs(); //returns the wordPairs map so the PoemWriter can access it
    map<string, int> getSyllableCount(); //returns the syllableCount map so the PoemWriter can access it
    bool getSyllablesMatter(); //returns the bool flag instantiated above
    string getPoemType(); //returns the type of poem we want the computer to write

    /**
     * Debugging display functions
     */
    void printWordPairs(); //prints the entirety of the wordPairs vector (mostly for debugging purposes)
    void printSyllableCount(); //prints the entirety of the syllableCount vector (mostly for debugging purposes)
};
#endif //UNTITLED_POEMREADER_H