#ifndef DEATH_HPP
#define DEATH_HPP
class Death;
#include "Screen.hpp"
#include "Menu.hpp"
#include "../../util/KeyInputList.hpp"
#include "../../util/Util.hpp"

class Death : public Screen {
protected:
	Menu *menu;
public:
	Death(Menu *menu);
	void backToMenu();
	void tick(KeyInputList *inputs);
	void render(ResizeInfo resizeInfo);
};

#endif /* DEATH_HPP */
