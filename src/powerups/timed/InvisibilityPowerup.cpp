#include <iostream>
#include <cstring>
#include "InvisibilityPowerup.hpp"
#include "../../util/Config.hpp"
#include "TimedPowerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"

using namespace std;

InvisibilityPowerup::InvisibilityPowerup(Position position, int seconds) : TimedPowerup(INVISIBILITY_TIMED_POWERUP_ID, position, seconds) {
	this->appearence = INVISIBILITY_POWERUP_CHAR;
}

void InvisibilityPowerup::onPickUp(Player *player) {
	if (!alreadyPickedUp) {
		player->increasePoints(INVISIBILITY_POWERUP_POINTS);
	}
	TimedPowerup::onPickUp(player);
	player->setVisible(false);
}

void InvisibilityPowerup::onDrop(Player *player) {
	player->setVisible(true);
}

void InvisibilityPowerup::onTimeEnd(Player *player) {
	TimedPowerup::onTimeEnd(player);
	player->setVisible(true);
}

void InvisibilityPowerup::getName(char name[], const int length) {
	if (length > 0) {
		strncpy(name, "Invisibility", length - 1);
		name[length - 1] = '\0';
	}
}
