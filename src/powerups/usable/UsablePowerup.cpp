#include <iostream>
#include <cstring>
#include "UsablePowerup.hpp"
#include "../../util/Util.hpp"
#include "GunPowerup.hpp"
#include "../Powerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"
#include "../../util/RenderableList.hpp"

using namespace std;

UsablePowerup::UsablePowerup(int id, Position position, int maxUses) : Powerup(USABLE_POWERUP_ID, position) {
	this->id = id;
	this->maxUses = maxUses;
	this->remainingUses = maxUses;
}

int UsablePowerup::getId() {
	return id;
}

int UsablePowerup::getMaxUses() {
	return maxUses;
}

int UsablePowerup::getRemainingUses() {
	return remainingUses;
}

void UsablePowerup::onUse(Player *player) {
	if (remainingUses > 0)
		remainingUses--;
	if (remainingUses == 0) {
		consumed = true;
	}
}

void UsablePowerup::getRenderInfo(char titleInfo[], const int length) {
	if (length > 0) {
		char number[10];
		int nLen = intToString(remainingUses, number, 10);
		if (nLen < length) {
			strncpy(titleInfo, number, nLen);
			int mLen = intToString(maxUses, number, 10);
			if (nLen + mLen + 1 < length) {
				titleInfo[nLen] = '/';
				titleInfo[nLen + 1] = '\0';
				strncat(titleInfo, number, mLen);
				titleInfo[nLen + mLen + 1] = '\0';
			}
			else {
				titleInfo[nLen] = '\0';
			}
		}
		else {
			titleInfo[0] = '\0';
		}
	}
}

void usable_powerup_destroy(UsablePowerup *powerup) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_USABLE_POWERUP_ID) {
			powerup->destroy();
		}
		else if (id == GUN_USABLE_POWERUP_ID) {
			((GunPowerup*) powerup)->destroy();
		}
	}
}

void usable_powerup_onUse(UsablePowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_USABLE_POWERUP_ID) {
			powerup->onUse(player);
		}
		else if (id == GUN_USABLE_POWERUP_ID) {
			((GunPowerup*) powerup)->onUse(player);
		}
	}
}

void usable_powerup_onPickUp(UsablePowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_USABLE_POWERUP_ID) {
			powerup->onPickUp(player);
		}
		else if (id == GUN_USABLE_POWERUP_ID) {
			((GunPowerup*) powerup)->onPickUp(player);
		}
	}
}

void usable_powerup_getName(UsablePowerup *powerup, char name[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_USABLE_POWERUP_ID) {
			powerup->getName(name, length);
		}
		else if (id == GUN_USABLE_POWERUP_ID) {
			((GunPowerup*) powerup)->getName(name, length);
		}
	}
}

void usable_powerup_getRenderInfo(UsablePowerup *powerup, char titleInfo[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_USABLE_POWERUP_ID) {
			powerup->getRenderInfo(titleInfo, length);
		}
		else if (id == GUN_USABLE_POWERUP_ID) {
			((GunPowerup*) powerup)->getRenderInfo(titleInfo, length);
		}
	}
}

void usable_powerup_getPlayerRenderInfo(UsablePowerup *powerup, Player *player, RenderableList *list) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_USABLE_POWERUP_ID) {
			powerup->getPlayerRenderInfo(player, list);
		}
		else if (id == GUN_USABLE_POWERUP_ID) {
			((GunPowerup*) powerup)->getPlayerRenderInfo(player, list);
		}
	}
}
