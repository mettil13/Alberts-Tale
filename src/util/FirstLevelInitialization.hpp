#ifndef FIRST_LEVEL_INITIALIZATION_HPP
#define FIRST_LEVEL_INITIALIZATION_HPP
#include "../game_engine/levels/Level.hpp"
#include "Block.hpp"
#include "Position.hpp"

void firstLevelInitialization(Level *level);
void drawAlbertBlocks(Level *level, Position position, Block material);
void drawColumn(Level *level, Position position, Block material);
void drawArch(Level *level, Position position, Block material);
void drawBigArch(Level *level, Position position, Block material);
void drawTower(Level *level, Position position, Block material);
void drawExitHill(Level *level, Position position, Block material);
void drawArrow(Level *level, Position position, Block material);

#endif /* FIRST_LEVEL_INITIALIZATION_HPP */
