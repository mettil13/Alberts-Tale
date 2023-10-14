#ifndef FLYING_ENEMY_HPP
#define FLYING_ENEMY_HPP
class FlyingEnemy;
#include "Enemy.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

class FlyingEnemy : public Enemy {
public:
	FlyingEnemy(Level *level, Position position);
	void tick();
	int getPoints();
};

#endif /* FLYING_ENEMY_HPP */
