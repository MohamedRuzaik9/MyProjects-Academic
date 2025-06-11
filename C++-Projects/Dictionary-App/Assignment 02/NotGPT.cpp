//Student Name: Mohamed Ruzaik MOHAMED RIZWAN
//Student ID: 10686380
//Date: 22/5/2025

#include "NotGPT.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

/*
Constructor for NotGPT class. Initializes the random number generator.
input      : None
output     : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
NotGPT::NotGPT() : rng(random_device{}()) 
{
    // Initialize random number generator with random seed
}


/*
Trains the NotGPT model using the provided text. It prepares the text, counts trigrams, and calculates probabilities.
input      : text - the text to train on
output     : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void NotGPT::trainOnText(const string& text) {
    string cleanText = prepareTrainingText(text);
    // Clear previious data
    trigramCounts.clear();
    trigramProbabilities.clear();
    // Count trigrams - analyze every three consecutive characters
    for (size_t i = 0; i < cleanText.length() - 2; ++i) 
    {
        // First two characters
        string context = cleanText.substr(i, 2);
        // Third character
        char nextChar = cleanText[i + 2];             
        trigramCounts[context][nextChar]++;
    }
    // Calculate probabilities from counts
    calculateProbabilities();
}

/*
Calculates the probabilities of each character following a given context. It normalizes the counts to get probabilities.
input      : None
output     : None
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
void NotGPT::calculateProbabilities() 
{
    for (const auto& contextPair : trigramCounts) 
    {
        const string& context = contextPair.first;
        const auto& charCounts = contextPair.second;
        // Calculate total count for this context
        int totalCount = 0;
        for (const auto& charCount : charCounts) 
        {
            totalCount += charCount.second;
        }
                // Calculate probabilities for each character
        for (const auto& charCount : charCounts) 
        {
            char ch = charCount.first;
            int count = charCount.second;
            trigramProbabilities[context][ch] = static_cast<double>(count) / totalCount;
        }
    }
}

/*
Gets the top three predictions for the next character based on the last two characters.
input      : twoChars - the last two characters
output     : vector of pairs containing character and its probability
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
vector<pair<char, double>> NotGPT::getTopThreePredictions(const string& twoChars) 
{
    vector<pair<char, double>> predictions;

    // Check if have data for this
    auto it = trigramProbabilities.find(twoChars);
    if (it != trigramProbabilities.end()) 
    {
        const auto& charProbs = it->second;

        // Convert map to vector for sorting
        for (const auto& pair : charProbs) 
        {
            predictions.push_back({ pair.first, pair.second });
        }
        // Sort by probability.highest is first
        sort(predictions.begin(), predictions.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        // Keep only top 3
        if (predictions.size() > 3) 
        {
            predictions.resize(3);
        }
    }
    return predictions;
}


/*
Predicts the next character based on the last two characters. It uses a weighted random selection based on the probabilities.
input      : context - the last two characters
output     : predicted character
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
char NotGPT::predictNextChar(const string& context) 
{
    auto predictions = getTopThreePredictions(context);
    if (predictions.empty()) 
    {
        // Default to space if no predictions available
        return ' '; 
    }
    // Weighted random selection based on the probabilities
    uniform_real_distribution<double> dist(0.0, 1.0);
    double random = dist(rng);
    double cumulative = 0.0;
    for (const auto& pred : predictions)
    {
        cumulative += pred.second;
        if (random <= cumulative)
        {
            return pred.first;
        }
    }
    return predictions[0].first;
}

/*
Gets a random starting character for word generation. It selects characters that commonly start words.
input      : None
output     : random starting character
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
char NotGPT::getRandomStartingChar() 
{
    vector<pair<char, double>> startingChars;
    // Look for patterns that start with the space 
    for (const auto& contextPair : trigramProbabilities) 
    {
        if (contextPair.first[0] == ' ') 
        {
            for (const auto& charProb : contextPair.second) 
            {
                if (isalpha(charProb.first)) 
                {
                    startingChars.push_back(charProb);
                }
            }
        }
    }

    if (startingChars.empty())
    {
        return 'a'; 
    }
    // Select random character weighted by probability
    uniform_real_distribution<double> dist(0.0, 1.0);
    double random = dist(rng);
    double cumulative = 0.0;
    for (const auto& charProb : startingChars) 
    {
        cumulative += charProb.second;
        if (random <= cumulative) 
        {
            return charProb.first;
        }
    }
    return startingChars[0].first;
}

/*
Prepares the training text by converting it to lowercase and removing unwanted characters.
input      : text - the text to prepare
output     : prepared text
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
string NotGPT::prepareTrainingText(const string& text) 
{
    string prepared;
    prepared.reserve(text.length());

    for (char c : text) 
    {
        if (isalpha(c))
        {
            prepared += tolower(c);
        }
        else if (c == ' ' || c == '-' || c == '\n' || c == '\r' || c == '\t') 
        {
            // Convert whitespace to single space
            if (!prepared.empty() && prepared.back() != ' ')
            {
                prepared += ' ';
            }
        }
        
    }
    return prepared;
}

/*
Generates a random word using the trained model. It starts with a random character and builds the word based on predictions.
input      : None
output     : generated word
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
string NotGPT::generateWord() 
{
    string word;
    // Start with a character that commonly begins words
    char firstChar = getRandomStartingChar();
    word += firstChar;
    // Add the second character to establish context
    string context = " ";
    context += firstChar;
    char secondChar = predictNextChar(context);
    if (isalpha(secondChar))
    {
        word += secondChar;
    }
    else 
    {
        word += 'e';
    }
    // Generate the remaining characters
    context = word.substr(word.length() - 2, 2);
    // Max additional characters
    for (int i = 0; i < 8; ++i) 
    { 
        char nextChar = predictNextChar(context);
        // stop if when space or non-alphabetic character
        if (nextChar == ' ' || !isalpha(nextChar)) 
        {
            break;
        }
        word += nextChar;
        // Update the context window
        context = context.substr(1) + nextChar; 
        // Stop if word gets too long
        if (word.length() >= 10)
        {
            break;
        }
    }
    // check minimum word length
    if (word.length() < 3)
    {
        word += "ing";
    }
    return word;
}

/*
Generates a random sentence using the trained model. It generates a random number of words and combines them into a sentence.
input      : None
output     : generated sentence
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
string NotGPT::generateSentence() 
{
    string sentence;
    uniform_int_distribution<int> wordDist(5, 10);
    int wordCount = wordDist(rng);
    for (int i = 0; i < wordCount; ++i) 
    {
        if (i > 0) {
            sentence += " ";
        }
        sentence += generateWord();
    }
    sentence += ".";
    // Capitalize the first letter
    if (!sentence.empty() && isalpha(sentence[0]))
    {
        sentence[0] = toupper(sentence[0]);
    }
    return sentence;
}

/*
Generates a random paragraph using the trained model. It generates a random number of sentences and combines them into a paragraph.
input      : None
output     : generated paragraph
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
string NotGPT::generateParagraph()
{
    string paragraph;
    uniform_int_distribution<int> sentDist(4, 8);
    int sentenceCount = sentDist(rng);
    for (int i = 0; i < sentenceCount; ++i) 
    {
        if (i > 0)
        {
            paragraph += " ";
        }
        paragraph += generateSentence();
    }
    return paragraph;
}

/*
Checks if the NotGPT model is trained. It returns true if the model has been trained with data.
input       : None
output      : true if trained, false otherwise
created by  : Mohamed Ruzaik MOHAMED RIZWAN
date        : 22/5/2025
*/
bool NotGPT::isTrained() const 
{
    return !trigramProbabilities.empty();
}