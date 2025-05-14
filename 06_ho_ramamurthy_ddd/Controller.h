#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <stack>
#include <utility>
#include <unordered_set>

#include "Node.h"
#include "Resource.h"

class Controller
{
	/* Attributes */
	std::unordered_map<int, std::vector<int>> graph;
	std::vector<std::shared_ptr<Resource>> resources;

public:
	/* Cosntructor */
	Controller(const std::vector<std::shared_ptr<Resource>>& resources);

	/* Public Methods */
	void update(const std::vector<std::shared_ptr<Node>>& nodes);
	bool detect_cycles();
};