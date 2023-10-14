#include <iostream>
#include "DoubleList.hpp"

using namespace std;

DoubleList::DoubleList() {
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
}

int DoubleList::getSize() {
	return size;
}

void DoubleList::add(OBJECT *value) {
	Node *node = new Node;
	node->next = NULL;
	node->value = value;
	if (first == NULL) {
		node->prev = NULL;
		first = node;
		last = node;
	}
	else {
		node->prev = last;
		last->next = node;
		last = node;
	}
	size++;
}

bool DoubleList::contains(OBJECT *value) {
	Node *node = first;
	bool found = false;
	while (!found && node != NULL) {
		if (node->value == value) {
			found = true;
		}
		else {
			node = node->next;
		}
	}
	return found;
}

void DoubleList::remove(OBJECT *value) {
	Node *node = first;
	bool guard = true;
	while (guard && node != NULL) {
		if (node->value == value) {
			guard = false;
		}
		else {
			node = node->next;
		}
	}
	if (node != NULL) {
		size--;

		if (current == node) {
			current = node->prev;
		}

		if (node->prev != NULL) {
			node->prev->next = node->next;
		}
		else {
			first = node->next;
		}

		if (node->next != NULL) {
			node->next->prev = node->prev;
		}
		else {
			last = node->prev;
		}
		delete node;
	}
}

OBJECT* DoubleList::iter_get() {
	if (current != NULL) {
		return current->value;
	}
	else {
		return NULL;
	}
}

bool DoubleList::iter_hasNext() {
	if (current == NULL) {
		return first != NULL;
	}
	else {
		return current->next != NULL;
	}
}

OBJECT* DoubleList::iter_next() {
	if (current == NULL) {
		current = first;
	}
	else {
		current = current->next;
	}

	if (current == NULL) {
		return NULL;
	}
	else {
		return current->value;
	}
}

bool DoubleList::iter_hasPrevious() {
	if (current == NULL) {
		return false;
	}
	else {
		return current->prev != NULL;
	}
}

OBJECT* DoubleList::iter_previous() {
	if (current != NULL) {
		current = current->prev;
	}

	if (current == NULL) {
		return NULL;
	}
	else {
		return current->value;
	}
}

void DoubleList::iter_insert(OBJECT *value) {
	Node *node = new Node;
	node->value = value;
	size++;

	if (current == NULL) {
		node->prev = NULL;
		node->next = first;
		if (first != NULL) {
			first->prev = node;
		}
		first = node;
		if (last == NULL) {
			last = node;
		}
	}
	else {
		node->prev = current;
		node->next = current->next;
		if (current->next != NULL) {
			current->next->prev = node;
		}
		else {
			last = node;
		}
		current->next = node;
	}
	iter_next();
}

OBJECT* DoubleList::iter_remove() {
	if (current != NULL) {
		size--;
		OBJECT *value = current->value;
		Node *n;
		if (current->prev != NULL) {
			current->prev->next = current->next;
			n = current->prev;
		}
		else {
			first = current->next;
			n = NULL;
		}
		if (current->next != NULL) {
			current->next->prev = current->prev;
		}
		else {
			last = current->prev;
		}
		delete current;
		current = n;
		return value;
	}
	else {
		return NULL;
	}
}

void DoubleList::iter_reset() {
	current = NULL;
}
