//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include "ImprovedDictionary.h"
#include <sstream>
#include <iostream>

using namespace std;

/*
Constructor for the  ImprovedDictionary class. This initializes the ImprovedDictionary object and its base class components.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
 */
ImprovedDictionary::ImprovedDictionary() : textGenerator() {}

/*
This displays the extended menu options for the ImprovedDictionary. This shows all the available options including Assignment 01 Dictionary functions and new functions
input       : None
output      : None
Created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
 */
void ImprovedDictionary::displayExtendedMenu() const 
{
    cout << ",_______________________________________,\n";
    cout << "|               Dictionary              |\n";
    cout << "|=======================================|\n";
    cout << "|  1. Load Dictionary (load)            |\n";
    cout << "|  2. Search for a Word (search)        |\n";
    cout << "|  3. Get a Random Word (random)        |\n";
    cout << "|  4. Train NotGPT (train)              |\n";
    cout << "|  5. Generate Text (generate)          |\n";
    cout << "|  6. Show Predictions (predict)        |\n";
    cout << "|  7. Clear Screen (cls)                |\n";
    cout << "|  8. Exit (x)                          |\n";
    cout << "|_______________________________________|\n";
    cout << "\nEnter your Choice (1-8):  ";
}

/*
This trains the NotGPT model by using the dictionary data. It combines all the words and definitions into a single string and trains the model on it.   
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void ImprovedDictionary::trainNotGPT() 
{
    if (entries.empty()) 
    {
        cout << "Error - dictionary empty.\n";
        return;
    }
    cout << "\nTraining NotGPT on dictionary data. Please wait...\n";
    // Combining all the dictionary text for training
    stringstream dictionaryText;
    for (const auto& word : entries) 
    {
        dictionaryText << word.getName() << " ";
        dictionaryText << word.getDefinition() << " ";
    }
    textGenerator.trainOnText(dictionaryText.str());
    clearScreen();
    cout << "NotGPT trained Successfully.\n";
}
 
/*
This Generates a paragraph of text using the trained NotGPT model. And it checks the model is trained before generating the text.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void ImprovedDictionary::generateText() 
{
    if (!textGenerator.isTrained()) 
    {
        cout << "Error - NotGPT is not trained yet.\n";
        return;
    }
    cout << "\n---------------- Generated Text -----------------------\n" << endl;
    cout << textGenerator.generateParagraph() << endl;
    cout << "\n-------------------------------------------------------\n" << endl;
}

/*
Shows predictions for the next character based on the last 2 characters entered by the user. This checks if the model is trained before showing predictions.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void ImprovedDictionary::showPredictions() 
{
    if (!textGenerator.isTrained()) 
    {
        cout << "Error - NotGPT is not trained yet.\n";
        return;
    }
    string input;
    cout << "\nEnter two characters to predict the next character: ";
    getline(cin, input);
    if (input.length() != 2) 
    {
        cout << "Please enter only two characters.\n";
        return;
    }
    auto predictions = textGenerator.getTopThreePredictions(input);
    cout << "\nPredictions after '" << input << "':\n";
    if (predictions.empty()) 
    {
        cout << "No predictions available.\n";
    }
    else 
    {
        for (size_t i = 0; i < predictions.size(); ++i) 
        {
            cout << (i + 1) << ". '" << predictions[i].first << "' \n";
        }
    }
}


/*
This handles the user choice from the menu. It checks the input and calls the appropriate function based on the user's selection.
input       : choice - the user's choice from the menu
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void ImprovedDictionary::handleUserChoice(const string& choice) 
{
    if (choice == "1" || choice == "load") 
    {
        const string filename = "dictionary_2025S1.txt";
        if (!load(filename)) 
        {
            cout << "\nError - dictionary emty" << endl;
        }
        else 
        {
            cout << "\nDictionary loaded successfully!" << endl;
        }
        system("pause");
        clearScreen();
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
    else if (choice == "4" || choice == "train") 
    {
        trainNotGPT();
        system("pause");
		clearScreen();
    }
    else if (choice == "5" || choice == "generate") 
    {
        generateText();
        system("pause");
    }
    else if (choice == "6" || choice == "predict") 
    {
        showPredictions();
        system("pause");
    }
    else if (choice == "7" || choice == "cls") 
    {
        clearScreen();
    }
    else if (choice == "8" || choice == "x") 
    {
        cout << "Exiting Program...\n\n";
        exit(0);
    }
    else 
    {
        cout << "\nInvalid Choice, Please select from 1-8!\n";
        system("pause");
    }
}

/*
Displays the menu and handles user input. It keeps running until the user chooses to exit.
input      : None
output     : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void ImprovedDictionary::displayMenu() 
{
    while (true) 
    {
        displayExtendedMenu();
        string choice;
        getline(cin, choice);
        handleUserChoice(choice);
    }
}