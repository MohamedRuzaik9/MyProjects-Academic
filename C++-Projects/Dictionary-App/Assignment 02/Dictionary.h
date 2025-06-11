//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include "Word.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Class representing a dictionary. It contains a list of words and provides methods to load the dictionary from a file, search for words, and get random words.
input       : None
output      : None 
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
class Dictionary 
{
protected:
    vector<Word> entries;

public:
    Dictionary();
    virtual ~Dictionary() = default;

    bool load(const string& filename);
    void search() const;
    void getRandomWord() const;
    virtual void displayMenu();

protected:
    void displayUI() const;
    void clearScreen() const;
};

