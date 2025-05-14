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

	std::vector<std::shared_ptr<Resource>> shared_resources;
	std::unordered_map<int, int> used_resources_to_holder;

	std::queue<int> proc_required_resources;
	std::vector<int> proc_pending_resources;

public:
	/* Constructor */
	Node(int id, std::queue<int> proc_resources = {});

	/* Public Methods  */
	bool update();
	void use_resource(int res_id, int user_id);

	/* Setters */
	void set_resource_ptr(const std::vector<std::shared_ptr<Resource>>& resources);

	/* Getters */
	std::string get_detailed_string() const;
	std::string get_clean_string() const;
	std::vector<int> get_pending_nodes() const;
	int get_blocker_of_res(int id) const;
	int get_id() const;
};