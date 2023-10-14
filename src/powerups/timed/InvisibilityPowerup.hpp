#ifndef INVISIBILITY_POWERUP_HPP
#define INVISIBILITY_POWERUP_HPP
class InvisibilityPowerup;
#include "TimedPowerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"
#include "../../util/RenderableList.hpp"

class InvisibilityPowerup : public TimedPowerup {
protected:
public:
	InvisibilityPowerup(Position position, int seconds);
	void onPickUp(Player *player);
	void onDrop(Player *player);
	void onTimeEnd(Player *player);
	void getName(char name[], const int length);
};

#endif /* INVISIBILITY_POWERUP_HPP */
