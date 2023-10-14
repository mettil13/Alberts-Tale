#include <iostream>
#include <cstring>
#include "InvincibilityPowerup.hpp"
#include "../../util/Config.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Position.hpp"
#include "TimedPowerup.hpp"

using namespace std;

InvincibilityPowerup::InvincibilityPowerup(Position position, int seconds) : TimedPowerup(INVINCIBILITY_TIMED_POWERUP_ID, position, seconds) {
	this->appearence = INVINCIBILITY_POWERUP_CHAR;
}

void InvincibilityPowerup::onPickUp(Player *player) {
	if (!alreadyPickedUp) {
		player->increasePoints(INVINCIBILITY_POWERUP_POINTS);
	}
	TimedPowerup::onPickUp(player);
	player->setInvincible(true);
}

void InvincibilityPowerup::onDrop(Player *player) {
	player->setInvincible(false);
}

void InvincibilityPowerup::onTimeEnd(Player *player) {
	TimedPowerup::onTimeEnd(player);
	player->setInvincible(false);
}

void InvincibilityPowerup::getName(char name[], const int length) {
	if (length > 0) {
		strncpy(name, "Invincibility", length - 1);
		name[length - 1] = '\0';
	}
}
