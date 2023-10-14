#include <iostream>
#include "ScreamingEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../Player.hpp"
#include "../../util/Position.hpp"
#include "Enemy.hpp"
#include "../../util/RenderableList.hpp"
#include "../../util/Renderable.hpp"

using namespace std;

ScreamingEnemy::ScreamingEnemy(Level *level, Position position) : Enemy(SCREAMING_ENEMY_ID, level, position) {
	this->appearence = SCREAMING_ENEMY_CHAR;
	leftScream = position;
	rightScream = position;
	screamProgression = 0;
	leftScreamActive = true;
	rightScreamActive = true;
}

void ScreamingEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position)) {
		player->decreaseLife(SCREAMING_ENEMY_DAMAGE);
	}

	if (skipTick(SCREAMING_ENEMY_AWAIT_TICKS)) {
		if (screamProgression < SCREAMING_ENEMY_RANGE) {
			screamProgression++;
			if (!level->getBlockAt(leftScream.left()).isSolid() && !level->getBlockAt(leftScream.left()).isInvalid() && leftScreamActive) {
				leftScream = leftScream.left();
			}
			else {
				leftScreamActive = false;
			}
			if (!level->getBlockAt(rightScream.right()).isSolid() && !level->getBlockAt(rightScream.right()).isInvalid() && rightScreamActive) {
				rightScream = rightScream.right();
			}
			else {
				rightScreamActive = false;
			}
		}
		else {
			leftScream = position;
			rightScream = position;
			screamProgression = 0;
			leftScreamActive = true;
			rightScreamActive = true;
		}
	}

	if (tickCounter != 0 && ((playerPos.equals(leftScream) && leftScreamActive) || (playerPos.equals(rightScream) && rightScreamActive))) {
		player->decreaseLife(SCREAMING_ENEMY_DAMAGE);
	}
}

int ScreamingEnemy::getPoints() {
	return SCREAMING_ENEMY_POINTS;
}

RenderableList* ScreamingEnemy::getRenderInfo() {
	RenderableList *ret = new RenderableList();
	if (!leftScream.equals(position) && leftScreamActive) {
		ret->add(new Renderable(leftScream, SCREAMING_ENEMY_LEFT_SCREAM_CHAR, attributes));
	}
	if (!rightScream.equals(position) && rightScreamActive) {
		ret->add(new Renderable(rightScream, SCREAMING_ENEMY_RIGHT_SCREAM_CHAR, attributes));
	}
	return ret;
}
