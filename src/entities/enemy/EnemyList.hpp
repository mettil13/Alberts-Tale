#ifndef ENEMY_LIST_HPP
#define ENEMY_LIST_HPP
class EnemyList;
#include "Enemy.hpp"
#include "../../util/Position.hpp"

class EnemyList {
protected:
	struct Node {
		Enemy *value;
		Node *prev, *next;
	};
	Node *first, *last, *current;
	int size;
public:
	EnemyList();
	int getSize();
	// Postcondition: returns the number of elements inside the list

	void add(Enemy *value);
	// Postcondition: adds value at the end of the list

	bool contains(Enemy *value);
	// Postcondition: returns whether value is inside the list

	void remove(Enemy *value);
	// Postcondition: removes value from the list. If the iterator is currently on the element to be removed, it is moved to the previous element

	EnemyList* getEnemiesAt(int x, int y);
	// Postcondition: returns a list of enemies at the specified x and y. Doesn't return NULL. Dead enemies are ignored

	EnemyList* getEnemiesAt(Position position);
	// Postcondition: returns a list of enemies at position. Doesn't return NULL. Dead enemies are ignored

	Enemy* iter_get();
	// Postcondition: returns the current element or NULL if the iterator is at the start of the list (before the first element)

	bool iter_hasNext();
	// Postcondition: returns whether the iterator can move on the next element

	Enemy* iter_next();
	// Precondition: iter_hasNext() must be true before calling this method
	// Postcondition: moves the iterator on the next element and returns it

	bool iter_hasPrevious();
	// Postcondition: returns whether the iterator can move on the previous element

	Enemy* iter_previous();
	// Precondition: iter_hasPrevious() must be true before calling this method
	// Postcondition: moves the iterator on the previous element and returns it

	void iter_insert(Enemy *value);
	// Postcondition: adds value after the iterator and then moves the iterator on it

	Enemy* iter_remove();
	// Postcondition: removes the current element and moves the iterator on the previous element.
	//                The removed element is then returned. If the iterator was at the start of the list (before the first element), no element is removed and NULL is returned instead.
	//                If there is no previous element, the iterator is set at the start of the list (before the first element)

	void iter_reset();
	// Postcondition: resets the iterator at the start of the list (before the first element)
};

#endif /* ENEMY_LIST_HPP */