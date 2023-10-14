#include <iostream>
#include <cstring>
#include <windows.h>
#include "SpearPowerup.hpp"
#include "../../util/Util.hpp"
#include "../../util/Config.hpp"
#include "AlwaysActivePowerup.hpp"
#include "../../util/Position.hpp"
#include "../../entities/Player.hpp"
#include "../../entities/enemy/EnemyList.hpp"
#include "../../util/Renderable.hpp"
#include "../../util/RenderableList.hpp"

using namespace std;

SpearPowerup::SpearPowerup(Position position, int maxDurability) : AlwaysActivePowerup(SPEAR_ALWAYS_ACTIVE_POWERUP_ID, position) {
	this->durability = maxDurability;
	this->maxDurability = maxDurability;
	this->appearence = SPEAR_POWERUP_CHAR;
}

void SpearPowerup::killEnemiesAt(Player *player, Position pos) {
	EnemyList *list = player->getLevel()->getEnemyList()->getEnemiesAt(pos);
	list->iter_reset();
	while (list->iter_hasNext() && durability > 0) {
		list->iter_next()->kill();
		durability--;
		list->iter_remove();
		// Don't delete the enemy since it is inside level->getEnemyList() and will be removed at the end of Level::tick()
	}
	while (list->iter_hasNext()) {
		list->iter_next();
		list->iter_remove();
		// Don't delete the enemy since it is inside level->getEnemyList()
	}
	delete list;
}

void SpearPowerup::tick(Player *player) {
	if (!consumed) {
		Position posSpear, posInFront;
		if (player->getOrientation() == ORIENTATION_RIGHT) {
			posSpear = player->getPosition().right();
			posInFront = posSpear.right();
		}
		else { // player->getOrientation() == ORIENTATION_LEFT
			posSpear = player->getPosition().left();
			posInFront = posSpear.left();
		}

		killEnemiesAt(player, posSpear);
		killEnemiesAt(player, posInFront);

		if (durability == 0) {
			consumed = true;
		}
	}
}

void SpearPowerup::onPickUp(Player *player) {
	if (!alreadyPickedUp) {
		player->increasePoints(SPEAR_POWERUP_POINTS);
	}
	AlwaysActivePowerup::onPickUp(player);
}

void SpearPowerup::getName(char name[], const int length) {
	if (length > 0) {
		strncpy(name, "Spear", length - 1);
		name[length - 1] = '\0';
	}
}

void SpearPowerup::getRenderInfo(char titleInfo[], const int length) {
	if (length > 0) {
		char number[10];
		int nLen = intToString(durability, number, 10);
		if (nLen < length) {
			strncpy(titleInfo, number, nLen);
			int mLen = intToString(maxDurability, number, 10);
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

void SpearPowerup::getPlayerRenderInfo(Player *player, RenderableList *list) {
	AlwaysActivePowerup::getPlayerRenderInfo(player, list);
	Position pos;
	if (player->getOrientation() == ORIENTATION_RIGHT) {
		pos = player->getPosition().right();
	}
	else { // player->getOrientation() == ORIENTATION_LEFT
		pos = player->getPosition().left();
	}

	CHAR_INFO charInfo;

#ifdef UNICODE
	charInfo.Char.UnicodeChar = SPEAR_POWERUP_CHAR;
#else
	charInfo.Char.AsciiChar = SPEAR_POWERUP_CHAR;
#endif /* UNICODE */
	charInfo.Attributes = COLOR_PLAYER;
	list->add(new Renderable(pos, charInfo));
}
