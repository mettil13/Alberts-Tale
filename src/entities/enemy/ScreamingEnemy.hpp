#ifndef SCREAMING_ENEMY_HPP
#define SCREAMING_ENEMY_HPP
class ScreamingEnemy;
#include "Enemy.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/RenderableList.hpp"

class ScreamingEnemy : public Enemy {
protected:
	Position leftScream, rightScream;
	bool leftScreamActive, rightScreamActive;
	int screamProgression;
public:
	ScreamingEnemy(Level *level, Position position);
	void tick();
	int getPoints();
	RenderableList* getRenderInfo();
};

#endif /* SCREAMING_ENEMY_HPP */
