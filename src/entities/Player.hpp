#ifndef PLAYER_HPP
#define PLAYER_HPP
class Player;
struct SharedData;
#include "Entity.hpp"
#include "../powerups/Powerup.hpp"
#include "../util/Config.hpp"
#include "../util/Util.hpp"
#include "../game_engine/screens/Death.hpp"
#include "../util/Position.hpp"
#include "../util/RenderableList.hpp"
#include "../util/KeyInputList.hpp"

struct SharedData {
	int life;
	int points;
	Powerup *activePowerup;
	bool visible, invincible;
	bool isBeingDamaged;
	int damageCounter;
	Death *deathScreen;
};

class Player : public Entity {
protected:
	SharedData *sharedData;
	bool isJumping, isGettingDown;
	int jumpCounter, gettingDownCounter;
	Orientation orientation;
	void handleConsumedActivePowerup();
	void deleteActivePowerup();
	void lookForPowerup();
	void killEnemiesBelow();
public:
	Player(Level *level, Position position, SharedData *sharedData);
	// Precondition: level and sharedData must be not NULL

	void updateAttributes();
	// Postcondition: updates player attributes based on its current state

	void tick(KeyInputList *inputs);
	// Precondition: inputs must be not NULL

	Orientation getOrientation();
	int getLife();
	// Postcondition: the returned value must be equal or greater than 0

	void setLife(int life);
	// Precondition: life must be greater than 0

	void increaseLife(int amount);
	// Precondition: amount must be greater than 0

	void decreaseLife(int amount);
	// Precondition: amount must be greater than 0

	bool canBeDamaged();
	void handleDamages();
	int getPoints();
	// Postcondition: the returned value must be greater or equal to zero

	void setPoints(int points);
	// Postcondition: points must be greater or equal to zero

	void increasePoints(int amount);
	// Precondition: amount must be greater than 0

	void decreasePoints(int amount);
	// Precondition: amount must be greater than 0

	void kill();
	// Postcondition: kills the player if it is not invincible

	void jump();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void use();
	// Postcondition: uses the active powerup if it's usable

	bool isVisible();
	void setVisible(bool visible);
	bool isInvincible();
	void setInvincible(bool invincible);
	void applyGravityAndJump();
	//Postcondition: makes the player fall or pushes it up if it's jumping

	void death();
	//Postcondition: sets the active screen to the Death screen

	bool replaceActivePowerup(Powerup *powerup);
	// Postcondition: returns true if powerup has to be deleted

	Powerup* getActivePowerup();
	RenderableList* getRenderInfo();
	// Postcondition: returns a pointer to a list containing some optional Renderables to render. The returned pointer is always not NULL
};

#endif /* PLAYER_HPP */
