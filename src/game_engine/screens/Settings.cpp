#include <iostream>
#include <cstring>
#include <windows.h>
#include "Settings.hpp"
#include "../../util/Util.hpp"
#include "../../util/Config.hpp"
#include "Screen.hpp"
#include "../GameManager.hpp"
#include "../../util/KeyInputList.hpp"

using namespace std;

#define UP_COMMAND 0
#define ALTERNATIVE_UP_COMMAND 1
#define DOWN_COMMAND 2
#define LEFT_COMMAND 3
#define RIGHT_COMMAND 4
#define USE_COMMAND 5
#define ESC_COMMAND 6
#define BACK_TO_MENU 7

Settings::Settings(GameManager *gameManager, Screen *prevScreen) : Screen(SETTINGS_SCREEN_ID, gameManager) {
	this->prevScreen = prevScreen;
	this->modifyingCommand = false;
	this->invalidCommand = false;
	this->currentlySelected = UP_COMMAND;
}

void Settings::tick(KeyInputList *inputs) {
	if (modifyingCommand) {
		char newCommand;
		if (getFirstRawInput(newCommand)) {
			if (newCommand >= 'a' && newCommand <= 'z') {
				newCommand = (char)(((int)newCommand) - ((int)'a') + ((int)'A')); // newCommand - ('a' - 'A')
			}

			Commands *commands = gameManager->getCommands();
			if (isInvalidCommand(commands, newCommand)) {
				invalidCommand = true;
			}
			else {
				if (currentlySelected == UP_COMMAND) {
					commands->upCommand = newCommand;
				}
				else if (currentlySelected == ALTERNATIVE_UP_COMMAND) {
					commands->jumpCommand = newCommand;
				}
				else if (currentlySelected == DOWN_COMMAND) {
					commands->downCommand = newCommand;
				}
				else if (currentlySelected == LEFT_COMMAND) {
					commands->leftCommand = newCommand;
				}
				else if (currentlySelected == RIGHT_COMMAND) {
					commands->rightCommand = newCommand;
				}
				else if (currentlySelected == USE_COMMAND) {
					commands->useCommand = newCommand;
				}
				else if (currentlySelected == ESC_COMMAND) {
					commands->escCommand = newCommand;
				}
				invalidCommand = false;
				modifyingCommand = false;
				gameManager->enableInputs();
			}
		}
	}
	else {
		bool skipOthers = false;
		inputs->iter_reset();
		while (!skipOthers && inputs->iter_hasNext()) {
			Input in = inputs->iter_next();
			inputs->iter_remove();
			if (in == UP) {
				if (currentlySelected == ALTERNATIVE_UP_COMMAND) {
					currentlySelected = UP_COMMAND;
				}
				else if (currentlySelected == DOWN_COMMAND) {
					currentlySelected = ALTERNATIVE_UP_COMMAND;
				}
				else if (currentlySelected == LEFT_COMMAND) {
					currentlySelected = DOWN_COMMAND;
				}
				else if (currentlySelected == RIGHT_COMMAND) {
					currentlySelected = LEFT_COMMAND;
				}
				else if (currentlySelected == USE_COMMAND) {
					currentlySelected = RIGHT_COMMAND;
				}
				else if (currentlySelected == ESC_COMMAND) {
					currentlySelected = USE_COMMAND;
				}
				else if (currentlySelected == BACK_TO_MENU) {
					currentlySelected = ESC_COMMAND;
				}
			}
			else if (in == DOWN) {
				if (currentlySelected == UP_COMMAND) {
					currentlySelected = ALTERNATIVE_UP_COMMAND;
				}
				else if (currentlySelected == ALTERNATIVE_UP_COMMAND) {
					currentlySelected = DOWN_COMMAND;
				}
				else if (currentlySelected == DOWN_COMMAND) {
					currentlySelected = LEFT_COMMAND;
				}
				else if (currentlySelected == LEFT_COMMAND) {
					currentlySelected = RIGHT_COMMAND;
				}
				else if (currentlySelected == RIGHT_COMMAND) {
					currentlySelected = USE_COMMAND;
				}
				else if (currentlySelected == USE_COMMAND) {
					currentlySelected = ESC_COMMAND;
				}
				else if (currentlySelected == ESC_COMMAND) {
					currentlySelected = BACK_TO_MENU;
				}
			}
			else if (in == USE) {
				if (currentlySelected == BACK_TO_MENU) {
					gameManager->setActiveScreen(prevScreen);
				}
				else {
					gameManager->disableInputs();
					// Remove every old input registered into the console input buffer, so only new ones will be used
					FlushConsoleInputBuffer(getInputHandle());
					modifyingCommand = true;
				}
				skipOthers = true;
			}
			else if (in == ESC) {
				gameManager->setActiveScreen(prevScreen);
				skipOthers = true;
			}
		}
	}
}

void Settings::render(ResizeInfo resizeInfo) {
	Commands *commands = gameManager->getCommands();

	cout << "Command Settings:\n\n";

	printArrow(UP_COMMAND);
	cout << "Jump command: ";
	printFormatted(commands->upCommand);
	cout << endl;

	printArrow(ALTERNATIVE_UP_COMMAND);
	cout << "Alternative jump command: ";
	printFormatted(commands->jumpCommand);
	cout << endl;

	printArrow(DOWN_COMMAND);
	cout << "Down command: ";
	printFormatted(commands->downCommand);
	cout << endl;

	printArrow(LEFT_COMMAND);
	cout << "Left command: ";
	printFormatted(commands->leftCommand);
	cout << endl;

	printArrow(RIGHT_COMMAND);
	cout << "Right command: ";
	printFormatted(commands->rightCommand);
	cout << endl;

	printArrow(USE_COMMAND);
	cout << "Use command: ";
	printFormatted(commands->useCommand);
	cout << endl;

	printArrow(ESC_COMMAND);
	cout << "Esc command: ";
	printFormatted(commands->escCommand);
	cout << endl;

	cout << endl;
	printArrow(BACK_TO_MENU);
	cout << "Return back\n";

	consoleSetLightGrayColor();
	if (modifyingCommand) {
		if (invalidCommand) {
			cout << "\n[That key is already binded. Enter a new command]\n";
		}
		else {
			cout << "\n[Enter the new command]\n";
		}
	}
	else {
		cout << "\n[Press ";
		printFancy(commands->useCommand);
		if (currentlySelected == BACK_TO_MENU) {
			cout << " to close settings]\n";
		}
		else {
			cout << " to modify]\n";
		}
	}
	consoleResetColor();
}

bool Settings::isInvalidCommand(Commands *command, char newCommand) {
	char current = newCommand;
	if (currentlySelected == UP_COMMAND) {
		current = command->upCommand;
	}
	else if (currentlySelected == ALTERNATIVE_UP_COMMAND) {
		current = command->jumpCommand;
	}
	else if (currentlySelected == DOWN_COMMAND) {
		current = command->downCommand;
	}
	else if (currentlySelected == LEFT_COMMAND) {
		current = command->leftCommand;
	}
	else if (currentlySelected == RIGHT_COMMAND) {
		current = command->rightCommand;
	}
	else if (currentlySelected == USE_COMMAND) {
		current = command->useCommand;
	}
	else if (currentlySelected == ESC_COMMAND) {
		current = command->escCommand;
	}
	return current != newCommand &&
		(command->upCommand == newCommand ||
		 command->jumpCommand == newCommand ||
		 command->downCommand == newCommand ||
		 command->leftCommand == newCommand ||
		 command->rightCommand == newCommand ||
		 command->useCommand == newCommand ||
		 command->escCommand == newCommand);
}

void Settings::printFormatted(char command) {
	consoleSetGrayColor();
	printFancy(command);
	consoleResetColor();
}

void Settings::printArrow(int currentElement) {
	consoleSetLightGrayColor();
	menusPrintArrow(currentlySelected == currentElement);
	consoleResetColor();
}
