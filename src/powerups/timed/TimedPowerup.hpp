#ifndef TIMED_POWERUP_HPP
#define TIMED_POWERUP_HPP
class TimedPowerup;
#include "../Powerup.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Position.hpp"
#include "../../util/RenderableList.hpp"

#define BASE_TIMED_POWERUP_ID 0
#define INVINCIBILITY_TIMED_POWERUP_ID 1
#define INVISIBILITY_TIMED_POWERUP_ID 2

class TimedPowerup : public Powerup {
protected:
	int id, seconds, ticks;
public:
	TimedPowerup(int id, Position position, int seconds);
	// Precondition: seconds >= 0 and position must be inside the level

	int getId();
	int getRemainingTime();
	// Postcondition: returns the remaining time in seconds

	void tick(Player *player);
	// Precondition: player is not NULL

	void onDrop(Player *player);
	// Precondition: player is not NULL

	void onTimeEnd(Player *player);
	// Precondition: player is not NULL

	void getRenderInfo(char titleInfo[], const int length);
};

void timed_powerup_onPickUp(TimedPowerup *powerup, Player *player);
void timed_powerup_onDrop(TimedPowerup *powerup, Player *player);
void timed_powerup_onTimeEnd(TimedPowerup *powerup, Player *player);
void timed_powerup_tick(TimedPowerup *powerup, Player *player);
void timed_powerup_destroy(TimedPowerup *powerup);
void timed_powerup_getName(TimedPowerup *powerup, char name[], const int length);
void timed_powerup_getRenderInfo(TimedPowerup *powerup, char titleInfo[], const int length);
void timed_powerup_getPlayerRenderInfo(TimedPowerup *powerup, Player *player, RenderableList *list);

#endif /* TIMED_POWERUP_HPP */
