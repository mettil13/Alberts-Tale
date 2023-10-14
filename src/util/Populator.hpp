#ifndef POPULATOR_HPP
#define POPULATOR_HPP
#include "../entities/enemy/Enemy.hpp"
#include "../powerups/Powerup.hpp"
#include "../game_engine/levels/Level.hpp"
#include "Position.hpp"

Enemy* generateRandomEnemy(Level *level, Position position, int difficulty);

Powerup* generateRandomPowerup(Position position, int difficulty);

#endif /* POPULATOR_HPP */
