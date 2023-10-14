#include <iostream>
#include "Screen.hpp"
#include "../GameManager.hpp"
#include "../../util/KeyInputList.hpp"
#include "Menu.hpp"
#include "../../util/Util.hpp"
#include "Pause.hpp"
#include "Settings.hpp"
#include "Death.hpp"
#include "LevelManager.hpp"

using namespace std;

Screen::Screen(int id, GameManager *gameManager) {
	this->id = id;
	this->gameManager = gameManager;
}

int Screen::getId() {
	return id;
}
void Screen::tick(KeyInputList *inputs) {
	// Do nothing
}
void Screen::render(ResizeInfo resizeInfo) {
	// Do nothing
}
void Screen::destroy() {
	// Do nothing
}

GameManager* Screen::getGameManager() {
	return gameManager;
}

void screen_tick(Screen *screen, KeyInputList *inputs) {
	if (screen != NULL) {
		int id = screen->getId();
		if (id == BASE_SCREEN_ID) {
			screen->tick(inputs);
		}
		else if (id == MENU_SCREEN_ID) {
			((Menu*) screen)->tick(inputs);
		}
		else if (id == SETTINGS_SCREEN_ID) {
			((Settings*) screen)->tick(inputs);
		}
		else if (id == LEVEL_MANAGER_SCREEN_ID) {
			((LevelManager*) screen)->tick(inputs);
		}
		else if (id == PAUSE_SCREEN_ID) {
			((Pause*) screen)->tick(inputs);
		}
		else if (id == DEATH_SCREEN_ID) {
			((Death*) screen)->tick(inputs);
		}
	}
}

void screen_render(Screen *screen, ResizeInfo resizeInfo) {
	if (screen != NULL) {
		int id = screen->getId();
		if (id == BASE_SCREEN_ID) {
			screen->render(resizeInfo);
		}
		else if (id == MENU_SCREEN_ID) {
			((Menu*) screen)->render(resizeInfo);
		}
		else if (id == SETTINGS_SCREEN_ID) {
			((Settings*) screen)->render(resizeInfo);
		}
		else if (id == LEVEL_MANAGER_SCREEN_ID) {
			((LevelManager*) screen)->render(resizeInfo);
		}
		else if (id == PAUSE_SCREEN_ID) {
			((Pause*) screen)->render(resizeInfo);
		}
		else if (id == DEATH_SCREEN_ID) {
			((Death*) screen)->render(resizeInfo);
		}
	}
}

void screen_destroy(Screen *screen) {
	if (screen != NULL) {
		int id = screen->getId();
		if (id == BASE_SCREEN_ID) {
			screen->destroy();
		}
		else if (id == MENU_SCREEN_ID) {
			((Menu*) screen)->destroy();
		}
		else if (id == SETTINGS_SCREEN_ID) {
			((Settings*) screen)->destroy();
		}
		else if (id == LEVEL_MANAGER_SCREEN_ID) {
			((LevelManager*) screen)->destroy();
		}
		else if (id == PAUSE_SCREEN_ID) {
			((Pause*) screen)->destroy();
		}
		else if (id == DEATH_SCREEN_ID) {
			((Death*) screen)->destroy();
		}
	}
}
