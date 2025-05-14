#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include "Node.h"
#include "Utility.h"
#include "Controller.h"

void main_loop(const std::vector<std::shared_ptr<Node>>& nodes, Controller& controller)
{
	while (true)
	{
		// Update nodes. Record if a change has happened
		bool state_change = false;
		for (auto node_ptr : nodes)
		{
			if (node_ptr->update())
				state_change = true;
		}

		// Deadlock happened -> Stop
		if (controller.check_deadlock(nodes))
		{
			std::cout << "Deadlock detected. Exitting main loop...\n";
			break;
		}

		// None of the nodes did anything -> Stop
		if (!state_change)
		{
			std::cout << "Stabilized. Exitting main loop...\n";
			break;
		}
	}
}

int main()
{
	std::string filename = "input1.txt";

	std::cout << "File name with extension: ";
	std::cin >> filename;

	std::pair<std::vector<std::shared_ptr<Node>>, std::shared_ptr<std::vector<int>>> loaded_data;
	try
	{
		loaded_data = load_from_file(filename);
	}
	catch (std::exception ex)
	{
		std::cout << "Exception: " << ex.what() << "\n";
		return 1;
	}

	// Map loaded data to components
	auto [nodes, resources] = loaded_data;

	// Initialize Controller
	Controller controller(resources);

	// Print inputted data
	std::cout << "--- Initial Node State ---\n";
	print_nodes(nodes, &Node::get_clean_string);

	// Enter main loop
	std::cout << "--- Within Main Loop ---\n";
	main_loop(nodes, controller);

	// Print final state
	std::cout << "\n--- Final Node State ---";
	print_nodes(nodes, &Node::get_detailed_string);
}