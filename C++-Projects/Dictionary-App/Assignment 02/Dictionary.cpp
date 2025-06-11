//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include "Dictionary.h"
#include <iostream>
#include <random>

using namespace std;

/*
Constructor for the Dictionary class. Initializes the dictionary and sets up the random number generator.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
Dictionary::Dictionary() 
{
    srand(time(0));
}

/*
Loads the dictionary from a file. It reads the file line by line, extracting the word name, type, and definition. 
input       : filename - the name of the file to load
output      : true if successful, false otherwise
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
bool Dictionary::load(const string& filename) 
{
    cout << "Dictionary is Loading. Please Wait...\n";
    entries.clear();
    ifstream dictionaryFile(filename);
    if (!dictionaryFile.is_open()) {
        cout << "Error - dictionary empty" << "\n";
        return false;
    }
    string line;
    Word newWord("", "", "");
    bool readDef = false;
	// Read the file line by line
    while (getline(dictionaryFile, line)) 
    {
		// Skips the empty lines
        if (line.empty() || line[line.length() - 1] != ';') 
        {
            continue;
        }
        newWord.setName(line.substr(0, line.length() - 1));
        if (!getline(dictionaryFile, line) || line.empty() || line[line.length() - 1] != ';') 
        {
            continue;
        }
        newWord.setType(line.substr(0, line.length() - 1));
        if (!getline(dictionaryFile, line)) 
        {
            continue;
        }
        newWord.setDefinition(line);
        getline(dictionaryFile, line);
        entries.push_back(newWord);
    }
	// Check if the last word was added
    if (!newWord.getName().empty()) 
    {
        entries.push_back(newWord);
    }
    dictionaryFile.close();
    clearScreen();
    return true;
}

/*
Searches for a word in the dictionary. It prompts the user for a word and checks if it exists in the dictionary. If found, it displays the word's details.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void Dictionary::search() const 
{
    string searchWord;
    cout << "Enter a word to search:  ";
    getline(cin, searchWord);
    bool found = false;
    string lowSearch = searchWord;
    Word::toLowerCase(lowSearch);
    for (const auto& entry : entries) 
    {
        string lowWord = entry.getName();
        Word::toLowerCase(lowWord);
        if (lowWord == lowSearch) 
        {
            found = true;
            cout << "\n---------------- Search Results -----------------------\n" << endl;
            cout << "Name: " << entry.getName();
            if (!entry.getType().empty()) 
            {
                cout << " (" << Word::getFullTypeName(entry.getType()) << ")" << "\n" << endl;
            }
            if (!entry.getDefinition().empty()) 
            {
                entry.printDefinition();
            }
            cout << "\n-------------------------------------------------------\n" << endl;
        }
    }
    if (!found) 
    {
        cout << "The word not found." << endl;
    }
}

/*
Gets a random word from the dictionary. It uses a random number generator to select an index and displays the corresponding word's details.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void Dictionary::getRandomWord() const 
{
    if (entries.empty()) 
    {
        cout << "Error - dictionary empty" << endl;
        return;
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, entries.size() - 1);
    int randomIndex = dist(gen);
    const Word& entry = entries[randomIndex];
    cout << "\n----------------------- Random Word ------------------------\n" << endl;
    cout << "Name: " << entry.getName();
    if (!entry.getType().empty()) 
    {
        cout << " (" << Word::getFullTypeName(entry.getType()) << ")" << "\n" << endl;
    }
    if (!entry.getDefinition().empty()) 
    {
        entry.printDefinition();
    }
    cout << "\n------------------------------------------------------------\n" << endl;
}

/*
Displays the user interface for the dictionary. It shows the available options and prompts the user for input.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void Dictionary::displayUI() const 
{
    cout << ",_______________________________________,\n";
    cout << "|               Dictionary              |\n";
    cout << "|=======================================|\n";
    cout << "|  1. Load Dictioanry (load)            |\n";
    cout << "|  2. Search for a Word (search)        |\n";
    cout << "|  3. Get a Random Word (random)        |\n";
    cout << "|  4. Clear Screen (cls)                |\n";
    cout << "|  5. Exit (x)                          |\n";
    cout << "|_______________________________________|\n";
    cout << "\nEnter your Choice (1/2/3/4/5):  ";
}

/*
Clears the screen. This is a simple utility function to clear the console output.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void Dictionary::clearScreen() const 
{
    system("cls");
}


/*
Displays the main menu for the dictionary. It continuously prompts the user for input until they choose to exit.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void Dictionary::displayMenu() 
{  
    while (true) 
    {
        displayUI();
        string choice;
        getline(cin, choice);
        if (choice == "1" || choice == "load") 
        {
            const string filename = "dictionary_2025S1.txt";
            if (!load(filename)) 
            {
                cout << "\nError - dictionary empty" << endl;
                return;
            }
        }
        else if (choice == "2" || choice == "search") 
        {
            search();
            system("pause");
        }
        else if (choice == "3" || choice == "random") 
        {
            getRandomWord();
            system("pause");
        }
        else if (choice == "4" || choice == "cls") 
        {
            clearScreen();
        }
        else if (choice == "5" || choice == "x") 
        {
            cout << "Exiting Program...\n\n";
            break;
        }
        else 
        {
            cout << "\nInvalid Choice, Please select from 1,2,3,4 or 5!  \n";
        }
    }
}