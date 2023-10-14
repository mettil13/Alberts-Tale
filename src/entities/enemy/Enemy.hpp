#ifndef ENEMY_HPP
#define ENEMY_HPP
class Enemy;
#ifndef LEVEL_CLASS_DECL
#define LEVEL_CLASS_DECL
class Level;
#endif /* LEVEL_CLASS_DECL */
#include "../Entity.hpp"
#include "../../util/Position.hpp"
#include "../../util/Config.hpp"
#include "../../util/RenderableList.hpp"

#define BASE_ENEMY_ID 0
#define STATIC_ENEMY_ID 1
#define SLOW_ENEMY_ID 2
#define FAST_ENEMY_ID 3
#define FLYING_ENEMY_ID 4
#define CHASING_ENEMY_ID 5
#define SHOOTING_ENEMY_ID 6
#define SPEAR_ENEMY_ID 7
#define SCREAMING_ENEMY_ID 8
#define BULLET_ENEMY_ID 9

class Enemy : public Entity {
protected:
	int id;
	int tickCounter;
public:
	Enemy(int id, Level *level, Position position);
	// Precondition: level must not be NULL and position must be inside the level

	int getId();
	void tick();
	bool skipTick(int tickNumber);
	// Precondition: tickNumber must be greater than 0
	// Postcondition: returns true if skipTick has been called tickNumber times since the last time it has returned
	//                true (or since the program started if true has never been returned), false otherwise
	
	bool moveUp();
	// Postcondition: returns true if the Enemy has moved up (so when its path was free), false otherwise

	bool moveDown();
	// Postcondition: returns true if the Enemy has moved down (so when its path was free), false otherwise

	bool moveLeft();
	// Postcondition: returns true if the Enemy has moved left (so when its path was free), false otherwise

	bool moveRight();
	// Postcondition: returns true if the Enemy has moved right (so when its path was free), false otherwise

	int getPoints();
	// Postcondition: the returned value must be greater or equal to zero
};

RenderableList* enemy_getRenderInfo(Enemy *enemy);
void enemy_tick(Enemy *enemy);
int enemy_getPoints(Enemy *enemy);
void enemy_destroy(Enemy *enemy);
void enemy_kill(Enemy *enemy);

#endif /* ENEMY_HPP */
