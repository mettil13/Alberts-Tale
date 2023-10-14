#include <iostream>
#include "BulletEnemy.hpp"
#include "../../util/Config.hpp"
#include "../../util/Position.hpp"
#include "../../util/Util.hpp"
#include "../Player.hpp"
#include "Enemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "EnemyList.hpp"

using namespace std;

BulletEnemy::BulletEnemy(Level *level, Position position, Orientation direction) : Enemy(BULLET_ENEMY_ID, level, position) {
	this->appearence = BULLET_ENEMY_CHAR;
	this->direction = direction;
}

void BulletEnemy::tick() {
	checkHit();

	if (!dead && skipTick(BULLET_ENEMY_AWAIT_TICKS)) {
		bool canMove;
		if (direction == ORIENTATION_RIGHT) {
			canMove = moveRight();
		}
		else {
			canMove = moveLeft();
		}

		if (!canMove) {
			kill();
		}

		checkHit();
	}
}

int BulletEnemy::getPoints() {
	return BULLET_ENEMY_POINTS;
}

void BulletEnemy::checkHit() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position)) {
		player->decreaseLife(BULLET_ENEMY_DAMAGE);
		kill();
	}

	EnemyList *list = level->getEnemyList()->getEnemiesAt(position);
	list->iter_reset();
	while (list->iter_hasNext()) {
		Enemy *currentEnemy = list->iter_next();
		if (currentEnemy != this) {
			currentEnemy->kill();
			player->increasePoints(enemy_getPoints(currentEnemy));
			kill();
		}
		list->iter_remove();
	}
	delete list;
}
