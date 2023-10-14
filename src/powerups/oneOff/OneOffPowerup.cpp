#include <iostream>
#include "OneOffPowerup.hpp"
#include "LifePowerup.hpp"
#include "../../util/Position.hpp"
#include "../Powerup.hpp"
#include "../../util/RenderableList.hpp"
#include "../../entities/Player.hpp"

using namespace std;

OneOffPowerup::OneOffPowerup(int id, Position position) : Powerup(ONE_OFF_POWERUP_ID, position) {
	this->id = id;
}

int OneOffPowerup::getId() {
	return id;
}

void oneOff_powerup_destroy(OneOffPowerup *powerup) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ONE_OFF_POWERUP_ID) {
			powerup->destroy();
		}
		else if (id == LIFE_ONE_OFF_POWERUP_ID) {
			((LifePowerup*) powerup)->destroy();
		}
	}
}

void oneOff_powerup_onPickUp(OneOffPowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ONE_OFF_POWERUP_ID) {
			powerup->onPickUp(player);
		}
		else if (id == LIFE_ONE_OFF_POWERUP_ID) {
			((LifePowerup*) powerup)->onPickUp(player);
		}
	}
}

void oneOff_powerup_getName(OneOffPowerup *powerup, char name[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ONE_OFF_POWERUP_ID) {
			powerup->getName(name, length);
		}
		else if (id == LIFE_ONE_OFF_POWERUP_ID) {
			((LifePowerup*) powerup)->getName(name, length);
		}
	}
}

void oneOff_powerup_getRenderInfo(OneOffPowerup *powerup, char titleInfo[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ONE_OFF_POWERUP_ID) {
			powerup->getRenderInfo(titleInfo, length);
		}
		else if (id == LIFE_ONE_OFF_POWERUP_ID) {
			((LifePowerup*) powerup)->getRenderInfo(titleInfo, length);
		}
	}
}

void oneOff_powerup_getPlayerRenderInfo(OneOffPowerup *powerup, Player *player, RenderableList *list) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ONE_OFF_POWERUP_ID) {
			powerup->getPlayerRenderInfo(player, list);
		}
		else if (id == LIFE_ONE_OFF_POWERUP_ID) {
			((LifePowerup*) powerup)->getPlayerRenderInfo(player, list);
		}
	}
}
