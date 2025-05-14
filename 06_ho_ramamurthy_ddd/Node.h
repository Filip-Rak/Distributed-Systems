#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include <string>
#include <sstream>
#include <iostream>

#include "Resource.h"

class Resource;

class Node
{	
	/* Attributes */
	const int id;

	std::shared_ptr<std::vector<int>> shared_resources;

	std::queue<int> proc_required_resources;
	std::vector<int> proc_pending_resources;

public:
	/* Constructor */
	Node(int id, std::queue<int> proc_resources = {});

	/* Public Methods  */
	bool update();

	/* Setters */
	void set_resource_ptr(const std::shared_ptr<std::vector<int>>& resources);

	/* Getters */
	std::string get_detailed_string() const;
	std::string get_clean_string() const;
	std::vector<int> get_pending_nodes() const;
	int get_id() const;
};