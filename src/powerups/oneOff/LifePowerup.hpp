#ifndef LIFE_POWERUP_HPP
#define LIFE_POWERUP_HPP
class LifePowerup;
#include "OneOffPowerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"

class LifePowerup : public OneOffPowerup {
	int lifeIncrease;
protected:
public:
	LifePowerup(Position position, int lifeIncrease);
	void onPickUp(Player *player);
};

#endif /* LIFE_POWERUP_HPP */
