#pragma once

#include "fBullCowGame.h"
#include <map>

#define TMap std::map
using int32 = int;

fBullCowGame::fBullCowGame(){
	Reset();
}

void fBullCowGame::Reset(){
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int fBullCowGame::GetMaxTries() const{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,18} };
	return WordLengthToMaxTries[MyHiddenWord.length()];

}

int fBullCowGame::GetCurrentTry() const{
	return MyCurrentTry;
}

int fBullCowGame::GetNumberOfTriesLeft() const{
	return 0;
}

int32 fBullCowGame::GetHiddenWordLength() const{
	return (MyHiddenWord.length());
}

bool fBullCowGame::IsGameWon() const{
	return bGameIsWon;
}

EWordStatus fBullCowGame::checkGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EWordStatus::NOT_ISOGRAM;
	}
	else if (!isLowercase(Guess)) {
		return EWordStatus::NOT_LOWERCASE;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EWordStatus::WRONG_LENGTH;
	}
	else {
		return EWordStatus::OK;
	}
}

// Receives a valid guess. Increments try. Return count
FBullCowCount fBullCowGame::SubmitValidGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	//loop pthorugh all letters. Sample algo
	int32 HiddenWordLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++) {
			if (MyHiddenWord[GChar] == Guess[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	// loop through all letters in the gues and for each letter compare letters against the given word
	return BullCowCount;
}

bool fBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool fBullCowGame::isLowercase(FString Word) const
{
	if (Word.length() == 0) { return true; }
	for (auto Letter : Word) {
		if (!islower(Letter))
			return false;
	}
	return true;
}
