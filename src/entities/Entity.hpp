#ifndef ENTITY_HPP
#define ENTITY_HPP
class Entity;
#ifndef LEVEL_CLASS_DECL
#define LEVEL_CLASS_DECL
class Level;
#endif /* LEVEL_CLASS_DECL */
#include "../util/Position.hpp"
#include "../util/RenderableList.hpp"
#include <windows.h>

#define BASE_ENTITY_ID 0
#define PLAYER_ENTITY_ID 1
#define ENEMY_ENTITY_ID 2

class Entity {
protected:
	int entityId;
	Level *level;
	Position position;
	char appearence;
	WORD attributes;
	bool dead;
public:
	Entity(int entityId, Level *level, Position position);
	// Precondition: level must not be NULL and position must be inside the level

	int getEntityId();
	Position getPosition();
	// Postcondition: the returned position is inside the level

	void setPosition(Position position);
	// Precondition: position must be inside the level

	void setX(int x);
	// Precondition: x must be greater or equal than 0 and less than LEVEL_MAX_X

	void setY(int y);
	// Precondition: y must be greater or equal than 0 and less than LEVEL_MAX_Y

	Level* getLevel();
	// Postcondition: the returned pointer is not NULL

	void kill();
	// Postcondition: kills the entity

	bool isDead();
	// Postcondition: returns true if the entity has been killed

	char toChar();
	CHAR_INFO toCharInfo();
	RenderableList* getRenderInfo();
	// Postcondition: returns a pointer to a list containing some optional Renderables to render.
	//                The returned pointer can be NULL if no additional Renderable is to be rendered

	void destroy();
};

RenderableList* entity_getRenderInfo(Entity *entity);
void entity_destroy(Entity *entity);

#endif /* ENTITY_HPP */
