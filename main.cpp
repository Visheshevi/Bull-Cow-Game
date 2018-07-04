/* This is the console executable, that makes use of the Bull cow class. 
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class*/
#pragma once

#include <iostream>
#include <string>
#include "fBullCowGame.h"

using FText = std::string;
using int32 = int;

void IntroduceTheGame();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

fBullCowGame BCGame; // Make an instance of a new game

int main() {
	
	bool bWantsToPlayAgain = false;
	do {
		IntroduceTheGame();
		PlayGame();
		bWantsToPlayAgain = AskToPlayAgain();
	} while (bWantsToPlayAgain);

	return 0; // Exits game
}

void  PlayGame(){
	BCGame.Reset();
	int32 maxTries = BCGame.GetMaxTries();

	
	// loop for the number of turns asking for guesses 
	// TODO change For loop to while loop once we are validating
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries) {
		FText Guess = "";
		Guess = GetValidGuess(); // TODO make loop checking valid
	
		
		// submit valid guess to the game and receive counts

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print32 number of bulls and cows
		std::cout << "Number of Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Number of Cows: " << BullCowCount.Cows << std::endl;
	
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

// Introduction for the Game
void IntroduceTheGame() {
	// introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows CLI" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter word that I am thinking of? " << std::endl;
	return;
}

// Method to get the guess from the player
FText GetValidGuess() {
	FText Guess = "";
	EWordStatus Status = EWordStatus::INVALID;
	do {
		int32 MyCurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << MyCurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.checkGuessValidity(Guess);
		switch (Status) {
		case EWordStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " length word" << std::endl;
			break;
		case EWordStatus::NOT_ISOGRAM:
			std::cout << "Please enter a word with all different characters" << std::endl;
			break;
		case EWordStatus::NOT_LOWERCASE:
			std::cout << "Please enter all lower case letters" << std::endl;
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EWordStatus::OK);
	return Guess;
}

bool AskToPlayAgain(){
	std::cout << "Do you want to play again?(y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


//summarize the game
void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You won!!! Congratulations." << std::endl;
	}
	else {
		std::cout << "Better luck next time. " << std::endl;
	}
	std::cout << std::endl;
}