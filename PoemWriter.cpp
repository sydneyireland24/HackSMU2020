#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "PoemReader.h"
#include "PoemWriter.h"

using namespace std;

PoemWriter::PoemWriter()
{
    syllablesMatter = pReader.getSyllablesMatter();

    if (syllablesMatter) //makes sure to account for syllables if they do matter
    {
        pReader.openFile();
        pReader.parseFile();
        pReader.closeFile();
        wordPairs = pReader.getWordPairs();
        syllableCount = pReader.getSyllableCount();
        poemType = pReader.getPoemType();
    }

    else //Omits syllable retrieval if syllables don't matter (copying over map takes extra time in the big picture)
    {
        pReader.openFile();
        pReader.parseFile();
        pReader.closeFile();
        wordPairs = pReader.getWordPairs();
        poemType = pReader.getPoemType();
    }

    //pReader.printWordPairs(); //prints the map of words and their vector of trailing words (debugging purposes only)
    //pReader.printSyllableCount(); //prints the map of words and their corresponding number of syllables (debugging purposes only)
}

void PoemWriter::openFile()
{
    outFS.open("output.txt");
}

void PoemWriter::closeFile()
{
    cout << "Poem has been written!" << endl;
    outFS.close();
}

void PoemWriter::writePoem() {
    //based on the poem type asked for by the user, different functions will be called
    if (poemType == "Iambic Pentameter")
        writeIambic(10);
    else if (poemType == "Iambic Tetrameter")
        writeIambic(8);
    else if (poemType == "Haiku")
        writeHaiku();
    else
        writeFree();
}

void PoemWriter::writeIambic(int syllableNum) {
    srand (time(NULL)); //sets random seed

    //random number to determine the number of lines the computer should write (max 40)
    int numLines = (rand() % 32 ) + 8;

    for (int i = 0; i < numLines; ++i)
    {
        //choose a random word to start with
        it = wordPairs.begin();
        it2 = syllableCount.begin();
        int randIndex = rand() % wordPairs.size();
        advance( it, randIndex); //chooses a random word in the map by advancing to a random index
        outFS << it->first << " ";

        int sCount = syllableCount[it->first]; //used to keep track of the number of syllables

        while(sCount < syllableNum)
        {
            if (!it->second.empty())
            {
                if ( it == wordPairs.end() )
                {
                    it = wordPairs.begin();
                    advance(it, (rand() % wordPairs.size()));
                }
                else
                {
                    bool space = onlySpaces(); //checks if the trailing words vector of a particular is just newlines or spaces
                    while(space) //if the trailing words vector is just spaces, we find a new random word
                    {
                        it = wordPairs.begin();
                        advance(it, (rand() % wordPairs.size()));
                        space = onlySpaces();
                    }

                    unsigned int randNum = (rand() % it->second.size());
                    string curr = it->second.at(randNum);
                    while(curr == "\n" || curr == " ")
                    {
                        randNum = (rand() % it->second.size());
                        curr = it->second.at(randNum);
                    }
                    outFS << curr << " ";
                    sCount += syllableCount[curr];
                    it2 = syllableCount.find(curr);
                    it = wordPairs.find(curr);
                }
            }
            else { //if there are NOT any words in the trailing vector for the current word, we will just choose another random word
                it = wordPairs.begin();
                advance(it, (rand() % wordPairs.size()));
            }
        }
        outFS << endl;
    }
}

void PoemWriter::writeHaiku()
{
    srand (time(NULL)); //sets random seed

    //choose a random word to start with
    it = wordPairs.begin();
    advance( it, ( rand() % wordPairs.size() ) );
    outFS << it->first << " ";
    int sCount = syllableCount[it->first];
    while(sCount < 5)
    {
        if (!it->second.empty())
        {
            if ( it == wordPairs.end() )
            {
                it = wordPairs.begin();
                advance(it, (rand() % wordPairs.size()));
            }
            else
            {
                bool space = onlySpaces();
                while(space)
                {
                    it = wordPairs.begin();
                    advance(it, (rand() % wordPairs.size()));
                    space = onlySpaces();
                }

                unsigned int randNum = (rand() % it->second.size());
                string curr = it->second.at(randNum);
                while(curr == "\n" || curr == " ")
                {
                    randNum = (rand() % it->second.size());
                    curr = it->second.at(randNum);
                }

                if(sCount += syllableCount[curr] <= 5)
                {
                    outFS << curr << " ";
                    sCount += syllableCount[curr];
                    it2 = syllableCount.find(curr);
                    it = wordPairs.find(curr);
                }
                else
                {
                    while((sCount += syllableCount[curr] > 5) || (curr == "\n" || curr == " "))
                    {
                        randNum = (rand() % it->second.size());
                        curr = it->second.at(randNum);
                    }
                    outFS << curr << " ";
                    sCount += syllableCount[curr];
                    it2 = syllableCount.find(curr);
                    it = wordPairs.find(curr);
                }
            }
        }
        else {
            it = wordPairs.begin();
            advance(it, (rand() % wordPairs.size()));
        }
    }
    outFS << endl;

    it = wordPairs.begin();
    advance( it, ( rand() % wordPairs.size() ) );
    outFS << it->first << " ";
    sCount = syllableCount[it->first];
    while(sCount < 7)
    {
        if (!it->second.empty())
        {
            if ( it == wordPairs.end() )
            {
                it = wordPairs.begin();
                advance(it, (rand() % wordPairs.size()));
            }
            else
            {
                bool space = onlySpaces();
                while(space)
                {
                    it = wordPairs.begin();
                    advance(it, (rand() % wordPairs.size()));
                    space = onlySpaces();
                }

                unsigned int randNum = (rand() % it->second.size());
                string curr = it->second.at(randNum);
                while(curr == "\n" || curr == " ")
                {
                    randNum = (rand() % it->second.size());
                    curr = it->second.at(randNum);
                }
                if(sCount += syllableCount[curr] <= 7)
                {
                    outFS << curr << " ";
                    sCount += syllableCount[curr];
                    it2 = syllableCount.find(curr);
                    it = wordPairs.find(curr);
                }
                else
                {
                    while((sCount += syllableCount[curr] > 7) || (curr == "\n" || curr == " "))
                    {
                        randNum = (rand() % it->second.size());
                        curr = it->second.at(randNum);
                    }
                    outFS << curr << " ";
                    sCount += syllableCount[curr];
                    it2 = syllableCount.find(curr);
                    it = wordPairs.find(curr);
                }
            }
        }
        else {
            it = wordPairs.begin();
            advance(it, (rand() % wordPairs.size()));
        }
    }
    outFS << endl;

    it = wordPairs.begin();
    advance( it, ( rand() % wordPairs.size() ) );
    outFS << it->first << " ";
    sCount = syllableCount[it->first];
    while(sCount < 5)
    {
        if (!it->second.empty())
        {
            if ( it == wordPairs.end() )
            {
                it = wordPairs.begin();
                advance(it, (rand() % wordPairs.size()));
            }
            else
            {
                bool space = onlySpaces();
                while(space)
                {
                    it = wordPairs.begin();
                    advance(it, (rand() % wordPairs.size()));
                    space = onlySpaces();
                }

                unsigned int randNum = (rand() % it->second.size());
                string curr = it->second.at(randNum);
                while(curr == "\n" || curr == " ")
                {
                    randNum = (rand() % it->second.size());
                    curr = it->second.at(randNum);
                }

                if(sCount += syllableCount[curr] <= 5)
                {
                    outFS << curr << " ";
                    sCount += syllableCount[curr];
                    it2 = syllableCount.find(curr);
                    it = wordPairs.find(curr);
                }
                else
                {
                    while((sCount += syllableCount[curr] > 5) || (curr == "\n" || curr == " "))
                    {
                        randNum = (rand() % it->second.size());
                        curr = it->second.at(randNum);
                    }
                    outFS << curr << " ";
                    sCount += syllableCount[curr];
                    it2 = syllableCount.find(curr);
                    it = wordPairs.find(curr);
                }
            }
        }
        else {
            it = wordPairs.begin();
            advance(it, (rand() % wordPairs.size()));
        }
    }
    outFS << endl;
}

void PoemWriter::writeFree()
{
    srand (time(NULL)); //sets random seed

    //random number to determine the number of lines the computer should write (max 40)
    int numLines = (rand() % 40 ) + 1;

    for (int i = 0; i < numLines; ++i)
    {
        //choose a random word to start with
        it = wordPairs.begin();
        advance( it, ( rand() % wordPairs.size() ) );
        outFS << it->first << " ";

        while(true) //writes a line until the computer finds a word that has a newline as a trailing entry
        {
            if (!it->second.empty())
            {
                if (it == wordPairs.end() )
                {
                    //outFS << endl;
                    break;
                }
                else
                {
                    int randNum = rand() % it->second.size();
                    outFS << it->second.at(randNum) << " ";
                    it = wordPairs.find(it->second.at(randNum));
                }
            }
            else
                advance( it, ( rand() % wordPairs.size() ) );
        }
    }
}

bool PoemWriter::onlySpaces() {
    for (int k = 0; k < it->second.size(); ++k)
        if(it->second.at(k) != " " && it->second.at(k) != "\n")
            return false;
    return true;
}