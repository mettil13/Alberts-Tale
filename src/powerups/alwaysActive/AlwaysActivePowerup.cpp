#include <iostream>
#include "AlwaysActivePowerup.hpp"
#include "SpearPowerup.hpp"
#include "../../util/RenderableList.hpp"
#include "../../util/Position.hpp"
#include "../Powerup.hpp"
#include "../../entities/Player.hpp"

using namespace std;

AlwaysActivePowerup::AlwaysActivePowerup(int id, Position position) : Powerup(ALWAYS_ACTIVE_POWERUP_ID, position) {
	this->id = id;
}

int AlwaysActivePowerup::getId() {
	return id;
}

void AlwaysActivePowerup::tick(Player *player) {
}

void alwaysActive_powerup_destroy(AlwaysActivePowerup *powerup) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ALWAYS_ACTIVE_POWERUP_ID) {
			powerup->destroy();
		}
		else if (id == SPEAR_ALWAYS_ACTIVE_POWERUP_ID) {
			((SpearPowerup*) powerup)->destroy();
		}
	}
}

void alwaysActive_powerup_onPickUp(AlwaysActivePowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ALWAYS_ACTIVE_POWERUP_ID) {
			powerup->onPickUp(player);
		}
		else if (id == SPEAR_ALWAYS_ACTIVE_POWERUP_ID) {
			((SpearPowerup*) powerup)->onPickUp(player);
		}
	}
}

void alwaysActive_powerup_tick(AlwaysActivePowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ALWAYS_ACTIVE_POWERUP_ID) {
			powerup->tick(player);
		}
		else if (id == SPEAR_ALWAYS_ACTIVE_POWERUP_ID) {
			((SpearPowerup*) powerup)->tick(player);
		}
	}
}

void alwaysActive_powerup_getName(AlwaysActivePowerup *powerup, char name[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ALWAYS_ACTIVE_POWERUP_ID) {
			powerup->getName(name, length);
		}
		else if (id == SPEAR_ALWAYS_ACTIVE_POWERUP_ID) {
			((SpearPowerup*) powerup)->getName(name, length);
		}
	}
}

void alwaysActive_powerup_getRenderInfo(AlwaysActivePowerup *powerup, char titleInfo[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ALWAYS_ACTIVE_POWERUP_ID) {
			powerup->getRenderInfo(titleInfo, length);
		}
		else if (id == SPEAR_ALWAYS_ACTIVE_POWERUP_ID) {
			((SpearPowerup*) powerup)->getRenderInfo(titleInfo, length);
		}
	}
}

void alwaysActive_powerup_getPlayerRenderInfo(AlwaysActivePowerup *powerup, Player *player, RenderableList *list) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_ALWAYS_ACTIVE_POWERUP_ID) {
			powerup->getPlayerRenderInfo(player, list);
		}
		else if (id == SPEAR_ALWAYS_ACTIVE_POWERUP_ID) {
			((SpearPowerup*) powerup)->getPlayerRenderInfo(player, list);
		}
	}
}
