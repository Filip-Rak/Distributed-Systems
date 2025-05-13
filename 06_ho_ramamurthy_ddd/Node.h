#pragma once

#include <vector>
#include <queue>

class Node
{
	/* Types */
	struct Process
	{
		int timestamp;
		std::vector<int> required_resources;
	};

	/* Attributes */
	const int id;
	std::queue<Process> jobs;

};