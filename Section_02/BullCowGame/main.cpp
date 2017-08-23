/* 
 * This is the console executable, that makes use of the BullCow class.
 * This acts as the view in a MVC pattern, and is responsible for all
 * user interaction. For game logic, see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;

// function prototype as outside a class
void PlayGame();
void PrintIntro();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// instantiate a new game, which we re-use across plays
FBullCowGame BCGame;

// the entry point for our application
int main()
{
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while(bPlayAgain);
	return 0; // exit the application
}


void PrintIntro()
{
    std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << "          }   {         ___              " << std::endl;
    std::cout << "          (o o)        (o o)             " << std::endl;
    std::cout << "   /-------\\ /          \\ /------\\    " << std::endl;
    std::cout << "  / | BULL |O            O| COW | \\     " << std::endl;
    std::cout << " *  |-,--- |              |-----|  *     " << std::endl;
    std::cout << "    ^      ^              ^     ^        " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}


// Plays a single game to completion
void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    PrintGameSummary();
    return;
}


// loop continually until the user gives a valid gues
FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lowercase letters.\n";
            break;
        default:
            // assume the guess is valid
            break;
        }
    } while (Status != EGuessStatus::OK);
    return Guess;
}



bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? (y/N) ";
    FText Response = "";
    std::getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL WONE - YOU WIN!\n";
    } 
    else
    {
        std::cout << "You loose! Better Luck Next Time!\n";
    }
    return;
}
