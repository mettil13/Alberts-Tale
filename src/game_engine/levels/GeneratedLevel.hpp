#ifndef GENERATED_LEVEL_HPP
#define GENERATED_LEVEL_HPP
class GeneratedLevel;
#include "Level.hpp"
#include "PositionList.hpp"
#include "../screens/LevelManager.hpp"
#include "../../entities/Player.hpp"

class GeneratedLevel : public Level {
protected:
	int generatorShortPlatformProbability;
	int generatorVeryLongPlatformProbability;

	int generatorShouldStartInvertedPlatforms;
	int generatorStopInvertedPlatforms;

	int generatorShouldStartDownwardsPlatforms;
	int generatorStopDownwardsPlatforms;

	int generatorUpperPlatformProbability;

	int generatorPopulatePlatformProbability;
	int generatorSpawnEnemyInsteadOfPowerupProbability;

	PositionList *positionList;

	bool generatePlatform(int x, int y, int &newX);
	bool generatePlatformInverted(int x, int y, int &newX);
	void generatePlatformDiagonal(int fromX, int fromY, bool firstGenerated);
	void generatePlatformDiagonalInverted(int fromX, int fromY, bool firstGenerated);
	void generatePlatformDiagonalDownwards(int fromX, int fromY);
	void populate(int difficulty);
public:
	GeneratedLevel(LevelManager *levelManager, SharedData *sharedData, int difficulty);
	void destroy();
};

#endif /* GENERATED_LEVEL_HPP */
