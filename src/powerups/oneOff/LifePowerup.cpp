#include <iostream>
#include <cstring>
#include "LifePowerup.hpp"
#include "../../util/Config.hpp"
#include "../../util/Position.hpp"
#include "OneOffPowerup.hpp"
#include "../../entities/Player.hpp"

using namespace std;

LifePowerup::LifePowerup(Position position, int lifeIncrease) : OneOffPowerup(LIFE_ONE_OFF_POWERUP_ID, position) {
	this->lifeIncrease = lifeIncrease;
	this->appearence = LIFE_POWERUP_CHAR;
}

void LifePowerup::onPickUp(Player *player) {
	if (!alreadyPickedUp) {
		player->increasePoints(LIFE_POWERUP_POINTS);
	}
	OneOffPowerup::onPickUp(player);
	player->increaseLife(lifeIncrease);
}
