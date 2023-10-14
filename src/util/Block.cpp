#include <iostream>
#include <windows.h>
#include "Block.hpp"
#include "Config.hpp"

using namespace std;

Block::Block(char type, WORD attributes) {
	this->type = type;
	this->attributes = attributes;
}

Block::Block(CHAR_INFO cInfo) {
#ifdef UNICODE
	type = (char)cInfo.Char.UnicodeChar;
#else
	type = (char)cInfo.Char.AsciiChar;
#endif /* UNICODE */
	attributes = cInfo.Attributes;
}

bool Block::isSolid() {
	char c = toChar();
	return c == BLOCK_PLATFORM || c == BLOCK_BORDER || c == BLOCK_NEXT_PORTAL || c == BLOCK_PREV_PORTAL;
}

bool Block::isAir() {
	char c = toChar();
	return c == BLOCK_AIR;
}

bool Block::isPlatform() {
	char c = toChar();
	return c == BLOCK_PLATFORM;
}

bool Block::isInvalid() {
	char c = toChar();
	return c == BLOCK_INVALID;
}

char Block::toChar() {
	return type;
}

CHAR_INFO Block::toCharInfo() {
	CHAR_INFO c;
#ifdef UNICODE
	c.Char.UnicodeChar = (WCHAR)type;
#else
	c.Char.AsciiChar = (CHAR)type;
#endif /* UNICODE */
	c.Attributes = attributes;
	return c;
}

bool Block::equalsType(Block block) {
	if (type == block.toChar()) {
		return true;
	}
	else {
		return false;
	}
}

bool Block::equalsAttributes(Block block) {
	if (attributes == block.toCharInfo().Attributes) {
		return true;
	}
	else {
		return false;
	}
}
