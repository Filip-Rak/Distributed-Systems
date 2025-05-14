#pragma once

#include <memory>

#include "Node.h"

class Node;

class Resource
{
	/* Attributes */
	const int id;

	bool taken = false;
	int taker_id = -1;

public:
	/* Constructor */
	Resource(int id);

	/* Public Methods */
	bool reserve(int requester_id);

	/* Getters */
	int get_taker_id();
};