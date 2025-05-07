/*
 *	Assignment: Ricart-Agrawala’s Symmetric Algorithm
 *	Author: Filip Rak
 * 
 *	Description:
 *		The program simulates nodes competing for acces to the Critical Section  
 *		using the Ricart-Agrawala’s Symmetric Algorithm.
 *
 *	Input format
 *		- Name of the file followed by it's extension.
 * 
 *	Example: input1.txt
 * 
 *	Example file format:
 *	Line 1:
 *		<number_of_nodes>
 *			e.g., "3" → means nodes with IDs 0, 1, and 2 will be simulated.
 *
 *	Subsequent lines:
 *		<process_id> <timestamp_1> <timestamp_2> ...
 *		- Each line defines one or more jobs for a given process.
 *		- The first number is the process ID (0-based).
 *		- The following numbers are timestamps at which that process wants to enter the critical section.
 *		- A process ID can appear on multiple lines — jobs will be merged.
 *		- Timestamps for each process will be sorted internally. The order of input is irrelevant.
 *
 *	Example:
 *		3
 *		0 1 2 3     // Node 0 wants to enter CS at logical times 1, 2, and 3
 *		2 3         // Node 2 has a job at logical time 3
 *		2 6 4       // Node 2 also has jobs at time 4 and 6
 *		1 0         // Node 1 has a job at time 0
 *
 *	Output:
 *		- Initial state of loaded nodes prior to simulation.
 *		- Critical Section entries.
 *		- Final state of the nodes once all jobs have been completed.
 */

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

		if (!jobs_left)
		{
			std::cout << "No jobs left. Exiting the main loop...\n";
			return;
		}

		// Go through each node and check if it's time for another request
		for (Node& node : *nodes)
			node.try_job();
	}
}

int main()
{
	/* Load the file data */
	std::string input_file = "input1.txt";

	std::cout << "Input file with extension: ";
	std::cin >> input_file;

	std::shared_ptr<std::vector<Node>> nodes;

	try
	{
		nodes = load_nodes(input_file);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception -> " << ex.what() << "\n";
		return 1;
	}

	/* Initial State Print */
	std::cout << "/* Initial state of all nodes */\n";
	print_nodes_state(nodes);
	std::cout << "\n";

	/* Start the sim */
	std::cout << "/* Within the main loop */\n";
	main_loop(nodes);

	/* Summary */
	std::cout << "\n/* Final state of all nodes */\n";
	print_nodes_state(nodes);
}