#include <iostream>
#include "PositionList.hpp"
#include "../../util/Position.hpp"

using namespace std;

PositionList::PositionList() {
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
}

int PositionList::getSize() {
	return size;
}

void PositionList::add(Position *value) {
	Node *node = new Node;
	node->next = NULL;
	node->value = value;
	if (first == NULL) {
		first = node;
		last = node;
	}
	else {
		last->next = node;
		last = node;
	}
	size++;
}

bool PositionList::contains(Position *value) {
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

void PositionList::remove(Position *value) {
	Node *node = first, *prev = NULL;
	bool guard = true;
	while (guard && node != NULL) {
		if (node->value == value) {
			guard = false;
		}
		else {
			prev = node;
			node = node->next;
		}
	}

	if (node != NULL) {
		size--;

		if (current == node) {
			current = prev;
		}

		if (prev != NULL) {
			prev->next = node->next;
		}
		else {
			first = node->next;
		}

		if (node->next == NULL) {
			last = prev;
		}

		delete node;
	}
}

Position* PositionList::iter_get() {
	if (current != NULL) {
		return current->value;
	}
	else {
		return NULL;
	}
}

bool PositionList::iter_hasNext() {
	if (current == NULL) {
		return first != NULL;
	}
	else {
		return current->next != NULL;
	}
}

Position* PositionList::iter_next() {
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

void PositionList::iter_insert(Position *value) {
	Node *node = new Node;
	node->value = value;
	size++;

	if (current == NULL) {
		node->next = first;
		first = node;
	}
	else {
		node->next = current->next;
		current->next = node;
	}
	if (node->next == NULL) {
		last = node;
	}
	iter_next();
}

Position* PositionList::iter_remove() {
	if (current != NULL) {
		size--;
		Position *value = current->value;

		Node *prev;
		if (first != current) {
			prev = first;
			while (prev->next != current) {
				prev = prev->next;
			}

			prev->next = current->next;
		}
		else {
			first = current->next;
			prev = NULL;
		}

		if (current->next == NULL) {
			last = prev;
		}

		delete current;
		current = prev;
		return value;
	}
	else {
		return NULL;
	}
}

void PositionList::iter_reset() {
	current = NULL;
}
