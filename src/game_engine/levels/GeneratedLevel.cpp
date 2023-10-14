#include <iostream>
#include <math.h>
#include "GeneratedLevel.hpp"
#include "../../util/Util.hpp"
#include "../../util/Config.hpp"
#include "../../util/Populator.hpp"
#include "../../util/Block.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Position.hpp"
#include "../screens/LevelManager.hpp"
#include "PositionList.hpp"
#include "Level.hpp"

using namespace std;

const int lastPlaceableBlockX = LEVEL_MAX_X - 2;
const int lastPlaceableBlockY = LEVEL_MAX_Y - 3;

GeneratedLevel::GeneratedLevel(LevelManager *levelManager, SharedData *sharedData, int difficulty) : Level(GENERATED_LEVEL_ID, levelManager, sharedData) {
	generatorShortPlatformProbability = GENERATOR_SHORT_PLATFORM_PROBABILITY_DEFAULT;
	generatorVeryLongPlatformProbability = GENERATOR_VERY_LONG_PLATFORM_PROBABILITY_DEFAULT;
	generatorShouldStartInvertedPlatforms = difficulty;
	generatorStopInvertedPlatforms = GENERATOR_STOP_INVERTED_PLATFORMS_DEFAULT;
	generatorShouldStartDownwardsPlatforms = difficulty;
	generatorStopDownwardsPlatforms = GENERATOR_STOP_DOWNWARDS_PLATFORMS_DEFAULT;
	generatorUpperPlatformProbability = GENERATOR_UPPER_PLATFORM_PROBABILITY_DEFAULT;
	generatorPopulatePlatformProbability = difficulty * 2/3;
	generatorSpawnEnemyInsteadOfPowerupProbability = GENERATOR_SPAWN_ENEMY_INSTEAD_OF_POWERUP_PROBABILITY_DEFAULT;

	positionList = new PositionList();
	blocks[0][1] = Block(BLOCK_PREV_PORTAL, COLOR_PREV_PORTAL);
	generatePlatformDiagonal(4, 2, true);
	populate(difficulty);
}

bool GeneratedLevel::generatePlatform(int x, int y, int &newX) {
	if (randomizeProbability(generatorShortPlatformProbability)) {
		newX = x + 4; // Platform length = 4
	}
	else if (randomizeProbability(generatorVeryLongPlatformProbability)) {
		newX = x + 8; // Platform length = 8
	}
	else { // Long Platform
		newX = x + 6; // Platform length = 6
	}

	bool endOfLevel = newX > lastPlaceableBlockX + 1;

	if (endOfLevel) {
		newX = lastPlaceableBlockX + 1;
	}

	for (int i = x; i < newX; i++) {
		blocks[i][y] = Block(BLOCK_PLATFORM, COLOR_PLATFORM);
	}

	// '+ 1' and '- 1' prevents the spawning of enemies at the platform edges
	if (x + 1 < newX - 1 && randomizeProbability(generatorPopulatePlatformProbability)) {
		int randomizedX = randomize(x + 1, newX - 1);
		positionList->add(new Position(randomizedX, y + 1));
	}

	return endOfLevel;
}

bool GeneratedLevel::generatePlatformInverted(int x, int y, int &newX) {
	if (randomizeProbability(generatorShortPlatformProbability)) {
		newX = x - 4; // Platform length = 4
	}
	else if (randomizeProbability(generatorVeryLongPlatformProbability)) {
		newX = x - 8; // Platform length = 8
	}
	else { // Long Platform
		newX = x - 6; // Platform length = 6
	}

	bool endOfLevel = newX <= 0;

	if (endOfLevel) {
		newX = 1;
	}

	bool invalid = false;

	for (int i = newX; !invalid && i < x; i++) {
		for (int tmp = y - 1; !invalid && tmp > 0 && tmp < lastPlaceableBlockY && tmp < y + 1; tmp++) {
			if (blocks[i][tmp].isSolid()) {
				invalid = true;
			}
		}
	}

	if (invalid) {
		return true;
	}
	else {
		for (int i = newX; i < x; i++) {
			blocks[i][y] = Block(BLOCK_PLATFORM, COLOR_PLATFORM);
		}

		// '+ 1' and '- 1' prevents the spawning of enemies at the platform edges
		if (newX + 1 < x - 1 && randomizeProbability(generatorPopulatePlatformProbability)) {
			int randomizedX = randomize(newX + 1, x - 1);
			positionList->add(new Position(randomizedX, y + 1));
		}

		return endOfLevel;
	}
}

void GeneratedLevel::generatePlatformDiagonal(int fromX, int fromY, bool firstGenerated) {
	int maxHeight;
	if (firstGenerated) {
		maxHeight = fromY + PLAYER_JUMP_HEIGHT - 1;
	}
	else {
		maxHeight = fromY + PLAYER_JUMP_HEIGHT;
	}
	int minHeight = fromY - PLAYER_JUMP_HEIGHT + 1;

	if (fromX <= lastPlaceableBlockX) {
		int nextX, nextY;
		int prob = randomizeProbability();
		bool generateInverted = false, generateDownwards = false;
		if (prob <= generatorUpperPlatformProbability) {
			nextY = randomize(fromY, min(maxHeight, lastPlaceableBlockY));
			if (randomizeProbability(generatorShouldStartInvertedPlatforms))
				generateInverted = true;
			if (randomizeProbability(generatorShouldStartDownwardsPlatforms))
				generateDownwards = true;
		}
		else if (fromY > 2) {
			nextY = randomize(max(minHeight, 2), fromY);
		}
		else {
			nextY = 2;
		}

		bool stop = generatePlatform(fromX, nextY, nextX);

		if (generateInverted)
			generatePlatformDiagonalInverted(fromX, nextY, true);

		if (generateDownwards)
			generatePlatformDiagonalDownwards(fromX, nextY);

		if (stop) {
			// Generate portal
			blocks[nextX][nextY + 1] = Block(BLOCK_NEXT_PORTAL, COLOR_NEXT_PORTAL);
		}
		else {
			generatePlatformDiagonal(nextX, nextY, false);
		}
	}
}

void GeneratedLevel::generatePlatformDiagonalInverted(int fromX, int fromY, bool firstGenerated) {
	if (fromX > 0 && fromY < lastPlaceableBlockY && !randomizeProbability(generatorStopInvertedPlatforms)) {
		int maxHeight = min(fromY + PLAYER_JUMP_HEIGHT, lastPlaceableBlockY);
		int minHeight = max(fromY, 2);

		if (firstGenerated) {
			// No check on fromX is needed since the function calling this function generates a platform starting at fromX
			if (blocks[fromX][fromY].isSolid()) {
				minHeight += 2;
			}
			else if (blocks[fromX][fromY - 1].isSolid()) {
				minHeight++;
			}
		}

		if (maxHeight > minHeight) {
			int nextX;
			int nextY = randomize(minHeight, maxHeight);
			if (!generatePlatformInverted(fromX, nextY, nextX))
				generatePlatformDiagonalInverted(nextX, nextY, false);
		}
	}
}

void GeneratedLevel::generatePlatformDiagonalDownwards(int fromX, int fromY) {
	if (fromX < lastPlaceableBlockX && fromY > 1 && !randomizeProbability(generatorStopDownwardsPlatforms)) {
		int maxHeight = fromY - 1;
		int minHeight = max(fromY - PLAYER_JUMP_HEIGHT, 2);

		if (maxHeight > minHeight) {
			int nextX;
			int nextY = randomize(minHeight, maxHeight);
			if (!generatePlatform(fromX, nextY, nextX))
				generatePlatformDiagonalDownwards(nextX, nextY);
		}
	}
}

void GeneratedLevel::populate(int difficulty) {
	if (positionList != NULL) {
		positionList->iter_reset();
		while (positionList->iter_hasNext()) {
			Position *position = positionList->iter_next();
			Position pos = position->clone();
			positionList->iter_remove();
			delete position;
			position = NULL;
			if (getBlockAt(pos).isAir()) {
				if (randomizeProbability(generatorSpawnEnemyInsteadOfPowerupProbability)) {
					// Spawn Enemy
					enemyList->add(generateRandomEnemy(this, pos, difficulty));
				}
				else {
					// Spawn Powerup
					powerupList->add(generateRandomPowerup(pos, difficulty));
				}
			}
		}
		delete positionList;
		positionList = NULL;
	}
}

void GeneratedLevel::destroy() {
	Level::destroy();
	if (positionList != NULL) {
		positionList->iter_reset();
		while (positionList->iter_hasNext()) {
			positionList->iter_next();
			Position *pos = positionList->iter_remove();
			delete pos;
		}
		delete positionList;
		positionList = NULL;
	}
}
