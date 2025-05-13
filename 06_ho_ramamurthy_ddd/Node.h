#pragma once

#include <vector>
#include <queue>
#include <memory>

#include "Resource.h"

class Node
{
	/* Attributes */
	const int id;

	std::vector<std::shared_ptr<Resource>> shared_resources;

	int process_timestamp;
	std::vector<int> proc_required_resources;
	std::vector<int> proc_held_resources;

public:
	/* Constructor */
	Node(int id, int proc_timestamp, std::vector<int> proc_resources);

	/* Public Methods  */
	bool process(int iteration);

private:
	/* Private Methods */
	void attempt_reserving_resources();
};