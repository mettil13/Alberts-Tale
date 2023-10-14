#ifndef GUN_POWERUP_HPP
#define GUN_POWERUP_HPP
class GunPowerup;
#include "UsablePowerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"

class GunPowerup : public UsablePowerup {
protected:
public:
	GunPowerup(Position position, int bullets);
	void onUse(Player *player);
	void onPickUp(Player *player);
	void getName(char name[], const int length);
};

#endif /* GUN_POWERUP_HPP */
