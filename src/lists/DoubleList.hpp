#ifndef DOUBLE_LIST_HPP
#define DOUBLE_LIST_HPP
class DoubleList;

// WARNING:
// NEVER create an instance of this class! This is only a blueprint for a double linked list class

// Remove the following typedef and rename every OBJECT with the actual type of the list
typedef int OBJECT;

class DoubleList {
protected:
	struct Node {
		OBJECT *value;
		Node *prev, *next;
	};
	Node *first, *last, *current;
	int size;
public:
	DoubleList();
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

	bool iter_hasPrevious();
	// Postcondition: returns whether the iterator can move on the previous element

	OBJECT* iter_previous();
	// Precondition: iter_hasPrevious() must be true before calling this method
	// Postcondition: moves the iterator on the previous element and returns it

	void iter_insert(OBJECT *value);
	// Postcondition: adds value after the iterator and then moves the iterator on it

	OBJECT* iter_remove();
	// Postcondition: removes the current element and moves the iterator on the previous element.
    //                The removed element is then returned. If the iterator was at the start of the list (before the first element), no element is removed and NULL is returned instead.
    //                If there is no previous element, the iterator is set at the start of the list (before the first element)

	void iter_reset();
	// Postcondition: resets the iterator at the start of the list (before the first element)
};

#endif /* DOUBLE_LIST_HPP */
