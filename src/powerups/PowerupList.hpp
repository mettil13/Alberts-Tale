#ifndef POWERUP_LIST_HPP
#define POWERUP_LIST_HPP
class PowerupList;
#include "Powerup.hpp"
#include "../util/Position.hpp"

class PowerupList {
protected:
	struct Node {
		Powerup *value;
		Node *prev, *next;
	};
	Node *first, *last, *current;
	int size;
public:
	PowerupList();
	int getSize();
	// Postcondition: returns the number of elements inside the list

	void add(Powerup *value);
	// Postcondition: adds value at the end of the list

	bool contains(Powerup *value);
	// Postcondition: returns whether value is inside the list

	void remove(Powerup *value);
	// Postcondition: removes value from the list. If the iterator is currently on the element to be removed, it is moved to the previous element

	PowerupList* getPowerupsAt(int x, int y);
	// Postcondition: returns a list of powerups at the specified x and y. Doesn't return NULL. Ignores consumed powerups

	PowerupList* getPowerupsAt(Position position);
	// Postcondition: returns a list of powerups at position. Doesn't return NULL. Ignores consumed powerups

	Powerup* iter_get();
	// Postcondition: returns the current element or NULL if the iterator is at the start of the list (before the first element)

	bool iter_hasNext();
	// Postcondition: returns whether the iterator can move on the next element

	Powerup* iter_next();
	// Precondition: iter_hasNext() must be true before calling this method
	// Postcondition: moves the iterator on the next element and returns it

	bool iter_hasPrevious();
	// Postcondition: returns whether the iterator can move on the previous element

	Powerup* iter_previous();
	// Precondition: iter_hasPrevious() must be true before calling this method
	// Postcondition: moves the iterator on the previous element and returns it

	void iter_insert(Powerup *value);
	// Postcondition: adds value after the iterator and then moves the iterator on it

	Powerup* iter_remove();
	// Postcondition: removes the current element and moves the iterator on the previous element.
	//                The removed element is then returned. If the iterator was at the start of the list (before the first element), no element is removed and NULL is returned instead.
	//                If there is no previous element, the iterator is set at the start of the list (before the first element)

	void iter_reset();
	// Postcondition: resets the iterator at the start of the list (before the first element)
};

#endif /* POWERUP_LIST_HPP */
