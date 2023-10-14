#include <iostream>
#include <windows.h>
#include "Entity.hpp"
#include "enemy/Enemy.hpp"
#include "Player.hpp"
#include "../game_engine/levels/Level.hpp"
#include "../util/Position.hpp"
#include "../util/Config.hpp"
#include "../util/RenderableList.hpp"

using namespace std;

Entity::Entity(int entityId, Level *level, Position position) {
	this->entityId = entityId;
	this->level = level;
	this->position = position;
	this->appearence = INVALID;
	this->attributes = COLOR_ENTITY;
	dead = false;
}

int Entity::getEntityId() {
	return entityId;
}

Position Entity::getPosition() {
	return position;
}

void Entity::setPosition(Position position) {
	this->position = position;
}

void Entity::setX(int x) {
	position.setX(x);
}

void Entity::setY(int y) {
	position.setY(y);
}

Level* Entity::getLevel() {
	return level;
}

void Entity::kill() {
	dead = true;
}

bool Entity::isDead() {
	return dead;
}

char Entity::toChar() {
	return appearence;
}

CHAR_INFO Entity::toCharInfo() {
	CHAR_INFO c;
#ifdef UNICODE
	c.Char.UnicodeChar = (WCHAR)appearence;
#else
	c.Char.AsciiChar = (CHAR)appearence;
#endif /* UNICODE */
	c.Attributes = attributes;
	return c;
}

RenderableList* Entity::getRenderInfo() {
	return NULL;
}

void Entity::destroy() {
	// Do nothing, level is deleted by LevelManager
}

RenderableList* entity_getRenderInfo(Entity *entity) {
	RenderableList *list = NULL;
	if (entity != NULL) {
		int id = entity->getEntityId();
		if (id == BASE_ENTITY_ID) {
			list = entity->getRenderInfo();
		}
		else if (id == PLAYER_ENTITY_ID) {
			list = ((Player*) entity)->getRenderInfo();
		}
		else if (id == ENEMY_ENTITY_ID) {
			list = enemy_getRenderInfo((Enemy*) entity);
		}
	}
	return list;
}

void entity_destroy(Entity *entity) {
	if (entity != NULL) {
		int id = entity->getEntityId();
		if (id == BASE_ENTITY_ID) {
			entity->destroy();
		}
		else if (id == PLAYER_ENTITY_ID) {
			((Player*) entity)->destroy();
		}
		else if (id == ENEMY_ENTITY_ID) {
			enemy_destroy((Enemy*) entity);
		}
	}
}
