#ifndef MENU_HPP
#define MENU_HPP
class Menu;
#include "../GameManager.hpp"
#include "Screen.hpp"
#include "LevelManager.hpp"
#include "Settings.hpp"
#include "../../util/KeyInputList.hpp"
#include "../../util/Util.hpp"

class Menu : public Screen {
protected:
	// Initially NULL
	LevelManager *levelManager;
	Settings *settings;

	int currentlySelected;
	void printArrow(int currentElement);
public:
	Menu(GameManager *gameManager);
	void startNewGame();
	void openSettings();
	void tick(KeyInputList *inputs);
	void render(ResizeInfo resizeInfo);
	void destroy();
};

#endif /* MENU_HPP */
