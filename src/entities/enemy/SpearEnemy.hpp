#ifndef SPEAR_ENEMY_HPP
#define SPEAR_ENEMY_HPP
class SpearEnemy;
#include "Enemy.hpp"
#include "../../util/Util.hpp"
#include "../../util/Position.hpp"
#include "../../game_engine/levels/Level.hpp"
#include "../../util/RenderableList.hpp"

class SpearEnemy : public Enemy {
protected:
	Orientation direction;
public:
	SpearEnemy(Level *level, Position position);
	void tick();
	int getPoints();
	RenderableList* getRenderInfo();
};

#endif /* SPEAR_ENEMY_HPP */
