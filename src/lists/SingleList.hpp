#ifndef SINGLE_LIST_HPP
#define SINGLE_LIST_HPP
class SingleList;

// WARNING:
// NEVER create an instance of this class! This is only a blueprint for a list class

// Remove the following typedef and rename every OBJECT with the actual type of the list
typedef int OBJECT;

class SingleList {
protected:
	struct Node {
		OBJECT *value;
		Node *next;
	};
	Node *first, *last, *current;
	int size;
public:
	SingleList();
	int getSize();
	// Postcondition: returns the number of elements inside the list

	void add(OBJECT *value);
	// Postcondition: adds value at the end of the list

	bool contains(OBJECT *value);
	// Postcondition: returns whether value is inside the list

	void remove(OBJECT *value);
	// Postcondition: removes value from the list. If the iterator is currently on the element to be removed, it is moved to the previous element

	OBJECT* iter_get();
	// Postcondition: returns the current element or NULL if the iterator is at the start of the list (before the first element)

	bool iter_hasNext();
	// Postcondition: returns whether the iterator can move on the next element

	OBJECT* iter_next();
	// Precondition: iter_hasNext() must be true before calling this method
	// Postcondition: moves the iterator on the next element and returns it

	void iter_insert(OBJECT *value);
	// Postcondition: adds value after the iterator and then moves the iterator on it

	OBJECT* iter_remove();
	// Postcondition: removes the current element and moves the iterator on the previous element.
	//                The removed element is then returned. If the iterator was at the start of the list (before the first element), no element is removed and NULL is returned instead.
	//                If there is no previous element, the iterator is set at the start of the list (before the first element)

	void iter_reset();
	// Postcondition: resets the iterator at the start of the list (before the first element)
};

#endif /* SINGLE_LIST_HPP */
