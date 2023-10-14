#ifndef LEVEL_LIST_HPP
#define LEVEL_LIST_HPP
class LevelList;
#include "../levels/Level.hpp"

class LevelList {
protected:
	struct Node {
		Level *value;
		Node *prev, *next;
	};
	Node *first, *last, *current;
	int size;
public:
	LevelList();
	int getSize();
	// Postcondition: returns the number of elements inside the list

	void add(Level *value);
	// Postcondition: adds value at the end of the list

	bool contains(Level *value);
	// Postcondition: returns whether value is inside the list

	void remove(Level *value);
	// Postcondition: removes value from the list. If the iterator is currently on the element to be removed, it is moved to the previous element

	Level* iter_get();
	// Postcondition: returns the current element or NULL if the iterator is at the start of the list (before the first element)

	bool iter_hasNext();
	// Postcondition: returns whether the iterator can move on the next element

	Level* iter_next();
	// Precondition: iter_hasNext() must be true before calling this method
	// Postcondition: moves the iterator on the next element and returns it

	bool iter_hasPrevious();
	// Postcondition: returns whether the iterator can move on the previous element

	Level* iter_previous();
	// Precondition: iter_hasPrevious() must be true before calling this method
	// Postcondition: moves the iterator on the previous element and returns it

	void iter_insert(Level *value);
	// Postcondition: adds value after the iterator and then moves the iterator on it

	Level* iter_remove();
	// Postcondition: removes the current element and moves the iterator on the previous element.
	//                The removed element is then returned. If the iterator was at the start of the list (before the first element), no element is removed and NULL is returned instead.
	//                If there is no previous element, the iterator is set at the start of the list (before the first element)

	void iter_reset();
	// Postcondition: resets the iterator at the start of the list (before the first element)
};

#endif /* LEVEL_LIST_HPP */
