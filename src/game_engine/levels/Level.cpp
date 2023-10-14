#include <iostream>
#include <windows.h>
#include <cstring>
#include "Level.hpp"
#include "FirstLevel.hpp"
#include "GeneratedLevel.hpp"
#include "../screens/LevelManager.hpp"
#include "../../entities/Entity.hpp"
#include "../../entities/enemy/EnemyList.hpp"
#include "../../powerups/Powerup.hpp"
#include "../../powerups/PowerupList.hpp"
#include "../../util/Block.hpp"
#include "../../util/Position.hpp"
#include "../../util/KeyInputList.hpp"
#include "../../util/Util.hpp"
#include "../../util/Config.hpp"
#include "../../util/Renderable.hpp"
#include "../../util/RenderableList.hpp"

using namespace std;

Level::Level(int id, LevelManager *levelManager, SharedData *sharedData) {
	this->id = id;
	this->levelManager = levelManager;
	this->enemyList = new EnemyList();
	this->powerupList = new PowerupList();
	this->player = new Player(this, getPlayerDefaultPosition(), sharedData);
	for (int x = 0; x < LEVEL_MAX_X; x++) {
		for (int y = 0; y < LEVEL_MAX_Y; y++) {
			if (x == 0 || x == LEVEL_MAX_X - 1 || y == 0 || y == LEVEL_MAX_Y - 1) {
				blocks[x][y] = Block(BLOCK_BORDER, COLOR_BORDER);
			}
			else {
				blocks[x][y] = Block(BLOCK_AIR, COLOR_AIR);
			}
		}
	}
}

int Level::getId() {
	return id;
}

Block Level::getBlockAt(int x, int y) {
	if (Level::isInsideLevel(x, y)) {
		return blocks[x][y];
	}
	else {
		return Block(BLOCK_INVALID, COLOR_INVALID);
	}
}

Block Level::getBlockAt(Position position) {
	return Level::getBlockAt(position.getX(), position.getY());
}

void Level::setBlockAt(int x, int y, Block blockToSet) {
	if (!blockToSet.isInvalid() && Level::isInsideLevel(x, y)) {
		blocks[x][y] = blockToSet;
	}
}

void Level::setBlockAt(Position position, Block blockToSet) {
	Level::setBlockAt(position.getX(), position.getY(), blockToSet);
}

bool Level::isInsideLevel(Position position) {
	return Level::isInsideLevel(position.getX(), position.getY());
}

bool Level::isInsideLevel(int x, int y) {
	return x >= 0 && y >= 0 && x < LEVEL_MAX_X && y < LEVEL_MAX_Y;
}

EnemyList* Level::getEnemyList() {
	return enemyList;
}

PowerupList* Level::getPowerupList() {
	return powerupList;
}

Player* Level::getPlayer() {
	return player;
}

LevelManager* Level::getLevelManager() {
	return levelManager;
}

void Level::tick(KeyInputList *inputs) {
	// Tick player
	player->tick(inputs);

	// Tick enemies
	enemyList->iter_reset();
	while (enemyList->iter_hasNext()) {
		Enemy *e = enemyList->iter_next();
		if (e->isDead()) {
			// Delete enemy if it is already dead
			enemyList->iter_remove();
			enemy_destroy(e);
			delete e;
		}
		else {
			enemy_tick(e);
		}
	}

	// Delete remaining dead enemies
	enemyList->iter_reset();
	while (enemyList->iter_hasNext()) {
		Enemy *e = enemyList->iter_next();
		if (e->isDead()) {
			enemyList->iter_remove();
			enemy_destroy(e);
			delete e;
		}
	}

	// Delete consumed powerups
	powerupList->iter_reset();
	while (powerupList->iter_hasNext()) {
		Powerup *p = powerupList->iter_next();
		if (p->isConsumed()) {
			powerupList->iter_remove();
			powerup_destroy(p);
			delete p;
		}
	}
}

void Level::render(ResizeInfo resizeInfo) {
	if (resizeInfo.X != 0 && resizeInfo.Y != 0) {
		renderLevel(resizeInfo);
		renderHUD();
	}
}

void Level::destroy() {
	// The LevelManager isn't destroyed here
	enemyList->iter_reset();
	while (enemyList->iter_hasNext()) {
		Enemy *e = enemyList->iter_next();
		enemyList->iter_remove();
		enemy_destroy(e);
		delete e;
	}
	enemyList = NULL;
	powerupList->iter_reset();
	while (powerupList->iter_hasNext()) {
		Powerup *p = powerupList->iter_next();
		powerupList->iter_remove();
		powerup_destroy(p);
		delete p;
	}
	powerupList = NULL;

	player->destroy();
	delete player;
	player = NULL;
}

void level_tick(Level *level, KeyInputList *inputs) {
	if (level != NULL) {
		int id = level->getId();
		if (id == BASE_LEVEL_ID) {
			level->tick(inputs);
		}
		else if (id == FIRST_LEVEL_ID) {
			((FirstLevel*) level)->tick(inputs);
		}
		else if (id == GENERATED_LEVEL_ID) {
			((GeneratedLevel*) level)->tick(inputs);
		}
	}
}

void level_render(Level *level, ResizeInfo resizeInfo) {
	if (level != NULL) {
		int id = level->getId();
		if (id == BASE_LEVEL_ID) {
			level->render(resizeInfo);
		}
		else if (id == FIRST_LEVEL_ID) {
			((FirstLevel*) level)->render(resizeInfo);
		}
		else if (id == GENERATED_LEVEL_ID) {
			((GeneratedLevel*) level)->render(resizeInfo);
		}
	}
}

void level_destroy(Level *level) {
	if (level != NULL) {
		int id = level->getId();
		if (id == BASE_LEVEL_ID) {
			level->destroy();
		}
		else if (id == FIRST_LEVEL_ID) {
			((FirstLevel*) level)->destroy();
		}
		else if (id == GENERATED_LEVEL_ID) {
			((GeneratedLevel*) level)->destroy();
		}
	}
}

void Level::renderLevel(ResizeInfo resizeInfo) {
	CHAR_INFO tmp[LEVEL_MAX_Y][LEVEL_MAX_X];
	Position playerPos = player->getPosition();

	// Level render area
	Position upperCorner = Position(playerPos.getX() - (resizeInfo.X / 2), playerPos.getY() + (resizeInfo.Y * 2) / 3);
	Position lowerCorner = Position(playerPos.getX() + (resizeInfo.X / 2), playerPos.getY() - (resizeInfo.Y / 3));
	if (upperCorner.getX() < 0) upperCorner.setX(0);
	if (upperCorner.getY() < 0) upperCorner.setY(0);
	if (upperCorner.getX() > LEVEL_MAX_X) upperCorner.setX(LEVEL_MAX_X);
	if (upperCorner.getY() > LEVEL_MAX_Y) upperCorner.setY(LEVEL_MAX_Y);
	if (lowerCorner.getX() < 0) lowerCorner.setX(0);
	if (lowerCorner.getY() < 0) lowerCorner.setY(0);
	if (lowerCorner.getX() > LEVEL_MAX_X) lowerCorner.setX(LEVEL_MAX_X);
	if (lowerCorner.getY() > LEVEL_MAX_Y) lowerCorner.setY(LEVEL_MAX_Y);

	// Console render area
	SMALL_RECT renderArea;
	renderArea.Top = (resizeInfo.Y * 2) / 3 - (upperCorner.getY() - playerPos.getY());
	renderArea.Left = resizeInfo.X / 2 - (playerPos.getX() - upperCorner.getX());
	renderArea.Bottom = (resizeInfo.Y * 2) / 3 + (playerPos.getY() - lowerCorner.getY() - 1);
	renderArea.Right = resizeInfo.X / 2 + (lowerCorner.getX() - playerPos.getX() - 1);

	// Blocks
	COORD origin;
	origin.X = 0;
	origin.Y = 0;
	COORD max;
	max.X = LEVEL_MAX_X;
	max.Y = LEVEL_MAX_Y;
	/*
	 blocks            tmp        Where a is the origin
	 1 2 3 4 5 6       a 1
	 a b c d e f  ==>  b 2
					   c 3
					   d 4
					   e 5
					   f 6
	*/
	for (int tmpY = 0; tmpY < lowerCorner.getX() - upperCorner.getX(); tmpY++) {
		for (int tmpX = 0; tmpX < upperCorner.getY() - lowerCorner.getY(); tmpX++) {
			tmp[tmpX][tmpY] = getBlockAt(upperCorner.getX() + tmpY, upperCorner.getY() - tmpX - 1).toCharInfo();
		}
	}

	// Powerups
	powerupList->iter_reset();
	while (powerupList->iter_hasNext()) {
		Powerup *powerup = powerupList->iter_next();
		Position powerupPos = powerup->getPosition();
		if (powerupPos.getX() > upperCorner.getX() && powerupPos.getX() < lowerCorner.getX() && powerupPos.getY() < upperCorner.getY() && powerupPos.getY() > lowerCorner.getY()) {
			tmp[upperCorner.getY() - powerupPos.getY() - 1][powerupPos.getX() - upperCorner.getX()] = powerup->toCharInfo();
		}
	}

	// Entities
	enemyList->iter_reset();
	while (enemyList->iter_hasNext()) {
		Enemy *enemy = enemyList->iter_next();
		Position enemyPos = enemy->getPosition();
		RenderableList *renderInfoList = entity_getRenderInfo(enemy);
		if (enemyPos.getX() > upperCorner.getX() && enemyPos.getX() < lowerCorner.getX() && enemyPos.getY() < upperCorner.getY() && enemyPos.getY() > lowerCorner.getY()) {
			tmp[upperCorner.getY() - enemyPos.getY() - 1][enemyPos.getX() - upperCorner.getX()] = enemy->toCharInfo();
		}
		if (renderInfoList != NULL) {
			while (renderInfoList->iter_hasNext()) {
				Renderable *renderInfo = renderInfoList->iter_next();
				if (renderInfo->getX() > upperCorner.getX() && renderInfo->getX() < lowerCorner.getX() && renderInfo->getY() < upperCorner.getY() && renderInfo->getY() > lowerCorner.getY()) {
					tmp[upperCorner.getY() - renderInfo->getY() - 1][renderInfo->getX() - upperCorner.getX()] = renderInfo->toCharInfo();
				}
				renderInfoList->iter_remove();
				delete renderInfo;
			}
			delete renderInfoList;
			renderInfoList = NULL;
		}
	}

	// Player
	tmp[upperCorner.getY() - playerPos.getY() - 1][playerPos.getX() - upperCorner.getX()] = player->toCharInfo();
	RenderableList *playerRenderInfoList = player->getRenderInfo();
	if (playerRenderInfoList != NULL) {
		while (playerRenderInfoList->iter_hasNext()) {
			Renderable *playerRenderInfo = playerRenderInfoList->iter_next();
			if (playerRenderInfo->getX() > upperCorner.getX() && playerRenderInfo->getX() < lowerCorner.getX() && playerRenderInfo->getY() < upperCorner.getY() && playerRenderInfo->getY() > lowerCorner.getY()) {
				tmp[upperCorner.getY() - playerRenderInfo->getY() - 1][playerRenderInfo->getX() - upperCorner.getX()] = playerRenderInfo->toCharInfo();
			}
			playerRenderInfoList->iter_remove();
			delete playerRenderInfo;
		}
		delete playerRenderInfoList;
		playerRenderInfoList = NULL;
	}

	// Print
	WriteConsoleOutput(getOutputHandle(), &tmp[origin.X][origin.Y], max, origin, &renderArea);
}

void Level::renderHUD() {
	// HUD background
	CHAR_INFO HUDBackground[HUD_LENGTH][HUD_HEIGHT];
	CHAR_INFO HUDTile;
#ifdef UNICODE
	HUDTile.Char.UnicodeChar = ' ';
#else
	HUDTile.Char.AsciiChar = ' ';
#endif /* UNICODE */
	HUDTile.Attributes = COLOR_HUD;
	for (int i = 0; i < HUD_LENGTH; i++) {
		for (int j = 0; j < HUD_HEIGHT; j++) {
			HUDBackground[i][j] = HUDTile;
		}
	}
	COORD HUDMax;
	HUDMax.X = HUD_LENGTH;
	HUDMax.Y = HUD_HEIGHT;
	COORD HUDOrigin;
	HUDOrigin.X = 0;
	HUDOrigin.Y = 0;
	SMALL_RECT HUDRenderArea;
	HUDRenderArea.Top = 0;
	HUDRenderArea.Bottom = HUD_HEIGHT;
	HUDRenderArea.Left = 0;
	HUDRenderArea.Right = HUD_LENGTH;
	WriteConsoleOutput(getOutputHandle(), &HUDBackground[HUDOrigin.X][HUDOrigin.Y], HUDMax, HUDOrigin, &HUDRenderArea);

	// HUD foreground
	consoleSetHUDColor();
	char stats[HUD_LENGTH] = "Life: ";
	char tmpStats[HUD_LENGTH];
	tmpStats[0] = '\0';
	intToString(player->getLife(), tmpStats, HUD_LENGTH);
	strncat(stats, tmpStats, HUD_LENGTH - 6);
	stats[HUD_LENGTH - 1] = '\0';
#ifdef UNICODE
	WCHAR unicodeStats[HUD_LENGTH];
	fromAsciiToUnicode(stats, HUD_LENGTH, unicodeStats, HUD_LENGTH);
	WriteConsoleW(getOutputHandle(), unicodeStats, HUD_LENGTH, NULL, NULL);
#else
	WriteConsoleA(getOutputHandle(), &stats, HUD_LENGTH, NULL, NULL);
#endif /* UNICODE */

	COORD cursorPos;
	cursorPos.X = 0;
	cursorPos.Y = 1;
	SetConsoleCursorPosition(getOutputHandle(), cursorPos);
	strncpy(stats, "Points: ", HUD_LENGTH);
	stats[HUD_LENGTH - 1] = '\0';
	tmpStats[0] = '\0';
	intToString(player->getPoints(), tmpStats, HUD_LENGTH);
	strncat(stats, tmpStats, HUD_LENGTH - 8);
	stats[HUD_LENGTH - 1] = '\0';
#ifdef UNICODE
	fromAsciiToUnicode(stats, HUD_LENGTH, unicodeStats, HUD_LENGTH);
	WriteConsoleW(getOutputHandle(), unicodeStats, HUD_LENGTH, NULL, NULL);
#else
	WriteConsoleA(getOutputHandle(), &stats, HUD_LENGTH, NULL, NULL);
#endif /* UNICODE */

	cursorPos.Y = 2;
	SetConsoleCursorPosition(getOutputHandle(), cursorPos);
	tmpStats[0] = '\0';
	Powerup *powerup = player->getActivePowerup();
	if (powerup != NULL) {
		if (!powerup->isConsumed()) {
			powerup_getName(powerup, stats, HUD_LENGTH);
			powerup_getRenderInfo(powerup, tmpStats, HUD_LENGTH);
			strncat(stats, " ", HUD_LENGTH - strlen(stats) - 1);
			strncat(stats, tmpStats, HUD_LENGTH - strlen(stats) - 1);
			stats[HUD_LENGTH - 1] = '\0';
#ifdef UNICODE
			fromAsciiToUnicode(stats, HUD_LENGTH, unicodeStats, HUD_LENGTH);
			WriteConsoleW(getOutputHandle(), unicodeStats, HUD_LENGTH, NULL, NULL);
#else
			WriteConsoleA(getOutputHandle(), &stats, HUD_LENGTH, NULL, NULL);
#endif /* UNICODE */
		}
	}
	consoleResetColor();
}
