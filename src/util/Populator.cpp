#include <iostream>
#include "Populator.hpp"
#include "Config.hpp"
#include "Util.hpp"
#include "../powerups/Powerup.hpp"
#include "../game_engine/levels/Level.hpp"
#include "../entities/enemy/Enemy.hpp"
#include "Position.hpp"
#include "../entities/enemy/ChasingEnemy.hpp"
#include "../entities/enemy/FastEnemy.hpp"
#include "../entities/enemy/FlyingEnemy.hpp"
#include "../entities/enemy/ScreamingEnemy.hpp"
#include "../entities/enemy/ShootingEnemy.hpp"
#include "../entities/enemy/SlowEnemy.hpp"
#include "../entities/enemy/SpearEnemy.hpp"
#include "../entities/enemy/StaticEnemy.hpp"
#include "../powerups/oneOff/LifePowerup.hpp"
#include "../powerups/timed/InvisibilityPowerup.hpp"
#include "../powerups/timed/InvincibilityPowerup.hpp"
#include "../powerups/usable/GunPowerup.hpp"
#include "../powerups/alwaysActive/SpearPowerup.hpp"

using namespace std;

bool checkRand(int &randomized, int prob) {
	bool b = randomized < prob;
	randomized -= prob;
	return b;
}

Enemy* generateRandomEnemy(Level *level, Position position, int difficulty) {
	int staticEnemy = static_enemy_spawn_probability(difficulty);
	int spearEnemy = spear_enemy_spawn_probability(difficulty);
	int slowEnemy = slow_enemy_spawn_probability(difficulty);
	int shootingEnemy = shooting_enemy_spawn_probability(difficulty);
	int screamingEnemy = screaming_enemy_spawn_probability(difficulty);
	int flyingEnemy = flying_enemy_spawn_probability(difficulty);
	int fastEnemy = fast_enemy_spawn_probability(difficulty);
	int chasingEnemy = chasing_enemy_spawn_probability(difficulty);

	int rand = randomize(staticEnemy + spearEnemy + slowEnemy + shootingEnemy + screamingEnemy + flyingEnemy + fastEnemy + chasingEnemy);
	if (checkRand(rand, staticEnemy)) {
		return new StaticEnemy(level, position);
	}
	else if (checkRand(rand, spearEnemy)) {
		return new SpearEnemy(level, position);
	}
	else if (checkRand(rand, slowEnemy)) {
		return new SlowEnemy(level, position);
	}
	else if (checkRand(rand, shootingEnemy)) {
		return new ShootingEnemy(level, position);
	}
	else if (checkRand(rand, screamingEnemy)) {
		return new ScreamingEnemy(level, position);
	}
	else if (checkRand(rand, flyingEnemy)) {
		return new FlyingEnemy(level, position);
	}
	else if (checkRand(rand, fastEnemy)) {
		return new FastEnemy(level, position);
	}
	else { // checkRand(rand, chasingEnemy)
		return new ChasingEnemy(level, position);
	}
}

Powerup* generateRandomPowerup(Position position, int difficulty) {
	int lifePowerup = life_powerup_spawn_probability(difficulty);
	int invincibilityPowerup = invincibility_powerup_spawn_probability(difficulty);
	int invisibilityPowerup = invisibility_powerup_spawn_probability(difficulty);
	int gunPowerup = gun_powerup_spawn_probability(difficulty);
	int spearPowerup = spear_powerup_spawn_probability(difficulty);

	int rand = randomize(lifePowerup + invincibilityPowerup + invisibilityPowerup + gunPowerup + spearPowerup);
	if (checkRand(rand, lifePowerup)) {
		return new LifePowerup(position, LIFE_INCREASE);
	}
	else if (checkRand(rand, invincibilityPowerup)) {
		return new InvincibilityPowerup(position, INVINCIBILITY_DURATION);
	}
	else if (checkRand(rand, invisibilityPowerup)) {
		return new InvisibilityPowerup(position, INVISIBILITY_DURATION);
	}
	else if (checkRand(rand, gunPowerup)) {
		return new GunPowerup(position, GUN_BULLETS);
	}
	else { // checkRand(rand, spearPowerup)
		return new SpearPowerup(position, SPEAR_DURABILITY);
	}
}
