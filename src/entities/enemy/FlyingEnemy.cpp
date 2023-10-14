#include <iostream>
#include "FlyingEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../Player.hpp"
#include "../../util/Position.hpp"
#include "Enemy.hpp"

using namespace std;

FlyingEnemy::FlyingEnemy(Level *level, Position position) : Enemy(FLYING_ENEMY_ID, level, position) {
	this->appearence = FLYING_ENEMY_CHAR;
}

void FlyingEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position.right()) || playerPos.equals(position.left()) || playerPos.equals(position)) {
		player->decreaseLife(FLYING_ENEMY_DAMAGE);
	}

	if (skipTick(FLYING_ENEMY_AWAIT_TICKS)) {
		int diffPositionX = position.getX() - playerPos.getX();
		int diffPositionY = position.getY() - playerPos.getY();

		if (player->isVisible() && diffPositionX * diffPositionX + diffPositionY * diffPositionY <= FLYING_ENEMY_RANGE * FLYING_ENEMY_RANGE) {
			if (playerPos.getX() < position.getX()) {
				moveLeft();
			}
			else if (playerPos.getX() > position.getX()) {
				moveRight();
			}

			if (playerPos.getY() < position.getY()) {
				moveDown();
			}
			else if (playerPos.getY() > position.getY()) {
				moveUp();
			}
		}
	}
}

int FlyingEnemy::getPoints() {
	return FLYING_ENEMY_POINTS;
}
