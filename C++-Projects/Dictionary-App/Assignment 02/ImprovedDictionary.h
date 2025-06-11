//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include "Dictionary.h"
#include "NotGPT.h"

using namespace std;
/*
Class representing an improved dictionary that extends the base Dictionary class. It adds features for training and using the NotGPT text generator.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
class ImprovedDictionary : public Dictionary 
{
private:
    NotGPT textGenerator;
    void displayExtendedMenu() const;
    void handleUserChoice(const std::string& choice);
    void generateText();

public:
    ImprovedDictionary();
    void displayMenu() override;
    void trainNotGPT();
    void showPredictions();    
};

