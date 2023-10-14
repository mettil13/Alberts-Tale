#ifndef STATIC_ENEMY_HPP
#define STATIC_ENEMY_HPP
class StaticEnemy;
#include "Enemy.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

class StaticEnemy : public Enemy {
public:
	StaticEnemy(Level *level, Position position);
	void tick();
	int getPoints();
};

#endif /* STATIC_ENEMY_HPP */
