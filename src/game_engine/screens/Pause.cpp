#include <iostream>
#include "Pause.hpp"
#include "Screen.hpp"
#include "LevelManager.hpp"
#include "../GameManager.hpp"
#include "Settings.hpp"
#include "../../util/KeyInputList.hpp"
#include "Menu.hpp"
#include "../../util/Util.hpp"
#include "../../util/Config.hpp"

using namespace std;

#define CONTINUE 0
#define SETTINGS 1
#define BACK_TO_MENU 2

Pause::Pause(GameManager *gameManager, LevelManager *levelManager, Menu *menu) : Screen(PAUSE_SCREEN_ID, gameManager) {
	this->levelManager = levelManager;
	this->menu = menu;
	this->settings = NULL;
	this->currentlySelected = CONTINUE;
}

void Pause::continueGame() {
	gameManager->setActiveScreen(levelManager);
}

void Pause::openSettings() {
	if (settings != NULL) {
		settings->destroy();
		delete settings;
	}
	settings = new Settings(gameManager, this);
	gameManager->setActiveScreen(settings);
}

void Pause::backToMenu() {
	gameManager->setActiveScreen(menu);
}

void Pause::tick(KeyInputList *inputs) {
	bool skipOthers = false;
	inputs->iter_reset();
	while (!skipOthers && inputs->iter_hasNext()) {
		Input in = inputs->iter_next();
		inputs->iter_remove();
		if (in == UP) {
			if (currentlySelected == SETTINGS) {
				currentlySelected = CONTINUE;
			}
			else if (currentlySelected == BACK_TO_MENU) {
				currentlySelected = SETTINGS;
			}
		}
		else if (in == DOWN) {
			if (currentlySelected == CONTINUE) {
				currentlySelected = SETTINGS;
			}
			else if (currentlySelected == SETTINGS) {
				currentlySelected = BACK_TO_MENU;
			}
		}
		else if (in == USE) {
			if (currentlySelected == CONTINUE) {
				continueGame();
			}
			else if (currentlySelected == SETTINGS) {
				openSettings();
			}
			else if (currentlySelected == BACK_TO_MENU) {
				backToMenu();
			}
			skipOthers = true;
		}
		else if (in == ESC) {
			continueGame();
			skipOthers = true;
		}
	}
}

void Pause::render(ResizeInfo resizeInfo) {
	cout << "Pause\n\n";
	printArrow(CONTINUE);
	cout << "Continue\n";
	printArrow(SETTINGS);
	cout << "Settings\n";
	printArrow(BACK_TO_MENU);
	cout << "Main menu\n";

	consoleSetLightGrayColor();
	cout << "\n[Press ";
	printFancy(gameManager->getCommands()->useCommand);
	if (currentlySelected == CONTINUE) {
		cout << " to continue the game]\n";
	}
	else if (currentlySelected == SETTINGS) {
		cout << " to open settings]\n";
	}
	else { // currentlySelected == BACK_TO_MENU
		cout << " to return to main menu]\n";
	}
	consoleResetColor();
}

void Pause::destroy() {
	if (settings != NULL) {
		settings->destroy();
		delete settings;
		settings = NULL;
	}
}

void Pause::printArrow(int currentElement) {
	consoleSetLightGrayColor();
	menusPrintArrow(currentlySelected == currentElement);
	consoleResetColor();
}
