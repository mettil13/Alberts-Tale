#ifndef PAUSE_HPP
#define PAUSE_HPP
class Pause;
#include "../GameManager.hpp"
#include "LevelManager.hpp"
#include "Menu.hpp"
#include "Screen.hpp"
#include "Settings.hpp"
#include "../../util/KeyInputList.hpp"
#include "../../util/Util.hpp"

class Pause : public Screen {
protected:
	// Initially NULL
	Settings *settings;

	LevelManager *levelManager;
	Menu *menu;
	int currentlySelected;
	void printArrow(int currentElement);
public:
	Pause(GameManager *gameManager, LevelManager *levelManager, Menu *menu);
	void continueGame();
	void openSettings();
	void backToMenu();
	void tick(KeyInputList *inputs);
	void render(ResizeInfo resizeInfo);
	void destroy();
};

#endif /* PAUSE_HPP */
