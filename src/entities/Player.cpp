#include <iostream>
#include "Player.hpp"
#include "../game_engine/levels/Level.hpp"
#include "../powerups/Powerup.hpp"
#include "../powerups/usable/UsablePowerup.hpp"
#include "../powerups/timed/TimedPowerup.hpp"
#include "../powerups/oneOff/OneOffPowerup.hpp"
#include "../powerups/alwaysActive/AlwaysActivePowerup.hpp"
#include "../util/Position.hpp"
#include "Entity.hpp"
#include "../util/Util.hpp"
#include "../util/Config.hpp"
#include "../powerups/PowerupList.hpp"
#include "enemy/EnemyList.hpp"
#include "../util/Block.hpp"
#include "../util/RenderableList.hpp"
#include "../game_engine/screens/Death.hpp"

using namespace std;

Player::Player(Level *level, Position position, SharedData *sharedData) : Entity(PLAYER_ENTITY_ID, level, position) {
	this->sharedData = sharedData;
	this->appearence = PLAYER_CHAR;
	this->attributes = COLOR_PLAYER;
	this->isJumping = false;
	this->isGettingDown = false;
	this->jumpCounter = 0;
	this->orientation = ORIENTATION_RIGHT;
	this->gettingDownCounter = 0;
}

void Player::handleConsumedActivePowerup() {
	if (sharedData->activePowerup != NULL) {
		if (sharedData->activePowerup->isConsumed()) {
			deleteActivePowerup();
		}
	}
}

void Player::deleteActivePowerup() {
	Powerup *activePowerup = sharedData->activePowerup;
	if (activePowerup != NULL) {
		powerup_destroy(activePowerup);
		delete activePowerup;
		sharedData->activePowerup = NULL;
	}
}

void Player::lookForPowerup() {
	PowerupList *list = level->getPowerupList()->getPowerupsAt(position);
	bool found = false;
	list->iter_reset();
	while (!found && list->iter_hasNext()) {
		Powerup *p = list->iter_next();
		list->iter_remove();
		if (replaceActivePowerup(p)) {
			level->getPowerupList()->remove(p);
			powerup_destroy(p);
			delete p;
		}
		else {
			found = true;
		}
	}
	while (list->iter_hasNext()) {
		list->iter_next();
		list->iter_remove();
		// Don't delete since powerups are inside level->getPowerupList()
	}
	delete list;
}

void Player::killEnemiesBelow() {
	// Kill every enemy below the player
	EnemyList *list = level->getEnemyList()->getEnemiesAt(position.down());
	list->iter_reset();
	while (list->iter_hasNext()) {
		list->iter_next()->kill();
		increasePoints(enemy_getPoints(list->iter_get()));
		list->iter_remove();
		// Don't delete the returned enemy since it is inside level->getEnemyList()
		// and will be removed at the end of Level::tick()
	}
	delete list;
}

void Player::updateAttributes() {
	if (sharedData->isBeingDamaged) {
		this->attributes = COLOR_PLAYER_DAMAGED;
	}
	else if (sharedData->invincible) {
		if (!sharedData->visible) {
			this->attributes = COLOR_PLAYER_INVISIBLE_AND_INVINCIBLE;
		}
		else {
			this->attributes = COLOR_PLAYER_INVINCIBLE;
		}
	}
	else if (!sharedData->visible) {
		this->attributes = COLOR_PLAYER_INVISIBLE;
	}
	else {
		this->attributes = COLOR_PLAYER;
	}
}

void Player::tick(KeyInputList *inputs) {
	// Make active powerup tick
	Powerup *activePowerup = sharedData->activePowerup;
	if (activePowerup != NULL) {
		if (!activePowerup->isConsumed()) {
			if (powerup_is_timed(activePowerup)) {
				timed_powerup_tick((TimedPowerup*) activePowerup, this);
			}
			else if (powerup_is_alwaysActive(activePowerup)) {
				alwaysActive_powerup_tick((AlwaysActivePowerup*) activePowerup, this);
			}
		}
		else {
			// Remove consumed powerup
			deleteActivePowerup();
		}
	}

	// CHECKS DONE BY THE PLAYER:
	// Am I dead?
	// Can I stay here?
	// Can I kill someone?
	// Movements
	// Can I kill someone now?
	// Can I pick up a powerup?
	// Update damages cooldown
	// Am I falling or jumping?

	// Am I dead?
	if (sharedData->life <= 0) {
		kill();
		death();
	}
	else if (dead == true) {
		death();
	}
	// Can I stay here?
	else if (level->getBlockAt(position).isInvalid()) {
		kill(); // death() will be called the next tick
	}
	else {
		if (level->getBlockAt(position).isSolid() && !isGettingDown) {
			decreaseLife(SUFFOCATE_DAMAGE);
		}

		// Can I kill someone?
		killEnemiesBelow();

		// Movements
		inputs->iter_reset();
		while (inputs->iter_hasNext()) {
			inputs->iter_next();
			Input input = inputs->iter_remove();
			if (input == UP) {
				jump();
			}
			else if (input == DOWN) {
				moveDown();
			}
			else if (input == LEFT) {
				moveLeft();
			}
			else if (input == RIGHT) {
				moveRight();
			}
			else if (input == USE) {
				use();
			}
		}

		// Can I kill someone now?
		killEnemiesBelow();

		// Can I pick up a powerup?
		lookForPowerup();

		// Update damages cooldown
		handleDamages();

		// Am I falling or jumping?
		applyGravityAndJump();
	}

	// Remove consumed powerup
	handleConsumedActivePowerup();
	// Update attributes
	updateAttributes();
}

Orientation Player::getOrientation() {
	return orientation;
}

int Player::getLife() {
	return sharedData->life;
}

void Player::setLife(int life) {
	if (life >= 0 && !(life == 0 && sharedData->invincible)) {
		sharedData->life = life;
	}
}

void Player::increaseLife(int amount) {
	if (amount > 0) {
		sharedData->life += amount;
	}
}

void Player::decreaseLife(int amount) {
	if (canBeDamaged()) {
		if (amount > 0 && amount < sharedData->life) {
			sharedData->life -= amount;
		}
		else if (amount > 0) {
			sharedData->life = 0;
		}
		sharedData->isBeingDamaged = true;
	}
}

bool Player::canBeDamaged() {
	return (!sharedData->isBeingDamaged && !sharedData->invincible);
}

void Player::handleDamages() {
	if (sharedData->isBeingDamaged) {
		if (sharedData->damageCounter <= 0) {
			sharedData->isBeingDamaged = false;
			sharedData->damageCounter = PLAYER_DAMAGE_COUNTDOWN;
		}
		else {
			sharedData->damageCounter--;
		}
	}
}

int Player::getPoints() {
	return sharedData->points;
}

void Player::setPoints(int points) {
	sharedData->points = points;
}

void Player::increasePoints(int amount) {
	if (amount > 0) {
		sharedData->points += amount;
	}
}

void Player::decreasePoints(int amount) {
	if (amount > 0 && amount < sharedData->points) {
		sharedData->points -= amount;
	}
	else if (amount > 0) {
		sharedData->points = 0;
	}
}

void Player::kill() {
	if (!sharedData->invincible) {
		Entity::kill();
		sharedData->life = 0;
	}
}

void Player::jump() {
	if (!isJumping) {
		if (jumpCounter <= 0) { // Better safe than sorry
			jumpCounter = 0;
		}
		if (jumpCounter == 0 && !level->getBlockAt(position.up()).isSolid() && level->getBlockAt(position.down()).isSolid()) {
			jumpCounter = PLAYER_JUMP_HEIGHT;
			isJumping = true;
		}
		// applyGravityAndJump() will take the player up
	}
}

void Player::moveUp() {
	if (!level->getBlockAt(position.up()).isSolid()) {
		position = position.up();
	}
}

void Player::moveDown() {
	if (level->getBlockAt(position.down()).isSolid() && level->getBlockAt(position.down()).toChar() != BLOCK_BORDER && !level->getBlockAt(position.down().down()).isSolid() && !level->getBlockAt(position.down().down()).isInvalid()) {
		isGettingDown = true;
		gettingDownCounter = 2;
		// applyGravityAndJump() will take the player down
	}
}

void Player::moveLeft() {
	orientation = ORIENTATION_LEFT;
	Block b = level->getBlockAt(position.left());
	if (b.toChar() == BLOCK_PREV_PORTAL) {
		level->getLevelManager()->previousLevel();
	}
	else if (!b.isSolid()) {
		position = position.left();
	}
}

void Player::moveRight() {
	orientation = ORIENTATION_RIGHT;
	Block b = level->getBlockAt(position.right());
	if (b.toChar() == BLOCK_NEXT_PORTAL) {
		level->getLevelManager()->nextLevel();
	}
	else if (!b.isSolid()) {
		position = position.right();
	}
}

void Player::use() {
	Powerup *activePowerup = sharedData->activePowerup;
	if (activePowerup != NULL) {
		if (!activePowerup->isConsumed()) {
			if (powerup_is_usable(activePowerup)) {
				usable_powerup_onUse((UsablePowerup*) activePowerup, this);
			}
		}
	}
}

bool Player::isVisible() {
	return sharedData->visible;
}

void Player::setVisible(bool visible) {
	sharedData->visible = visible;
}

bool Player::isInvincible() {
	return sharedData->invincible;
}

void Player::setInvincible(bool invincible) {
	sharedData->invincible = invincible;
}

void Player::applyGravityAndJump() {
	if (isJumping && jumpCounter > 0) {
		moveUp();
		jumpCounter--;
	}
	else if (isGettingDown && gettingDownCounter > 0) {
		position = position.down();
		gettingDownCounter--;
	}
	else if (!level->getBlockAt(position.down()).isSolid()) {
		position = position.down();
		isGettingDown = false;
	}
	else {
		isJumping = false;
		isGettingDown = false;
	}
}

void Player::death() {
	if (sharedData->deathScreen != NULL) {
		sharedData->deathScreen->destroy();
		delete sharedData->deathScreen;
	}
	sharedData->deathScreen = new Death(level->getLevelManager()->getMenu());
	level->getLevelManager()->getGameManager()->setActiveScreen(sharedData->deathScreen);
}

bool Player::replaceActivePowerup(Powerup *powerup) {
	bool toDelete = false;
	if (powerup != NULL) {
		if (powerup_is_oneOff(powerup)) {
			OneOffPowerup *oneOffPowerup = (OneOffPowerup*) powerup;
			oneOff_powerup_onPickUp(oneOffPowerup, this);
			toDelete = true;
		}
	}
	if (!toDelete) {
		Powerup *activePowerup = sharedData->activePowerup;
		if (activePowerup != powerup) {
			if (activePowerup != NULL) {
				if (!activePowerup->isConsumed()) {
					Position dropPosition;
					if (orientation == ORIENTATION_RIGHT) {
						if (level->getBlockAt(position.left()).isAir()) {
							dropPosition = position.left();
						}
						else if (level->getBlockAt(position.right()).isAir()) {
							dropPosition = position.right();
						}
						else {
							// Our position should be safe
							dropPosition = position;
						}
					}
					else { // orientation == ORIENTATION_LEFT
						if (level->getBlockAt(position.right()).isAir()) {
							dropPosition = position.right();
						}
						else if (level->getBlockAt(position.left()).isAir()) {
							dropPosition = position.left();
						}
						else {
							// Our position should be safe
							dropPosition = position;
						}
					}
					activePowerup->setPosition(dropPosition);
					level->getPowerupList()->add(activePowerup);
					if (powerup_is_timed(activePowerup)) {
						timed_powerup_onDrop((TimedPowerup*) activePowerup, this);
					}
				}
				else {
					deleteActivePowerup();
				}
			}
			sharedData->activePowerup = powerup;
			if (powerup != NULL) {
				level->getPowerupList()->remove(powerup);
				if (!powerup->isConsumed()) {
					powerup_onPickUp(powerup, this);
				}
			}
		}
	}
	return toDelete;
}

Powerup* Player::getActivePowerup() {
	// Remove powerup if consumed
	handleConsumedActivePowerup();
	return sharedData->activePowerup;
}

RenderableList* Player::getRenderInfo() {
	RenderableList *list = new RenderableList();
	if (sharedData->activePowerup != NULL) {
		if (!sharedData->activePowerup->isConsumed()) {
			powerup_getPlayerRenderInfo(sharedData->activePowerup, this, list);
		}
	}
	return list;
}
