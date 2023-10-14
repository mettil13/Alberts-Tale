#ifndef FAST_ENEMY_HPP
#define FAST_ENEMY_HPP
class FastEnemy;
#include "Enemy.hpp"
#include "../../util/Util.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

class FastEnemy : public Enemy {
protected:
	Orientation direction;
public:
	FastEnemy(Level *level, Position position);
	void tick();
	int getPoints();
};

#endif /* FAST_ENEMY_HPP */
