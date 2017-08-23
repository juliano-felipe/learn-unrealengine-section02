/*
 *
 */
#pragma once
#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal Engine friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

// default constructor
FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const
{ 
    TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
    return WordLengthToMaxTries[MyHiddenWord.length()]; 
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess)) { return EGuessStatus::Not_Isogram; }
    if (!IsLowerCase(Guess)) { return EGuessStatus::Not_Lowercase; }
    if (Guess.length() != GetHiddenWordLength()) { return EGuessStatus::Wrong_Length; }
    return EGuessStatus::OK;
}


void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "pla"; // this must be an isogram
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}


// receives a VALID guess, increments turn, and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = GetHiddenWordLength(); // assumes same length as guess
    for (int32 i = 0; i < WordLength; i++) // loop through hidden word letters
    {
        for (int32 j = 0; j < WordLength; j++) // compare letters against the guess
        {
            if (Guess[j] == MyHiddenWord[i])
            {
                if (i == j)
                {
                    BullCowCount.Bulls++;
                }
                else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    }
    else 
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

// checks if Guess is an isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1) { return true; }
    TMap<char, bool> LetterSeen;
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) { return false; }
        LetterSeen[Letter] = true;
    }
    return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter)) { return false; }
    }
    return true;
}
