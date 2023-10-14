#include <iostream>
#include <windows.h>
#include "GameManager.hpp"
#include "../util/Config.hpp"
#include "../util/Util.hpp"
#include "../util/KeyInputList.hpp"
#include "screens/Screen.hpp"

using namespace std;

GameManager::GameManager() {
	activeScreen = NULL;
	active = false;
	newScreenLoaded = false;
	commands = getDefaultCommands();
	inputActivated = true;
}

void GameManager::start() {
	if (!active) {
		newScreenLoaded = false;
		active = true;
		DWORD tickTimer = 0;
		DWORD lastExec = GetCurrentTime();

		while (active) {
			DWORD now = GetCurrentTime();
			tickTimer += now - lastExec;
			lastExec = now;
			if (tickTimer >= TICK_MILLISECONDS) {
				tickTimer = tickTimer % TICK_MILLISECONDS;

				if (activeScreen == NULL) {
					active = false;
				}
				else {
					KeyInputList *input;
					if (inputActivated) {
						input = getGameInput(&commands);
					}
					else {
						input = new KeyInputList();
					}

					screen_tick(activeScreen, input);

					input->iter_reset();
					while (input->iter_hasNext()) {
						input->iter_next();
						input->iter_remove();
					}
					delete input;
					input = NULL;
					if (active) {
						if (newScreenLoaded) {
							newScreenLoaded = false;
							FlushConsoleInputBuffer(getInputHandle());
						}
						else {
							LockWindowUpdate(GetConsoleWindow());
							ResizeInfo windowSize = getWindowSize();
							clearScreen(windowSize.X, windowSize.Y);
							hideConsoleCursor();
							screen_render(activeScreen, windowSize);
							LockWindowUpdate(NULL);
						}
					}
				}
			}
		}
	}
}

void GameManager::stop() {
	active = false;
}

bool GameManager::isActive() {
	return active;
}

void GameManager::enableInputs() {
	inputActivated = true;
}

void GameManager::disableInputs() {
	inputActivated = false;
}

bool GameManager::isNewScreenLoaded() {
	return newScreenLoaded;
}

Screen* GameManager::setActiveScreen(Screen *screen) {
	Screen *old = activeScreen;
	activeScreen = screen;
	newScreenLoaded = true;
	enableInputs();
	return old;
}

Screen* GameManager::getActiveScreen() {
	return activeScreen;
}

Commands* GameManager::getCommands() {
	return &commands;
}
