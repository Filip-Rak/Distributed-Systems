#pragma once

#include <memory>

#include "Node.h"

class Resource
{
	/* Attributes */
	bool taken = false;
	std::shared_ptr<Node> parent;

public:
	/* Public Methods */
	Resource(const std::shared_ptr<Node>& parent);

	bool reserve(int requester_id);
};