#include <iostream>
#include "Position.hpp"

using namespace std;

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

void Position::setX(int x) {
	this->x = x;
}

void Position::setY(int y) {
	this->y = y;
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}

Position Position::clone() {
	return Position(x, y);
}

bool Position::equals(Position position) {
	if (position.x == x && position.y == y) {
		return true;
	}
	else {
		return false;
	}
}

Position Position::right() {
	return Position(x + 1, y);
}

Position Position::left() {
	return Position(x - 1, y);
}

Position Position::up() {
	return Position(x, y + 1);
}

Position Position::down() {
	return Position(x, y - 1);
}
