#ifndef CHASING_ENEMY_HPP
#define CHASING_ENEMY_HPP
class ChasingEnemy;
#include "Enemy.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"

class ChasingEnemy : public Enemy {
public:
	ChasingEnemy(Level *level, Position position);
	void tick();
	int getPoints();
};

#endif /* CHASING_ENEMY_HPP */