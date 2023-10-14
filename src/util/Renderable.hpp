#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP
class Renderable;
#include <windows.h>
#include "Position.hpp"

class Renderable {
protected:
	Position pos;
	CHAR_INFO charInfo;
public:
	Renderable(int x, int y, char appearence, WORD attributes);
	Renderable(Position pos, char appearence, WORD attributes);
	Renderable(int x, int y, CHAR_INFO charInfo);
	Renderable(Position pos, CHAR_INFO charInfo);
	int getX();
	int getY();
	Position getPosition();
	CHAR_INFO toCharInfo();
	char toChar();
};

#endif /* RENDERABLE_HPP */
