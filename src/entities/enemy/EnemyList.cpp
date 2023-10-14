#include <iostream>
#include "EnemyList.hpp"
#include "Enemy.hpp"
#include "../../util/Position.hpp"

using namespace std;

EnemyList::EnemyList() {
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
}

int EnemyList::getSize() {
	return size;
}

void EnemyList::add(Enemy *value) {
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

bool EnemyList::contains(Enemy *value) {
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

void EnemyList::remove(Enemy *value) {
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

EnemyList* EnemyList::getEnemiesAt(int x, int y) {
	return getEnemiesAt(Position(x, y));
}

EnemyList* EnemyList::getEnemiesAt(Position position) {
	EnemyList *list = new EnemyList();
	Node *node = first;
	while (node != NULL) {
		if (!node->value->isDead() && node->value->getPosition().equals(position)) {
			list->add(node->value);
		}
		node = node->next;
	}
	return list;
}

Enemy* EnemyList::iter_get() {
	if (current != NULL) {
		return current->value;
	}
	else {
		return NULL;
	}
}

bool EnemyList::iter_hasNext() {
	if (current == NULL) {
		return first != NULL;
	}
	else {
		return current->next != NULL;
	}
}

Enemy* EnemyList::iter_next() {
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

bool EnemyList::iter_hasPrevious() {
	if (current == NULL) {
		return false;
	}
	else {
		return current->prev != NULL;
	}
}

Enemy* EnemyList::iter_previous() {
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

void EnemyList::iter_insert(Enemy *value) {
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

Enemy* EnemyList::iter_remove() {
	if (current != NULL) {
		size--;
		Enemy *value = current->value;
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

void EnemyList::iter_reset() {
	current = NULL;
}
