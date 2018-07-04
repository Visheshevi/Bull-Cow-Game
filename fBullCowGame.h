#pragma once
#include <string>

using int32 = int;;
using FString = std::string;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus{
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE,
};

class fBullCowGame {
public:
	fBullCowGame();

	void Reset(); // TODO make a more rich return value.
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetNumberOfTriesLeft() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus checkGuessValidity(FString) const; // TODO make a more rich return value.
	// Counts bulls and cows and increases try, assuming valid guess.
	FBullCowCount SubmitValidGuess(FString);

private:
	// See constructor for initial values
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool isLowercase(FString) const;
};