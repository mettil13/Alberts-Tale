#include <iostream>
#include "SpearEnemy.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Config.hpp"
#include "../Player.hpp"
#include "../../util/Position.hpp"
#include "../../util/Util.hpp"
#include "Enemy.hpp"
#include "../../util/Renderable.hpp"

using namespace std;

SpearEnemy::SpearEnemy(Level *level, Position position) : Enemy(SPEAR_ENEMY_ID, level, position) {
	this->appearence = SPEAR_ENEMY_CHAR;
	if (randomizeProbability() <= 50) {
		this->direction = ORIENTATION_RIGHT;
	}
	else {
		this->direction = ORIENTATION_LEFT;
	}
}

void SpearEnemy::tick() {
	Player *player = level->getPlayer();
	Position playerPos = player->getPosition();

	Position spearPos;
	if (direction == ORIENTATION_LEFT) {
		spearPos = position.left();
	}
	else {
		spearPos = position.right();
	}

	if (playerPos.equals(spearPos) || (direction == ORIENTATION_LEFT && playerPos.equals(spearPos.left())) || (direction == ORIENTATION_RIGHT && playerPos.equals(spearPos.right())) || playerPos.equals(position)) {
		player->decreaseLife(SPEAR_ENEMY_DAMAGE);
	}

	if (skipTick(SPEAR_ENEMY_AWAIT_TICKS)) {
		if (direction == ORIENTATION_LEFT && !level->getBlockAt(position.right()).isSolid() && !level->getBlockAt(position.right()).isInvalid()) {
			direction = ORIENTATION_RIGHT;
		}
		else if (direction == ORIENTATION_RIGHT && !level->getBlockAt(position.left()).isSolid() && !level->getBlockAt(position.left()).isInvalid()) {
			direction = ORIENTATION_LEFT;
		}
	}
}

int SpearEnemy::getPoints() {
	return SPEAR_ENEMY_POINTS;
}

RenderableList* SpearEnemy::getRenderInfo() {
	RenderableList *ret = new RenderableList();
	Position spearPos;
	if (direction == ORIENTATION_LEFT) {
		spearPos = position.left();
	}
	else {
		spearPos = position.right();
	}
	ret->add(new Renderable(spearPos, SPEAR_POWERUP_CHAR, attributes));
	return ret;
}
