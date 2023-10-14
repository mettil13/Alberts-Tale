#include <iostream>
#include "FastEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../Player.hpp"
#include "../../util/Util.hpp"
#include "../../util/Position.hpp"
#include "Enemy.hpp"

using namespace std;

FastEnemy::FastEnemy(Level *level, Position position) : Enemy(FAST_ENEMY_ID, level, position) {
	this->appearence = FAST_ENEMY_CHAR;
	if (randomizeProbability() <= 50) {
		this->direction = ORIENTATION_RIGHT;
	}
	else {
		this->direction = ORIENTATION_LEFT;
	}
}

void FastEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position.right()) || playerPos.equals(position.left()) || playerPos.equals(position)) {
		player->decreaseLife(FAST_ENEMY_DAMAGE);
	}

	if (skipTick(FAST_ENEMY_AWAIT_TICKS)) {
		bool canMove = false;
		if (direction == ORIENTATION_LEFT && level->getBlockAt(position.left().down()).isSolid()) {
			canMove = moveLeft();
		}
		else if (direction == ORIENTATION_RIGHT && level->getBlockAt(position.right().down()).isSolid()) {
			canMove = moveRight();
		}

		if (!canMove && direction == ORIENTATION_LEFT) {
			direction = ORIENTATION_RIGHT;
		}
		else if (!canMove) {
			direction = ORIENTATION_LEFT;
		}
	}
}

int FastEnemy::getPoints() {
	return FAST_ENEMY_POINTS;
}
