#include <iostream>
#include <windows.h>
#include "Powerup.hpp"
#include "usable/UsablePowerup.hpp"
#include "timed/TimedPowerup.hpp"
#include "oneOff/OneOffPowerup.hpp"
#include "alwaysActive/AlwaysActivePowerup.hpp"
#include "../util/Config.hpp"
#include "../util/Position.hpp"
#include "../entities/Player.hpp"
#include "../util/RenderableList.hpp"

using namespace std;

Powerup::Powerup(int powerupId, Position position) {
	this->powerupId = powerupId;
	this->position = position;
	this->appearence = INVALID;
	this->attributes = COLOR_POWERUP;
	this->consumed = false;
	this->alreadyPickedUp = false;
}

int Powerup::getPowerupId() {
	return powerupId;
}

void Powerup::setPosition(Position position) {
	this->position = position;
}

Position Powerup::getPosition() {
	return position;
}

char Powerup::toChar() {
	return appearence;
}

CHAR_INFO Powerup::toCharInfo() {
	CHAR_INFO charInfo;
#ifdef UNICODE
	charInfo.Char.UnicodeChar = (WCHAR)appearence;
#else
	charInfo.Char.AsciiChar = (CHAR)appearence;
#endif /* UNICODE */
	charInfo.Attributes = attributes;
	return charInfo;
}

bool Powerup::isConsumed() {
	return consumed;
}

void Powerup::onPickUp(Player *player) {
	alreadyPickedUp = true;
}

void Powerup::getName(char name[], const int length) {
	if (length > 0) {
		name[0] = '\0';
	}
}

void Powerup::getRenderInfo(char titleInfo[], const int length) {
	if (length > 0) {
		titleInfo[0] = '\0';
	}
}

void Powerup::getPlayerRenderInfo(Player *player, RenderableList *list) {
}

void Powerup::destroy() {
}

bool powerup_is_usable(Powerup *powerup) {
	return powerup->getPowerupId() == USABLE_POWERUP_ID;
}

bool powerup_is_timed(Powerup *powerup) {
	return powerup->getPowerupId() == TIMED_POWERUP_ID;
}

bool powerup_is_oneOff(Powerup *powerup) {
	return powerup->getPowerupId() == ONE_OFF_POWERUP_ID;
}

bool powerup_is_alwaysActive(Powerup *powerup) {
	return powerup->getPowerupId() == ALWAYS_ACTIVE_POWERUP_ID;
}

void powerup_destroy(Powerup *powerup) {
	if (powerup != NULL) {
		int id = powerup->getPowerupId();
		if (id == BASE_POWERUP_ID) {
			powerup->destroy();
		}
		else if (id == USABLE_POWERUP_ID) {
			usable_powerup_destroy((UsablePowerup*) powerup);
		}
		else if (id == TIMED_POWERUP_ID) {
			timed_powerup_destroy((TimedPowerup*) powerup);
		}
		else if (id == ONE_OFF_POWERUP_ID) {
			oneOff_powerup_destroy((OneOffPowerup*) powerup);
		}
		else if (id == ALWAYS_ACTIVE_POWERUP_ID) {
			alwaysActive_powerup_destroy((AlwaysActivePowerup*) powerup);
		}
	}
}

void powerup_onPickUp(Powerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getPowerupId();
		if (id == BASE_POWERUP_ID) {
			powerup->onPickUp(player);
		}
		else if (id == USABLE_POWERUP_ID) {
			usable_powerup_onPickUp((UsablePowerup*) powerup, player);
		}
		else if (id == TIMED_POWERUP_ID) {
			timed_powerup_onPickUp((TimedPowerup*) powerup, player);
		}
		else if (id == ONE_OFF_POWERUP_ID) {
			oneOff_powerup_onPickUp((OneOffPowerup*) powerup, player);
		}
		else if (id == ALWAYS_ACTIVE_POWERUP_ID) {
			alwaysActive_powerup_onPickUp((AlwaysActivePowerup*) powerup, player);
		}
	}
}

void powerup_getName(Powerup *powerup, char name[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getPowerupId();
		if (id == BASE_POWERUP_ID) {
			powerup->getName(name, length);
		}
		else if (id == USABLE_POWERUP_ID) {
			usable_powerup_getName((UsablePowerup*) powerup, name, length);
		}
		else if (id == TIMED_POWERUP_ID) {
			timed_powerup_getName((TimedPowerup*) powerup, name, length);
		}
		else if (id == ONE_OFF_POWERUP_ID) {
			oneOff_powerup_getName((OneOffPowerup*) powerup, name, length);
		}
		else if (id == ALWAYS_ACTIVE_POWERUP_ID) {
			alwaysActive_powerup_getName((AlwaysActivePowerup*) powerup, name, length);
		}
	}
}

void powerup_getRenderInfo(Powerup *powerup, char titleInfo[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getPowerupId();
		if (id == BASE_POWERUP_ID) {
			powerup->getRenderInfo(titleInfo, length);
		}
		else if (id == USABLE_POWERUP_ID) {
			usable_powerup_getRenderInfo((UsablePowerup*) powerup, titleInfo, length);
		}
		else if (id == TIMED_POWERUP_ID) {
			timed_powerup_getRenderInfo((TimedPowerup*) powerup, titleInfo, length);
		}
		else if (id == ONE_OFF_POWERUP_ID) {
			oneOff_powerup_getRenderInfo((OneOffPowerup*) powerup, titleInfo, length);
		}
		else if (id == ALWAYS_ACTIVE_POWERUP_ID) {
			alwaysActive_powerup_getRenderInfo((AlwaysActivePowerup*) powerup, titleInfo, length);
		}
	}
}

void powerup_getPlayerRenderInfo(Powerup *powerup, Player *player, RenderableList *list) {
	if (powerup != NULL) {
		int id = powerup->getPowerupId();
		if (id == BASE_POWERUP_ID) {
			powerup->getPlayerRenderInfo(player, list);
		}
		else if (id == USABLE_POWERUP_ID) {
			usable_powerup_getPlayerRenderInfo((UsablePowerup*) powerup, player, list);
		}
		else if (id == TIMED_POWERUP_ID) {
			timed_powerup_getPlayerRenderInfo((TimedPowerup*) powerup, player, list);
		}
		else if (id == ONE_OFF_POWERUP_ID) {
			oneOff_powerup_getPlayerRenderInfo((OneOffPowerup*) powerup, player, list);
		}
		else if (id == ALWAYS_ACTIVE_POWERUP_ID) {
			alwaysActive_powerup_getPlayerRenderInfo((AlwaysActivePowerup*) powerup, player, list);
		}
	}
}
