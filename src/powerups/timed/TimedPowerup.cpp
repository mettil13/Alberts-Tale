#include <iostream>
#include "TimedPowerup.hpp"
#include "InvincibilityPowerup.hpp"
#include "InvisibilityPowerup.hpp"
#include "../../util/Util.hpp"
#include "../Powerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"
#include "../../util/RenderableList.hpp"

using namespace std;

TimedPowerup::TimedPowerup(int id, Position position, int seconds) : Powerup(TIMED_POWERUP_ID, position) {
	this->id = id;
	this->seconds = seconds;
	this->ticks = 0;
}

int TimedPowerup::getId() {
	return id;
}

int TimedPowerup::getRemainingTime() {
	return seconds;
}

void TimedPowerup::tick(Player *player) {
	if (seconds >= 0) {
		ticks++;
		if (ticks == TICKS_PER_SECOND) {
			ticks = 0;
			if (seconds == 0) {
				timed_powerup_onTimeEnd(this, player);
			}
			else {
				seconds--;
			}
		}
	}
}

void TimedPowerup::onDrop(Player *player) {
}

void TimedPowerup::onTimeEnd(Player *player) {
	consumed = true;
}

void TimedPowerup::getRenderInfo(char titleInfo[], const int length) {
	if (length > 0) {
		char number[10];
		int nLen = intToString(seconds, number, 10);
		if (nLen < length) {
			strncpy(titleInfo, number, nLen);
			if (nLen + 1 < length) {
				titleInfo[nLen] = 's';
				titleInfo[nLen + 1] = '\0';
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

void timed_powerup_onPickUp(TimedPowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->onPickUp(player);
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->onPickUp(player);
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->onPickUp(player);
		}
	}
}

void timed_powerup_onDrop(TimedPowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->onDrop(player);
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->onDrop(player);
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->onDrop(player);
		}
	}
}

void timed_powerup_onTimeEnd(TimedPowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->onTimeEnd(player);
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->onTimeEnd(player);
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->onTimeEnd(player);
		}
	}
}

void timed_powerup_tick(TimedPowerup *powerup, Player *player) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->tick(player);
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->tick(player);
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->tick(player);
		}
	}
}

void timed_powerup_destroy(TimedPowerup *powerup) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->destroy();
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->destroy();
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->destroy();
		}
	}
}

void timed_powerup_getName(TimedPowerup *powerup, char name[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->getName(name, length);
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->getName(name, length);
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->getName(name, length);
		}
	}
}

void timed_powerup_getRenderInfo(TimedPowerup *powerup, char titleInfo[], const int length) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->getRenderInfo(titleInfo, length);
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->getRenderInfo(titleInfo, length);
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->getRenderInfo(titleInfo, length);
		}
	}
}

void timed_powerup_getPlayerRenderInfo(TimedPowerup *powerup, Player *player, RenderableList *list) {
	if (powerup != NULL) {
		int id = powerup->getId();
		if (id == BASE_TIMED_POWERUP_ID) {
			powerup->getPlayerRenderInfo(player, list);
		}
		else if (id == INVINCIBILITY_TIMED_POWERUP_ID) {
			((InvincibilityPowerup*) powerup)->getPlayerRenderInfo(player, list);
		}
		else if (id == INVISIBILITY_TIMED_POWERUP_ID) {
			((InvisibilityPowerup*) powerup)->getPlayerRenderInfo(player, list);
		}
	}
}
