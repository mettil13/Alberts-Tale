#ifndef SCREEN_HPP
#define SCREEN_HPP
class Screen;
#include "../GameManager.hpp"
#include "../../util/KeyInputList.hpp"
#include "../../util/Util.hpp"

#define BASE_SCREEN_ID 0
#define MENU_SCREEN_ID 1
#define SETTINGS_SCREEN_ID 2
#define LEVEL_MANAGER_SCREEN_ID 3
#define PAUSE_SCREEN_ID 4
#define DEATH_SCREEN_ID 5

class Screen {
protected:
	int id;
	GameManager *gameManager;
public:
	Screen(int id, GameManager *gameManager);
	// Postcondition: gameManager must be not NULL

	GameManager *getGameManager();
	// Postcondition: the returned pointer is always not NULL

	int getId();
	void tick(KeyInputList *inputs);
	// Precondition: inputs must be not NULL

	void render(ResizeInfo resizeInfo);
	void destroy();
};

void screen_tick(Screen *screen, KeyInputList *inputs);
void screen_render(Screen *screen, ResizeInfo resizeInfo);
void screen_destroy(Screen *screen);

#endif /* SCREEN_HPP */
