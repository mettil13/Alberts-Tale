#include <iostream>
#include "PowerupList.hpp"
#include "Powerup.hpp"
#include "../util/Position.hpp"

using namespace std;

PowerupList::PowerupList() {
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
}

int PowerupList::getSize() {
	return size;
}

void PowerupList::add(Powerup *value) {
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

bool PowerupList::contains(Powerup *value) {
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

void PowerupList::remove(Powerup *value) {
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

PowerupList* PowerupList::getPowerupsAt(int x, int y) {
	return getPowerupsAt(Position(x, y));
}

PowerupList* PowerupList::getPowerupsAt(Position position) {
	PowerupList *list = new PowerupList();
	Node *node = first;
	while (node != NULL) {
		if (!node->value->isConsumed() && node->value->getPosition().equals(position)) {
			list->add(node->value);
		}
		node = node->next;
	}
	return list;
}

Powerup* PowerupList::iter_get() {
	if (current != NULL) {
		return current->value;
	}
	else {
		return NULL;
	}
}

bool PowerupList::iter_hasNext() {
	if (current == NULL) {
		return first != NULL;
	}
	else {
		return current->next != NULL;
	}
}

Powerup* PowerupList::iter_next() {
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

bool PowerupList::iter_hasPrevious() {
	if (current == NULL) {
		return false;
	}
	else {
		return current->prev != NULL;
	}
}

Powerup* PowerupList::iter_previous() {
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

void PowerupList::iter_insert(Powerup *value) {
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

Powerup* PowerupList::iter_remove() {
	if (current != NULL) {
		size--;
		Powerup *value = current->value;
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

void PowerupList::iter_reset() {
	current = NULL;
}
