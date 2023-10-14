#include <iostream>
#include <math.h>
#include "Config.hpp"
#include "Position.hpp"

using namespace std;

// Handle
HANDLE getInputHandle() {
	return GetStdHandle(STD_INPUT_HANDLE);
}

HANDLE getOutputHandle() {
	return GetStdHandle(STD_OUTPUT_HANDLE);
}


// Populator
int getLevelDifficulty(int levelNumber) {
	// y^2 = 65x + 65
	int difficulty = sqrt(65 * levelNumber + 65);
	if (difficulty < 1) {
		difficulty = 1;
	}
	else if (difficulty > 100) {
		difficulty = 100;
	}
	return difficulty;
}

int static_enemy_spawn_probability(int difficulty) {
	// y = (1 / ((x + 1) * 0.005)) + 1
	int probability = (int)((1 / ((difficulty + 1) * 0.005)) + 1);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int spear_enemy_spawn_probability(int difficulty) {
	// y = 55
	return 55;
}

int slow_enemy_spawn_probability(int difficulty) {
	// y = (1 / ((x + 1) * 0.005)) + 1
	int probability = (int)((1 / ((difficulty + 1) * 0.005)) + 1);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int shooting_enemy_spawn_probability(int difficulty) {
	// y = sqrt(30 * (x + 1))
	int probability = (int)(sqrt((difficulty + 1) * 30));
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int screaming_enemy_spawn_probability(int difficulty) {
	// y = 0.2 * x + 40
	int probability = (int)(difficulty * 0.2 + 40);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int flying_enemy_spawn_probability(int difficulty) {
	// y = 0.8 * sqrt(30 * (x + 1))
	int probability = (int)(sqrt((difficulty + 1) * 30) * 0.8);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int fast_enemy_spawn_probability(int difficulty) {
	// y = (1 / (0.005 * (difficulty + 1))) + 11
	int probability = (int)((1 / ((difficulty + 1) * 0.005)) + 11);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int chasing_enemy_spawn_probability(int difficulty) {
	// y = 0.5 * x + 10
	int probability = (int)(difficulty * 0.5 + 10);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int life_powerup_spawn_probability(int difficulty) {
	// y = 50
	return 50;
}

int invincibility_powerup_spawn_probability(int difficulty) {
	// y = 1 / (0.005 * (x + 1)) + 13
	int probability = (int)(1 / ((difficulty + 1) * 0.005) + 13);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int invisibility_powerup_spawn_probability(int difficulty) {
	// y = 1 / (0.003 * (x + 1)) + 20
	int probability = (int)(1 / ((difficulty + 1) * 0.003) + 20);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}

int gun_powerup_spawn_probability(int difficulty) {
	return 20;
}

int spear_powerup_spawn_probability(int difficulty) {
	// y = -(1 / (0.001 * (x + 25))) + 50
	int probability = (int)(-(1 / ((difficulty + 25) * 0.001)) + 50);
	if (probability < 1) {
		probability = 1;
	}
	else if (probability > 100) {
		probability = 100;
	}
	return probability;
}


// Player
Position getPlayerDefaultPosition() {
	return Position(1, 1);
}

Position getPlayerFirstLevelPosition() {
	return Position(53, 1);
}


// Default command set
Commands getDefaultCommands() {
	Commands commands;
	commands.upCommand = DEFUALT_COMMAND_UP;
	commands.jumpCommand = DEFUALT_COMMAND_JUMP;
	commands.downCommand = DEFUALT_COMMAND_DOWN;
	commands.leftCommand = DEFUALT_COMMAND_LEFT;
	commands.rightCommand = DEFUALT_COMMAND_RIGHT;
	commands.useCommand = DEFUALT_COMMAND_USE;
	commands.escCommand = DEFUALT_COMMAND_ESC;
	return commands;
}
