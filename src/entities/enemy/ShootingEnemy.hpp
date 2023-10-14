#ifndef SHOOTING_ENEMY_HPP
#define SHOOTING_ENEMY_HPP
class ShootingEnemy;
#include "Enemy.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

class ShootingEnemy : public Enemy {
public:
	ShootingEnemy(Level *level, Position position);
	void tick();
	int getPoints();
};

#endif /* SHOOTING_ENEMY_HPP */
