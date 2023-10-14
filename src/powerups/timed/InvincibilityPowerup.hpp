#ifndef INVINCIBILITY_POWERUP_HPP
#define INVINCIBILITY_POWERUP_HPP
class InvincibilityPowerup;
#include "TimedPowerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"

class InvincibilityPowerup : public TimedPowerup {
protected:
public:
	InvincibilityPowerup(Position position, int seconds);
	void onPickUp(Player *player);
	void onDrop(Player *player);
	void onTimeEnd(Player *player);
	void getName(char name[], const int length);
};

#endif /* INVINCIBILITY_POWERUP_HPP */
