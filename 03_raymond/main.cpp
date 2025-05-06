#include <iostream>
#include <memory>
#include <vector>

#include "Node.h"
#include "Utils.h"

void main_loop(std::vector<std::shared_ptr<Node>>& nodes)
{
	int iteration = 0;
	while (true)
	{
		// Check if there are jobs left
		bool jobs_left = false;
		for (auto node_ptr : nodes)
		{
			if (node_ptr->has_jobs())
			{
				jobs_left = true;
				break;
			}
		}

		// Exit if no job
		if (!jobs_left) 
			break;

		// Process each node
		for (auto node_ptr : nodes)
			node_ptr->process(iteration);

		iteration += 1;
	}

	std::cout << "No jobs left. Exitting main loop...\n";
}

int main()
{
	std::vector<std::shared_ptr<Node>> nodes;
	std::string filename = "input.txt";

	try
	{
		nodes = load_nodes_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 0;
	}

	// Print initial state of the nodes
	std::cout << "-- Nodes on initialization --\n";
	print_node_info(nodes);

	// Start the main loop
	main_loop(nodes);

	// Print the final state of the nodes
	std::cout << "-- Nodes after exit --\n";
	print_node_info(nodes);
}