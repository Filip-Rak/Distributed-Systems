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
	std::shared_ptr<std::vector<int>> resources;	// Integer represents the holder. -1 for free

public:
	/* Cosntructor */
	Controller(const std::shared_ptr<std::vector<int>>& resources);

	/* Public Methods */
	bool check_deadlock(const std::vector<std::shared_ptr<Node>>& nodes);

private:
	/* Private Methods */
	void rebuild_graph(const std::vector<std::shared_ptr<Node>>& nodes);
	void print_graph();
	bool detect_cycles();
};