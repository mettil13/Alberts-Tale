#ifndef ALWAYS_ACTIVE_POWERUP_HPP
#define ALWAYS_ACTIVE_POWERUP_HPP
class AlwaysActivePowerup;
#include "../Powerup.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Position.hpp"
#include "../../util/RenderableList.hpp"

#define BASE_ALWAYS_ACTIVE_POWERUP_ID 0
#define SPEAR_ALWAYS_ACTIVE_POWERUP_ID 1

class AlwaysActivePowerup : public Powerup {
protected:
	int id;
public:
	AlwaysActivePowerup(int id, Position position);
	// Precondition: position must be inside the level

	int getId();
	void tick(Player *player);
	// Precondition: player is not NULL
};

void alwaysActive_powerup_destroy(AlwaysActivePowerup *powerup);
void alwaysActive_powerup_onPickUp(AlwaysActivePowerup *powerup, Player *player);
void alwaysActive_powerup_tick(AlwaysActivePowerup *powerup, Player *player);
void alwaysActive_powerup_getName(AlwaysActivePowerup *powerup, char name[], const int length);
void alwaysActive_powerup_getRenderInfo(AlwaysActivePowerup *powerup, char titleInfo[], const int length);
void alwaysActive_powerup_getPlayerRenderInfo(AlwaysActivePowerup *powerup, Player *player, RenderableList *list);

#endif /* ALWAYS_ACTIVE_POWERUP_HPP */
