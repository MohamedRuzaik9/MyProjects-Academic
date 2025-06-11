//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include <string>
#include <map>
#include <vector>
#include <random>

using namespace std;
/*
Class representing a simple text generator. It uses trigrams to predict the next character based on the last two characters.
input       : None
output      : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/

class NotGPT {
private:
    map<string, map<char, int>> trigramCounts;
    map<string, map<char, double>> trigramProbabilities;
    mt19937 rng;
    void calculateProbabilities();
    char predictNextChar(const string& context);
    char getRandomStartingChar();
    string prepareTrainingText(const string& text);

public:
    NotGPT();
    void trainOnText(const string& text);
    vector<pair<char, double>> getTopThreePredictions(const string& twoChars);
    string generateWord();
    string generateSentence();
    string generateParagraph();
    bool isTrained() const;
};