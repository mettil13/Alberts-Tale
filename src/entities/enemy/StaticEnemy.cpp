#include <iostream>
#include "StaticEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../Player.hpp"
#include "../../util/Position.hpp"
#include "Enemy.hpp"

using namespace std;

StaticEnemy::StaticEnemy(Level *level, Position position) : Enemy(STATIC_ENEMY_ID, level, position) {
	this->appearence = STATIC_ENEMY_CHAR;
}

void StaticEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	if (playerPos.equals(position.right()) || playerPos.equals(position.left()) || playerPos.equals(position)) {
		player->decreaseLife(STATIC_ENEMY_DAMAGE);
	}

	/*
	if (skipTick(STATIC_ENEMY_AWAIT_TICKS)) {
		//do nothing
	}
	*/
}

int StaticEnemy::getPoints() {
	return STATIC_ENEMY_POINTS;
}
