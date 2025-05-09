#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <fstream>
#include <fstream>
#include <string>

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