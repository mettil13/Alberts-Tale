#ifndef FIRST_LEVEL_HPP
#define FIRST_LEVEL_HPP
class FirstLevel;
#include "Level.hpp"
#include "../screens/LevelManager.hpp"
#include "../../entities/Player.hpp"

class FirstLevel : public Level {
protected:
public:
	FirstLevel(LevelManager *levelManager, SharedData *sharedData);
};

#endif /* FIRST_LEVEL_HPP */
