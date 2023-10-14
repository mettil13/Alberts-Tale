#ifndef POSITION_HPP
#define POSITION_HPP
class Position;

class Position {
protected:
	int x, y;
public:
	Position(int x = 0, int y = 0);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	Position clone();
	bool equals(Position position);
	Position right();
	Position left();
	Position up();
	Position down();
};

#endif /* POSITION_HPP */
