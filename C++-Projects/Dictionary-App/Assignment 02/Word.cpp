//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include "Word.h"
#include <iostream>

using namespace std;
/*
Constructor for the Word class. Initializes the word with its name, type, and definition.
input       : name - the name of the word
		    : type - the type of the word
			: definition - the definition of the word
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
Word::Word(const string& name, const string& type, const string& definition): name(name), type(type), definition(definition) {}
string Word::getName() const { return name; }
string Word::getType() const { return type; }
string Word::getDefinition() const { return definition; }
void Word::setName(const string& name) { this->name = name; }
void Word::setType(const string& type) { this->type = type; }
void Word::setDefinition(const string& definition) { this->definition = definition; }

/*
Returns the full type name based on the provided type abbreviation.
input       : type - the type abbreviation
output      : type name
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
string Word::getFullTypeName(const string& type) 
{
    if (type == "adv") return "adv.";
    if (type == "v") return "v.";
    if (type == "adj") return "adj.";
    if (type == "n") return "n.";
    if (type == "prep") return "prep.";
    if (type == "misc") return "misc.";
    if (type == "pn") return "pn";
    if (type == "n v") return "n.v.";
    return "Unknown";
}


/*
Converts the string to lowercase.
input       : str - the string to convert
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void Word::toLowerCase(string& str) 
{
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) 
        {
        return tolower(c);
        });
}

/*
Prints the definition of the word. If the definition is empty, it does nothing.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void Word::printDefinition() const 
{
    if (definition.empty()) return;
    cout << "Definitions:   \n\n- ";
    bool afterSemicolon = false;
    for (char printDef : definition) 
    {
        if (afterSemicolon) 
        {
            if (printDef != ' ') 
            {
                cout << ".\n\n- " << printDef;
                afterSemicolon = false;
            }
        }
        else if (printDef == ';') 
        {
            afterSemicolon = true;
        }
        else 
        {
            cout << printDef;
        }
    }
    cout << endl;
}


