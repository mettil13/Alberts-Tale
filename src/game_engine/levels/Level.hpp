#ifndef LEVEL_HPP
#define LEVEL_HPP
#ifndef LEVEL_CLASS_DECL
#define LEVEL_CLASS_DECL
class Level;
#endif /* LEVEL_CLASS_DECL */
#include "../../util/Block.hpp"
#include "../screens/LevelManager.hpp"
#include "../../util/Position.hpp"
#include "../../entities/enemy/EnemyList.hpp"
#include "../../powerups/PowerupList.hpp"
#include "../../util/Config.hpp"
#include "../../entities/Player.hpp"
#include "../../util/Util.hpp"
#include "../../util/KeyInputList.hpp"

#define BASE_LEVEL_ID 0
#define FIRST_LEVEL_ID 1
#define GENERATED_LEVEL_ID 2

class Level {
protected:
	int id;
	Block blocks[LEVEL_MAX_X][LEVEL_MAX_Y];
	LevelManager *levelManager;
	EnemyList *enemyList;
	PowerupList *powerupList;
	Player *player;
	void renderLevel(ResizeInfo resizeInfo);
	void renderHUD();
public:
	Level(int id, LevelManager *levelManager, SharedData *sharedData);
	// Precondition: levelManager and sharedData must be not NULL

	int getId();
	Block getBlockAt(int x, int y);
	// Postcondition: returns the block at (x, y). An invalid block is returned if (x, y) is outside the level

	Block getBlockAt(Position position);
	// Postcondition: returns the block at position. An invalid block is returned if position is outside the level

	void setBlockAt(int x, int y, Block blockToSet);
	// Postcondition: sets blockToSet at (x, y) if the provided coordinates are inside the level and the provided block is not invalid

	void setBlockAt(Position position, Block blockToSet);
	// Postcondition: sets blockToSet at position if the provided position is inside the level and the provided block is not invalid

	bool isInsideLevel(Position position);
	// Postcondition: returns whether position is inside the level

	bool isInsideLevel(int x, int y);
	// Postcondition: returns whether (x, y) is inside the level

	EnemyList* getEnemyList();
	// Postcondition: the returned pointer is not NULL

	PowerupList* getPowerupList();
	// Postcondition: the returned pointer is not NULL

	Player* getPlayer();
	// Postcondition: the returned pointer is not NULL

	LevelManager* getLevelManager();
	// Postcondition: the returned pointer is not NULL

	void tick(KeyInputList *inputs);
	void render(ResizeInfo resizeInfo);
	void destroy();
};

void level_tick(Level *level, KeyInputList *inputs);
void level_render(Level *level, ResizeInfo resizeInfo);
void level_destroy(Level *level);

#endif /* LEVEL_HPP */
