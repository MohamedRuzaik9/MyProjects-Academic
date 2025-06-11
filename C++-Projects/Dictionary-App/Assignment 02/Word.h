//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
Class representing a word in the dictionary. It contains the word's name, type, and definition.
input       : name - the name of the word
			: type - the type of the word
			: definition - the definition of the word
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
class Word 
{
private:
    string name;
    string type;
    string definition;

public:
    Word(const string& name, const string& type, const string& definition);
    string getName() const;
    string getType() const;
    string getDefinition() const;
    void setName(const string& name);
    void setType(const string& type);
    void setDefinition(const string& definition);
    void printDefinition() const;
    static string getFullTypeName(const string& type);
    static void toLowerCase(string& str);
};
