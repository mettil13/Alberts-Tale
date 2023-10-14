#include <iostream>
#include "FirstLevel.hpp"
#include "Level.hpp"
#include "../screens/LevelManager.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Config.hpp"
#include "../../entities/enemy/StaticEnemy.hpp"
#include "../../util/FirstLevelInitialization.hpp"
#include "../../powerups/oneOff/LifePowerup.hpp"
#include "../../util/Block.hpp"
#include "../../util/Position.hpp"

using namespace std;

FirstLevel::FirstLevel(LevelManager *levelManager, SharedData *sharedData) : Level(FIRST_LEVEL_ID, levelManager, sharedData) {
	player->setPosition(getPlayerFirstLevelPosition());

	firstLevelInitialization(this);

	blocks[LEVEL_MAX_X - 1][9] = Block(BLOCK_NEXT_PORTAL, COLOR_NEXT_PORTAL);
	enemyList->add(new StaticEnemy(this, Position(99, 1)));
	enemyList->add(new StaticEnemy(this, Position(126, 1)));
	enemyList->add(new StaticEnemy(this, Position(132, 1)));
	enemyList->add(new StaticEnemy(this, Position(159, 1)));
	powerupList->add(new LifePowerup(Position(33, 1), LIFE_INCREASE));
	powerupList->add(new LifePowerup(Position(LEVEL_MAX_X - 2, 1), LIFE_INCREASE));
}
