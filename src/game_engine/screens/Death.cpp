#include <iostream> 
#include "Death.hpp"
#include "Screen.hpp"
#include "../../util/KeyInputList.hpp"
#include "../../util/Util.hpp"

using namespace std;

Death::Death(Menu *menu) : Screen(DEATH_SCREEN_ID, menu->getGameManager()) {
	this->menu = menu;
}

void Death::backToMenu() {
	gameManager->setActiveScreen(menu);
}

void Death::tick(KeyInputList *inputs) {
	inputs->iter_reset();
	while (inputs->iter_hasNext()) {
		inputs->iter_next();
		if (inputs->iter_get() == USE) {
			backToMenu();
		}
	}
}

void Death::render(ResizeInfo resizeInfo) {
	cout << "GAME OVER" << endl;
	cout << endl;
	consoleSetLightGrayColor();
	menusPrintArrow(true);
	consoleResetColor();
	cout << "Main Menu";
	cout << endl;
	consoleSetLightGrayColor();
	cout << "\n[Press ";
	printFancy(gameManager->getCommands()->useCommand);
	cout << " to return to main menu]\n";
	consoleResetColor();
}
