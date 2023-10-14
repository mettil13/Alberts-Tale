#ifndef BULLET_ENEMY_HPP
#define BULLET_ENEMY_HPP
class BulletEnemy;
#include "Enemy.hpp"
#include "../../util/Util.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

class BulletEnemy : public Enemy {
protected:
	Orientation direction;
	void checkHit();
public:
	BulletEnemy(Level *level, Position position, Orientation direction);
	void tick();
	int getPoints();
};

#endif /* BULLET_ENEMY_HPP */
