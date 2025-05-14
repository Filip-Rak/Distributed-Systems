#pragma once

#include <memory>

#include "Node.h"

class Node;

class Resource
{
	/* Attributes */
	const int id;

	bool taken = false;
	std::shared_ptr<Node> parent;

public:
	/* Constructor */
	Resource(int id, const std::shared_ptr<Node>& parent);

	/* Public Methods */
	bool reserve(int requester_id);

	/* Getters */
	std::shared_ptr<Node> get_parent();
};