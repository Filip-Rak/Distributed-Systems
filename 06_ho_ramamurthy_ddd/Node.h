#pragma once

#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>

#include "Resource.h"

class Node
{	
	/* Attributes */
	const int id;

	std::vector<std::shared_ptr<Resource>> shared_resources;

	std::unordered_map<int, int> used_resources_to_holder;

	int proc_time_entry;
	std::vector<int> proc_required_resources;
	std::vector<int> proc_held_resources;

public:
	/* Constructor */
	Node(int id, int proc_timestamp, std::vector<int> proc_resources);

	/* Public Methods  */
	bool process(int iteration);

	/* Setters */
	void use_resource(int res_id, int user_id);

private:
	/* Private Methods */
	void try_reserve_resource();
};