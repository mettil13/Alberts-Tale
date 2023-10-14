#ifndef POWERUP_HPP
#define POWERUP_HPP
class Powerup;
#include "../util/Position.hpp"
#include "../entities/Player.hpp"
#include "../util/RenderableList.hpp"
#include <windows.h>

#define BASE_POWERUP_ID 0
#define USABLE_POWERUP_ID 1
#define TIMED_POWERUP_ID 2
#define ONE_OFF_POWERUP_ID 3
#define ALWAYS_ACTIVE_POWERUP_ID 4

// It is not safe to store any pointer to Player in any Powerup, since players are deleted before the activePowerup.
class Powerup {
protected:
	int powerupId;
	char appearence;
	bool consumed, alreadyPickedUp;
	WORD attributes;
	Position position;
public:
	Powerup(int powerupId, Position position);
	// Precondition: position must be inside the level

	int getPowerupId();
	void setPosition(Position position);
	// Precondition: position must be inside the level
	// Postcondition: sets the position of the powerup

	Position getPosition();
	// Postcondition: returns the position of the powerup. Note that the position is not updated if the powerup is currently picked up by the player
	
	char toChar();
	CHAR_INFO toCharInfo();
	bool isConsumed();
	// Postcondition: returns if the powerup is consumed

	void onPickUp(Player *player);
	// Precondition: player must be not NULL

	void getName(char name[], const int length);
	// Precondition: length is the length of name
	// Postcondition: name contains the string with the name of this powerup

	void getRenderInfo(char titleInfo[], const int length);
	// Precondition: length is the length of titleInfo
	// Postcondition: titleInfo contains an string with optional additional information to render

	void getPlayerRenderInfo(Player *player, RenderableList *list);
	// Precondition: player and list must be not NULL
	// Postcondition: optional Renderables to render are added to list

	void destroy();
};

bool powerup_is_usable(Powerup *powerup);
// Precondition: powerup must be not NULL
// Postcondition: returns if powerup is an UsablePowerup

bool powerup_is_timed(Powerup *powerup);
// Precondition: powerup must be not NULL
// Postcondition: returns if powerup is a TimedPowerup

bool powerup_is_oneOff(Powerup *powerup);
// Precondition: powerup must be not NULL
// Postcondition: returns if powerup is a OneOffPowerup

bool powerup_is_alwaysActive(Powerup *powerup);
// Precondition: powerup must be not NULL
// Postcondition: returns if powerup is an AlwaysActivePowerup

void powerup_destroy(Powerup *powerup);
void powerup_onPickUp(Powerup *powerup, Player *player);
void powerup_getName(Powerup *powerup, char name[], const int length);
void powerup_getRenderInfo(Powerup *powerup, char titleInfo[], const int length);
void powerup_getPlayerRenderInfo(Powerup *powerup, Player *player, RenderableList *list);

#endif /* POWERUP_HPP */
