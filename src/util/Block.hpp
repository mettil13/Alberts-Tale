#ifndef BLOCK_HPP
#define BLOCK_HPP
class Block;
#include <windows.h>
#include "Config.hpp"

class Block {
protected:
	char type;
	WORD attributes;
public:
	Block(char type = BLOCK_INVALID, WORD attributes = COLOR_TEXT);
	Block(CHAR_INFO cInfo);
	bool isSolid();
	bool isAir();
	bool isPlatform();
	bool isInvalid();
	char toChar();
	CHAR_INFO toCharInfo();
	bool equalsType(Block block);
	bool equalsAttributes(Block block);
};

#endif /* BLOCK_HPP */
