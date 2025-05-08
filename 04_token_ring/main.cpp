#include <iostream>
#include <memory>
#include <vector>

#include "Node.h"
#include "Utility.h"

void main_loop(std::vector<std::shared_ptr<Node>>& nodes)
{
	int iteration = 0;
	while (true)
	{
		bool jobs_left = false;
		for (auto node_ptr : nodes)
		{
			if (node_ptr->has_jobs())
			{
				jobs_left = true;
				break;
			}
		}

		if (!jobs_left)
		{
			std::cout << "No jobs left. Exiting main loop...\n";
			break;
		}

		for (auto node_ptr : nodes)
			node_ptr->process(iteration);

		iteration += 1;
	}
}

int main()
{
	std::string filename = "input1.txt";
	std::vector<std::shared_ptr<Node>> nodes;

	try
	{
		nodes = load_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cerr << "Exception: " << ex.what() << "\n";
		return 1;
	}

	// Print the state of the nodes
	std::cout << "--- Initial Node State ---\n";
	print_nodes(nodes);

	std::cout << "Ring order: ";
	for (int i = 0; i < nodes.size(); i++)
		std::cout << "<- " << i << " ";

	std::cout << "<-\n\n";

	// Run main loop
	std::cout << "--- Within Main Loop ---\n";
	main_loop(nodes);

	// Print the final state
	std::cout << "\n--- Final Node State ---\n";
	print_nodes(nodes);
}