#ifndef SETTINGS_HPP
#define SETTINGS_HPP
class Settings;
#include "../GameManager.hpp"
#include "Screen.hpp"
#include "../../util/Config.hpp"
#include "../../util/Util.hpp"
#include "../../util/KeyInputList.hpp"

class Settings : public Screen {
protected:
	Screen *prevScreen;
	int currentlySelected;
	bool modifyingCommand, invalidCommand;
	bool isInvalidCommand(Commands *command, char newCommand);
	void printFormatted(char command);
	void printArrow(int currentElement);
public:
	Settings(GameManager *gameManager, Screen *prevScreen);
	void tick(KeyInputList *inputs);
	void render(ResizeInfo resizeInfo);
};

#endif /* SETTINGS_HPP */
