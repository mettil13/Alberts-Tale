#include <iostream>
#include "Menu.hpp"
#include "../GameManager.hpp"
#include "LevelManager.hpp"
#include "../../util/KeyInputList.hpp"
#include "Settings.hpp"
#include "Screen.hpp"
#include "../../util/Util.hpp"
#include "../../util/Config.hpp"

using namespace std;

#define NEW_GAME 0
#define SETTINGS 1
#define EXIT 2

Menu::Menu(GameManager *gameManager) : Screen(MENU_SCREEN_ID, gameManager) {
	currentlySelected = NEW_GAME;
	levelManager = NULL;
	settings = NULL;
}

void Menu::startNewGame() {
	if (levelManager != NULL) {
		levelManager->destroy();
		delete levelManager;
	}
	levelManager = new LevelManager(this);
	gameManager->setActiveScreen(levelManager);
}

void Menu::openSettings() {
	if (settings != NULL) {
		settings->destroy();
		delete settings;
	}
	settings = new Settings(gameManager, this);
	gameManager->setActiveScreen(settings);
}

void Menu::tick(KeyInputList *inputs) {
	bool skipOthers = false;
	inputs->iter_reset();
	while (!skipOthers && inputs->iter_hasNext()) {
		Input in = inputs->iter_next();
		inputs->iter_remove();
		if (in == UP) {
			if (currentlySelected == SETTINGS) {
				currentlySelected = NEW_GAME;
			}
			else if (currentlySelected == EXIT) {
				currentlySelected = SETTINGS;
			}
		}
		else if (in == DOWN) {
			if (currentlySelected == NEW_GAME) {
				currentlySelected = SETTINGS;
			}
			else if (currentlySelected == SETTINGS) {
				currentlySelected = EXIT;
			}
		}
		else if (in == USE) {
			if (currentlySelected == NEW_GAME) {
				startNewGame();
			}
			else if (currentlySelected == SETTINGS) {
				openSettings();
			}
			else if (currentlySelected == EXIT) {
				gameManager->stop();
			}
			skipOthers = true;
		}
	}
}

void Menu::render(ResizeInfo resizeInfo) {
	cout << "Main Menu\n\n";
	printArrow(NEW_GAME);
	cout << "New Game\n";
	printArrow(SETTINGS);
	cout << "Settings\n";
	printArrow(EXIT);
	cout << "Exit\n";

	consoleSetLightGrayColor();
	cout << "\n[Press ";
	printFancy(gameManager->getCommands()->useCommand);
	if (currentlySelected == NEW_GAME) {
		cout << " to start a new game]\n";
	}
	else if (currentlySelected == SETTINGS) {
		cout << " to open settings]\n";
	}
	else { // currentlySelected == EXIT
		cout << " to close the game]\n";
	}
	consoleResetColor();
}

void Menu::destroy() {
	if (levelManager != NULL) {
		levelManager->destroy();
		delete levelManager;
		levelManager = NULL;
	}
	if (settings != NULL) {
		settings->destroy();
		delete settings;
		settings = NULL;
	}
}

void Menu::printArrow(int currentElement) {
	consoleSetLightGrayColor();
	menusPrintArrow(currentlySelected == currentElement);
	consoleResetColor();
}
