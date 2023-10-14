#ifndef POSITION_LIST_HPP
#define POSITION_LIST_HPP
class PositionList;
#include "../../util/Position.hpp"

class PositionList {
protected:
	struct Node {
		Position *value;
		Node *next;
	};
	Node *first, *last, *current;
	int size;
public:
	PositionList();
	int getSize();
	// Postcondition: returns the number of elements inside the list

	void add(Position *value);
	// Postcondition: adds value at the end of the list

	bool contains(Position *value);
	// Postcondition: returns whether value is inside the list

	void remove(Position *value);
	// Postcondition: removes value from the list. If the iterator is currently on the element to be removed, it is moved to the previous element

	Position* iter_get();
	// Postcondition: returns the current element or NULL if the iterator is at the start of the list (before the first element)

	bool iter_hasNext();
	// Postcondition: returns whether the iterator can move on the next element

	Position* iter_next();
	// Precondition: iter_hasNext() must be true before calling this method
	// Postcondition: moves the iterator on the next element and returns it

	void iter_insert(Position *value);
	// Postcondition: adds value after the iterator and then moves the iterator on it

	Position* iter_remove();
	// Postcondition: removes the current element and moves the iterator on the previous element.
	//                The removed element is then returned. If the iterator was at the start of the list (before the first element), no element is removed and NULL is returned instead.
	//                If there is no previous element, the iterator is set at the start of the list (before the first element)

	void iter_reset();
	// Postcondition: resets the iterator at the start of the list (before the first element)
};

#endif /* POSITION_LIST_HPP */
