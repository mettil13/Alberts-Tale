#include <iostream>
#include "LevelList.hpp"
#include "../levels/Level.hpp"

using namespace std;

LevelList::LevelList() {
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
}

int LevelList::getSize() {
	return size;
}

void LevelList::add(Level *value) {
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

bool LevelList::contains(Level *value) {
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

void LevelList::remove(Level *value) {
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

Level* LevelList::iter_get() {
	if (current != NULL) {
		return current->value;
	}
	else {
		return NULL;
	}
}

bool LevelList::iter_hasNext() {
	if (current == NULL) {
		return first != NULL;
	}
	else {
		return current->next != NULL;
	}
}

Level* LevelList::iter_next() {
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

bool LevelList::iter_hasPrevious() {
	if (current == NULL) {
		return false;
	}
	else {
		return current->prev != NULL;
	}
}

Level* LevelList::iter_previous() {
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

void LevelList::iter_insert(Level *value) {
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

Level* LevelList::iter_remove() {
	if (current != NULL) {
		size--;
		Level *value = current->value;
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

void LevelList::iter_reset() {
	current = NULL;
}
