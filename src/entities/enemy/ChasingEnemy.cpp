#include <iostream>
#include "ChasingEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../../util/Position.hpp"
#include "../Player.hpp"
#include "Enemy.hpp"

using namespace std;

ChasingEnemy::ChasingEnemy(Level *level, Position position) : Enemy(CHASING_ENEMY_ID, level, position) {
	this->appearence = CHASING_ENEMY_CHAR;
}

void ChasingEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position.right()) || playerPos.equals(position.left()) || playerPos.equals(position)) {
		player->decreaseLife(CHASING_ENEMY_DAMAGE);
	}

	if (skipTick(CHASING_ENEMY_AWAIT_TICKS)) {
		int diffPositionX = position.getX() - playerPos.getX();
		int diffPositionY = position.getY() - playerPos.getY();

		if (player->isVisible() && diffPositionX * diffPositionX + diffPositionY * diffPositionY <= CHASING_ENEMY_RANGE * CHASING_ENEMY_RANGE) {
			if (playerPos.getX() < position.getX()) {
				if (level->getBlockAt(position.left().down()).isSolid() || playerPos.getY() < position.getY()) {
					moveLeft();
				}
			}
			else if (playerPos.getX() > position.getX()) {
				if (level->getBlockAt(position.right().down()).isSolid() || playerPos.getY() < position.getY()) {
					moveRight();
				}
			}
		}
		moveDown();
	}
}

int ChasingEnemy::getPoints() {
	return CHASING_ENEMY_POINTS;
}
