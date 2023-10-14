#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
class GameManager;
#include "screens/Screen.hpp"
#include "../util/Util.hpp"
#include "../util/Config.hpp"

class GameManager {
protected:
	Screen *activeScreen;
	bool active, newScreenLoaded, inputActivated;
	Commands commands;
public:
	GameManager();
	void start();
	// Postcondition: starts the game if it isn't already started

	void stop();
	// Postcondition: stops the game if it is already started

	bool isActive();
	// Postcondition: returns whether the game is started

	void enableInputs();
	// Postcondition: enables automatic inputs handling if they have been disabled
	//                Screen::tick(KeyInputList* list) will receive a list containing the user's inputs starting from the next tick

	void disableInputs();
	// Postcondition: disables automatic inputs handling. Screen::tick(KeyInputList* list) will receive an empty list starting from the next tick

	bool isNewScreenLoaded();
	// Postcondition: returns whether a new screen has been loaded during this tick

	Screen* setActiveScreen(Screen *screen);
	// Postcondition: loads screen, returning the previous one. If the new screen is NULL, then the game will stop.
	//                Automatic inputs handling is enabled if it was disabled

	Screen* getActiveScreen();
	// Postcondition: returns the active screen

	Commands* getCommands();
	// Postcondition: returns a pointer to the struct with the command settings for the game
};

#endif /* GAME_MANAGER_HPP */
