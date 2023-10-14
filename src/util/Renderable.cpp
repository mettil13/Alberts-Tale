#include <iostream>
#include <windows.h>
#include "Renderable.hpp"
#include "Position.hpp"

using namespace std;

Renderable::Renderable(int x, int y, char appearence, WORD attributes) {
	pos = Position(x, y);
#ifdef UNICODE
	charInfo.Char.UnicodeChar = appearence;
#else
	charInfo.Char.AsciiChar = appearence;
#endif /* UNICODE */
	charInfo.Attributes = attributes;
}

Renderable::Renderable(Position pos, char appearence, WORD attributes) {
	this->pos = pos;
#ifdef UNICODE
	charInfo.Char.UnicodeChar = appearence;
#else
	charInfo.Char.AsciiChar = appearence;
#endif /* UNICODE */
	charInfo.Attributes = attributes;
}

Renderable::Renderable(int x, int y, CHAR_INFO charInfo) {
	pos = Position(x, y);
	this->charInfo = charInfo;
}

Renderable::Renderable(Position pos, CHAR_INFO charInfo) {
	this->pos = pos;
	this->charInfo = charInfo;
}

int Renderable::getX() {
	return pos.getX();
}

int Renderable::getY() {
	return pos.getY();
}

Position Renderable::getPosition() {
	return pos;
}

CHAR_INFO Renderable::toCharInfo() {
	return charInfo;
}

char Renderable::toChar() {
	return charInfo.Char.AsciiChar;
}
