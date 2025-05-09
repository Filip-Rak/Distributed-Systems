/*
 *  Assignment: Mitchell-Merritt Deadlock Detection Algorithm
 *  Author: Filip Rak
 *
 *  Description:
 *      This program simulates a distributed deadlock detection algorithm using the
 *      Mitchell-Merritt label propagation method. Each node maintains a public and
 *      private label to track causal dependencies created by blocking relationships.
 *      When a node becomes blocked by another, its labels are updated and may propagate
 *      backward through the dependency graph. Deadlock is detected locally by nodes
 *      using label comparisons, with no explicit message passing or central coordinator.
 *
 *  Input:
 *      - Single file name with extension.
 *
 *  Input Format (from file):
 *      Line 1:
 *          <number_of_nodes>
 *              - Total number of nodes in the simulation.
 *
 *      Subsequent lines:
 *          <blocked_node_id> <blocking_node_id>
 *              - Each line indicates that the node on the left becomes blocked by the
 *                node on the right at the next simulation step.
 *              - These lines are processed sequentially (one per time step).
 *
 *	Example Input:
 *		3
 *      0 1     <- At time step 0, Node 0 is blocked by Node 1
 *      1 2     <- At time step 1, Node 1 is blocked by Node 2
 *      2 0     <- At time step 2, Node 2 is blocked by Node 0
 *
 *  Output:
 *      - Initial state of all nodes
 *      - Per-tick log including:
 *          * Blocking events and resulting label changes
 *          * Transmit rule activations (label propagation)
 *          * Deadlock detection (if and when it occurs)
 *      - Final state of all nodes
 */


#include <iostream>
#include <vector>
#include <memory>
#include <queue>

#include "Node.h"
#include "Utility.h"

void main_loop(const std::vector<std::shared_ptr<Node>>& nodes, std::queue<std::pair<int, int>>& nodes_to_block)
{
	int tick = 0;
	while (true)
	{
		std::cout << "\n/*Tick #" << tick++ << "*/\n";

		bool keep_alive = false;

		// Apply a block
		if (!nodes_to_block.empty())
		{
			auto [blocked, blocker] = nodes_to_block.front();
			nodes_to_block.pop();
			
			nodes[blocked]->block_with(nodes[blocker]);
			keep_alive = true;
		}

		// Run through the update
		for (auto node_ptr : nodes)
		{
			if (node_ptr->update())
				keep_alive = true;

			if (node_ptr->detected_deadlock())
			{
				std::cout << "[Main Loop] Deadlock confirmed. Halting...\n";
				return;
			}
		}

		// Stay in loop as long as changes happen
		if (!keep_alive && nodes_to_block.empty())
		{
			std::cout << "[Main Loop] Stabilized. Halting...\n";
			break;
		}
	}
}

int main()
{
	/* Initialize */
	std::pair<int, std::queue<std::pair<int, int>>> loaded_data;

	// Query file name
	std::string filename = "input1.txt";

	// Read file
	try
	{
		loaded_data = load_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 1;
	}

	// Unpack & print loaded data
	auto [num_nodes, block_queue] = loaded_data;

	std::cout << "--- Initialization ---\n";
	print_loaded_data(num_nodes, block_queue);

	// Create nodes
	std::vector<std::shared_ptr<Node>> nodes = create_nodes(num_nodes);

	// Enter main loop
	std::cout << "\n--- Within Main Loop ---";
	main_loop(nodes, block_queue);

	// Print final state
	std::cout << "\n--- Final Node State ---\n";
	print_node_state(nodes);
}