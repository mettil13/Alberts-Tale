#ifndef UTIL_HPP
#define UTIL_HPP
#include <windows.h>
#include "Config.hpp"

typedef bool Orientation;
#define ORIENTATION_RIGHT true
#define ORIENTATION_LEFT false

typedef int Input;
#define NONE 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define USE 5
// 6 unused
#define ESC 7

typedef COORD ResizeInfo;

#include "KeyInputList.hpp"

KeyInputList* getGameInput(Commands *commands);
// Precondition: commands != NULL
// Postcondition: The returned pointer is always != NULL

bool getFirstRawInput(char &rawInput);

ResizeInfo getWindowSize();

void clearScreen(int windowLength, int windowHeight);
// Precondition: windowLength > 0 and windowHeight > 0
// Postcondition: Clears the specified portion of the console

int randomize(int max);
// Precondition: max > 0
// Postcondition: returns a random integer between 0 and max - 1

int randomize(int min, int max);
// Precondition: 0 <= min < max
// Postcondition: returns a random integer between min and max - 1

int randomizeProbability();
// Postcondition: returns a random generated number between 1 and 100

bool randomizeProbability(const int probability);
// Precondition: 0 <= probability <= 100
// Postcondition: returns whether a random generated number between 1 and 100 is lower or equals to probability.
//                Passing zero to this function returns false everytime, while passing 100 returns true everytime

int intToString(int number, char string[], const int length);
// Precondition: length >= 0
// Postcondition: puts the number converted into string in the string array and returns the length of the number.
//                For example, for 157 string is "157\0" and the returned value is 3.
//                The returned value is always >= 0. If length is 0, the returned value is 0, else it is < length

void consoleSetGrayColor();

void consoleSetLightGrayColor();

void consoleSetHUDColor();

void consoleResetColor();

void menusPrintArrow(bool condition);

void printFancy(char command);

void hideConsoleCursor();

void showConsoleCursor();

void fromAsciiToUnicode(char asciiArray[], int asciiArrayLenght, WCHAR unicodeArray[], int unicodeArrayLenght);
// Precondition: asciiArrayLenght >= 0 and unicodeArrayLenght >= 0
// Postcondition: unicodeArray is filled with the converted values from asciiArray

#endif /* UTIL_HPP */
