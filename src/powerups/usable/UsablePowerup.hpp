#ifndef USABLE_POWERUP_HPP
#define USABLE_POWERUP_HPP
class UsablePowerup;
#include "../Powerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"
#include "../../util/RenderableList.hpp"

#define BASE_USABLE_POWERUP_ID 0
#define GUN_USABLE_POWERUP_ID 1

class UsablePowerup : public Powerup {
protected:
	int id, remainingUses, maxUses;
public:
	UsablePowerup(int id, Position position, int maxUses);
	// Precondition: maxUses >= 0 and position must be inside the level

	int getId();
	int getMaxUses();
	// Postcondition: returns the max uses. The returned value is always >= 0

	int getRemainingUses();
	// Postcondition: returns the remaining uses. The returned value is always >= 0

	void onUse(Player *player);
	// Precondition: player is not NULL

	void getRenderInfo(char titleInfo[], const int length);
};

void usable_powerup_destroy(UsablePowerup *powerup);
void usable_powerup_onUse(UsablePowerup *powerup, Player *player);
void usable_powerup_onPickUp(UsablePowerup *powerup, Player *player);
void usable_powerup_getName(UsablePowerup *powerup, char name[], const int length);
void usable_powerup_getRenderInfo(UsablePowerup *powerup, char titleInfo[], const int length);
void usable_powerup_getPlayerRenderInfo(UsablePowerup *powerup, Player *player, RenderableList *list);

#endif /* USABLE_POWERUP_HPP */
