#include <iostream>
#include "Enemy.hpp"
#include "../Entity.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/Position.hpp"
#include "BulletEnemy.hpp"
#include "ChasingEnemy.hpp"
#include "FastEnemy.hpp"
#include "FlyingEnemy.hpp"
#include "ScreamingEnemy.hpp"
#include "ShootingEnemy.hpp"
#include "SlowEnemy.hpp"
#include "SpearEnemy.hpp"
#include "StaticEnemy.hpp"
#include "../../util/RenderableList.hpp"

using namespace std;

Enemy::Enemy(int id, Level *level, Position position) : Entity(ENEMY_ENTITY_ID, level, position) {
	this->id = id;
	tickCounter = 1;
}

int Enemy::getId() {
	return id;
}

void Enemy::tick() {
	//do nothing
}

bool Enemy::skipTick(int tickNumber) {
	if (tickCounter >= tickNumber) {
		tickCounter = 1;
		return true;
	}
	else {
		tickCounter++;
		return false;
	}
}

bool Enemy::moveUp() {
	Position newPos = position.up();
	bool canMove = !level->getBlockAt(newPos).isSolid() && !level->getBlockAt(newPos).isInvalid();
	if (canMove) {
		position = newPos;
	}
	return canMove;
}

bool Enemy::moveDown() {
	Position newPos = position.down();
	bool canMove = !level->getBlockAt(newPos).isSolid() && !level->getBlockAt(newPos).isInvalid();
	if (canMove) {
		position = newPos;
	}
	return canMove;
}

bool Enemy::moveLeft() {
	Position newPos = position.left();
	bool canMove = !level->getBlockAt(newPos).isSolid() && !level->getBlockAt(newPos).isInvalid();
	if (canMove) {
		position = newPos;
	}
	return canMove;
}

bool Enemy::moveRight() {
	Position newPos = position.right();
	bool canMove = !level->getBlockAt(newPos).isSolid() && !level->getBlockAt(newPos).isInvalid();
	if (canMove) {
		position = newPos;
	}
	return canMove;
}

int Enemy::getPoints() {
	return 0;
}

void enemy_tick(Enemy *enemy) {
	if (enemy != NULL) {
		int id = enemy->getId();
		if (id == BASE_ENEMY_ID) {
			enemy->tick();
		}
		else if (id == STATIC_ENEMY_ID) {
			((StaticEnemy*) enemy)->tick();
		}
		else if (id == SLOW_ENEMY_ID) {
			((SlowEnemy*) enemy)->tick();
		}
		else if (id == FAST_ENEMY_ID) {
			((FastEnemy*) enemy)->tick();
		}
		else if (id == FLYING_ENEMY_ID) {
			((FlyingEnemy*) enemy)->tick();
		}
		else if (id == CHASING_ENEMY_ID) {
			((ChasingEnemy*) enemy)->tick();
		}
		else if (id == SHOOTING_ENEMY_ID) {
			((ShootingEnemy*) enemy)->tick();
		}
		else if (id == SPEAR_ENEMY_ID) {
			((SpearEnemy*) enemy)->tick();
		}
		else if (id == SCREAMING_ENEMY_ID) {
			((ScreamingEnemy*) enemy)->tick();
		}
		else if (id == BULLET_ENEMY_ID) {
			((BulletEnemy*) enemy)->tick();
		}
	}
}

RenderableList* enemy_getRenderInfo(Enemy *enemy) {
	RenderableList *list = NULL;
	if (enemy != NULL) {
		int id = enemy->getId();
		if (id == BASE_ENEMY_ID) {
			list = enemy->getRenderInfo();
		}
		else if (id == STATIC_ENEMY_ID) {
			list = ((StaticEnemy*) enemy)->getRenderInfo();
		}
		else if (id == SLOW_ENEMY_ID) {
			list = ((SlowEnemy*) enemy)->getRenderInfo();
		}
		else if (id == FAST_ENEMY_ID) {
			list = ((FastEnemy*) enemy)->getRenderInfo();
		}
		else if (id == FLYING_ENEMY_ID) {
			list = ((FlyingEnemy*) enemy)->getRenderInfo();
		}
		else if (id == CHASING_ENEMY_ID) {
			list = ((ChasingEnemy*) enemy)->getRenderInfo();
		}
		else if (id == SHOOTING_ENEMY_ID) {
			list = ((ShootingEnemy*) enemy)->getRenderInfo();
		}
		else if (id == SPEAR_ENEMY_ID) {
			list = ((SpearEnemy*) enemy)->getRenderInfo();
		}
		else if (id == SCREAMING_ENEMY_ID) {
			list = ((ScreamingEnemy*) enemy)->getRenderInfo();
		}
		else if (id == BULLET_ENEMY_ID) {
			list = ((BulletEnemy*) enemy)->getRenderInfo();
		}
	}
	return list;
}

int enemy_getPoints(Enemy *enemy) {
	int points = 0;
	if (enemy != NULL) {
		int id = enemy->getId();
		if (id == BASE_ENEMY_ID) {
			points = enemy->getPoints();
		}
		else if (id == STATIC_ENEMY_ID) {
			points = ((StaticEnemy*) enemy)->getPoints();
		}
		else if (id == SLOW_ENEMY_ID) {
			points = ((SlowEnemy*) enemy)->getPoints();
		}
		else if (id == FAST_ENEMY_ID) {
			points = ((FastEnemy*) enemy)->getPoints();
		}
		else if (id == FLYING_ENEMY_ID) {
			points = ((FlyingEnemy*) enemy)->getPoints();
		}
		else if (id == CHASING_ENEMY_ID) {
			points = ((ChasingEnemy*) enemy)->getPoints();
		}
		else if (id == SHOOTING_ENEMY_ID) {
			points = ((ShootingEnemy*) enemy)->getPoints();
		}
		else if (id == SPEAR_ENEMY_ID) {
			points = ((SpearEnemy*) enemy)->getPoints();
		}
		else if (id == SCREAMING_ENEMY_ID) {
			points = ((ScreamingEnemy*) enemy)->getPoints();
		}
		else if (id == BULLET_ENEMY_ID) {
			points = ((BulletEnemy*) enemy)->getPoints();
		}
	}
	return points;
}

void enemy_destroy(Enemy *enemy) {
	if (enemy != NULL) {
		int id = enemy->getId();
		if (id == BASE_ENEMY_ID) {
			enemy->destroy();
		}
		else if (id == STATIC_ENEMY_ID) {
			((StaticEnemy*) enemy)->destroy();
		}
		else if (id == SLOW_ENEMY_ID) {
			((SlowEnemy*) enemy)->destroy();
		}
		else if (id == FAST_ENEMY_ID) {
			((FastEnemy*) enemy)->destroy();
		}
		else if (id == FLYING_ENEMY_ID) {
			((FlyingEnemy*) enemy)->destroy();
		}
		else if (id == CHASING_ENEMY_ID) {
			((ChasingEnemy*) enemy)->destroy();
		}
		else if (id == SHOOTING_ENEMY_ID) {
			((ShootingEnemy*) enemy)->destroy();
		}
		else if (id == SPEAR_ENEMY_ID) {
			((SpearEnemy*) enemy)->destroy();
		}
		else if (id == SCREAMING_ENEMY_ID) {
			((ScreamingEnemy*) enemy)->destroy();
		}
		else if (id == BULLET_ENEMY_ID) {
			((BulletEnemy*) enemy)->destroy();
		}
	}
}

void enemy_kill(Enemy *enemy) {
	if (enemy != NULL) {
		int id = enemy->getId();
		if (id == BASE_ENEMY_ID) {
			enemy->kill();
		}
		else if (id == STATIC_ENEMY_ID) {
			((StaticEnemy*) enemy)->kill();
		}
		else if (id == SLOW_ENEMY_ID) {
			((SlowEnemy*) enemy)->kill();
		}
		else if (id == FAST_ENEMY_ID) {
			((FastEnemy*) enemy)->kill();
		}
		else if (id == FLYING_ENEMY_ID) {
			((FlyingEnemy*) enemy)->kill();
		}
		else if (id == CHASING_ENEMY_ID) {
			((ChasingEnemy*) enemy)->kill();
		}
		else if (id == SHOOTING_ENEMY_ID) {
			((ShootingEnemy*) enemy)->kill();
		}
		else if (id == SPEAR_ENEMY_ID) {
			((SpearEnemy*) enemy)->kill();
		}
		else if (id == SCREAMING_ENEMY_ID) {
			((ScreamingEnemy*) enemy)->kill();
		}
		else if (id == BULLET_ENEMY_ID) {
			((BulletEnemy*) enemy)->kill();
		}
	}
}
