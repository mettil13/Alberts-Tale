#include <iostream>
#include "RenderableList.hpp"
#include "Renderable.hpp"

using namespace std;

RenderableList::RenderableList() {
	first = NULL;
	last = NULL;
	current = NULL;
	size = 0;
}

int RenderableList::getSize() {
	return size;
}

void RenderableList::add(Renderable *value) {
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

bool RenderableList::contains(Renderable *value) {
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

void RenderableList::remove(Renderable *value) {
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

Renderable* RenderableList::iter_get() {
	if (current != NULL) {
		return current->value;
	}
	else {
		return NULL;
	}
}

bool RenderableList::iter_hasNext() {
	if (current == NULL) {
		return first != NULL;
	}
	else {
		return current->next != NULL;
	}
}

Renderable* RenderableList::iter_next() {
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

void RenderableList::iter_insert(Renderable *value) {
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

Renderable* RenderableList::iter_remove() {
	if (current != NULL) {
		size--;
		Renderable *value = current->value;

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

void RenderableList::iter_reset() {
	current = NULL;
}
