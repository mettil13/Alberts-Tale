#include <iostream>
#include "SlowEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../Player.hpp"
#include "../../util/Util.hpp"
#include "../../util/Position.hpp"
#include "Enemy.hpp"

using namespace std;

SlowEnemy::SlowEnemy(Level *level, Position position) : Enemy(SLOW_ENEMY_ID, level, position) {
	this->appearence = SLOW_ENEMY_CHAR;
	if (randomizeProbability() <= 50) {
		this->direction = ORIENTATION_RIGHT;
	}
	else {
		this->direction = ORIENTATION_LEFT;
	}
}

void SlowEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position.right()) || playerPos.equals(position.left()) || playerPos.equals(position)) {
		player->decreaseLife(SLOW_ENEMY_DAMAGE);
	}

	if (skipTick(SLOW_ENEMY_AWAIT_TICKS)) {
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

int SlowEnemy::getPoints() {
	return SLOW_ENEMY_POINTS;
}
