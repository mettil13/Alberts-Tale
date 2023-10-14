#include <iostream>
#include <cstring>
#include "GunPowerup.hpp"
#include "../../entities/Player.hpp"
#include "../../entities/enemy/BulletEnemy.hpp"
#include "../../util/Config.hpp"
#include "../../util/Util.hpp"
#include "UsablePowerup.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

using namespace std;

GunPowerup::GunPowerup(Position position, int bullets) : UsablePowerup(GUN_USABLE_POWERUP_ID, position, bullets) {
	this->appearence = GUN_POWERUP_CHAR;
}

void GunPowerup::onUse(Player *player) {
	if (remainingUses > 0) {
		Level *level = player->getLevel();
		Position pos = player->getPosition();
		Orientation o = player->getOrientation();
		if (o == ORIENTATION_RIGHT) {
			pos = pos.right();
		}
		else if (o == ORIENTATION_LEFT) {
			pos = pos.left();
		}
		player->getLevel()->getEnemyList()->add(new BulletEnemy(level, pos, o));
	}
	UsablePowerup::onUse(player);
}

void GunPowerup::onPickUp(Player *player) {
	if (!alreadyPickedUp) {
		player->increasePoints(GUN_POWERUP_POINTS);
	}
	UsablePowerup::onPickUp(player);
}

void GunPowerup::getName(char name[], const int length) {
	if (length > 0) {
		strncpy(name, "Gun", length - 1);
		name[length - 1] = '\0';
	}
}
