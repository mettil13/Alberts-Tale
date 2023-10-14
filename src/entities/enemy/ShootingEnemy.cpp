#include <iostream>
#include <math.h>
#include "ShootingEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../Player.hpp"
#include "BulletEnemy.hpp"
#include "../../util/Position.hpp"
#include "Enemy.hpp"

using namespace std;

ShootingEnemy::ShootingEnemy(Level *level, Position position) : Enemy(SHOOTING_ENEMY_ID, level, position) {
	this->appearence = SHOOTING_ENEMY_CHAR;
}

void ShootingEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position)) {
		player->decreaseLife(SHOOTING_ENEMY_DAMAGE);
	}

	if (tickCounter == 1) {
		if (player->isVisible() && abs(position.getX() - playerPos.getX()) <= SHOOTING_ENEMY_RANGE && playerPos.getY() == position.getY()) {
			if (playerPos.getX() < position.getX()) {
				level->getEnemyList()->add(new BulletEnemy(level, position.left(), ORIENTATION_LEFT));
			}
			else if (playerPos.getX() > position.getX()) {
				level->getEnemyList()->add(new BulletEnemy(level, position.right(), ORIENTATION_RIGHT));
			}
			skipTick(SHOOTING_ENEMY_AWAIT_TICKS);
		}
	}
	else {
		skipTick(SHOOTING_ENEMY_AWAIT_TICKS);
	}
}

int ShootingEnemy::getPoints() {
	return SHOOTING_ENEMY_POINTS;
}
