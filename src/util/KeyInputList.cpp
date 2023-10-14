#include <iostream>
#include "KeyInputList.hpp"
#include "Util.hpp"

using namespace std;

KeyInputList::KeyInputList() {
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
}

int KeyInputList::getSize() {
	return size;
}

void KeyInputList::add(Input value) {
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

bool KeyInputList::contains(Input value) {
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

void KeyInputList::remove(Input value) {
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

Input KeyInputList::iter_get() {
	if (current != NULL) {
		return current->value;
	}
	else {
		return NONE;
	}
}

bool KeyInputList::iter_hasNext() {
	if (current == NULL) {
		return first != NULL;
	}
	else {
		return current->next != NULL;
	}
}

Input KeyInputList::iter_next() {
	if (current == NULL) {
		current = first;
	}
	else {
		current = current->next;
	}

	if (current == NULL) {
		return NONE;
	}
	else {
		return current->value;
	}
}

void KeyInputList::iter_insert(Input value) {
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

Input KeyInputList::iter_remove() {
	if (current != NULL) {
		size--;
		Input value = current->value;

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
		return NONE;
	}
}

void KeyInputList::iter_reset() {
	current = NULL;
}
