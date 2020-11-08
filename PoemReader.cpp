#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include "PoemReader.h"

using namespace std;

PoemReader::PoemReader()
{
    string userChoice = "HanShotFirst";
    cout << "What type of poem would you like written - Iambic Pentameter, or Free Verse?" << endl;
    cout << "Press \"A\" for Iambic Pentameter" << endl;
    cout << "Press \"B\" for Iambic Tetrameter" << endl;
    cout << "Press \"C\" for Haiku" << endl;
    cout << "Press \"D\" for Free Verse" << endl;

    //if the user doesn't enter a or b, or just enters in a bunch of gibberish this code will stop that nonsense
    while(userChoice.length() > 1 || (userChoice != "A" && userChoice != "a" && userChoice != "B" && userChoice != "b" && userChoice != "C" && userChoice != "c" && userChoice != "D" && userChoice != "d"))
    {
        cin >> userChoice;
        if (userChoice.length() > 1 || (userChoice != "A" && userChoice != "a" && userChoice != "B" && userChoice != "b" && userChoice != "C" && userChoice != "c" && userChoice != "D" && userChoice != "d"))
        {
            cout << "You have entered invalid input, please try again." << endl;
            cout << "What type of poem would you like written - Iambic Pentameter, or Free Verse?" << endl;
            cout << "Press \"A\" for Iambic Pentameter" << endl;
            cout << "Press \"B\" for Iambic Tetrameter" << endl;
            cout << "Press \"C\" for Haiku" << endl;
            cout << "Press \"D\" for Free Verse" << endl;
        }
    }

    if (userChoice == "A" || userChoice == "a") {
        poemType = "Iambic Pentameter";
        syllablesMatter = true;
    }
    else if (userChoice == "B" || userChoice == "b") {
        poemType = "Iambic Tetrameter";
        syllablesMatter = true;
    }
    else if (userChoice == "C" || userChoice == "c") {
        poemType = "Haiku";
        syllablesMatter = true;
    }
    else{
        poemType = "Free Verse";
        syllablesMatter = false;
    }
}

void PoemReader::openFile()
{
    inFS.open(fileName);
    if (!inFS.is_open()) {
        cout << "You're a second year CS major and you're STILL getting this wrong. Drop out." << endl;
        exit(01134);
    }
}

void PoemReader::closeFile()
{
    inFS.close();
}

void PoemReader::parseFile()
{
    int counter = 0;
    string currLine; //holds the current line as we parse through the file
    while(!inFS.eof()) //loops through the file until the end of said file
    {
        //cout << ++counter << endl; //debugging code
        getline(inFS, currLine); //extracts each line of the file throughout the loop
        if (currLine == ":)") //I separated all the poems with smiley faces because I could use a bit of joy in my life
        {
            //have code that will navigate you to the next poem
            string dedSpace;
            getline(inFS, dedSpace);
        }
        else
        {
            vector<string> curr = tokenizeLine(currLine); //tokenizes the line into separate strings
            for (int i = 0; i < curr.size(); ++i) //goes through tokenized vector and adds words to the map
            {
                if (i < curr.size() - 1) //this statement helps us prevent out of bounds errors
                {
                    string currWord = curr.at(i);
                    string trailingWord = curr.at(i + 1);

                    myIt = wordPairs.find(currWord);
                    if (myIt == wordPairs.end()) //if the current word doesn't already exist in the map, add it with a blank vector
                    {
                        vector<string> vect;
                        vect.push_back(trailingWord);
                        wordPairs.insert(pair<string, vector<string>>(currWord, vect));

                        int sCount = countSyllables(currWord);
                        syllableCount.insert(pair<string, int>(currWord, sCount));
                    }
                    else
                        wordPairs[currWord].push_back(trailingWord); //pushes back the word directly after the current word we are on
                }
                else //similar code to above, but slightly modified as the currWord will now be the last word in the vector
                {
                    string currWord = curr.at(i);

                    myIt = wordPairs.find(currWord);
                    if (myIt == wordPairs.end()) //if the current word doesn't already exist in the map, add it with a blank vector
                    {
                        vector<string> vect;
                        vect.push_back("\n");
                        wordPairs.insert(pair<string, vector<string>>(currWord, vect));

                        int sCount = countSyllables(currWord);
                        syllableCount.insert(pair<string, int>(currWord, sCount));
                    }
                    else
                        wordPairs[currWord].push_back("\n"); //pushes back the word directly after the current word we are on
                }
            }
        }
    }
}

vector<string> PoemReader::tokenizeLine(string line)
{
    vector<string> tokenizedWords;
    for (int i = 0; i < line.length(); ++i)
    {
        string currWord = "";
        while(isalpha(line[i]))
        {
            currWord += line[i];
            ++i;
        }
        tokenizedWords.push_back(currWord);
        while(!isalpha(line[i]))
            ++i;
        --i;
    }
    return tokenizedWords;
}

int PoemReader::countSyllables(string word) {
        if (word.length() == 0) //no syllables if word is empty
            return 0;
        else if (word.length() <= 2) //only one syllable if word is 1 or 2 letters
            return 1;

        string lower = lowerCase(word); //make everything lowercase to make it easier to work with

        //This segment of code removes trailing e's for syllable counting purposes (otherwise we'd get extra syllables for a word
        string prunned;

        if (lower[lower.length() - 1] == 'e')
            prunned = lower.substr(0, lower.length() - 1);
        else
            prunned = lower;

        int count = 0; //holds the number of syllables
        bool prevIsVowel = false;
        for (int i = 0; i < prunned.length(); ++i)
        {
            bool vow = isVowel(prunned[i]);
            if (vow && !prevIsVowel) //if the current letter is a vowel AND the previous letter is NOT a vowel, a syllables is found and the count increases
                ++count;
            prevIsVowel = vow;
        }
        return count;
}

bool PoemReader::isVowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

string PoemReader::lowerCase(string word)
{
    string lowercase = "";
    for (int i = 0; i < word.length(); ++i)
        lowercase += tolower(word[i]);
    return lowercase;
}

map<string, vector<string>> PoemReader::getWordPairs() {
    return wordPairs;
}

map<string, int> PoemReader::getSyllableCount() {
    return syllableCount;
}

bool PoemReader::getSyllablesMatter() {
    return syllablesMatter;
}

string PoemReader::getPoemType() {
    return poemType;
}

void PoemReader::printWordPairs() {
    for (myIt = wordPairs.begin(); myIt != wordPairs.end(); ++myIt)
    {
        cout << "WORD: " << myIt->first << endl;
        vector<string> temp = myIt->second;
        cout << "Trailing words list: " << endl;
        for (int i = 0; i < temp.size(); ++i)
            cout << temp.at(i) << endl;
        cout << "End " << myIt->first << endl << endl;
    }
}

void PoemReader::printSyllableCount() {
    for (myIt2 = syllableCount.begin(); myIt2 != syllableCount.end(); ++myIt2)
        cout << "WORD: " << myIt2->first << " " << myIt2->second << endl;
}