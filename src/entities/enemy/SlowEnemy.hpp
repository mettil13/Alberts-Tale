#ifndef SLOW_ENEMY_HPP
#define SLOW_ENEMY_HPP
class SlowEnemy;
#include "Enemy.hpp"
#include "../../util/Util.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

class SlowEnemy : public Enemy {
protected:
	Orientation direction;
public:
	SlowEnemy(Level *level, Position position);
	void tick();
	int getPoints();
};

#endif /* SLOW_ENEMY_HPP */
