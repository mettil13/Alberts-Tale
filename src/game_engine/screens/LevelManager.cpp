#include <iostream>
#include "LevelManager.hpp"
#include "../levels/FirstLevel.hpp"
#include "Menu.hpp"
#include "Pause.hpp"
#include "Screen.hpp"
#include "Death.hpp"
#include "../../entities/Player.hpp"
#include "../levels/GeneratedLevel.hpp"
#include "LevelList.hpp"
#include "../levels/Level.hpp"
#include "../../powerups/Powerup.hpp"
#include "../../util/Config.hpp"
#include "../../util/KeyInputList.hpp"
#include "../../util/Util.hpp"

using namespace std;

LevelManager::LevelManager(Menu *menu) : Screen(LEVEL_MANAGER_SCREEN_ID, menu->getGameManager()) {
	this->sharedData = new SharedData;
	this->sharedData->activePowerup = NULL;
	this->sharedData->invincible = false;
	this->sharedData->visible = true;
	this->sharedData->life = PLAYER_LIFE_DEFAULT;
	this->sharedData->points = 0;
	this->sharedData->isBeingDamaged = false;
	this->sharedData->damageCounter = PLAYER_DAMAGE_COUNTDOWN;
	this->sharedData->deathScreen = NULL;
	this->menu = menu;
	this->pause = NULL;
	levels = new LevelList();
	levels->add(new FirstLevel(this, sharedData));
	levels->iter_next();
}

Menu* LevelManager::getMenu() {
	return menu;
}

Level* LevelManager::getCurrentLevel() {
	return levels->iter_get();
}

// Va al livello successivo e lo crea se non c'è, l'inizializzazione del primo livello è nel costruttore
void LevelManager::nextLevel() {
	if (levels->iter_hasNext()) {
		levels->iter_next();
		levels->iter_get()->getPlayer()->updateAttributes();
	}
	else {
		Level *l = new GeneratedLevel(this, sharedData, getLevelDifficulty(levels->getSize()));
		levels->add(l);
		levels->iter_next();
		Player *p = l->getPlayer();
		p->increasePoints(NEW_LEVEL_POINTS);
		p->updateAttributes();
	}
}

// Va al precedente, se c'è
void LevelManager::previousLevel() {
	if (levels->iter_hasPrevious()) {
		levels->iter_previous();
		levels->iter_get()->getPlayer()->updateAttributes();
	}
}

void LevelManager::pauseGame() {
	if (pause != NULL) {
		pause->destroy();
		delete pause;
	}
	pause = new Pause(gameManager, this, menu);
	gameManager->setActiveScreen(pause);
}

void LevelManager::tick(KeyInputList *inputs) {
	bool skipOthers = false;
	inputs->iter_reset();
	while (!skipOthers && inputs->iter_hasNext()) {
		Input input = inputs->iter_next();
		if (input == ESC) {
			skipOthers = true;
			pauseGame();
		}
	}
	if (!skipOthers) {
		inputs->iter_reset();
		level_tick(getCurrentLevel(), inputs);
	}
}

void LevelManager::render(ResizeInfo resizeInfo) {
	level_render(levels->iter_get(), resizeInfo);
}

void LevelManager::destroy() {
	// The Menu isn't destroyed since this LevelManager instance is stored inside the Menu instance
	if (levels != NULL) {
		levels->iter_reset();
		while (levels->iter_hasNext()) {
			Level *l = levels->iter_next();
			levels->iter_remove();
			level_destroy(l);
			delete l;
		}
		delete levels;
		levels = NULL;
	}
	if (sharedData != NULL) {
		if (sharedData->activePowerup != NULL) {
			powerup_destroy(sharedData->activePowerup);
			delete sharedData->activePowerup;
			sharedData->activePowerup = NULL;
		}
		if (sharedData->deathScreen != NULL) {
			sharedData->deathScreen->destroy();
			delete sharedData->deathScreen;
			sharedData->deathScreen = NULL;
		}
		delete sharedData;
		sharedData = NULL;
	}
}
