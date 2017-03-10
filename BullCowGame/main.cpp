/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game, which we re-use across plays

//the entry point for our application
int main()
{

	do
	{
		std::cout << std::endl;
		PrintIntro();
		PlayGame();

	} while (AskToPlayAgain());

	return 0; // exit the application
}
  

void PrintIntro() 
{

	// introduce the game
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;

	std::cout << "MM                   MM                                     \n";
	std::cout << "MMM+                8MM                                     \n";
	std::cout << "MMMMMM            :MMM                        MM,     ZMM   \n";
	std::cout << "ZMMM+MMMM+       MMMM                         MMMO  MMMMM   \n";
	std::cout << "   MMM  MMMMMMMMMMMN                            MMMMMMMZ    \n";
	std::cout << "    MMMMM   MMMMMMMMM                        ZMMMZMZ, MMMMMM\n";
	std::cout << "      $MMD  MMM    MMMMMMM         MMMMMMMMMMMMM         MMM\n";
	std::cout << "777MMMMDI               I7MMM~  7MMMIIIIIII+                \n";
	std::cout << "MMM?                       MMM +MM                          \n";
	std::cout << "                           ZMM +M+                          \n";
	std::cout << "        B U L L S          MMM  MM            C O W S       \n";
	std::cout << "                     MMMMMMMO    MMMMMMM                    \n";
	std::cout << "               ZMMMMMMMM               MMMMM                \n";
	std::cout << "             MMMM                         MMMMM             \n";
	std::cout << "            MMM                               MMMMM         \n";
	std::cout << "           MMO                                   MM,        \n";
       
	std::cout << "\n Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << "\n What is an isogram, you ask? A word that does not have any repeating letters in it.\n";
	std::cout << "  \"planet\" is an isogram, while \"pollen\" is not.\n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

	    Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter word without repeating letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";

	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
