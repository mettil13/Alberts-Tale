#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "Util.hpp"
#include "Block.hpp"
#include "Config.hpp"
#include "KeyInputList.hpp"

using namespace std;

KeyInputList* getGameInput(Commands *commands) {
	KeyInputList *keyInput = new KeyInputList();

	if (GetConsoleWindow() == GetForegroundWindow()) {
		if ((GetKeyState(commands->upCommand) < 0 || GetKeyState(commands->jumpCommand) < 0) && !keyInput->contains(UP)) {
			keyInput->add(UP);
		}
		if (GetKeyState(commands->downCommand) < 0 && !keyInput->contains(DOWN)) {
			keyInput->add(DOWN);
		}
		if (GetKeyState(commands->leftCommand) < 0 && !keyInput->contains(LEFT)) {
			keyInput->add(LEFT);
		}
		if (GetKeyState(commands->rightCommand) < 0 && !keyInput->contains(RIGHT)) {
			keyInput->add(RIGHT);
		}
		if (GetKeyState(commands->useCommand) < 0 && !keyInput->contains(USE)) {
			keyInput->add(USE);
		}
		if (GetKeyState(commands->escCommand) < 0 && !keyInput->contains(ESC)) {
			keyInput->add(ESC);
		}
	}

	return keyInput;
}

bool getFirstRawInput(char &rawInput) {
	bool found = false;
	if (GetConsoleWindow() == GetForegroundWindow()) {
		INPUT_RECORD inputRecord;
		DWORD eventsRead;
		DWORD bufferEvents = 0;

		if (GetNumberOfConsoleInputEvents(getInputHandle(), &bufferEvents)) {
			if (bufferEvents > 0) {
				if (ReadConsoleInput(getInputHandle(), &inputRecord, 1, &eventsRead)) {
					if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
#ifdef UNICODE
						WCHAR key = inputRecord.Event.KeyEvent.uChar.UnicodeChar;
#else
						CHAR key = inputRecord.Event.KeyEvent.uChar.AsciiChar;
#endif /* UNICODE */
						if (((int)key) > 0 && ((int)key) <= 127) { // Better safe than sorry
							rawInput = (char)key;
							found = true;
						}
					}
				}
			}
		}

		FlushConsoleInputBuffer(getInputHandle());
	}
	return found;
}

ResizeInfo getWindowSize() {
	ResizeInfo windowSize;
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(getOutputHandle(), &bufferInfo);
	windowSize.X = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
	windowSize.Y = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
	return windowSize;
}

void clearScreen(int windowLength, int windowHeight) {
	COORD origin;
	origin.X = 0;
	origin.Y = 0;
	DWORD useless; // Variable required by FillConsoleOutputCharacter and FillConsoleOutputAttribute (cannot be put to NULL), but never used after that

	int res = windowLength * windowHeight;
	FillConsoleOutputCharacter(getOutputHandle(), ' ', res, origin, &useless);
	FillConsoleOutputAttribute(getOutputHandle(), COLOR_AIR, res, origin, &useless);
	SetConsoleCursorPosition(getOutputHandle(), origin);
}

int randomize(int max) {
	return randomize(0, max);
}

int randomize(int min, int max) {
	return min + rand() % (max - min);
}

int randomizeProbability() {
	return randomize(1, 101);
}

bool randomizeProbability(const int probability) {
	return randomizeProbability() <= probability;
}

int intToString(int number, char string[], const int length) {
	if (length > 1) {
		if (number == 0) {
			string[0] = '0';
			string[1] = '\0';
			return 1;
		}
		else {
			int i = 0;
			int n;
			if (number < 0) {
				string[0] = '-';
				number = -number;
				i++;
				n = 1;
			}
			else {
				n = 0;
			}

			while (number > 0 && i < length - 1) {
				string[i] = (char)(number % 10 + ((int)'0'));
				number = number / 10;
				i++;
			}

			string[i] = '\0';

			int t = i - 1;
			while (n < t) {
				char tmp = string[n];
				string[n] = string[t];
				string[t] = tmp;
				n++;
				t--;
			}
			return i;
		}
	}
	else {
		if (length != 0) {
			string[0] = '\0';
		}
		return 0;
	}
}

void consoleSetGrayColor() {
	SetConsoleTextAttribute(getOutputHandle(), COLOR_GRAY);
}

void consoleSetLightGrayColor() {
	SetConsoleTextAttribute(getOutputHandle(), COLOR_LIGHT_GRAY);
}

void consoleSetHUDColor() {
	SetConsoleTextAttribute(getOutputHandle(), COLOR_HUD);
}

void consoleResetColor() {
	SetConsoleTextAttribute(getOutputHandle(), COLOR_TEXT);
}

void menusPrintArrow(bool condition) {
	if (condition) {
		cout << "-> ";
	}
	else {
		cout << "   ";
	}
}

void printFancy(char command) {
	if (command >= 'a' && command <= 'z') {
		cout << (char)(((int)command) - ((int)'a') + ((int)'A')); // command - ('a' - 'A')
	}
	else if (command == ' ') {
		cout << "SPACE";
	}
	else if (((int)command) == 27) { // esc
		cout << "ESC";
	}
	else if (((int)command) == 9) { // tab
		cout << "TAB";
	}
	else if (((int)command) == 24) { // canc
		cout << "CANC";
	}
	else if (((int)command) == 127) { // del
		cout << "DEL";
	}
	else if (((int)command) == 13) { // enter
		cout << "ENTER";
	}
	else {
		cout << command;
	}
}

void hideConsoleCursor() {
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	if (GetConsoleCursorInfo(getOutputHandle(), &consoleCursorInfo)) {
		consoleCursorInfo.bVisible = false;
		SetConsoleCursorInfo(getOutputHandle(), &consoleCursorInfo);
	}
}

void showConsoleCursor() {
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	if (GetConsoleCursorInfo(getOutputHandle(), &consoleCursorInfo)) {
		consoleCursorInfo.bVisible = true;
		SetConsoleCursorInfo(getOutputHandle(), &consoleCursorInfo);
	}
}

void fromAsciiToUnicode(char asciiArray[], int asciiArrayLenght, WCHAR unicodeArray[], int unicodeArrayLenght) {
	int i;
	for (i = 0; i < asciiArrayLenght || i < unicodeArrayLenght; i++) {
		unicodeArray[i] = (WCHAR) asciiArray[i];
	}
	unicodeArray[i - 1] = (WCHAR) '\0';
}
