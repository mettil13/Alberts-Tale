#ifndef ONE_OFF_POWERUP_HPP
#define ONE_OFF_POWERUP_HPP
class OneOffPowerup;
#include "../Powerup.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Position.hpp"
#include "../../util/RenderableList.hpp"

#define BASE_ONE_OFF_POWERUP_ID 0
#define LIFE_ONE_OFF_POWERUP_ID 1

class OneOffPowerup : public Powerup {
protected:
	int id;
public:
	OneOffPowerup(int id, Position position);
	// Precondition: position must be inside the level

	int getId();
};

void oneOff_powerup_destroy(OneOffPowerup *powerup);
void oneOff_powerup_onPickUp(OneOffPowerup *powerup, Player *player);
void oneOff_powerup_getName(OneOffPowerup *powerup, char name[], const int length);
void oneOff_powerup_getRenderInfo(OneOffPowerup *powerup, char titleInfo[], const int length);
void oneOff_powerup_getPlayerRenderInfo(OneOffPowerup *powerup, Player *player, RenderableList *list);

#endif /* ONE_OFF_POWERUP_HPP */
