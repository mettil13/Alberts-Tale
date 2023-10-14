#include <iostream>
#include "FirstLevelInitialization.hpp"
#include "../game_engine/levels/Level.hpp"
#include "Block.hpp"
#include "Position.hpp"

using namespace std;

void firstLevelInitialization(Level *level) {
	Position p = Position(7, 1);
	drawAlbertBlocks(level, p, Block(BLOCK_BORDER, COLOR_WHITE_TILE));
	p = Position(1, 1);
	drawColumn(level, p, Block(BLOCK_PLATFORM, COLOR_PLATFORM));
	p = Position(45, 1);
	for (int i = 0; i < 9; i++) {
		drawColumn(level, p, Block(BLOCK_PLATFORM, COLOR_PLATFORM));
		p.setX(p.getX() + 15);
	}
	p = Position(45 + 1, 27);
	for (int i = 0; i < 8; i++) {
		drawArch(level, p, Block(BLOCK_PLATFORM, COLOR_PLATFORM));
		p.setX(p.getX() + 15);
	}
	p = Position(1, 27);
	drawBigArch(level, p, Block(BLOCK_PLATFORM, COLOR_PLATFORM));
	p = Position(166, 1);
	drawTower(level, p, Block(BLOCK_PLATFORM, COLOR_PLATFORM));
	p = Position(176, 1);
	drawExitHill(level, p, Block(BLOCK_PLATFORM, COLOR_PLATFORM));
	p = Position(50 + 30, 10);
	drawArrow(level, p, Block(BLOCK_BORDER, COLOR_PLATFORM));
	p = Position(110 + 15, 10);
	drawArrow(level, p, Block(BLOCK_BORDER, COLOR_PLATFORM));
}

void drawAlbertBlocks(Level *level, Position position, Block material) {
	int x = position.getX() - 1;
	int y = position.getY() - 1;

	level->setBlockAt(x + 2, y + 1, material);
	level->setBlockAt(x + 5, y + 1, material);
	level->setBlockAt(x + 8, y + 1, material);
	level->setBlockAt(x + 11, y + 1, material);
	level->setBlockAt(x + 12, y + 1, material);
	level->setBlockAt(x + 15, y + 1, material);
	level->setBlockAt(x + 18, y + 1, material);
	level->setBlockAt(x + 21, y + 1, material);

	level->setBlockAt(x + 1, y + 2, material);
	level->setBlockAt(x + 4, y + 2, material);
	level->setBlockAt(x + 7, y + 2, material);
	level->setBlockAt(x + 10, y + 2, material);
	level->setBlockAt(x + 13, y + 2, material);
	level->setBlockAt(x + 16, y + 2, material);
	level->setBlockAt(x + 19, y + 2, material);
	level->setBlockAt(x + 22, y + 2, material);

	level->setBlockAt(x + 1, y + 3, material);
	level->setBlockAt(x + 4, y + 3, material);
	level->setBlockAt(x + 7, y + 3, material);
	level->setBlockAt(x + 10, y + 3, material);
	level->setBlockAt(x + 13, y + 3, material);
	level->setBlockAt(x + 16, y + 3, material);
	level->setBlockAt(x + 19, y + 3, material);
	level->setBlockAt(x + 22, y + 3, material);

	level->setBlockAt(x + 2, y + 4, material);
	level->setBlockAt(x + 5, y + 4, material);
	level->setBlockAt(x + 8, y + 4, material);
	level->setBlockAt(x + 11, y + 4, material);
	level->setBlockAt(x + 12, y + 4, material);
	level->setBlockAt(x + 15, y + 4, material);
	level->setBlockAt(x + 18, y + 4, material);
	level->setBlockAt(x + 21, y + 4, material);

	level->setBlockAt(x + 5, y + 6, material);
	level->setBlockAt(x + 8, y + 6, material);
	level->setBlockAt(x + 11, y + 6, material);
	level->setBlockAt(x + 12, y + 6, material);
	level->setBlockAt(x + 15, y + 6, material);
	level->setBlockAt(x + 18, y + 6, material);

	level->setBlockAt(x + 4, y + 7, material);
	level->setBlockAt(x + 7, y + 7, material);
	level->setBlockAt(x + 10, y + 7, material);
	level->setBlockAt(x + 13, y + 7, material);
	level->setBlockAt(x + 16, y + 7, material);
	level->setBlockAt(x + 19, y + 7, material);

	level->setBlockAt(x + 4, y + 8, material);
	level->setBlockAt(x + 7, y + 8, material);
	level->setBlockAt(x + 10, y + 8, material);
	level->setBlockAt(x + 13, y + 8, material);
	level->setBlockAt(x + 16, y + 8, material);
	level->setBlockAt(x + 19, y + 8, material);

	level->setBlockAt(x + 5, y + 9, material);
	level->setBlockAt(x + 8, y + 9, material);
	level->setBlockAt(x + 11, y + 9, material);
	level->setBlockAt(x + 12, y + 9, material);
	level->setBlockAt(x + 15, y + 9, material);
	level->setBlockAt(x + 18, y + 9, material);

	level->setBlockAt(x + 5, y + 11, material);
	level->setBlockAt(x + 8, y + 11, material);
	level->setBlockAt(x + 11, y + 11, material);
	level->setBlockAt(x + 12, y + 11, material);
	level->setBlockAt(x + 15, y + 11, material);
	level->setBlockAt(x + 18, y + 11, material);

	level->setBlockAt(x + 5, y + 12, material);
	level->setBlockAt(x + 7, y + 12, material);
	level->setBlockAt(x + 10, y + 12, material);
	level->setBlockAt(x + 13, y + 12, material);
	level->setBlockAt(x + 16, y + 12, material);
	level->setBlockAt(x + 18, y + 12, material);

	level->setBlockAt(x + 4, y + 13, material);
	level->setBlockAt(x + 7, y + 13, material);
	level->setBlockAt(x + 10, y + 13, material);
	level->setBlockAt(x + 13, y + 13, material);
	level->setBlockAt(x + 16, y + 13, material);
	level->setBlockAt(x + 19, y + 13, material);

	level->setBlockAt(x + 4, y + 14, material);
	level->setBlockAt(x + 8, y + 14, material);
	level->setBlockAt(x + 11, y + 14, material);
	level->setBlockAt(x + 12, y + 14, material);
	level->setBlockAt(x + 15, y + 14, material);
	level->setBlockAt(x + 19, y + 14, material);

	level->setBlockAt(x + 3, y + 16, material);
	level->setBlockAt(x + 11, y + 16, material);
	level->setBlockAt(x + 12, y + 16, material);
	level->setBlockAt(x + 15, y + 16, material);
	level->setBlockAt(x + 20, y + 16, material);

	level->setBlockAt(x + 3, y + 17, material);
	level->setBlockAt(x + 10, y + 17, material);
	level->setBlockAt(x + 13, y + 17, material);
	level->setBlockAt(x + 16, y + 17, material);
	level->setBlockAt(x + 20, y + 17, material);

	level->setBlockAt(x + 2, y + 18, material);
	level->setBlockAt(x + 10, y + 18, material);
	level->setBlockAt(x + 11, y + 18, material);
	level->setBlockAt(x + 12, y + 18, material);
	level->setBlockAt(x + 13, y + 18, material);
	level->setBlockAt(x + 15, y + 18, material);
	level->setBlockAt(x + 21, y + 18, material);

	level->setBlockAt(x + 2, y + 19, material);
	level->setBlockAt(x + 21, y + 19, material);
}

void drawColumn(Level *level, Position position, Block material) {
	int x = position.getX() - 1;
	int y = position.getY() - 1;

	level->setBlockAt(x + 1, y + 3, material);
	level->setBlockAt(x + 1, y + 5, material);
	level->setBlockAt(x + 1, y + 7, material);
	level->setBlockAt(x + 1, y + 9, material);
	level->setBlockAt(x + 1, y + 10, material);
	level->setBlockAt(x + 1, y + 12, material);
	level->setBlockAt(x + 1, y + 13, material);
	level->setBlockAt(x + 1, y + 14, material);
	level->setBlockAt(x + 1, y + 16, material);
	level->setBlockAt(x + 1, y + 17, material);
	level->setBlockAt(x + 1, y + 18, material);
	level->setBlockAt(x + 1, y + 20, material);
	level->setBlockAt(x + 1, y + 21, material);
	level->setBlockAt(x + 1, y + 22, material);
	level->setBlockAt(x + 1, y + 23, material);
	level->setBlockAt(x + 1, y + 25, material);
	level->setBlockAt(x + 1, y + 26, material);

	level->setBlockAt(x + 3, y + 2, material);
	level->setBlockAt(x + 3, y + 4, material);
	level->setBlockAt(x + 3, y + 6, material);
	level->setBlockAt(x + 3, y + 8, material);
	level->setBlockAt(x + 3, y + 9, material);
	level->setBlockAt(x + 3, y + 11, material);
	level->setBlockAt(x + 3, y + 12, material);
	level->setBlockAt(x + 3, y + 14, material);
	level->setBlockAt(x + 3, y + 15, material);
	level->setBlockAt(x + 3, y + 16, material);
	level->setBlockAt(x + 3, y + 18, material);
	level->setBlockAt(x + 3, y + 19, material);
	level->setBlockAt(x + 3, y + 20, material);
	level->setBlockAt(x + 3, y + 21, material);
	level->setBlockAt(x + 3, y + 23, material);
	level->setBlockAt(x + 3, y + 24, material);
	level->setBlockAt(x + 3, y + 25, material);
	level->setBlockAt(x + 3, y + 26, material);
}

void drawArch(Level *level, Position position, Block material) {
	int x = position.getX() - 1;
	int y = position.getY() - 1;

	level->setBlockAt(x + 2, y + 1, material);
	level->setBlockAt(x + 3, y + 1, material);
	level->setBlockAt(x + 14, y + 1, material);
	level->setBlockAt(x + 15, y + 1, material);

	level->setBlockAt(x + 1, y + 2, material);
	level->setBlockAt(x + 3, y + 2, material);
	level->setBlockAt(x + 14, y + 2, material);
	level->setBlockAt(x + 16, y + 2, material);

	level->setBlockAt(x + 1, y + 3, material);
	level->setBlockAt(x + 4, y + 3, material);
	level->setBlockAt(x + 13, y + 3, material);
	level->setBlockAt(x + 16, y + 3, material);

	level->setBlockAt(x + 2, y + 4, material);
	level->setBlockAt(x + 4, y + 4, material);
	level->setBlockAt(x + 13, y + 4, material);
	level->setBlockAt(x + 15, y + 4, material);

	level->setBlockAt(x + 2, y + 5, material);
	level->setBlockAt(x + 5, y + 5, material);
	level->setBlockAt(x + 12, y + 5, material);
	level->setBlockAt(x + 15, y + 5, material);

	level->setBlockAt(x + 3, y + 6, material);
	level->setBlockAt(x + 5, y + 6, material);
	level->setBlockAt(x + 12, y + 6, material);
	level->setBlockAt(x + 14, y + 6, material);

	level->setBlockAt(x + 3, y + 7, material);
	level->setBlockAt(x + 6, y + 7, material);
	level->setBlockAt(x + 11, y + 7, material);
	level->setBlockAt(x + 14, y + 7, material);

	level->setBlockAt(x + 4, y + 8, material);
	level->setBlockAt(x + 7, y + 8, material);
	level->setBlockAt(x + 10, y + 8, material);
	level->setBlockAt(x + 13, y + 8, material);

	level->setBlockAt(x + 4, y + 9, material);
	level->setBlockAt(x + 5, y + 9, material);
	level->setBlockAt(x + 8, y + 9, material);
	level->setBlockAt(x + 9, y + 9, material);
	level->setBlockAt(x + 12, y + 9, material);
	level->setBlockAt(x + 13, y + 9, material);

	level->setBlockAt(x + 6, y + 10, material);
	level->setBlockAt(x + 11, y + 10, material);

	level->setBlockAt(x + 6, y + 11, material);
	level->setBlockAt(x + 7, y + 11, material);
	level->setBlockAt(x + 10, y + 11, material);
	level->setBlockAt(x + 11, y + 11, material);

	level->setBlockAt(x + 8, y + 12, material);
	level->setBlockAt(x + 9, y + 12, material);

}

void drawBigArch(Level *level, Position position, Block material) {
	int x = position.getX() - 1;
	int y = position.getY() - 1;

	level->setBlockAt(x + 3, y + 1, material);
	level->setBlockAt(x + 45, y + 1, material);

	level->setBlockAt(x + 1, y + 2, material);
	level->setBlockAt(x + 4, y + 2, material);
	level->setBlockAt(x + 44, y + 2, material);
	level->setBlockAt(x + 46, y + 2, material);

	level->setBlockAt(x + 1, y + 3, material);
	level->setBlockAt(x + 4, y + 3, material);
	level->setBlockAt(x + 44, y + 3, material);
	level->setBlockAt(x + 46, y + 3, material);

	level->setBlockAt(x + 2, y + 4, material);
	level->setBlockAt(x + 4, y + 4, material);
	level->setBlockAt(x + 44, y + 4, material);
	level->setBlockAt(x + 46, y + 4, material);

	level->setBlockAt(x + 2, y + 5, material);
	level->setBlockAt(x + 5, y + 5, material);
	level->setBlockAt(x + 43, y + 5, material);
	level->setBlockAt(x + 46, y + 5, material);

	level->setBlockAt(x + 2, y + 6, material);
	level->setBlockAt(x + 3, y + 6, material);
	level->setBlockAt(x + 5, y + 6, material);
	level->setBlockAt(x + 43, y + 6, material);
	level->setBlockAt(x + 45, y + 6, material);
	level->setBlockAt(x + 46, y + 6, material);

	level->setBlockAt(x + 3, y + 7, material);
	level->setBlockAt(x + 6, y + 7, material);
	level->setBlockAt(x + 42, y + 7, material);
	level->setBlockAt(x + 45, y + 7, material);

	level->setBlockAt(x + 3, y + 8, material);
	level->setBlockAt(x + 4, y + 8, material);
	level->setBlockAt(x + 6, y + 8, material);
	level->setBlockAt(x + 42, y + 8, material);
	level->setBlockAt(x + 44, y + 8, material);
	level->setBlockAt(x + 45, y + 8, material);

	level->setBlockAt(x + 4, y + 9, material);
	level->setBlockAt(x + 7, y + 9, material);
	level->setBlockAt(x + 41, y + 9, material);
	level->setBlockAt(x + 44, y + 9, material);

	level->setBlockAt(x + 4, y + 10, material);
	level->setBlockAt(x + 5, y + 10, material);
	level->setBlockAt(x + 7, y + 10, material);
	level->setBlockAt(x + 41, y + 10, material);
	level->setBlockAt(x + 43, y + 10, material);
	level->setBlockAt(x + 44, y + 10, material);

	level->setBlockAt(x + 5, y + 11, material);
	level->setBlockAt(x + 8, y + 11, material);
	level->setBlockAt(x + 40, y + 11, material);
	level->setBlockAt(x + 43, y + 11, material);

	level->setBlockAt(x + 6, y + 12, material);
	level->setBlockAt(x + 9, y + 12, material);
	level->setBlockAt(x + 39, y + 12, material);
	level->setBlockAt(x + 42, y + 12, material);
}

void drawTower(Level *level, Position position, Block material) {
	int x = position.getX() - 1;
	int y = position.getY() - 1;

	level->setBlockAt(x + 1, y + 36, material);
	level->setBlockAt(x + 1, y + 37, material);
	level->setBlockAt(x + 1, y + 38, material);

	level->setBlockAt(x + 2, y + 30, material);
	level->setBlockAt(x + 2, y + 31, material);
	level->setBlockAt(x + 2, y + 32, material);
	level->setBlockAt(x + 2, y + 33, material);
	level->setBlockAt(x + 2, y + 34, material);
	level->setBlockAt(x + 2, y + 35, material);

	level->setBlockAt(x + 3, y + 36, material);

	level->setBlockAt(x + 4, y + 3, material);
	level->setBlockAt(x + 4, y + 5, material);
	level->setBlockAt(x + 4, y + 7, material);
	level->setBlockAt(x + 4, y + 9, material);
	level->setBlockAt(x + 4, y + 10, material);
	level->setBlockAt(x + 4, y + 12, material);
	level->setBlockAt(x + 4, y + 13, material);
	level->setBlockAt(x + 4, y + 14, material);
	level->setBlockAt(x + 4, y + 16, material);
	level->setBlockAt(x + 4, y + 17, material);
	level->setBlockAt(x + 4, y + 18, material);
	level->setBlockAt(x + 4, y + 20, material);
	level->setBlockAt(x + 4, y + 21, material);
	level->setBlockAt(x + 4, y + 22, material);
	level->setBlockAt(x + 4, y + 23, material);
	level->setBlockAt(x + 4, y + 26, material);
	level->setBlockAt(x + 4, y + 27, material);
	level->setBlockAt(x + 4, y + 28, material);
	level->setBlockAt(x + 4, y + 29, material);
	level->setBlockAt(x + 4, y + 35, material);
	level->setBlockAt(x + 4, y + 38, material);

	level->setBlockAt(x + 5, y + 31, material);
	level->setBlockAt(x + 5, y + 32, material);
	level->setBlockAt(x + 5, y + 35, material);

	level->setBlockAt(x + 6, y + 4, material);
	level->setBlockAt(x + 6, y + 6, material);
	level->setBlockAt(x + 6, y + 8, material);
	level->setBlockAt(x + 6, y + 9, material);
	level->setBlockAt(x + 6, y + 11, material);
	level->setBlockAt(x + 6, y + 12, material);
	level->setBlockAt(x + 6, y + 14, material);
	level->setBlockAt(x + 6, y + 15, material);
	level->setBlockAt(x + 6, y + 16, material);
	level->setBlockAt(x + 6, y + 18, material);
	level->setBlockAt(x + 6, y + 19, material);
	level->setBlockAt(x + 6, y + 20, material);
	level->setBlockAt(x + 6, y + 21, material);
	level->setBlockAt(x + 6, y + 24, material);
	level->setBlockAt(x + 6, y + 25, material);
	level->setBlockAt(x + 6, y + 26, material);
	level->setBlockAt(x + 6, y + 27, material);
	level->setBlockAt(x + 6, y + 30, material);
	level->setBlockAt(x + 6, y + 33, material);
	level->setBlockAt(x + 6, y + 36, material);

	level->setBlockAt(x + 7, y + 31, material);
	level->setBlockAt(x + 7, y + 32, material);
	level->setBlockAt(x + 7, y + 35, material);

	level->setBlockAt(x + 8, y + 5, material);
	level->setBlockAt(x + 8, y + 7, material);
	level->setBlockAt(x + 8, y + 9, material);
	level->setBlockAt(x + 8, y + 10, material);
	level->setBlockAt(x + 8, y + 12, material);
	level->setBlockAt(x + 8, y + 13, material);
	level->setBlockAt(x + 8, y + 14, material);
	level->setBlockAt(x + 8, y + 16, material);
	level->setBlockAt(x + 8, y + 17, material);
	level->setBlockAt(x + 8, y + 18, material);
	level->setBlockAt(x + 8, y + 20, material);
	level->setBlockAt(x + 8, y + 21, material);
	level->setBlockAt(x + 8, y + 22, material);
	level->setBlockAt(x + 8, y + 23, material);
	level->setBlockAt(x + 8, y + 26, material);
	level->setBlockAt(x + 8, y + 27, material);
	level->setBlockAt(x + 8, y + 28, material);
	level->setBlockAt(x + 8, y + 29, material);
	level->setBlockAt(x + 8, y + 35, material);
	level->setBlockAt(x + 8, y + 38, material);

	level->setBlockAt(x + 9, y + 36, material);

	level->setBlockAt(x + 10, y + 6, material);
	level->setBlockAt(x + 10, y + 8, material);
	level->setBlockAt(x + 10, y + 9, material);
	level->setBlockAt(x + 10, y + 11, material);
	level->setBlockAt(x + 10, y + 12, material);
	level->setBlockAt(x + 10, y + 14, material);
	level->setBlockAt(x + 10, y + 15, material);
	level->setBlockAt(x + 10, y + 16, material);
	level->setBlockAt(x + 10, y + 18, material);
	level->setBlockAt(x + 10, y + 19, material);
	level->setBlockAt(x + 10, y + 20, material);
	level->setBlockAt(x + 10, y + 21, material);
	level->setBlockAt(x + 10, y + 23, material);
	level->setBlockAt(x + 10, y + 24, material);
	level->setBlockAt(x + 10, y + 25, material);
	level->setBlockAt(x + 10, y + 26, material);
	level->setBlockAt(x + 10, y + 27, material);
	level->setBlockAt(x + 10, y + 28, material);
	level->setBlockAt(x + 10, y + 29, material);
	level->setBlockAt(x + 10, y + 30, material);
	level->setBlockAt(x + 10, y + 31, material);
	level->setBlockAt(x + 10, y + 32, material);
	level->setBlockAt(x + 10, y + 33, material);
	level->setBlockAt(x + 10, y + 34, material);
	level->setBlockAt(x + 10, y + 35, material);

	level->setBlockAt(x + 11, y + 36, material);
	level->setBlockAt(x + 11, y + 37, material);
	level->setBlockAt(x + 11, y + 38, material);
}

void drawExitHill(Level *level, Position position, Block material) {
	int x = position.getX() - 1;
	int y = position.getY() - 1;

	level->setBlockAt(x + 1, y + 1, material);
	level->setBlockAt(x + 2, y + 1, material);
	level->setBlockAt(x + 12, y + 1, material);
	level->setBlockAt(x + 21, y + 1, material);

	level->setBlockAt(x + 4, y + 2, material);
	level->setBlockAt(x + 5, y + 2, material);
	level->setBlockAt(x + 6, y + 2, material);
	level->setBlockAt(x + 11, y + 2, material);
	level->setBlockAt(x + 20, y + 2, material);

	level->setBlockAt(x + 7, y + 3, material);
	level->setBlockAt(x + 8, y + 3, material);
	level->setBlockAt(x + 9, y + 3, material);
	level->setBlockAt(x + 10, y + 3, material);
	level->setBlockAt(x + 19, y + 3, material);

	level->setBlockAt(x + 10, y + 4, material);
	level->setBlockAt(x + 11, y + 4, material);
	level->setBlockAt(x + 12, y + 4, material);
	level->setBlockAt(x + 18, y + 4, material);

	level->setBlockAt(x + 13, y + 5, material);
	level->setBlockAt(x + 14, y + 5, material);
	level->setBlockAt(x + 15, y + 5, material);
	level->setBlockAt(x + 17, y + 5, material);

	level->setBlockAt(x + 16, y + 6, material);
	level->setBlockAt(x + 17, y + 6, material);
	level->setBlockAt(x + 18, y + 6, material);

	level->setBlockAt(x + 19, y + 7, material);
	level->setBlockAt(x + 20, y + 7, material);
	level->setBlockAt(x + 21, y + 7, material);

	level->setBlockAt(x + 22, y + 8, material);
	level->setBlockAt(x + 23, y + 8, material);
}

void drawArrow(Level *level, Position position, Block material) {
	int x = position.getX() - 1;
	int y = position.getY() - 1;

	level->setBlockAt(x + 3, y + 1, material);
	level->setBlockAt(x + 4, y + 1, material);

	level->setBlockAt(x + 5, y + 2, material);
	level->setBlockAt(x + 6, y + 2, material);

	level->setBlockAt(x + 1, y + 3, material);
	level->setBlockAt(x + 2, y + 3, material);
	level->setBlockAt(x + 3, y + 3, material);
	level->setBlockAt(x + 7, y + 3, material);
	level->setBlockAt(x + 8, y + 3, material);

	level->setBlockAt(x + 5, y + 4, material);
	level->setBlockAt(x + 6, y + 4, material);

	level->setBlockAt(x + 3, y + 5, material);
	level->setBlockAt(x + 4, y + 5, material);
}
