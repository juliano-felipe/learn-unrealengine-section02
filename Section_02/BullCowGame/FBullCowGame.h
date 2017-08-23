/* The game logic (no view code or direct user interaction)
 * The game is a simple guess word game based on Mastermind
 */
#pragma once
#include <string>

// To make the syntax Unreal Engine friendly
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};


enum class EGuessStatus 
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};


class FBullCowGame {
public:
    FBullCowGame(); // constructor

    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;

    EGuessStatus CheckGuessValidity(FString) const;

    void Reset();
    FBullCowCount SubmitValidGuess(FString);

// ^^ Please try and ignore this and focus on the interface above ^^
private:
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;

    // see constructor for initialisation
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;
    
};
