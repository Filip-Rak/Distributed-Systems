#include <iostream>
#include <vector>
#include <memory>

#include "Node.h"
#include "Utils.h"

/*
 * @brief Runs the main loop of the sim.
 * @param nodes: A reference to a shared pointer to a vector of Node.
 */
void main_loop(const std::shared_ptr<std::vector<Node>>& nodes)
{
	while (true)
	{
		// Run the loop as long as there are jobs left
		bool jobs_left = false;
		for (Node node : *nodes)
		{
			// break;
			if (node.has_jobs())
			{
				jobs_left = true;
				break;
			}
		}

		if (!jobs_left) return;

		// Try job
		for (Node& node : *nodes)
			node.try_job();
	}
}

int main()
{
	/* Load the file data */
	std::string input_file = "input.txt";
	std::shared_ptr<std::vector<Node>> nodes;

	try
	{
		nodes = load_nodes(input_file);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 0;
	}

	/* Initial State Print */
	std::cout << "---- Intiial State of All Nodes ---\n";
	print_nodes_state(nodes);
	std::cout << "\n";

	/* Start the sim */
	std::cout << "---- Within the critical section ----\n";
	main_loop(nodes);

	/* Summary */
	std::cout << "\n---- Final State of All Nodes ---\n";
	print_nodes_state(nodes);
}