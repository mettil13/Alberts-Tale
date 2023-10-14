#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP
class LevelManager;
#include "Screen.hpp"
#include "Menu.hpp"
#include "../levels/Level.hpp"
#include "../../entities/Player.hpp"
#include "LevelList.hpp"
#include "Pause.hpp"
#include "../../util/Util.hpp"
#include "../../util/KeyInputList.hpp"

class LevelManager : public Screen {
protected:
	// Initially NULL
	Pause *pause;

	LevelList *levels;
	SharedData *sharedData;
	Menu *menu;
public:
	LevelManager(Menu *menu);
	// Precondition: menu must be not NULL
	// Postcondition: adds the first level to the level list

	Menu* getMenu();
	// Postcondition: the returned pointer is always not NULL

	Level* getCurrentLevel();
	// Postcondition: returns the current level. The returned pointer is always not NULL

	void nextLevel();
	// Postcondition: moves to the next level and generates it if it doesn't exist yet

	void previousLevel();
	// Postcondition: moves to the previous level if there is one
	
	void pauseGame();
	// Postcondition: opens the Pause screen

	void tick(KeyInputList *inputs);
	void render(ResizeInfo resizeInfo);
	void destroy();
};

#endif /* LEVEL_MANAGER_HPP */
